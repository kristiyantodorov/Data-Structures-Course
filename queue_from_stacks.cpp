#include <iostream>
#include <stack>
#include <cassert>
#include "queue_from_stacks.h"

using namespace std;

template <class T>
MyStack<T>::MyStack()
{
  capacity = 10;
  current_size = 0;
  st = new T[capacity];
}

template <class T>
void MyStack<T>::resize(int new_capacity)
{
  T* buffer = new T[new_capacity + 1];
  capacity = new_capacity;

  for (int i = 0; i < current_size; i++)
  {
    buffer[i] = st[i];
  }

  delete [] st;
  st = buffer;
}

template <class T>
bool MyStack<T>::empty()
{
  return current_size == 0;
}

template <class T>
int MyStack<T>::size()
{
  return current_size;
}

template <class T>
T MyStack<T>::top()
{
  assert(("The stack is empty!", !empty()));
  return st[current_size - 1];
}

template <class T>
void MyStack<T>::push(T item)
{
  st[current_size] = item;
  current_size += 1;
  if (size() > (3 * capacity / 4))
  {
    resize(capacity * 2);
  }
}

template <class T>
void MyStack<T>::pop()
{
  assert(("The stack is empty!", !empty()));
  current_size -= 1;
  if (current_size < capacity / 4)
    resize(capacity / 2);
}

template <class T>
MyStack<T>::~MyStack()
{
  delete [] st;
}

//Queue
template <class T>
MyQueue<T>::MyQueue()
{
  current_size = 0;
}

template <class T>
bool MyQueue<T>::empty()
{
  return current_size == 0;
}

template <class T>
int MyQueue<T>::size()
{
  return current_size;
}

template <class T>
T MyQueue<T>::front()
{
  assert(("The queue is empty!", !empty()));
  if(right.empty())
  {
    while (!left.empty())
    {
      right.push(left.top());
      left.pop();
    }
  }
  return right.top();
}

template <class T>
T MyQueue<T>::back()
{
  assert(("The queue is empty!", !empty()));
  return left.top();
}

template <class T>
void MyQueue<T>::push(T item)
{
  left.push(item);
  current_size += 1;
}

template <class T>
void MyQueue<T>::pop()
{
  assert(("The queue is empty!", !empty()));
  if (right.empty())
  {
    while (!left.empty())
    {
      right.push(left.top());
      left.pop();
    }
  }
  right.pop();
  current_size -= 1;
}

template <class T>
void MyQueue<T>::print()
{
  assert(("The queue is empty!", !empty()));
  while(!empty())
  {
    cout << front() << " ";
    pop();
  }
  cout << endl;
}

int main()
{
  MyQueue<char> q;
  q.push('a');
  q.push('b');
  q.push('c');
  q.push('d');
  q.push('e');
  q.push('f');
  q.push('g');
  q.push('h');
  q.print();
  return 0;
}