#include <iostream>
#include <limits>

#include "list.h"

class DebugList : public List {
 private:
  static bool ReadInt(const char* prompt, int& value);

 public:
  void Print() const;
  void Menu();
};

bool DebugList::ReadInt(const char* prompt, int& value) {
  while (true) {
    std::cout << prompt;
    if (std::cin >> value) {
      return true;
    }
    if (std::cin.eof()) {
      return false;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Input an integer.\n";
  }
}

void DebugList::Print() const {
  std::cout << "List: " << this << "  Head: " << Head() << "  Tail: " << Tail()
            << '\n';
  std::cout << "#\tp\tprev\tnext\n";
  int index = 0;
  for (Item* item = Head(); item != nullptr; item = item->Next()) {
    std::cout << index << '\t' << item << '\t' << item->Prev() << '\t'
              << item->Next() << '\n';
    index++;
  }
}

void DebugList::Menu() {
  while (true) {
    std::cout << "\n========== MENU ==========\n"
                 "1. Add item\n"
                 "2. Insert item at index\n"
                 "3. Delete item at index\n"
                 "4. Remove item at index\n"
                 "5. Get item at index\n"
                 "6. Get index by pointer\n"
                 "7. Count items\n"
                 "8. Clear list\n"
                 "9. Print list\n"
                 "0. Exit\n";
    int choice;
    if (!ReadInt("Input operation: ", choice) || choice == 0) {
      return;
    }

    int index = 0;
    if (choice >= 2 && choice <= 5) {
      if (!ReadInt("Input index (starting at 0): ", index)) {
        return;
      }
    }

    switch (choice) {
      case 1:
        Add(new Item());
        break;
      case 2:
        Insert(index, new Item());
        break;
      case 3:
        Delete(index);
        break;
      case 4: {
        Item* item = Remove(index);
        std::cout << "Removed item: " << item << '\n';
        delete item;
        break;
      }
      case 5:
        std::cout << "Item: " << GetItem(index) << '\n';
        break;
      case 6: {
        void* address = nullptr;
        std::cout << "Input pointer from the table (0x...): ";
        if (!(std::cin >> address)) {
          if (std::cin.eof()) {
            return;
          }
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Invalid pointer.\n";
          break;
        }
        std::cout << "Index: " << GetIndex(static_cast<Item*>(address)) << '\n';
        break;
      }
      case 7:
        std::cout << "Item count: " << Count() << '\n';
        break;
      case 8:
        Clear();
        break;
      case 9:
        Print();
        break;
      default:
        std::cout << "Invalid operation.\n";
        break;
    }
  }
}

int main() {
  DebugList list;
  list.Menu();
  return 0;
}
