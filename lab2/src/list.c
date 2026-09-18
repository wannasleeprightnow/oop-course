#include "list.h"

#include <stdlib.h>

void Add(List* list, Item* item) {
  if (list == NULL || item == NULL) {
    return;
  }

  if (list->head == NULL) {
    list->head = item;
    list->tail = item;

    item->prev = NULL;
    item->next = NULL;
  } else {
    item->prev = list->tail;
    item->next = NULL;

    list->tail->next = item;
    list->tail = item;
  }
}

Item* GetItem(const List* list, int item_index) {
  if (list == NULL || item_index < 0) {
    return NULL;
  }

  Item* current = list->head;
  int current_index = 0;

  while (current != NULL) {
    if (current_index == item_index) {
      return current;
    }

    current = current->next;
    current_index++;
  }

  return NULL;
}

void Delete(List* list, int item_index) {
  Item* item = Remove(list, item_index);

  free(item);
}

Item* Remove(List* list, int item_index) {
  Item* current = GetItem(list, item_index);

  if (current == NULL) {
    return NULL;
  }

  if (current->prev != NULL) {
    current->prev->next = current->next;
  } else {
    list->head = current->next;
  }

  if (current->next != NULL) {
    current->next->prev = current->prev;
  } else {
    list->tail = current->prev;
  }

  current->prev = NULL;
  current->next = NULL;

  return current;
}

void Insert(List* list, int item_index, Item* item) {
  if (list == NULL || item == NULL || item_index < 0) {
    return;
  }

  Item* current = GetItem(list, item_index);

  if (current == NULL) {
    Add(list, item);
    return;
  }

  if (current == list->head) {
    item->prev = NULL;
    item->next = list->head;

    list->head->prev = item;
    list->head = item;

    return;
  }

  item->prev = current->prev;
  item->next = current;

  current->prev->next = item;
  current->prev = item;
}

int Count(const List* list) {
  if (list == NULL) {
    return 0;
  }

  Item* current = list->head;
  int counter = 0;

  while (current != NULL) {
    current = current->next;
    counter++;
  }

  return counter;
}

void Clear(List* list) {
  if (list == NULL) {
    return;
  }

  Item* current = list->head;

  while (current != NULL) {
    Item* next = current->next;

    free(current);

    current = next;
  }

  list->head = NULL;
  list->tail = NULL;
}

int GetIndex(const List* list, const Item* item) {
  if (list == NULL || item == NULL) {
    return -1;
  }

  Item* current = list->head;
  int current_index = 0;

  while (current != NULL) {
    if (current == item) {
      return current_index;
    }

    current = current->next;
    current_index++;
  }

  return -1;
}