#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int space_optimisation_in_better_tabulation(vector<int> &a)
{
    int n = a.size();
    vector<int> front2(2, 0); // dp[idx+2] ==> front2
    vector<int> front1(2, 0); // dp[idx+1] ==> front1
    vector<int> curr(2, 0);   // dp[idx] ==> curr;
    for (int idx = n - 1; idx >= 0; idx--)
    {
        curr[1] = max(-a[idx] + front1[0], 0 + front1[1]);
        curr[0] = max(a[idx] + front2[1], 0 + front1[0]);
        front2 = front1;
        front1 = curr;
    }
    return curr[1];
}
int better_tabulation(vector<int> &a) // Slight observation in tabulation code itself (Only if or else will be executed ==> Inner loop can be removed);
{
    int n = a.size();
    vector<vector<int>> dp(n + 2, vector<int>(2, 0)); // n+2 because trying to access dp[idx+2]; (Fill matrix with zero);
    for (int idx = n - 1; idx >= 0; idx--)
    {
        dp[idx][1] = max(-a[idx] + dp[idx + 1][0], 0 + dp[idx + 1][1]);
        dp[idx][0] = max(a[idx] + dp[idx + 2][1], 0 + dp[idx + 1][0]);
    }
    return dp[0][1];
}
int tabulation_space_optimisation(vector<int> &a)
{
    return 0;
    // Since here dp[idx] depends on dp[idx+1] and dp[idx+2];
    // So we will not discuss that here.
    // Let's discuss better tabulation;
}
int tabulation(vector<int> &a)
{
    int n = a.size();
    vector<vector<int>> dp(n + 2, vector<int>(2, 0)); // n+2 because trying to access dp[idx+2]; (Fill matrix with zero);
    for (int idx = n - 1; idx >= 0; idx--)
    {
        int profit = 0;
        for (int buy = 0; buy <= 1; buy++)
        {
            if (buy)
                profit = max(-a[idx] + dp[idx + 1][0], 0 + dp[idx + 1][1]);
            else
                profit = max(a[idx] + dp[idx + 2][1], 0 + dp[idx + 1][0]);
            dp[idx][buy] = profit;
        }
    }
    return dp[0][1];
}
int solve_memoize(int idx, bool buy, vector<int> &a, vector<vector<int>> &dp)
{
    if (idx >= a.size())
    {
        return 0;
    }
    if (dp[idx][buy] != -1)
        return dp[idx][buy];
    int profit = 0;
    if (buy)
        profit = max(-a[idx] + solve_memoize(idx + 1, 0, a, dp), 0 + solve_memoize(idx + 1, 1, a, dp));
    else
        profit = max(a[idx] + solve_memoize(idx + 2, 1, a, dp), 0 + solve_memoize(idx + 1, 0, a, dp));
    return dp[idx][buy] = profit;
}
int solve(int idx, bool buy, vector<int> &a)
{
    if (idx >= a.size())
    {
        return 0;
    }
    int profit = 0;
    if (buy)
        profit = max(-a[idx] + solve(idx + 1, 0, a), 0 + solve(idx + 1, 1, a));
    else
        profit = max(a[idx] + solve(idx + 2, 1, a), 0 + solve(idx + 1, 0, a)); //======>If selled then directly go to idx+2 (THIS IS CHANGE);
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
    cout << solve(0, true, a) << endl;
    vector<vector<int>> dp(n, vector<int>(2, -1)); // idx can have values from [0..n-1] and buy [0 or 1];
    cout << solve_memoize(0, true, a, dp) << endl;
    cout << tabulation(a) << endl;
    cout << tabulation_space_optimisation(a) << endl;
    cout << better_tabulation(a) << endl;
    cout << space_optimisation_in_better_tabulation(a) << endl;
    return 0;
}
/*
Buy and sell stocks with cooldown
Here can't buy right after sell.
*/
// Code is exactly same as buy and sell stock 2
// Only single change is there ===> See highlighted change.
// Also since here idx+2 can happen hence we can reach at index n or n+1 hence change base condition like idx>=a.size();
/*
Leetcode link : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/
==> All functions are submitted (All are working correctly); (Verified);
==> Just read see this cpp file itself for codes.
*/
