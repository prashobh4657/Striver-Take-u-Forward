#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
int tabulation_space_optimised(vector<int> &h, int k)
{
    // TC : O(NK)
    // SC : O(K)
    /*
        But this code is not required;
        For this, you can create a vector of size k ==> vector<int>z(k),
        in each iteration just remove the z[0] and push the curr into z;
        In this way list of k elements can be maintained.
        But if k tends to n then Space complexity tends to O(N);
    */
    return 0;
}
int tabulation(vector<int> &h, int k) // TC : O(NK), SP : O(N) (dp array)
{
    int n=h.size();
    vector<int> dp(n, -1);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
    {
        int temp = INT_MAX;
        for (int j = 1; j <= k; j++)
        {
            if (i - j >= 0)
                temp = min(temp, dp[i - j] + abs(h[i] - h[i - j]));
        }
        dp[i] = temp;
    }
    return dp[n-1];
}
int frog_jump_memoize(int n, vector<int> &h, vector<int> &dp, int k) // TC : O(NK), SP : O(N) (dp array) + O(N) (recursive stack);
{
    if (n == 0)
        return dp[0] = 0;
    int ans = INT_MAX;
    for (int i = 1; i <= k; i++)
    {
        if (n - i >= 0)
            ans = min(ans, frog_jump_memoize(n - i, h, dp, k) + abs(h[n] - h[n - i]));
    }
    return dp[n] = ans;
}
int frog_jump(int n, vector<int> &h, int k)
{
    if (n == 0)
        return 0;
    int ans = INT_MAX;
    for (int i = 1; i <= k; i++)
    {
        if (n - i >= 0)
            ans = min(ans, frog_jump(n - i, h, k) + abs(h[n] - h[n - i]));
    }
    return ans;
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    int k;
    cin >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << frog_jump(n - 1, a, k) << endl;
    vector<int> dp(n, -1);
    cout << frog_jump_memoize(n - 1, a, dp, k) << endl;
    cout << tabulation(a, k) << endl;
    // cout << tabulation_space_optimised(a, k) << endl;
    return 0;
}
// All functions return the cost to reach nth index;
// Since we need to reach (n-1)th index hence call for n-1 is made in main();
// GFG Link : https://www.geeksforgeeks.org/problems/minimal-cost/1 : (Just see latest submission) 
