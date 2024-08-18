#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int four_variable_solution(vector<int> &a)
{
    // Observer tabulation_space_optmisation code in that buy loop when buy=0 ==> if part executes else "else" part executes;
    // Let next[0]=ahead_not_buy, next[1]=ahead_buy;
    // Let curr[0]=curr_not_buy,curr[1]=curr_buy;
    int n = a.size();
    int ahead_not_buy, ahead_buy;
    ahead_not_buy = ahead_buy = -1;
    int curr_not_buy, curr_buy;
    curr_not_buy = curr_buy = 0;

    // Corresponding to line next=curr;
    ahead_not_buy = curr_not_buy;
    ahead_buy = curr_buy;

    for (int idx = n - 1; idx >= 0; idx--)
    {
        curr_buy = max(-a[idx] + ahead_not_buy, 0 + ahead_buy);    // buy=0 iteration;
        curr_not_buy = max(a[idx] + ahead_buy, 0 + ahead_not_buy); // buy=1 iteration;

        // Corresponding to line next=curr;
        ahead_not_buy = curr_not_buy;
        ahead_buy = curr_buy;
    }
    return curr_buy;
}
int tabulation_space_optimisation(vector<int> &a) // TC : O(2N), SC :O(1) (2 size vector = O(1));
{
    // Clearly dp[idx][buy] only depend on dp[idx+1][buy];
    int n = a.size();
    vector<int> next(2, -1);
    vector<int> curr(2, -1);
    curr[0] = curr[1] = 0;
    next = curr;
    for (int idx = n - 1; idx >= 0; idx--)
    {
        int profit = 0;
        for (int buy = 0; buy <= 1; buy++)
        {
            // Copy the recurrence here; (and do slight changes);
            if (buy)
                profit = max(-a[idx] + next[0], 0 + next[1]);
            else
                profit = max(a[idx] + next[1], 0 + next[0]);
            curr[buy] = profit;
        }
        next = curr;
    }
    return curr[1];
}
int tabulation(vector<int> &a) // TC : O(2N), SC :O(2N)
{
    int n = a.size();
    vector<vector<int>> dp(n + 1, vector<int>(2, -1));
    // Making dp of size n+1 because of base case
    dp[n][0] = dp[n][1] = 0; // Base case;

    // Since we call for solve(0,true) from main hence idx go from 0 --> n-1 hence apply loop from n-1 to 0;
    // similarly apply loop for buy; Since dp[idx][buy] depends on dp[idx+1][buy] hence buy loop can be from 0 to 1 or 1 to 0 (anyway is fine);
    for (int idx = n - 1; idx >= 0; idx--)
    {
        int profit = 0;
        for (int buy = 0; buy <= 1; buy++)
        {
            // Copy the recurrence here; (and do slight changes);
            if (buy)
                profit = max(-a[idx] + dp[idx + 1][0], 0 + dp[idx + 1][1]);
            else
                profit = max(a[idx] + dp[idx + 1][1], 0 + dp[idx + 1][0]);
            dp[idx][buy] = profit;
        }
    }
    return dp[0][1];
}
int solve_memoize(int idx, bool buy, vector<int> &a, vector<vector<int>> &dp) // TC : O(2N), SC :O(2N) + O(N)(recursion stack space);
{
    if (idx == a.size())
    {
        return 0;
    }
    if (dp[idx][buy] != -1)
        return dp[idx][buy];
    int profit = 0;
    if (buy)
        profit = max(-a[idx] + solve_memoize(idx + 1, 0, a, dp), 0 + solve_memoize(idx + 1, 1, a, dp));
    else
        profit = max(a[idx] + solve_memoize(idx + 1, 1, a, dp), 0 + solve_memoize(idx + 1, 0, a, dp));
    return dp[idx][buy] = profit;
}
int solve(int idx, bool buy, vector<int> &a) // TC : O(2^n), SC : O(n);
{
    if (idx == a.size())
    {
        return 0;
    }

    int profit = 0;
    if (buy) // If this stock can be bought;
    {
        profit = max(-a[idx] + solve(idx + 1, 0, a), 0 + solve(idx + 1, 1, a));
        // Either buy or not buy (Take maximum of it);
        // 1. If buy then profit added by -a[idx] (as we spent money to buy it) and pass buy=0 (as now further nothing can be bought);
        // 2. If not buy then profit added by 0 and pass buy=1 (since buy=1 and at this step also we not bought anything hence further can be bought);
    }
    else // If this stock can't be bought;
    {
        profit = max(a[idx] + solve(idx + 1, 1, a), 0 + solve(idx + 1, 0, a));
        // If buy=false hence at this idx either we can sell it or can't sell it;
        // 1. If sell then profit added by a[idx] and pass buy=1 (as now everything is clear till now hence new stock can be bought further);
        // 2. If not sell then profit added by 0 and pass buy=same as now = 0 (buy was 0 and at this step also we not sell anything hence further anything can't be bought);
    }
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
    cout << four_variable_solution(a) << endl;
    return 0;
}
/*
Here you can buy and sell as many times as you want.
Also you can't buy until you solve previous.
Your sequence of operation must be of type : Buy Sell Buy Sell...... and so on.

Here a lot of ways possbile : Hence we will try out all of them ==> Recursion
==> f(idx,buy)
      ==> (Denotes maximum profit if we start buying at index=idx);
     (on index=idx we are making decision, buy variable denotes whether is it possible to buy stock on index=idx);
Now see code;
*/
/*
Leetcode Link : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
===> I executed all functions on given testcases of leetcode all are working.
===> Just see latest submission : Just submitted four_variable_solution()  (Just revise this cpp to reach to that solution);

GFG Link : https://practice.geeksforgeeks.org/problems/buy-stock-2/1?problemStatus=unsolved&page=1&sortBy=newest&query=problemStatusunsolvedpage1sortBynewest
===> Just see latest submission (Exactly same as leetcode);
*/