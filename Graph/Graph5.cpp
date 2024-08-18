#include <bits/stdc++.h>
using namespace std;

vector<int> BFS(vector<vector<int>> adj)
{
    int n = adj.size();
    vector<int> bfs;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) // for all components of graph;
    {
        if (!visited[i]) // If unvisited;
        {
            queue<int> q;
            q.push(i); // source vertex;
            visited[i] = true;
            while (!q.empty())
            {
                int node = q.front();
                q.pop();
                bfs.push_back(node); // Node get traversed;
                for (int j = 0; j < adj[node].size(); j++)
                {
                    if (!visited[adj[node][j]]) // If unvisited;
                    {
                        q.push(adj[node][j]);
                        visited[adj[node][j]] = true;
                    }
                }
            }
        }
    }
    return bfs;
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<int> bfs = BFS(adj);
    for (int i = 0; i < bfs.size(); i++)
        cout << bfs[i] << " ";
    cout << endl;
    return 0;
}
/*
Important points :
1. Mark it visited just after pushing into queue. (V. imp) (Common mistake is to mark it visited when we are popping from queue that is wrong) (Just dry run) (I tested on GFG Link));

GFG Link : https://practice.geeksforgeeks.org/problems/bfs-traversal-of-graph/1
===> Just see latest submission;
===> Just commented that for-loop because BFS traversal is required only from source vertex=0;
*/
