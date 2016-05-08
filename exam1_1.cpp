#include <iostream>
#include <queue>

using namespace std;

int main()
{
  int n;
  int p;
  cout << "Enter starting number: ";
  cin >> n;
  cout << "Enter the number of element you want to look for:";
  cin >> p;

  queue<int> q;
  q.push(n);
  for (int i = 0; i < p; ++i)
  {
    n = q.front();
    q.push(n + 1);
    q.push(n * 2);
    q.pop();
  }

  cout << "The " << p << "-th element is: " << n << endl;
}