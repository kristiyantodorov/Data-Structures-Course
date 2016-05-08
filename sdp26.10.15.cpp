#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

struct Student
{
	int fn;
	char name[100];
	Student()
	{
		fn = 0;
		strcpy(name, "No name");
	}
};

class Container
{
public:
	//virtual Student find(int) = 0;
	//virtual void add(Student) = 0;

};

class Array
{
public:
	Student st[10];
  int size;

	Array()
	{
		size = 10;
	}

  Array& operator[](int n)
  {

  }

	Student find(int facnum)
	{
		Student false_student;
		false_student.fn = -1;
		strcpy(false_student.name, "False student");
		int i = 0;
		while(facnum != st[i].fn && i < size)
		{
			++i;
		}
		if (i < size) return st[i];
		return false_student;
	}


	void print()
	{
		for (int i = 0; i < size; ++i)
		{
			cout<< st[i].fn << " " << st[i].name<<endl;
		}
	}
	void add(Student newst)
	{
		st[size].fn = newst.fn;
		strcpy(st[size].name, newst.name);
		size ++;
	}

	void delst(int n)
	{
		while (n < size - 1)
		{
			st[n] = st[n+1];
			n++;
		}
		size--;
	}

};

class TextFile
{
public:
	string fname;

	TextFile(string name = "TextFile.txt")
	{
		fname = name;
	}




	void print()
	{
		ifstream input(fname.c_str());
		int fn;
		string st;

		while (getline(input, st))
		{
			input >> fn;
			input.get();
			cout << st << " " << fn << endl;
		}
		input.close();
	}

	void add(Student newst)
	{
		ofstream output(fname.c_str(), ios::app);
		output << newst.name << "\n" << newst.fn << endl;
	}
};

class Binary
{
public:
	string fname;

	Binary(string name = "TextFile.bin")
	{
		fname = name;
	}

	void add(Student newst)
	{
		ofstream output(fname.c_str(), ios::binary | ios::app);
		output.seekp(0, ios::end);

		output.write((char*)& newst, sizeof(Student));

	}

	void printAll()
	{
		Student pr_st;
		ifstream input(fname.c_str(), ios::binary);

		while (input.read((char*)& pr_st, sizeof(Student)))
		{
			cout << pr_st.name << " " << pr_st.fn << endl;
		}
	}

};

struct Node
{
	Student data;
	Node* next;

	Node(Student st, Node* pointer = NULL)
	{
		data = st;
		next = pointer;
	}
};

class LList
{
public:
	Node* first;

	LList()
	{
		first = NULL;
	}

  LList(const LList& other)
  {
    Node* current_other = other.first;
    first = NULL;
    while(current_other)
    {
      add(current_other -> data);
      current_other = current_other -> next;
    }
  }

	void add(Student newst)
	{
		Node* current = first;

		if (first == NULL)
		{
			first = new Node(newst, NULL);
		}
		else
		{
			while (current -> next)
			{
				current = current -> next;
			}
			current -> next = new Node(newst, NULL);
		}
	}

  void delete_by_fn(int facnum)
  {
    Node* previous = first;
    Node* current = previous -> next;
    if(first -> data.fn == facnum)
    {
      delete first;
      first = current;
    }
    else
    {
      while(current)
      {
        if(current -> data.fn == facnum)
        {
          previous -> next = current -> next;
          delete current;
        }
        previous = current;
        current = current -> next;
      }
    }
  }

  void delete_all()
  {
    Node* current = first;
    while(current)
    {
      first = current -> next;
      delete current;
      current = first;
    }
  }

  void recursive_print_forward(Node* start)
  {
    if(start == NULL) return;
    cout << start -> data.name << " " << start -> data.fn << endl;
    recursive_print_forward(start -> next);
  }

  void recursive_print_backward(Node* start)
  {
    if(start == NULL) return;
    recursive_print_backward(start -> next);
    cout << start -> data.name << " " << start -> data.fn << endl;
  }

  void reverse()
  {
    Node* previous = NULL;
    Node* current = first;
    Node* temp = current -> next;
    while(current)
    {
      current -> next = previous;
      previous = current;
      current = temp;
      if(temp)
      {
        temp = temp -> next;
      }
    }
    first = previous;
  }


	void print()
	{
		Node* current = first;

		while(current)
		{
			cout << current -> data.name << " " << current -> data.fn << endl;
			current = current -> next;
		}
	}

  ~LList()
  {
    delete_all();
  }

};


int main()
{
	Array st_arr;

	//Student st[10];

	for (int i = 0; i < st_arr.size; ++i)
	{
		st_arr[i].fn = i;
	}
  st_arr.print();
	return 0;
}
