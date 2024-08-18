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

int tabulation_space_optimisation(vector<vector<int>> &v)
{
    int n = v.size();
    int m = v[0].size();
    vector<int> curr(m, 0);
    vector<int> prev(m, 0);
    for (int j = 0; j < m; j++) // Base case i==0;
        curr[j] = v[0][j];
    prev = curr;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int a = v[i][j] + prev[j];
            int b;
            if (j - 1 >= 0)
                b = v[i][j] + prev[j - 1];
            else
                b = -1e8;
            int c;
            if (j + 1 < m)
                c = v[i][j] + prev[j + 1];
            else
                c = -1e8;
            curr[j] = max({a, b, c});
        }
        prev = curr;
    }
    return *max_element(curr.begin(), curr.end());
}
int tabulation(vector<vector<int>> &v)
{
    int n = v.size();
    int m = v[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0)); // dp[i][j] denotes maximum path sum to reach [i,j] from any cell in 1st row;
    for (int j = 0; j < m; j++)                   // Base case i==0;
        dp[0][j] = v[0][j];
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int a = v[i][j] + dp[i - 1][j];
            int b;
            if (j - 1 >= 0)
                b = v[i][j] + dp[i - 1][j - 1];
            else
                b = -1e8;
            int c;
            if (j + 1 < m)
                c = v[i][j] + dp[i - 1][j + 1];
            else
                c = -1e8;
            dp[i][j] = max({a, b, c});
        }
    }
    return *max_element(dp[n - 1].begin(), dp[n - 1].end());
}
int solve_memoize(int i, int j, vector<vector<int>> &v, vector<vector<int>> &dp)
{
    int n = v.size();
    int m = v[0].size();
    if (j < 0 || j >= m)
        return -1e8;
    if (i == 0)
        return v[0][j];
    if (dp[i][j] != -1)
        return dp[i][j];

    int a = v[i][j] + solve_memoize(i - 1, j, v, dp);
    int b = v[i][j] + solve_memoize(i - 1, j - 1, v, dp);
    int c = v[i][j] + solve_memoize(i - 1, j + 1, v, dp);
    return dp[i][j] = max({a, b, c});
}
int solve(int i, int j, vector<vector<int>> &v) // return maximum path sum to reach (i,j) from any cell in the first row;   // TC :O(3^(mn) for each cell 3 possiblities)
{
    int n = v.size();
    int m = v[0].size();
    if (j < 0 || j >= m)
        return -1e8;
    if (i == 0)
        return v[0][j];

    int a = v[i][j] + solve(i - 1, j, v);
    int b = v[i][j] + solve(i - 1, j - 1, v);
    int c = v[i][j] + solve(i - 1, j + 1, v);
    return max({a, b, c});
}
int32_t main()
{
    fio;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cin >> v[i][j];
    }
    int mx = -1e8;
    for (int j = 0; j < m; j++)
        mx = max(mx, solve(n - 1, j, v));
    cout << mx << endl;

    vector<vector<int>> dp(n, vector<int>(m, -1));
    int mx1 = -1e8;
    for (int j = 0; j < m; j++)
        mx1 = max(mx1, solve_memoize(n - 1, j, v, dp));
    cout << mx1 << endl;

    cout << tabulation(v);
    cout << tabulation_space_optimisation(v);

    return 0;
}
/*
Here source (any point in first row) and destination (any point in last row) both are variable;

Coding Ninja Link : https://www.codingninjas.com/codestudio/problems/maximum-path-sum-in-the-matrix_797998?leftPanelTab=0
==> Just see latest 4 submissions : Submitted : solve() (TLE),solve_memoize(),tabulation(),tabulation_space_optimisation()({Accepted});
==> Don't submit these submissions on GFG,Leetcode;
Here dp[i][j] denotes maximum path sum to reach (i,j) from any cell in the 1st row;
--------------------------------------------------------------------------------------------------------------------------------------

Wonderful tabulation done by me. (Just revise these also as it is).
Leetcode link : https://leetcode.com/problems/minimum-falling-path-sum/  (Just see LQN 931)
==> That is intuitive tabulation (done by me) : dp[i][j] denotes maximum path sum from [i..j] to any cell in last row
    which is somewhat opposite of striver, but we can think its recursive structure also but don't do that now.
    That's enough.
GFG Link : https://practice.geeksforgeeks.org/problems/path-in-matrix3805/1
===> Exactly same submission as that of leetcode (Just changed min-->max);
-------------------------------------------------------------------------------------------------------------------------------------
*/