template <class T>
class MyStack
{
  T* st;
  int current_size;
  int capacity;

public:
  MyStack();
  void resize(int);
  bool empty();
  int size();
  T top();
  void push(T);
  void pop();
  ~MyStack();
};

template <class T>
class MyQueue
{
  MyStack<T> left, right;
  int current_size;

public:
  MyQueue();
  bool empty();
  int size();
  T front();
  T back();
  void push(T);
  void pop();
  void print();
};