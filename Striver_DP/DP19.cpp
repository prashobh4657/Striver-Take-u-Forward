#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int tabulation_space_optimisation(int W, vector<int> &weight, vector<int> &value)
{
    // dp[i] only depends on dp[i-1] (current row depends on previous row);
    int n = weight.size();
    vector<int> curr(W + 1, 0);
    vector<int> prev(W + 1, 0);
    for (int j = weight[0]; j <= W; j++) // first row;
        curr[j] = value[0];
    prev = curr;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            int not_take = 0 + prev[j];
            int take = INT_MIN;
            if (weight[i] <= j)
                take = value[i] + prev[j - weight[i]];
            curr[j] = max(take, not_take);
        }
        prev = curr;
    }
    return curr[W];
}
int tabulation(int W, vector<int> &weight, vector<int> &value)
{
    int n = weight.size();
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));
    for (int j = weight[0]; j <= W; j++) // Base case; (idx==0) (Fill first row);
        dp[0][j] = value[0];

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            int not_take = 0 + dp[i - 1][j];
            int take = INT_MIN;
            if (weight[i] <= j)
                take = value[i] + dp[i - 1][j - weight[i]];
            dp[i][j] = max(take, not_take);
        }
    }
    return dp[n - 1][W];
}
int solve_memoize(int idx, int W, vector<int> &weight, vector<int> &value, vector<vector<int>> &dp)
{
    if (idx == 0)
    {
        if (weight[0] <= W)
            return value[0];
        else
            return 0;
    }
    if (dp[idx][W] != -1)
        return dp[idx][W];
    int not_take = 0 + solve_memoize(idx - 1, W, weight, value, dp);
    int take = INT_MIN;
    if (weight[idx] <= W)
        take = value[idx] + solve_memoize(idx - 1, W - weight[idx], weight, value, dp);
    return dp[idx][W] = max(take, not_take);
}
int solve(int idx, int W, vector<int> &weight, vector<int> &value) // Returns answer for array [0..idx];
{
    if (idx == 0)
    {
        if (weight[0] <= W)
            return value[0];
        else
            return 0;
    }

    int not_take = 0 + solve(idx - 1, W, weight, value);
    int take = INT_MIN;
    if (weight[idx] <= W)
        take = value[idx] + solve(idx - 1, W - weight[idx], weight, value);
    return max(take, not_take);
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> value(n);
    for (int i = 0; i < n; i++)
        cin >> value[i];
    vector<int> weight(n);
    for (int i = 0; i < n; i++)
        cin >> weight[i];
    int W;
    cin >> W;
    cout << solve(n - 1, W, weight, value) << endl;
    vector<vector<int>> dp(n, vector<int>(W + 1, -1)); // n will vary from [0..n-1] and W [0...W] hence (W+1); ==>dp[n][W+1];
    cout << solve_memoize(n - 1, W, weight, value, dp) << endl;
    cout << tabulation(W, weight, value) << endl;
    cout << tabulation_space_optimisation(W, weight, value) << endl;
    return 0;
}

/*
Points discussed :
1. Why greedy will not work?
2. Explore all possibilities (take,not_take);

Coding ninja link : https://www.codingninjas.com/codestudio/problems/0-1-knapsack_920542?leftPanelTab=0
==> Just see latest 4 submissions ==> Submitted solve() (TLE), solve_memoize(),tabulation(),tabulation_space_optimisation() {Accepted};

GFG link : https://practice.geeksforgeeks.org/problems/0-1-knapsack-problem0945/1
==> Just see latest submission : 2022-12-26 17:24:24	Correct	cpp	1210 / 1210  ===> Tabulation() submitted;
*/
