#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void PrintList(const List* list);

int read_int(const char* prompt, int* out);
void read_str(const char* prompt, char* buf, int size);

void menu(List* list);

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
  if (list == NULL || item == NULL) {
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

void PrintList(const List* list) {
  if (list == NULL) {
    return;
  }

  printf("List: %p  Head: %p  Tail: %p\n", (void*)list, (void*)list->head,
         (void*)list->tail);
  printf("#\tp\t\tprev\t\tnext\n");

  Item* current = list->head;
  int i = 0;

  while (current != NULL) {
    printf("%d\t%p\t%p\t\t%p\n", i, (void*)current, (void*)current->prev,
           (void*)current->next);
    current = current->next;
    i++;
  }
}

int read_int(const char* prompt, int* out) {
  char buf[64];

  printf("%s", prompt);
  if (fgets(buf, sizeof(buf), stdin) == NULL) {
    return 0;
  }

  char* end;
  long val = strtol(buf, &end, 10);

  if (end == buf || (*end != '\n' && *end != '\0')) {
    return 0;
  }

  *out = (int)val;
  return 1;
}

void read_str(const char* prompt, char* buf, int size) {
  printf("%s", prompt);
  if (fgets(buf, size, stdin) == NULL) {
    buf[0] = '\0';
    return;
  }

  size_t len = strlen(buf);
  if (len > 0 && buf[len - 1] == '\n') {
    buf[len - 1] = '\0';
  }
}

void menu(List* list) {
  int choice;

  while (1) {
    printf("\n========== MENU ==========\n");
    printf("1. Add element\n");
    printf("2. GetItem by index\n");
    printf("3. Delete element at index\n");
    printf("4. Remove element at index\n");
    printf("5. Insert element at index\n");
    printf("6. GetIndex by pointer\n");
    printf("7. Count elements\n");
    printf("8. Clear list\n");
    printf("9. PrintList\n");
    printf("0. Exit\n");
    printf("==========================\n");

    if (!read_int("Input choice: ", &choice)) {
      printf("Invalid input.\n");
      continue;
    }

    switch (choice) {
      case 1: {
        Item* item = malloc(sizeof(Item));

        if (item == NULL) {
          printf("Memory allocation error.\n");
          break;
        }

        item->prev = NULL;
        item->next = NULL;

        Add(list, item);
        printf("Element added.\n");

        break;
      }

      case 2: {
        int index;

        if (!read_int("Input index: ", &index)) {
          printf("Invalid input.\n");
          break;
        }

        Item* item = GetItem(list, index);

        if (item == NULL) {
          printf("Element not found.\n");
        } else {
          printf("Element at index %d: %p\n", index, (void*)item);
        }

        break;
      }

      case 3: {
        int index;

        if (!read_int("Input index: ", &index)) {
          printf("Invalid input.\n");
          break;
        }

        Delete(list, index);
        printf("Element deleted.\n");

        break;
      }

      case 4: {
        int index;

        if (!read_int("Input index: ", &index)) {
          printf("Invalid input.\n");
          break;
        }

        Item* item = Remove(list, index);

        printf("Removed element: %p\n", (void*)item);
        free(item);

        break;
      }

      case 5: {
        int index;

        if (!read_int("Input index: ", &index)) {
          printf("Invalid input.\n");
          break;
        }

        Item* item = malloc(sizeof(Item));

        if (item == NULL) {
          printf("Memory allocation error.\n");
          break;
        }

        item->prev = NULL;
        item->next = NULL;

        Insert(list, index, item);
        printf("Element inserted.\n");

        break;
      }

      case 6: {
        Item* item;

        printf("Input element pointer: ");
        if (scanf("%p", (void**)&item) != 1) {
          printf("Invalid input.\n");
        } else {
          int index = GetIndex(list, item);

          if (index < 0) {
            printf("Element not found.\n");
          } else {
            printf("Index of element %p: %d\n", (void*)item, index);
          }
        }

        char rest[64];
        fgets(rest, sizeof(rest), stdin);

        break;
      }

      case 7:
        printf("Number of elements: %d\n", Count(list));
        break;

      case 8:
        Clear(list);
        printf("List cleared.\n");
        break;

      case 9:
        PrintList(list);
        break;

      case 0:
        return;

      default:
        printf("Invalid choice.\n");
    }
  }
}

int main(void) {
  List list = {NULL, NULL};

  menu(&list);

  Clear(&list);

  return 0;
}