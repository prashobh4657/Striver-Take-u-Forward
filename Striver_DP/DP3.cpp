#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
int tabulation_space_optimised(int n, vector<int> &h)
{
    vector<int> dp(n, -1);
    if (n == 0)
        return 0;
    if (n == 1)
        return abs(h[1] - h[0]);
    int prev1 = abs(h[1] - h[0]);
    int prev2 = 0;
    int curr;
    for (int i = 2; i <= n; i++) // prev2 prev1 curr
    {
        curr = min(prev1 + abs(h[i] - h[i - 1]), prev2 + abs(h[i] - h[i - 2]));
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}
int tabulation(int n, vector<int> &h)
{
    vector<int> dp(n, -1);
    dp[0] = 0;
    dp[1] = abs(h[1] - h[0]);
    for (int i = 2; i <= n; i++)
        dp[i] = min(dp[i - 1] + abs(h[i] - h[i - 1]), dp[i - 2] + abs(h[i] - h[i - 2]));
    return dp[n];
}
int frog_jump_memoize(int n, vector<int> &h, vector<int> &dp)
{
    if (n == 0)
        return dp[0] = 0;
    if (n == 1)
        return dp[1] = abs(h[1] - h[0]);
    if (dp[n] != -1)
        return dp[n];
    return dp[n] = min(frog_jump_memoize(n - 1, h, dp) + abs(h[n] - h[n - 1]), frog_jump_memoize(n - 2, h, dp) + abs(h[n] - h[n - 2]));
}
int frog_jump(int n, vector<int> &h)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return abs(h[1] - h[0]);
    return min(frog_jump(n - 1, h) + abs(h[n] - h[n - 1]), frog_jump(n - 2, h) + abs(h[n] - h[n - 2]));
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << frog_jump(n - 1, a) << endl;
    vector<int> dp(n, -1);
    cout << frog_jump_memoize(n - 1, a, dp) << endl;
    cout << tabulation(n - 1, a) << endl;
    cout << tabulation_space_optimised(n - 1, a) << endl;
    return 0;
}
// All functions return the cost to reach nth index;
// Since we need to reach (n-1)th index hence call for n-1 is made in main();

// Problem link : https://www.codingninjas.com/codestudio/problem-details/frog-jump_3621012
// Submission : same as tabulation_space_optimised() function in this cpp file;
