#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int32_t main()
{
    fio;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj_matrix(n, vector<int>(n, 0));
    vector<vector<int>> adj_list(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj_matrix[x][y] = 1;
        adj_matrix[y][x] = 1;
        adj_list[x].push_back(y);
        adj_list[y].push_back(x);
    }

    cout << "Adjacency Matrix" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << adj_matrix[i][j] << " ";
        cout << endl;
    }

    cout << "Adjacency List" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << "--->";
        for (int j = 0; j < adj_list[i].size(); j++)
            cout << adj_list[i][j] << " ";
        cout << endl;
    }

    return 0;
}

// Assuming nodes are given in 0-based indexing;
