// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Item {
    T data;
    Item* next;
    explicit Item(const T& value) : data(value), next(nullptr) {}
  };
  Item* head;

 public:
  TPQueue() : head(nullptr) {}
  ~TPQueue() {
    clear();
  }
  TPQueue(const TPQueue&) = delete;
  TPQueue& operator=(const TPQueue&) = delete;
  bool empty() const {
    return head == nullptr;
  }
  void clear() {
    while (head != nullptr) {
      Item* temp = head;
      head = head->next;
      delete temp;
    }
  }
  void push(const T& value) {
    Item* nnItem = new Item(value);
    if (head == nullptr) {
      head = nnItem;
      return;
    }
    if (value.prior > head->data.prior) {
      nnItem->next = head;
      head = nnItem;
      return;
    }
    Item* current = head;
    while (current->next != nullptr &&
        current->next->data.prior >= value.prior) {
      current = current->next;
    }
    nnItem->next = current->next;
    current->next = nnItem;
  }
  T pop() {
    if (head == nullptr) {
      throw std::out_of_range("TPQueue is empty");
    }
    Item* temp = head;
    T result = head->data;
    head = head->next;
    delete temp;
    return result;
  }
};
struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
