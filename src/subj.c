#include "subj.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct InternetAddress {
  struct Item* prev;
  struct Item* next;
  ItemType type;
  char* description;

  char* protocol;
  char* node_name;
  char* path;
  char* filename;
} InternetAddress;

typedef struct LocalNetworkAddress {
  struct Item* prev;
  struct Item* next;
  ItemType type;
  char* description;

  char* machine_name;
  char* path;
  char* filename;
} LocalNetworkAddress;

typedef struct LocalResourceAddress {
  struct Item* prev;
  struct Item* next;
  ItemType type;
  char* description;

  char disk_letter;
  char* path;
  char* filename;
} LocalResourceAddress;

typedef struct EmailAddress {
  struct Item* prev;
  struct Item* next;
  ItemType type;
  char* description;

  char* node_name;
  char* username;
} EmailAddress;

const char* const TypeName[] = {"(unknown)", "Internet", "Local network",
                                "Local resource", "Email"};

static char* read_line(const char* prompt) {
  char buf[200];

  printf("%s", prompt);
  if (fgets(buf, sizeof(buf), stdin) == NULL) {
    return NULL;
  }

  size_t len = strlen(buf);
  if (len > 0 && buf[len - 1] == '\n') {
    buf[len - 1] = '\0';
  }

  if (buf[0] == '\0') {
    return strdup("");
  }

  return strdup(buf);
}

static void replace(char** field, const char* prompt) {
  char* value = read_line(prompt);

  if (value == NULL) {
    return;
  }

  free(*field);
  *field = value;
}

static void input_description(Base* p) {
  replace(&p->description, "Input description: ");
}

static void input_internet(InternetAddress* a) {
  replace(&a->protocol, "Input protocol: ");
  replace(&a->node_name, "Input node name: ");
  replace(&a->path, "Input path: ");
  replace(&a->filename, "Input filename: ");
  input_description((Base*)a);
}

static void input_local_network(LocalNetworkAddress* a) {
  replace(&a->machine_name, "Input machine name: ");
  replace(&a->path, "Input path: ");
  replace(&a->filename, "Input filename: ");
  input_description((Base*)a);
}

static void input_local_resource(LocalResourceAddress* a) {
  char buf[64];

  while (1) {
    printf("Input disk letter (A-Z): ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
      return;
    }

    if (buf[0] != '\0' && buf[1] == '\n') {
      if ((buf[0] >= 'A' && buf[0] <= 'Z') ||
          (buf[0] >= 'a' && buf[0] <= 'z')) {
        a->disk_letter = buf[0];
        break;
      }
    }

    printf("Invalid disk letter. Try again.\n");
  }

  replace(&a->path, "Input path: ");
  replace(&a->filename, "Input filename: ");
  input_description((Base*)a);
}

static void input_email(EmailAddress* a) {
  replace(&a->node_name, "Input node name: ");
  replace(&a->username, "Input username: ");
  input_description((Base*)a);
}

void Input(struct Base* p) {
  if (p == NULL) {
    return;
  }

  switch (p->type) {
    case IT_INTERNET:
      input_internet((InternetAddress*)p);
      break;

    case IT_LOCAL_NETWORK:
      input_local_network((LocalNetworkAddress*)p);
      break;

    case IT_LOCAL_RESOURCE:
      input_local_resource((LocalResourceAddress*)p);
      break;

    case IT_EMAIL:
      input_email((EmailAddress*)p);
      break;

    default:
      printf("ERROR: object type unknown.\n");
  }
}

static void print_internet(const InternetAddress* a) {
  printf("\tProtocol: %s\n", a->protocol);
  printf("\tNode name: %s\n", a->node_name);
  printf("\tDescription: %s\n", ((const Base*)a)->description);
  printf("\tAddress: %s://%s/%s/%s\n", a->protocol, a->node_name, a->path,
         a->filename);
  printf("\n");
}

static void print_local_network(const LocalNetworkAddress* a) {
  printf("\tMachine name: %s\n", a->machine_name);
  printf("\tDescription: %s\n", ((const Base*)a)->description);
  printf("\tAddress: \\\\%s\\%s\\%s\n", a->machine_name, a->path, a->filename);
  printf("\n");
}

static void print_local_resource(const LocalResourceAddress* a) {
  printf("\tDisk: %c:\n", a->disk_letter);
  printf("\tDescription: %s\n", ((const Base*)a)->description);
  printf("\tAddress: %c:\\%s\\%s\n", a->disk_letter, a->path, a->filename);
  printf("\n");
}

static void print_email(const EmailAddress* a) {
  printf("\tDescription: %s\n", ((const Base*)a)->description);
  printf("\tAddress: %s@%s\n", a->username, a->node_name);
  printf("\n");
}

void Print(const struct Base* p) {
  if (p == NULL) {
    printf("ERROR: null pointer.\n");
    return;
  }

  if (p->type <= 0 || p->type > 4) {
    printf("ERROR: unknown object type.\n");
    return;
  }

  printf("%s:\n", TypeName[p->type]);

  switch (p->type) {
    case IT_INTERNET:
      print_internet((const InternetAddress*)p);
      break;

    case IT_LOCAL_NETWORK:
      print_local_network((const LocalNetworkAddress*)p);
      break;

    case IT_LOCAL_RESOURCE:
      print_local_resource((const LocalResourceAddress*)p);
      break;

    case IT_EMAIL:
      print_email((const EmailAddress*)p);
      break;

    default:
      break;
  }
}

static void destroy_internet(InternetAddress* a) {
  free(a->protocol);
  free(a->node_name);
  free(a->path);
  free(a->filename);
}

static void destroy_local_network(LocalNetworkAddress* a) {
  free(a->machine_name);
  free(a->path);
  free(a->filename);
}

static void destroy_local_resource(LocalResourceAddress* a) {
  free(a->path);
  free(a->filename);
}

static void destroy_email(EmailAddress* a) {
  free(a->node_name);
  free(a->username);
}

void Destroy(struct Base* p) {
  if (p == NULL) {
    return;
  }

  switch (p->type) {
    case IT_INTERNET:
      destroy_internet((InternetAddress*)p);
      break;

    case IT_LOCAL_NETWORK:
      destroy_local_network((LocalNetworkAddress*)p);
      break;

    case IT_LOCAL_RESOURCE:
      destroy_local_resource((LocalResourceAddress*)p);
      break;

    case IT_EMAIL:
      destroy_email((EmailAddress*)p);
      break;

    default:
      break;
  }

  free(p->description);
  free(p);
}

struct Base* Create(ItemType t) {
  switch (t) {
    case IT_INTERNET: {
      InternetAddress* a = calloc(1, sizeof(InternetAddress));
      if (a != NULL) {
        a->type = t;
      }
      return (struct Base*)a;
    }

    case IT_LOCAL_NETWORK: {
      LocalNetworkAddress* a = calloc(1, sizeof(LocalNetworkAddress));
      if (a != NULL) {
        a->type = t;
      }
      return (struct Base*)a;
    }

    case IT_LOCAL_RESOURCE: {
      LocalResourceAddress* a = calloc(1, sizeof(LocalResourceAddress));
      if (a != NULL) {
        a->type = t;
      }
      return (struct Base*)a;
    }

    case IT_EMAIL: {
      EmailAddress* a = calloc(1, sizeof(EmailAddress));
      if (a != NULL) {
        a->type = t;
      }
      return (struct Base*)a;
    }

    default:
      return NULL;
  }
}

static const char* get_node_name(const struct Base* p) {
  switch (p->type) {
    case IT_INTERNET:
      return ((const InternetAddress*)p)->node_name;

    case IT_LOCAL_NETWORK:
      return ((const LocalNetworkAddress*)p)->machine_name;

    case IT_EMAIL:
      return ((const EmailAddress*)p)->node_name;

    default:
      return "";
  }
}

static void swap_nodes(struct List* list, struct Item* a, struct Item* b) {
  struct Item* pre = a->prev;
  struct Item* post = b->next;

  a->next = post;
  if (post != NULL) {
    post->prev = a;
  }

  b->prev = pre;
  if (pre != NULL) {
    pre->next = b;
  }

  b->next = a;
  a->prev = b;

  if (list->head == a) {
    list->head = b;
  }
  if (list->tail == b) {
    list->tail = a;
  }
}

void Sort(struct List* L) {
  if (L == NULL) {
    return;
  }

  int n = Count(L);

  for (int i = 0; i < n - 1; i++) {
    struct Item* current = L->head;
    int swapped = 0;

    for (int j = 0; j < n - 1 - i && current != NULL && current->next != NULL;
         j++) {
      const struct Base* a = (const struct Base*)current;
      const struct Base* b = (const struct Base*)current->next;

      if (strcmp(get_node_name(a), get_node_name(b)) > 0) {
        swap_nodes(L, current, current->next);
        swapped = 1;
      }

      current = current->next;
    }

    if (!swapped) {
      break;
    }
  }
}

void PrintList(const struct List* L) {
  if (L == NULL) {
    printf("ERROR: wrong list.\n");
    return;
  }

  if (L->head == NULL) {
    printf("List is empty.\n");
    return;
  }

  int i = 0;
  struct Item* p = L->head;

  while (p != NULL) {
    printf("%d. ", i++);
    Print((const struct Base*)p);
    p = p->next;
  }
}

void Find(const struct List* L, const char* keyword) {
  if (L == NULL || keyword == NULL) {
    return;
  }

  int found = 0;
  struct Item* p = L->head;

  while (p != NULL) {
    const struct Base* b = (const struct Base*)p;

    if (b->description != NULL && strstr(b->description, keyword) != NULL) {
      found = 1;
      Print(b);
    }

    p = p->next;
  }

  if (!found) {
    printf("No addresses found.\n");
  }
}

void PrintType(const struct List* L, ItemType type) {
  if (L == NULL) {
    return;
  }

  int found = 0;
  struct Item* p = L->head;

  while (p != NULL) {
    const struct Base* b = (const struct Base*)p;

    if (b->type == type) {
      found = 1;
      Print(b);
    }

    p = p->next;
  }

  if (!found) {
    printf("No addresses of this type.\n");
  }
}