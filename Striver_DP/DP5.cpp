#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
int tabulation_space_optimisation(vector<int> &a) // prev2 prev1 curr;
{
    int n=a.size();
    int prev1 = a[0];
    int prev2 = 0;
    int curr  = a[0]; //Currently at i=0 hence a[0];
    for (int i = 1; i < n; i++)
    {
        int not_take = prev1;
        int take = a[i];
        if (i - 2 >= 0)
            take += prev2;
        curr = max(take, not_take);
        // cout << curr << " ";
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}
int tabulation(vector<int> &a)
{
    int n=a.size();
    vector<int> dp(n, -1);
    dp[0] = a[0];
    for (int i = 1; i < n; i++)
    {
        int not_take = dp[i - 1];
        int take = a[i];
        if (i - 2 >= 0)
            take += dp[i - 2]; // actually take = a[i]+dp[i-2];   (But if dp[i-2] is not exist then it should be 0);
        dp[i] = max(take, not_take);
    }
    return dp[n-1];
}
int maximumNonAdjacentSum_memoize(int n, vector<int> a, vector<int> &dp)
{
    if (n < 0)
        return 0;
    if (n == 0)
        return dp[0] = a[0];
    if (dp[n] != -1)
        return dp[n];
    return dp[n] = max(maximumNonAdjacentSum_memoize(n - 1, a, dp), maximumNonAdjacentSum_memoize(n - 2, a, dp) + a[n]);
}
int maximumNonAdjacentSum(int n, vector<int> a) // Hypothesis : return maximum_Non_Adjacent_Sum considering array from index=0 to n;
{
    if (n < 0)
        return 0;
    if (n == 0)
        return a[0];

    // Calling n-1 means not pick current;
    // Calling n-2 means picked this element (and can't pick n-1 hence don't go there) and directly go to n-2;
    return max(maximumNonAdjacentSum(n - 1, a), maximumNonAdjacentSum(n - 2, a) + a[n]);
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << maximumNonAdjacentSum(n - 1, a) << endl;
    vector<int> dp(n, -1);
    cout << maximumNonAdjacentSum_memoize(n - 1, a, dp) << endl;
    for (int i = 0; i < n; i++)
        cout << dp[i] << " ";
    cout << endl;
    cout << tabulation(a) << endl;
    cout << tabulation_space_optimisation(a) << endl;
    return 0;
}
// Leetcode problem link : https://leetcode.com/problems/house-robber/description/
// GFG Problem link : https://practice.geeksforgeeks.org/problems/stickler-theif-1587115621/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
// Coding ninja Problem link : https://www.codingninjas.com/codestudio/problems/maximum-sum-of-non-adjacent-elements_843261?leftPanelTab=0
// Just see latest Submission in each of these links which have this function used : "tabulation_space_optimisation(vector<int> &a)" in this cpp file
