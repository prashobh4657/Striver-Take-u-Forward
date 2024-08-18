#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
vector<int> LDS(vector<int> &a)
{
    int n = a.size();
    vector<int> dp(n, 1);
    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (a[j] < a[i])
                dp[i] = max(dp[i], 1 + dp[j]);
        }
    }
    // return *max_element(dp.begin(), dp.end());
    return dp;
}
vector<int> LIS(vector<int> &a)
{
    int n = a.size();
    vector<int> dp(n, 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] < a[i])
                dp[i] = max(dp[i], 1 + dp[j]);
        }
    }
    // return *max_element(dp.begin(), dp.end());
    return dp;
}
int LBS(vector<int> &a)
{
    int n = a.size();
    vector<int> dp1 = LIS(a); // dp1[i] denotes length of LIS (longest increasing subsequence) ending at index i;
    vector<int> dp2 = LDS(a); // dp2[i] denotes length of LDS (longest decreasing subsequence) start from index i;
    vector<int> dp(n);        // dp[i] denotes maximum length of bitonic sequence having peak of subsequence at index=i;
    for (int i = 0; i < n; i++)
        dp[i] = dp1[i] + dp2[i] - 1; //-1 because (it is counted twice in dp1[i] and dp2[i]);
    return *max_element(dp.begin(), dp.end());
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << LBS(a) << endl;
    return 0;
}

/*
GFG Link : https://practice.geeksforgeeks.org/problems/longest-bitonic-subsequence0824/1
==>Just see latest submission ==> LBS() function submitted
*/
