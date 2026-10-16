#ifndef SUBJ_H
#define SUBJ_H

#include "list.h"

typedef enum ItemType {
  IT_NONE,
  IT_INTERNET,
  IT_LOCAL_NETWORK,
  IT_LOCAL_RESOURCE,
  IT_EMAIL
} ItemType;

extern const char* const TypeName[];

typedef struct Base {
  struct Item* prev;
  struct Item* next;
  ItemType type;
  char* description;
} Base;

void Input(struct Base* p);
void Print(const struct Base* p);
void Destroy(struct Base* p);

void PrintList(const struct List* L);
void Sort(struct List* L);
void Find(const struct List* L, const char* keyword);
void PrintType(const struct List* L, ItemType type);

struct Base* Create(ItemType t);

#endif  // SUBJ_H