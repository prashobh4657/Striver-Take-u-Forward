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
    {
        if (j % coins[0] == 0)
            curr[j] = j / coins[0];
        else
            curr[j] = 1e9;
    }
    prev = curr;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= target; j++)
        {
            int not_take = 0 + prev[j];
            int take = INT_MAX;
            if (coins[i] <= j)
                take = 1 + curr[j - coins[i]];
            curr[j] = min(not_take, take);
        }
        prev = curr;
    }
    return curr[target];
}
int tabulation(int target, vector<int> &coins)
{
    int n = coins.size();
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    for (int j = 0; j <= target; j++) // Base case; (idx==0) (Fill first row);
    {
        if (j % coins[0] == 0)
            dp[0][j] = j / coins[0];
        else
            dp[0][j] = 1e9;
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= target; j++)
        {
            int not_take = 0 + dp[i - 1][j];
            int take = INT_MAX;
            if (coins[i] <= j)
                take = 1 + dp[i][j - coins[i]];
            dp[i][j] = min(not_take, take);
        }
    }
    return dp[n - 1][target];
}
int solve_memoize(int idx, int target, vector<int> &coins, vector<vector<int>> &dp) // TC : O(n*target), SC : O(n*target) + O(target)
{
    if (idx == 0)
    {
        if (target % coins[idx] == 0)
            return target / coins[idx];
        return 1e9;
    }
    if (dp[idx][target] != -1)
        return dp[idx][target];
    int not_take = 0 + solve_memoize(idx - 1, target, coins, dp);
    int take = INT_MAX;
    if (coins[idx] <= target)
        take = 1 + solve_memoize(idx, target - coins[idx], coins, dp); // Pass idx only;
    return dp[idx][target] = min(not_take, take);
}
int solve(int idx, int target, vector<int> &coins) // TC : O(2^n) (greater than >>2^n), SC : O(n) (greater than >n) (Since it may happen standing at same index for a long time hence time and space will be huge in that case);
{
    if (idx == 0)
    {
        if (target % coins[idx] == 0)
            return target / coins[idx];
        return 1e9;
    }
    int not_take = 0 + solve(idx - 1, target, coins);
    int take = INT_MAX;
    if (coins[idx] <= target)
        take = 1 + solve(idx, target - coins[idx], coins); // Pass idx only;
    return min(not_take, take);
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
    // If value_printed>=1e9 means answer is -1;
    return 0;
}
/*
Greedy Solution :
    1. sort the denomination vector and traverse it reverse way.
    2. check target/d[i] = p;  now take p instances of denomination[i] and now target=target-p*denomination[i];
Where will greedy solution fail ?
target = 11, coins[] = {9, 6, 5, 1}
As per greedy : {1,5,6,9} ==> First take coin 9 now target=2 hence go to 6 ==> 2/6=0 hence don't take 6 similarly don't take 5
                              and finally 2/1 = 2 (2 instances of coin 1) hence overall {1,1,9}=11. But this is wrong actually.
Actual solution is 2 : (5,6)=11 (2 coins required);
For denomination : {1, 2, 5, 10, 20, 50, 100, 500, 1000}  (Greedy solution will work);  (In gfg article it is mentioned) (https://www.geeksforgeeks.org/greedy-algorithm-to-find-minimum-number-of-coins/)

// In case of infinite supply or multiple use : during making recursive call of take then pass idx itself (not idx-1);

// Coding ninja link : https://www.codingninjas.com/codestudio/problems/minimum-elements_3843091?leftPanelTab=0&campaign=striver_dpseries&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dpseries
// Submitted : solve() {TLE} ,solve_memoize(),tabulation(),tabulation_space_optimisation() ({Accepted});

// Leetcode Link : https://leetcode.com/problems/coin-change/description/
// Just see latest submission (tabulation_space_optimisation() submitted);

// GFG Link : https://practice.geeksforgeeks.org/problems/number-of-coins1824/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
// Just see latest submission (tabulation_space_optimisation() submitted);
*/
