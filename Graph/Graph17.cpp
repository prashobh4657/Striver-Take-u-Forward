#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
template <typename T>
istream &operator>>(istream &input, vector<T> &v)
{
    for (auto &i : v)
        cin >> i;
    return input;
}
template <typename T>
ostream &operator<<(ostream &output, vector<T> &v)
{
    for (auto &i : v)
        cout << i << " ";
    return output;
}
bool BFS(int start, vector<vector<int>> &adj, vector<int> &color)
{
    queue<int> q;
    q.push(start);
    color[start] = 0; // Let's colour 1st node with colour 0 without any loss of generality.
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        for (int j = 0; j < adj[node].size(); j++)
        {
            if (color[adj[node][j]] == -1) // Not yet coloured (Then just colour it with opposite colour of "node")
            {
                q.push(adj[node][j]);
                color[adj[node][j]] = 1 - color[node];
            }
            else if (color[adj[node][j]] == color[node]) // Adjacent node is colored with same color as that of node (hence return false);
                return false;
        }
    }
    return true;
}
bool IsBipartite(vector<vector<int>> &adj)
{
    int n = adj.size();
    vector<int> color(n, -1); //-1 denotes not coloured yet, 1st colour : 0, 2nd colour : 1;
    for (int i = 0; i < n; i++)
    {
        if (color[i] == -1)
        {
            if (BFS(i, adj, color) == false) // If any one of the component is not bipartite then overall graph is also not bi-partite.
                return false;
        }
    }
    return true;
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
/*
Bipartite graph: Graph can be colored using 2 colors such that no two adjacent nodes have same colour.
==> Linear-graph (having no cycle) ==> are always bipartitie.
==> Any graph with even length cycle can also be bi-partite.
==> Any graph with odd length cycle can't be bi-paritite.

Intuition : Simple brute force traversal (BFS) And try to colour it (If can't colour just return false else true);

Here don't need to keep visited array (You can keep but it will be redundant);
(As color array will itself behave as visited array, because if it is not coloured means not visited else visited).
Time complexity / Space complexity : Same as BFS traversal;
*/
/*
GFG Link : https://practice.geeksforgeeks.org/problems/bipartite-graph/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
Just see latest submission ==> Submitted IsBiPartite()
Leetcode Link : https://leetcode.com/problems/is-graph-bipartite/ 
Just see latest subumission ==> Submitted IsBiPartite()
*/