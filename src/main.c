#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "subj.h"

int read_int(const char* prompt, int* out);
void read_str(const char* prompt, char* buf, int size);

void destroy_all_contents(List* list);
int select_type(void);
void menu(List* list);

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

void destroy_all_contents(List* list) {
  Item* item;

  while ((item = Remove(list, 0)) != NULL) {
    Destroy((Base*)item);
  }

  Clear(list);
}

int select_type(void) {
  int t;

  while (1) {
    printf("Select address type:\n");
    printf("1. %s\n", TypeName[1]);
    printf("2. %s\n", TypeName[2]);
    printf("3. %s\n", TypeName[3]);
    printf("4. %s\n", TypeName[4]);

    if (read_int("Input type: ", &t) && t >= 1 && t <= 4) {
      return t;
    }

    printf("Invalid type.\n");
  }
}

Base* create_from_menu(void) {
  Base* p = Create(select_type());

  if (p == NULL) {
    printf("Memory allocation error.\n");
    return NULL;
  }

  Input(p);
  return p;
}

void menu(List* list) {
  int choice;

  while (1) {
    printf("\n========== MENU ==========\n");
    printf("1. Add address\n");
    printf("2. Insert address\n");
    printf("3. Delete address at index\n");
    printf("4. Remove address at index\n");
    printf("5. Find by keyword in description\n");
    printf("6. Sort by node name\n");
    printf("7. Print all addresses\n");
    printf("8. Print addresses of a type\n");
    printf("9. Count\n");
    printf("0. Exit\n");
    printf("==========================\n");

    if (!read_int("Input choice: ", &choice)) {
      printf("Invalid input.\n");
      continue;
    }

    switch (choice) {
      case 1: {
        Base* p = create_from_menu();

        if (p != NULL) {
          Add(list, (Item*)p);
          printf("Address added.\n");
        }

        break;
      }

      case 2: {
        int index;

        if (!read_int("Input index: ", &index)) {
          printf("Invalid input.\n");
          break;
        }

        Base* p = create_from_menu();

        if (p != NULL) {
          Insert(list, index, (Item*)p);
          printf("Address inserted.\n");
        }

        break;
      }

      case 3: {
        int index;

        if (!read_int("Input index: ", &index)) {
          printf("Invalid input.\n");
          break;
        }

        Destroy((Base*)Remove(list, index));

        printf("Address deleted.\n");

        break;
      }

      case 4: {
        int index;

        if (!read_int("Input index: ", &index)) {
          printf("Invalid input.\n");
          break;
        }

        Destroy((Base*)Remove(list, index));

        printf("Address removed.\n");

        break;
      }

      case 5: {
        char keyword[100];

        read_str("Input keyword: ", keyword, sizeof(keyword));
        Find(list, keyword);

        break;
      }

      case 6:
        Sort(list);
        printf("List sorted by node name.\n");
        break;

      case 7:
        PrintList(list);
        break;

      case 8: {
        ItemType t = (ItemType)select_type();
        PrintType(list, t);
        break;
      }

      case 9:
        printf("Number of addresses: %d\n", Count(list));
        break;

      case 0:
        destroy_all_contents(list);
        return;

      default:
        printf("Invalid choice.\n");
    }
  }
}

int main(void) {
  List list = {NULL, NULL};

  menu(&list);

  return 0;
}