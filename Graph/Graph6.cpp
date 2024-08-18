#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<vector<int>> adj, vector<bool> &visited, vector<int> &dfs_traversal) // Pass by reference is important;
{
    visited[node] = true;
    dfs_traversal.push_back(node);
    for (int j = 0; j < adj[node].size(); j++) // Apply dfs to all its adjacents one by one;
    {
        if (!visited[adj[node][j]]) // if unvisited;
            dfs(adj[node][j], adj, visited, dfs_traversal);
    }
    return;
}
vector<int> DFS(vector<vector<int>> adj)
{
    int n = adj.size();
    vector<int> dfs_traversal;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) // for all components of graph
    {
        if (!visited[i])
            dfs(i, adj, visited, dfs_traversal);
    }
    return dfs_traversal
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
    vector<int> dfs = DFS(adj);
    for (int i = 0; i < dfs.size(); i++)
        cout << dfs[i] << " ";
    cout << endl;
    return 0;
}
/*
GFG Link : https://practice.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
==>Just see latest submission;
==>DFS traversal is required only for source vertex=0; (Hence not applied that loop from 0 to n);
*/
