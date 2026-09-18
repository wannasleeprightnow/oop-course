#ifndef LIST_H
#define LIST_H

typedef struct Item {
  struct Item* prev;
  struct Item* next;
} Item;

typedef struct List {
  Item* head;
  Item* tail;
} List;

void Add(List* list, Item* item);
void Delete(List* list, int item_index);
Item* GetItem(const List* list, int item_index);
Item* Remove(List* list, int item_index);
void Insert(List* list, int item_index, Item* item);
int Count(const List* list);
void Clear(List* list);
int GetIndex(const List* list, const Item* item);

#endif