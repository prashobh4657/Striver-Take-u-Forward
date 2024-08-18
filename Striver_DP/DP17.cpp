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
    vector<int> curr(k + 1, 0);
    for (int j = 0; j <= k; j++) // Base case (First row);
    {
        if (j == 0 && a[0] == 0)
            curr[j] = 2;
        else if (j == 0 || j == a[0])
            curr[j] = 1;
        else
            curr[j] = 0;
    }
    vector<int> prev(k + 1, 0);
    prev = curr;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            int not_take = prev[j];
            int take = 0;
            if (a[i] <= j)
                take = prev[j - a[i]];
            curr[j] = (not_take + take);
        }
        prev = curr;
    }
    return curr[k];
}
int tabulation(vector<int> &a, int k)
{
    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(k + 1, 0)); // n vary from [0..n-1] and k[0..k] ==> dp[n][k+1];
    for (int j = 0; j <= k; j++)                      // Base case (First row);
    {
        if (j == 0 && a[0] == 0)
            dp[0][j] = 2;
        else if (j == 0 || j == a[0])
            dp[0][j] = 1;
        else
            dp[0][j] = 0;
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            int not_take = dp[i - 1][j];
            int take = 0;
            if (a[i] <= j)
                take = dp[i - 1][j - a[i]];
            dp[i][j] = (not_take + take);
        }
    }
    return dp[n - 1][k];
}
int solve_memoize(int idx, vector<int> &a, int k, vector<vector<int>> &dp)
{
    if (idx == 0)
    {
        if (k == 0 && a[0] == 0) // Since that is 0 hence either take it or not take it both ways are correct hence return 2;
            return 2;
        if (k == 0 || k == a[0])
            return 1;
        return 0;
    }
    if (dp[idx][k] != -1)
        return dp[idx][k];
    int not_take = solve_memoize(idx - 1, a, k, dp);
    int take = 0;
    if (a[idx] <= k)
        take = solve_memoize(idx - 1, a, k - a[idx], dp);
    return dp[idx][k] = (not_take + take);
}
int solve(int idx, vector<int> &a, int k)
{
    if (idx == 0)
    {
        if (k == 0 && a[0] == 0) // Since that is 0 hence either take it or not take it both ways are correct hence return 2;
            return 2;
        if (k == 0 || k == a[0])
            return 1;
        return 0;
    }
    int not_take = solve(idx - 1, a, k);
    int take = 0; // logically 0 as won't affect answer; (If a[idx]>k)
    if (a[idx] <= k)
        take = solve(idx - 1, a, k - a[idx]);
    return not_take + take;
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
    cout << solve(n - 1, a, k) << endl;
    vector<vector<int>> dp(n, vector<int>(k + 1, -1)); // n vary from [0..n-1] and k[0..k] ==> dp[n][k+1]; (Here it can't be of bool type as -1 can't be stored into that);
    cout << solve_memoize(n - 1, a, k, dp) << endl;
    cout << tabulation(a, k) << endl;
    cout << tabulation_space_optimisation(a, k) << endl;
    return 0;
}
/*
Coding ninja link : https://www.codingninjas.com/codestudio/problems/number-of-subsets_3952532?leftPanelTab=0 
==> Submitted solve() (TLE), solve_memoize(),tabulation(),tabulation_space_optimisation() {Accepted};
    (No need to see them actually ==> it gurantees that code written in above cpp file are absolutely correct);
*/