#include <iostream>
#include <vector>
using namespace std;

int N, M, start_vertex;
vector <int> v[100];

void input()
{
    cin >> M;
    int x, y;
    for( int i = 0; i < M; i++ )
    {
        cin >> x >> y;
        v[x-1].push_back(y-1);
    }
    cin >> start_vertex;
}

bool used[100];
void dfs( int i )
{
    cout << i+1 << " ";
    used[i] = 1;
    for( int j = 0; j < v[i].size(); j++ )
        if( !used[v[i][j]] )
        {
            dfs(v[i][j]);
        }
}

int main()
{
    input();
    dfs(start_vertex-1);
    cout << endl;

    return 0;
}