#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

bool dfs(int node, int parent, vector<vector<int>> &adj, vector<bool> &visited)
{
    visited[node] = true;
    for (int i = 0; i < adj[node].size(); i++)
    {
        if (!visited[adj[node][i]])
        {
            if (dfs(adj[node][i], node, adj, visited))
                return true;
        }
        else if (parent != adj[node][i])
            return true;
    }
    return false;
}
bool isCycle(vector<vector<int>> &adj)
{
    int n = adj.size();
    vector<bool> vis(n, 0);
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            if (dfs(i, -1, adj, vis))
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
    cout << isCycle(adj);
    return 0;
}
/*
SC : O(N) (recursion stack space) + O(N) (visited array) == > O(N), TC : O(N+2E) (DFS traversal);
Coding ninja link : https://www.codingninjas.com/codestudio/problems/cycle-detection-in-undirected-graph_1062670?leftPanelTab=0
==> Just see latest submission ==> Submitted isCycle() function
*/
// Here on GFG I submitted cycle detection using BFS, on coding ninja submited using DFS. (Just see cpp file for code);