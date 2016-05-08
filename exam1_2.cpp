#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

struct Problem
{
  char task[1000];
  int difficulty;
  char tag[10];
};

using namespace std;

void add_to_binary(Problem* problems, int n)
{
  ofstream fout;
  fout.open("problems.bin", ios::binary);
  for(int i = 0; i < n; i++)
  {
    fout.write((char*) &problems[i], sizeof(Problem));
  }
  fout.close();
}

void read_from_binary(int n)
{
  ifstream fin;
  fin.open("problems.bin", ios::binary);
  Problem p;
  for(int i = 0; i < n; i++)
  {
    fin.read((char*) &p, sizeof(p));
    cout << p.task << " " << p.difficulty << " ";
    cout << p.tag << " " << endl;
  }
  fin.close();
}

void sort(int n, Problem* problems)
{
  for (int i = 0; i < n; ++i)
  {
    Problem min = problems[i];
    for (int j = i + 1; j < n; ++j)
    {
      if(problems[j].difficulty < problems[i].difficulty)
      {
        problems[i] = problems[j];
        problems[j] = min;
      }
    }
  }
}

int main()
{
  int n;
  cout << "Enter the number of problems: ";
  cin >> n;

  Problem* problems = new Problem[n];

  for (int i = 0; i < n; ++i)
  {
    cout << "Enter the task: ";
    cin.ignore();
    cin.getline(problems[i].task, 1000);
    cout << "Enter complexity: ";
    cin >> problems[i].difficulty;
    if (problems[i].difficulty < 30)
      strcpy(problems[i].tag, "Easy");
    else
    {
      if (problems[i].difficulty <= 70)
        strcpy(problems[i].tag, "Medium");
      else
        strcpy(problems[i].tag, "Hard");
    }
  }

  sort(n, problems);

  add_to_binary(problems, n);
  read_from_binary(n);

  delete [] problems;
}