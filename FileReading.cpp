#include <iostream>
#include <fstream>

using namespace std;

struct Student 
{
	char name[100];
	int fn;
	double grade;
};

int main()
{
	fstream fin;
	fin.open("student.txt", ios::binary);

	int n = 2;

	Student st = new Student[n];

	for (int i = 0; i < n; ++i)
	{
		while (fin.getline(st[i].name, 100))
		{
			fin >> st[i].fn;
			fin >> st[i].grade;
			fin.get();	
		}
	}

	return 0;
}