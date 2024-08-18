#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

bool checkForCycle(int src, vector<vector<int>> &adj, vector<int> &visited)
{
    queue<pair<int, int>> q;
    q.push({src, -1});
    visited[src] = true;
    while (!q.empty())
    {
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();
        for (int i = 0; i < adj[node].size(); i++)
        {
            if (!visited[adj[node][i]])
            {
                q.push({adj[node][i], node});
                visited[adj[node][i]] = true; // mark it visited just after pushing into queue;
            }
            else if (parent != adj[node][i])
                return true;
        }
    }
    return false;
}
bool isCycle(vector<vector<int>> &adj)
{
    int n = adj.size();
    vector<int> vis(n, 0);
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            if (checkForCycle(i, adj, vis))
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
// TC : O(n+2e), SC : O(n)
// GFG Link : https://practice.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
// Just see latest submission (Exactly same as above code) : 2022-06-14 17:00:08	Correct	cpp	210 / 210 
// ==> (Just one extra argument passed V as that is array) (Ignore it (main code is exactly same) just see code here itself);
/*
==> If a graph has one or more than one component and if any component has at least one cycle then that graph is said to be cyclic.
==> Like BFS traversal, here also we will apply loop for each component, and if any component has iscycle=true then return true 
    else outside loop finally return false;
==> We will take a queue of type <node,parent>. Starting configuration: Take node for which is cycle(i) is called into queue and push into queue like this {node,-1} (this is source vertex);
Concept : (jisss node se aaye h wo toh visit hogi hi) (cycle detect tab maani jaaeygi jab hum jiss aisi node ki adjacent mein ho 
          (jo already visited ho) (and most imp is that should not be parent, as parent adjacent aur visited toh hoga hi kyonki 
          whi se toh hum current node pr aaye h) (hence if there is a node which is not parent and already visited means cycle present).
          Hence we also need to maintain a parent for each node.
As soon as we are trying to traverse an already visited node (which is not parent) it is said to have a cycle.
*/
