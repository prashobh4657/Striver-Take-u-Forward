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
int tabulation_space_optimisation(int target, vector<int> &coins)
{
    int n = coins.size();
    // vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    vector<int> prev(target + 1), curr(target + 1);
    for (int j = 0; j <= target; j++) // Base case; (idx==0) (Fill first row);
        curr[j] = ((j % coins[0]) == 0);
    prev = curr;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= target; j++)
        {
            int not_take = prev[j];
            int take = 0;
            if (coins[i] <= j)
                take = curr[j - coins[i]];
            curr[j] = not_take + take;
        }
        prev = curr;
    }
    return curr[target];
}
int tabulation(int target, vector<int> &coins)
{
    int n = coins.size();
    vector<vector<int>> dp(n, vector<int>(target + 1, 0));
    for (int j = 0; j <= target; j++) // Base case; (idx==0) (Fill first row);
        dp[0][j] = ((j % coins[0]) == 0);

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= target; j++)
        {
            int not_take = dp[i - 1][j];
            int take = 0;
            if (coins[i] <= j)
                take = dp[i][j - coins[i]];
            dp[i][j] = not_take + take;
        }
    }
    return dp[n - 1][target];
}
int solve_memoize(int idx, int target, vector<int> &coins, vector<vector<int>> &dp) // TC : O(n*target), SC : O(n*target) + O(target) (auxilary stack space);
{
    if (idx == 0)
        return dp[idx][target] = ((target % coins[0]) == 0);
    if (dp[idx][target] != -1)
        return dp[idx][target];
    int not_take = solve_memoize(idx - 1, target, coins, dp);
    int take = 0;
    if (coins[idx] <= target)
        take = solve_memoize(idx, target - coins[idx], coins, dp); // Pass idx only;
    return dp[idx][target] = not_take + take;
}
int solve(int idx, int target, vector<int> &coins) // TC : O(2^n) (greater than >>2^n), SC : O(n) (greater than >n) (Since it may happen standing at same index for a long time hence time and space will be huge in that case, ==> SC>>O(n) or O(target) )
{
    if (idx == 0)
        return ((target % coins[0]) == 0);
    int not_take = solve(idx - 1, target, coins);
    int take = 0;
    if (coins[idx] <= target)
        take = solve(idx, target - coins[idx], coins); // Pass idx only;
    return not_take + take;
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> coins(n);
    cin >> coins;
    int target;
    cin >> target;
    cout << solve(n - 1, target, coins) << endl;
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    cout << solve_memoize(n - 1, target, coins, dp) << endl;
    cout << tabulation(target, coins) << endl;
    cout << tabulation_space_optimisation(target, coins) << endl;
    return 0;
}
/*
-> Any element can be used any no. of times.
-> Base case return 1 or 0 if condition met or not.
-> Sum all possibilities and return.
*/
/*
Coding Ninja Link : https://www.codingninjas.com/codestudio/problems/ways-to-make-coin-change_630471?leftPanelTab=0
==> Submitted all 4 functions (All functions are working correctly); (Don't see there ==> just see code here)

Leetcode Link : https://leetcode.com/problems/coin-change-ii/
==> Just see latest submission (tabulation_space_optimisation() submitted);

GFG Link : https://practice.geeksforgeeks.org/problems/coin-change2448/1?utm_source=gfg&utm_medium=article utm_campaign=bottom_sticky_on_article
==> Just see latest submission (tabulation_space_optimisation() submitted)
*/
