#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

bool dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, vector<bool> &path_vis)
{
    visited[node] = true;
    path_vis[node] = true;
    for (int i = 0; i < adj[node].size(); i++)
    {
        if (!visited[adj[node][i]]) // When node is not visited
        {
            if (dfs(adj[node][i], adj, visited, path_vis))
                return true;
        }
        else if (path_vis[adj[node][i]]) // If the node has been previously visited on the same path
            return true;
    }
    path_vis[node] = false; // On returning mark it path_vis=false;
    return false;
}
bool isCycle(vector<vector<int>> &adj)
{
    int n = adj.size();
    vector<bool> vis(n, false);
    vector<bool> path_vis(n, false);
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            if (dfs(i, adj, vis, path_vis))
                return true;
        }
    }
    return false;
}
int32_t main()
{
    fio;
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
    return 0;
}
// Detect cycle in a directed graph (DFS);
// Why Detect cycle in a undirected graph (DFS) approach will fail? (Took a testcase and make understand);
// Key point : On the same path node has to be visited again. For this keep two visited arrays, 1. visited, 2. path_visited;
// TC : O(V+E) (DFS traversal), SC : O(2N);
// Here we can use single visited array as well : Just keep defination like vis[i]=1 (if visited), vis[i]=2 (if path visited);
// GFG Link : https://practice.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1 
// Just see latest submission ==> Submitted isCycle();