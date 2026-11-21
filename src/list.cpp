#include "list.h"

Item::Item() : prev(nullptr), next(nullptr), owner(nullptr) {}

Item::~Item() {
  if (owner != nullptr) {
    owner->Remove(owner->GetIndex(this));
  }
}

Item* Item::Prev() const { return prev; }

Item* Item::Next() const { return next; }

List::List() : head(nullptr), tail(nullptr) {}

List::~List() { Clear(); }

Item* List::Head() const { return head; }

Item* List::Tail() const { return tail; }

void List::Add(Item* item) {
  if (item == nullptr || item->owner != nullptr) {
    return;
  }

  item->prev = tail;
  item->next = nullptr;
  item->owner = this;

  if (tail != nullptr) {
    tail->next = item;
  } else {
    head = item;
  }
  tail = item;
}

Item* List::GetItem(int item_index) const {
  if (item_index < 0) {
    return nullptr;
  }

  Item* current = head;
  int current_index = 0;
  while (current != nullptr) {
    if (current_index == item_index) {
      return current;
    }
    current = current->next;
    current_index++;
  }
  return nullptr;
}

void List::Delete(int item_index) { delete Remove(item_index); }

Item* List::Remove(int item_index) {
  Item* current = GetItem(item_index);
  if (current == nullptr) {
    return nullptr;
  }

  if (current->prev != nullptr) {
    current->prev->next = current->next;
  } else {
    head = current->next;
  }

  if (current->next != nullptr) {
    current->next->prev = current->prev;
  } else {
    tail = current->prev;
  }

  current->prev = nullptr;
  current->next = nullptr;
  current->owner = nullptr;
  return current;
}

void List::Insert(int item_index, Item* item) {
  if (item == nullptr || item->owner != nullptr) {
    return;
  }

  Item* current = GetItem(item_index);
  if (current == nullptr) {
    Add(item);
    return;
  }

  item->prev = current->prev;
  item->next = current;
  item->owner = this;

  if (current->prev != nullptr) {
    current->prev->next = item;
  } else {
    head = item;
  }
  current->prev = item;
}

int List::Count() const {
  int counter = 0;
  for (Item* current = head; current != nullptr; current = current->next) {
    counter++;
  }
  return counter;
}

void List::Clear() {
  while (head != nullptr) {
    delete head;
  }
}

int List::GetIndex(const Item* item) const {
  int current_index = 0;
  for (Item* current = head; current != nullptr; current = current->next) {
    if (current == item) {
      return current_index;
    }
    current_index++;
  }
  return -1;
}
