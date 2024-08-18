#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int tabulation_space_optimisation(vector<int> &a, int k)
{
    int n = a.size();
    vector<vector<int>> next(2, vector<int>(k + 1, 0));
    vector<vector<int>> curr(2, vector<int>(k + 1, 0));
    next = curr;
    for (int idx = n - 1; idx >= 0; idx--)
    {
        int profit = 0;
        for (int buy = 0; buy <= 1; buy++)
        {
            for (int cap = 1; cap <= k; cap++)
            {
                if (buy == 1)
                    curr[buy][cap] = max(-a[idx] + next[0][cap], 0 + next[1][cap]);
                else
                    curr[buy][cap] = max(a[idx] + next[1][cap - 1], 0 + next[0][cap]);
            }
        }
        next = curr;
    }
    return curr[1][k];
}
int tabulation(vector<int> &a, int k)
{
    int n = a.size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));
    for (int idx = 0; idx <= n - 1; idx++)
    {
        for (int buy = 0; buy <= 1; buy++)
            dp[idx][buy][0] = 0;
    }
    for (int buy = 0; buy <= 1; buy++)
    {
        for (int cap = 0; cap <= k; cap++)
            dp[n][buy][cap] = 0;
    }
    for (int idx = n - 1; idx >= 0; idx--)
    {
        int profit = 0;
        for (int buy = 0; buy <= 1; buy++)
        {
            for (int cap = 1; cap <= k; cap++)
            {
                if (buy == 1)
                    dp[idx][buy][cap] = max(-a[idx] + dp[idx + 1][0][cap], 0 + dp[idx + 1][1][cap]);
                else
                    dp[idx][buy][cap] = max(a[idx] + dp[idx + 1][1][cap - 1], 0 + dp[idx + 1][0][cap]);
            }
        }
    }
    return dp[0][1][2];
}
int solve_memoize(int idx, int buy, int cap, vector<int> &a, vector<vector<vector<int>>> &dp)
{
    if (cap == 0)
        return 0;
    if (idx == a.size())
        return 0;
    if (dp[idx][buy][cap] != -1)
        return dp[idx][buy][cap];
    int profit = 0;
    if (buy == 1)
        profit = max(-a[idx] + solve_memoize(idx + 1, 0, cap, a, dp), 0 + solve_memoize(idx + 1, 1, cap, a, dp));
    else
        profit = max(a[idx] + solve_memoize(idx + 1, 1, cap - 1, a, dp), 0 + solve_memoize(idx + 1, 0, cap, a, dp));
    return dp[idx][buy][cap] = profit;
}
int solve(int idx, int buy, int cap, vector<int> &a)
{
    if (cap == 0)
        return 0;
    if (idx == a.size())
        return 0;

    int profit = 0;
    if (buy == 1)
        profit = max(-a[idx] + solve(idx + 1, 0, cap, a), 0 + solve(idx + 1, 1, cap, a));
    else
        profit = max(a[idx] + solve(idx + 1, 1, cap - 1, a), 0 + solve(idx + 1, 0, cap, a));
    return profit;
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int k;
    cin >> k;
    cout << solve(0, 1, k, a) << endl;
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
    cout << solve_memoize(0, 1, k, a, dp) << endl;
    cout << tabulation(a, k) << endl;
    cout << tabulation_space_optimisation(a, k) << endl;
    return 0;
}

/*
At-most k transacations;
In DP37.cpp ==> Just replace 2---->K and 3---->k+1  (Actually in DP37.cpp cap=2 or k=2) ==> DP38.cpp
*/

/*
Leetcode Link : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
===> I executed all functions on given testcases of leetcode all are working.
===> Just see latest submission : Just submitted tabulation_space_optimisation() (Just revise this cpp to reach to that solution);
GFG Link : https://practice.geeksforgeeks.org/problems/maximum-profit4657/1 
===> Just see latest submission (Exactly same as leetcode);
*/