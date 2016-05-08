#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

struct Student
{
  char name[100];
  int fn;

  Student(const char* set_name = "No name", int set_fn = 0)
  {
    strcpy(name, set_name);
    fn = set_fn;
  }

  bool operator == (const Student other)
  {
    return (name == other.name) && (fn == other.fn);
  }

  bool operator < (const Student& other)
  {
    return (fn < other.fn);
  }
};

template <class T>
struct Record
{
  T rec;
  bool flag;

public:
  Record()
  {
    flag = true;
  }

  void print()
  {
    cout << "Data: " << rec << " Flag: " << boolalpha << flag << endl;
  }
};

template <class T>
class Container
{
public:
  virtual void add(const T&) = 0;
  virtual void print() = 0;
  virtual void remove(const T&) = 0;
  virtual bool member(const T&) = 0;
  virtual void map(T (T&)) = 0;
  //virtual void filter(bool(T&));
};

template<class T>
class Array : public Container<T>
{
public:
  int size;
  int capacity;
  T* arr;

  Array()
  {
    capacity = 100;
    size = 0;
    arr = new T[capacity];
  }

  void print()
  {
    for (int i = 0; i < size; ++i)
    {
      cout << arr[i] << endl;
    }
  }

  void remove(const T& to_remove)
  {
    int iter = 0;
    while(arr[iter] != to_remove)
    {
      iter ++;
    }
    for (int i = iter; i < size; ++i)
    {
        arr[i] = arr[i + 1];
    }
    size --;
  }

  void add(const T& to_add)
  {
    arr[size] = to_add;
    size++;
  }

  int count()
  {
    return size;
  }

  bool member(const T& to_search)
  {
    for (int i = 0; i < size; ++i)
    {
      if(arr[i] == to_search) return true;
    }
    return false;
  }

  T& find(bool (*pred)(const T&))
  {
    for (int i = 0; i < size; ++i)
    {
      if(pred(arr[i]))
        return arr[i];
    }
  }

  Container<T>* filter(bool (*pred)(const T&))
  {
    Container<T>* filtered_array = new Array<T>;
    for (int i = 0; i < size; ++i)
    {
      if (pred(arr[i]))
      {
        filtered_array -> add(arr[i]);
      }
    }
    return filtered_array;
  }

  void map(T (*mapper)(T&))
  {
    for (int i = 0; i < size; ++i)
    {
      arr[i] = mapper(arr[i]);
    }
  }

  ~Array()
  {
    delete [] arr;
  }
};

template <class T>
class BinFile : public Container<T>
{
  char name[100];

public:
  BinFile(const char* file_name)
  {
    strcpy(name, file_name);
  }

  void add(const T& to_add)
  {
    Record<T> item;
    item.rec = to_add;
    ofstream fout;
    fout.open(name, ios::binary | ios::app);
    fout.write((char*)&to_add, sizeof(item));
    fout.close();
  }

  void print()
  {
    Record<T> to_print;
    ifstream fin;
    fin.open(name, ios::binary);
    fin.seekg(0, ios::beg);
    while(fin.read((char*)& to_print, sizeof(to_print)))
    {
      to_print.print();
    }
    fin.close();
  }

  void map(T (*mapper)(T&))
  {
    fstream fio;
    Record <T> item;
    int iterator = 0;
    fio.open(name, ios::binary | ios::in | ios::out);
    fio.seekg(0, ios::beg);
    while(fio.read((char*)& item, sizeof(item)))
    {
      fio.seekp(iterator * sizeof(item), ios::beg);
      item.rec = mapper(item.rec);
      fio.write((char*)& item, sizeof(item));
      iterator++;
    }
  }

  int size()
  {
    ifstream fin;
    int position;
    fin.open(name, ios::binary);
    fin.seekg(0, ios::end);
    position = fin.tellg();
    return position / sizeof(Record<T>);
  }

  void remove(const T& to_remove)
  {
    fstream fio;
    Record <T> item;
    fio.open(name, ios::binary | ios::in | ios::out);
    fio.seekg(0, ios::beg);
    for (int i = 0; i < size(); ++i)
    {
      fio.read((char*)& item, sizeof(item));
      fio.seekp(i * sizeof(item), ios::beg);
      if(item.rec == to_remove)
      {
        item.flag = false;
      }
      fio.write((char*)& item, sizeof(item));
    }
  }

  void filter(bool (*pred)(T& item))
  {
    fstream fio;
    Record <T> item;
    fio.open(name, ios::binary | ios::in | ios::out);
    fio.seekg(0, ios::beg);
    for (int i = 0; i < size(); ++i)
    {
      fio.read((char*)& item, sizeof(item));
      fio.seekp(i * sizeof(item), ios::beg);
      if(!pred(item))
      {
        item.flag = false;
      }
      fio.write((char*)& item, sizeof(item));
    }
  }

  bool member(const T& check)
  {
    Record<T> iterator;
    ifstream fin;
    fin.open(name, ios::binary);
    fin.seekg(0, ios::beg);
    while(fin.read((char*)& iterator, sizeof(iterator)))
    {
      if (iterator.rec == check) return true;
    }
    fin.close();
    return false;
  }
};

template <class T>
T mapper(T& item)
{
  return item *= 2;
}

template <class T>
bool pred(T item)
{
  return item % 2 == 0;
}

template <class T>
struct Node
{
  T data;
  Node* left;
  Node* right;

  void print_node()
  {
    if(this == NULL)
      return;
    left -> print_node();
    cout << data << " ";
    right -> print_node();
  }

  void map_node(T (*mapper (T& item)))
  {
    if(this == NULL)
      return;
    data = mapper(data);
  }

  Node<T>* find_min()
  {
    Node<T>* tmp = this;
    while(tmp -> left)
    {
      tmp = tmp -> left;
    }
    return tmp;
  }

  Node<T>* find_max()
  {
    Node<T>* tmp = this;
    while(tmp -> right)
    {
      tmp = tmp -> right;
    }
    return tmp;
  }


  Node(const T& item)
  {
    data = item;
    left = NULL;
    right = NULL;
  }
};

template <class T>
class BinarySearchTree : public Container<T>
{
  Node<T>* root;
  int size;

public:
  BinarySearchTree()
  {
    size = 0;
    root = NULL;
  }

  Node<T>* find_node(const T& item)
  {
    Node<T>* tmp = root;
    while(tmp && (tmp -> data != item))
    {
      if(item < tmp -> data)
        tmp = tmp -> left;
      else
        tmp = tmp -> right;

    }
    return tmp;
  }

  bool contains(const T& item)
  {
    Node<T>* tmp = find_node(item);
    return tmp != NULL;
  }

  void add(const T& item)
  {
    Node<T>* tmp = root;
    Node<T>* tmp_parent = NULL;
    if(contains(item))
      return;

    if(root == NULL)
      root = new Node<T>(item);
    else
    {
      while(tmp)
      {
        tmp_parent = tmp;
        if(item < tmp -> data)
          tmp = tmp -> left;
        else
          tmp = tmp -> right;
      }

      tmp = new Node<T>(item);
      if(item < tmp_parent -> data)
        tmp_parent -> left = tmp;
      else
        tmp_parent -> right = tmp;
    }
    size ++;
  }



/*
  int get_height_of_node(const T& n)
  {
    Node<T>* tmp = root;
    int height = 0;
    while(tmp -> data != n)
    {
      if(n < tmp -> data)
        tmp = tmp -> left;
      else
        tmp = tmp -> right;
      height ++;
    }
    return height;
  }

  int height()
  {

  }
*/

  T get_max()
  {
    return root -> find_max() -> data;
  }

  T get_min()
  {
    return root -> find_min() -> data;
  }

  void print()
  {
    root -> print_node();
  }

  int get_size() const
  {
    return size;
  }

  void help_remove(Node<T>*& tmp, T item)
  {
    if(item < tmp -> data)
      help_remove(tmp -> left, item);
    else if(item > tmp -> data)
      help_remove(tmp -> right, item);
    else
    {
      save = tmp;
      delete tmp;
      tmp = save -> left;
    }

  }

  void remove(const T& item)
  {
    if(!contains(item))
      return;
    help_remove(root, item);
  }

  bool member(const T& item)
  {
    Node<T>* tmp = find_node(item);
    return tmp != NULL;
  }

  void map(T (*mapper) (T&)){};

  Container<T>* filter(bool (*pred)(T&)){};
};


int main()
{
  BinarySearchTree<int> tree;
  //Container<int>* cont = &tree;

  tree.add(-1);
  tree.add(0);
  tree.add(1);
  tree.add(2);
  tree.add(3);
  tree.add(4);
  tree.add(5);

  //tree.map(mapper(T&));
  cout << tree.get_max() << endl;

  tree.print();

  return 0;
}
