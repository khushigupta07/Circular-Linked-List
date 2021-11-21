#include "circular-linked-list.hpp"

CircularLinkedList::CircularLinkedList():
    head_(nullptr), tail_(nullptr), node_order_(Order::kASC){};

CircularLinkedList::CircularLinkedList(const CircularLinkedList& source) {
  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {  // source size = 0
    head_ = tail_ = nullptr;
  } else if (source.head_ == source.tail_) {  // source size = 1
    head_ = tail_ = new Node(source.head_->data);
  } else {                                 // source size > 1
    head_ = new Node(source.head_->data);  // init head
    Node* curr_node = head_;               // node being initialized
    Node* next_node = source.head_->next;  // iterator through source
    while (next_node != source.head_) {
      curr_node->next = new Node(next_node->data);
      next_node = next_node->next;
      curr_node = curr_node->next;
    }
    tail_ = curr_node;
    tail_->next = head_;
  }
};

CircularLinkedList& CircularLinkedList::operator=(
    const CircularLinkedList& source) {
  if (this == &source) return *this;
  Clear();
  head_ = tail_ = nullptr;
  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {  // source size = 0
    head_ = tail_ = nullptr;
  } else if (source.head_ == source.tail_) {  // source size = 1
    head_ = tail_ = new Node(source.head_->data);
  } else {                                 // source size > 1
    head_ = new Node(source.head_->data);  // init head
    Node* curr_node = head_;               // node being initialized
    Node* next_node = source.head_->next;  // iterator through source
    while (next_node != source.head_) {
      curr_node->next = new Node(next_node->data);
      next_node = next_node->next;
      curr_node = curr_node->next;
    }
    tail_ = curr_node;
    tail_->next = head_;
  }
  return *this;
}

void CircularLinkedList::InsertInOrder(int data) {
  Node* new_node = new Node(data);
  if (head_ == nullptr) {  // empty list
    head_ = tail_ = new_node;
  } else if (head_ == tail_) {  // list size 1
    if (data <= head_->data &&
        node_order_ == Order::kASC) {  // ascending if data <= head
      head_->next = new_node;
      new_node->next = head_;
      head_ = new_node;
    } else if (node_order_ == Order::kASC) {  // ascending if data > head
      head_->next = new_node;
      new_node->next = head_;
      tail_ = new_node;
    } else if (data >= head_->data &&
               node_order_ == Order::kDESC) {  // descending if data >= head
      head_->next = new_node;
      new_node->next = head_;
      head_ = new_node;
    } else {  // descending if data < head
      head_->next = new_node;
      new_node->next = head_;
      tail_ = new_node;
    }
  } else {  // list size > 1
    Node* curr_node = head_;
    Node* next_node = head_->next;
    switch (node_order_) {
    case Order::kASC:
      if (data <= curr_node->data) {  // inserted as head_
        tail_->next = new_node;
        new_node->next = head_;
        head_ = new_node;
        break;
      }
      while ((next_node != head_) && (data > curr_node->data)) {
        if (data < next_node->data) {
          break;
        }
        curr_node = next_node;
        next_node = next_node->next;
      }
      curr_node->next = new_node;
      new_node->next = next_node;
      if (next_node == head_) {
        tail_ = new_node;
      }
      break;
    case Order::kDESC:
      if (data >= curr_node->data) {  // inserted as head_
        tail_->next = new_node;
        new_node->next = head_;
        head_ = new_node;
        break;
      }
      while ((next_node != head_) && (data < curr_node->data)) {
        if (data > next_node->data) {
          break;
        }
        curr_node = next_node;
        next_node = next_node->next;
      }
      curr_node->next = new_node;
      new_node->next = next_node;
      if (next_node == head_) {
        tail_ = new_node;
      }
      break;
    }
  }
}

CircularLinkedList::~CircularLinkedList() { Clear(); }

void CircularLinkedList::Reverse() {
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else if (node_order_ == Order::kDESC) {
    node_order_ = Order::kASC;
  }
  if (head_ == nullptr) return;
  Node* prev_node = nullptr;
  Node* curr_node = head_;
  Node* next_node = nullptr;
  do {
    next_node = curr_node->next;
    curr_node->next = prev_node;
    prev_node = curr_node;
    curr_node = next_node;
  } while (curr_node != head_);
  head_->next = prev_node;
  tail_ = head_;
  head_ = prev_node;
}

void CircularLinkedList::Clear() {
  Node* curr_node = head_;
  while (curr_node != nullptr) {
    if (curr_node == tail_) {
      delete tail_;
      break;
    }
    Node* next = curr_node->next;
    delete curr_node;
    curr_node = next;
  }
}

std::ostream& operator<<(std::ostream& os, const CircularLinkedList& cll) {
  os << cll.head_->data << ' ' << cll.tail_->data;
  return os;
}