#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int other_solution(vector<int> &a)
{
    /* dp[N*4] solution == this we will discuss;
       4 variable solution (actually it should be 12 variable solution as in tabulation space optimisation we are using 12 variables)
       but yes there exist 4 variable solution which is not intuitive (hence should not tell in interview as well);
    */
    /*
     2D DP Solution;
     f(ind,transaction) //transaction denotes index;
     Instead of keeping buy variable which tells whether to buy or not; We can control that thing using cap only
     by increasing cap range that for n=2, cap will vary from 0 to 3
     denotes Buy(0) Sell(1) Buy(2) sell(3) index=4(end)  ==> Even index = buy and odd index =sell.

     f(idx,trasaction)  //Recurrence; (Further you can do memoization,tabulation for this as well);
     {
       if(idx==n||transaction==4)return 0;
       if(transaction%2==0) //buy
       max(-a[idx]+f(idx+1,transaction), 0 + f(idx+1,transaction));
       else
       max(a[idx]+f(idx+1,transaction+1),0+f(idx+1,transaction);
     }
    */
    // We will not follow these solutions as of now.
    return 0;
}
int tabulation_space_optimisation(vector<int> &a) // TC : O(N*2*3), SC :O(1) (6 size 2D vector);
{
    // Clearly dp[idx][buy][cap] only depend on dp[idx+1][buy][cap];
    int n = a.size();
    vector<vector<int>> next(2, vector<int>(3, 0));
    vector<vector<int>> curr(2, vector<int>(3, 0));
    next = curr;
    for (int idx = n - 1; idx >= 0; idx--)
    {
        int profit = 0;
        for (int buy = 0; buy <= 1; buy++)
        {
            for (int cap = 1; cap <= 2; cap++) // Imp : Here start from cap=1 (otherwise error also cap=0 is in base case so cap must be from 1 to 2 only);
            {
                // Copy the recurrence here; (and do slight changes);
                if (buy == 1)
                    curr[buy][cap] = max(-a[idx] + next[0][cap], 0 + next[1][cap]);
                else
                    curr[buy][cap] = max(a[idx] + next[1][cap - 1], 0 + next[0][cap]);
            }
        }
        next = curr;
    }
    return curr[1][2];
}
int tabulation(vector<int> &a) // TC : O(N*2*3), SC :O(N*2*3)
{
    int n = a.size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));
    // Making dp of size n+1 because of base case
    // Base case : dp[n] is 2d vector just must be zero completely; (idx==a.size());
    // Also when cap==0 then idx and buy can be anything then answer is zero;

    // You can write these two for-loops of base-cases or can't write (Because DP is already filled with 0 hence optional);
    for (int idx = 0; idx <= n - 1; idx++) // cap==0; return 0;
    {
        for (int buy = 0; buy <= 1; buy++)
            dp[idx][buy][0] = 0;
    }
    for (int buy = 0; buy <= 1; buy++) // if idx==a.size()=n return 0;
    {
        for (int cap = 0; cap <= 2; cap++)
            dp[n][buy][cap] = 0;
    }

    // Since we call for solve(0,1,2) from main hence idx go from 0 --> n-1 hence apply loop from n-1 to 0;
    // similarly buy from 1-->0 hence apply loop from 0 to 1;
    // similarly cap from 2-->0 hence apply loop from 0 to 2;
    for (int idx = n - 1; idx >= 0; idx--)
    {
        int profit = 0;
        for (int buy = 0; buy <= 1; buy++)
        {
            for (int cap = 1; cap <= 2; cap++) // Imp : Here start from cap=1 (otherwise error also cap=0 is in base case so cap must be from 1 to 2 only);
            {
                // Copy the recurrence here; (and do slight changes);
                if (buy == 1)
                    dp[idx][buy][cap] = max(-a[idx] + dp[idx + 1][0][cap], 0 + dp[idx + 1][1][cap]);
                else
                    dp[idx][buy][cap] = max(a[idx] + dp[idx + 1][1][cap - 1], 0 + dp[idx + 1][0][cap]);
            }
        }
    }
    return dp[0][1][2];
}
int solve_memoize(int idx, int buy, int cap, vector<int> &a, vector<vector<vector<int>>> &dp) // TC : O(N*2*3), SC :O(N*2*3) + O(N)(recursion stack space);
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
int solve(int idx, int buy, int cap, vector<int> &a) // TC : O(exponential), SC : O(n);(recursive stack space);
{
    if (cap == 0)
        return 0;
    if (idx == a.size())
        return 0;

    int profit = 0;
    if (buy == 1) // If this stock can be bought;
    {
        profit = max(-a[idx] + solve(idx + 1, 0, cap, a), 0 + solve(idx + 1, 1, cap, a));
        // Either buy or not buy (Take maximum of it);
        // 1. If buy, ==> cap will remain same (as transaction is not yet completed as only bought operation performed);
        // 2. If not buy ==> cap will remain same (as nothing happened at this idx);
    }
    else // If this stock can't be bought;
    {
        profit = max(a[idx] + solve(idx + 1, 1, cap - 1, a), 0 + solve(idx + 1, 0, cap, a));
        // If buy=false hence at this idx either we can sell it or can't sell it;
        // 1. If sell, ==> cap will decrease by 1 (1 transaction is performed);
        // 2. If not sell ==> cap will remain same (as nothing happened at this idx);
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
    cout << solve(0, 1, 2, a) << endl;
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1))); // idx can have values from [0..n-1] and buy [0 or 1] and cap can be [0 or 1 or 2];  ==> dp[N][2][3];
    cout << solve_memoize(0, 1, 2, a, dp) << endl;
    cout << tabulation(a) << endl;
    cout << tabulation_space_optimisation(a) << endl;
    cout << other_solution(a) << endl;
    return 0;
}

/*
Problem link : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
=>Here you can buy and sell at-most 2 times.
=>Also you can't buy until you solve previous.
=>Your sequence of operation must be of type : Buy Sell Buy Sell
=>Here a lot of ways possbile : Hence we will try out all of them ==> Recursion
==> f(idx,buy,cap)
      ==> (Denotes maximum profit if we start buying at index=idx);
          (on index=idx we are making decision, buy variable denotes whether is it possible to buy stock on index=idx);
          (cap denotes the maximum no. of transactions can be made);
Now see code;
*/

/*
Leetcode Link : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
===> I executed all functions on given testcases of leetcode all are working.
===> Just see latest submission : Just submitted tabulation_space_optimisation() (Just revise this cpp to reach to that solution);
GFG Link : https://practice.geeksforgeeks.org/problems/buy-and-sell-a-share-at-most-twice/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
===> Just see latest submission (Exactly same as leetcode);
*/
