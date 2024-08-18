#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int tabulation_space_optimised(int n) // Time : O(N), Space : O(1);
{
    if (n == 0 || n == 1)
        return n;
    int prev1 = 1, prev2 = 0, curr;
    for (int i = 2; i <= n; i++) // dp[i] requires only dp[i-1] and dp[i-2]; That is prev1,prev2;
    {
        curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}
int tabulation(int n) // Time : O(n), Space : O(n);
{
    vector<int> dp(n + 1); // dp[i] denotes (i)th fibonacci;
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}
int recursive_memoize(int n, vector<int> &dp) // Time : O(n), Space : O(n) (Dp vector) + O(n)(recursive stack);
{
    if (n == 1 || n == 0)
        return dp[n] = n;
    if (dp[n] != -1)
        return dp[n];
    return dp[n] = recursive_memoize(n - 1, dp) + recursive_memoize(n - 2, dp);
}
int recursive(int n) // https://www.geeksforgeeks.org/time-complexity-recursive-fibonacci-program/#:~:text=Mathematically%20Fibonacci%20numbers%20can%20be%20written%20by%20the%20following%20recursive%20formula.&text=What%20this%20means%20is%2C%20the,to%20perform%20the%20previous%20addition.&text=but%20this%20is%20not%20the%20tight%20upper%20bound.
{
    if (n == 1 || n == 0)
        return n;
    return recursive(n - 1) + recursive(n - 2);
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    cout << recursive(n) << endl;
    vector<int> dp(n + 1, -1);
    cout << recursive_memoize(n, dp) << endl;
    cout << tabulation(n) << endl;
    cout << tabulation_space_optimised(n);
    return 0;
}

/*
GFG Link : https://practice.geeksforgeeks.org/problems/nth-fibonacci-number1335/1  (Just see latest submission)
*/
