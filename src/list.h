#ifndef LIST_H
#define LIST_H

class List;

class Item {
  friend class List;

 private:
  Item* prev;
  Item* next;
  List* owner;

 public:
  Item();
  ~Item();

  Item(const Item&) = delete;
  Item& operator=(const Item&) = delete;

  Item* Prev() const;
  Item* Next() const;
};

class List {
 private:
  Item* head;
  Item* tail;

 public:
  List();
  ~List();

  List(const List&) = delete;
  List& operator=(const List&) = delete;

  Item* Head() const;
  Item* Tail() const;

  void Add(Item* item);
  void Insert(int item_index, Item* item);
  void Delete(int item_index);
  Item* Remove(int item_index);
  Item* GetItem(int item_index) const;
  int GetIndex(const Item* item) const;
  int Count() const;
  void Clear();
};

#endif
