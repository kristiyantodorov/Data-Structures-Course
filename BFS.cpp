#include <iostream>
#include <vector>
#include <queue>
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
void bfs( int i )
{
    queue <int> q;
    q.push(i);
    used[i] = 1;

    while( !q.empty() )
    {
        int curr_vertex = q.front();
        q.pop();
        cout << curr_vertex+1 << " ";
        for( int j = 0; j < v[curr_vertex].size(); j++ )
            if( !used[v[curr_vertex][j]] )
            {
                q.push(v[curr_vertex][j]);
                used[v[curr_vertex][j]] = 1;
            }
    }
    cout << endl;
}

int main()
{
    input();
    bfs(start_vertex-1);

    return 0;
}
