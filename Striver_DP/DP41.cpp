#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
int LIS_memoize(int idx, vector<int> &a, int prev, vector<vector<int>> &dp) // TC : O(n*n), SC:O(n*n) (2D dp vector) + O(n) (recursion stack space);
{
    if (idx == a.size())
        return 0;
    if (dp[idx][prev + 1] != -1)
        return dp[idx][prev + 1];

    int not_take = LIS_memoize(idx + 1, a, prev, dp);
    int take = INT_MIN;
    if (prev == -1 || a[prev] < a[idx])
        take = 1 + LIS_memoize(idx + 1, a, idx, dp);
    return dp[idx][prev + 1] = max(take, not_take); // don't store in dp[idx][prev] as prev can be -1 hence just a shift of +1;
}
int LIS(int idx, vector<int> &a, int prev) // TC : O(2^n), SC:O(n);
{
    // Hypothesis : Return answer for array from index=idx to last and a[prev] is included in LIS till now.
    if (idx == a.size())
        return 0;
    int not_take = LIS(idx + 1, a, prev); // Not take;
    int take = INT_MIN;
    if (prev == -1 || a[prev] < a[idx]) // Then only we can take;
        take = 1 + LIS(idx + 1, a, prev);
    return max(take, not_take);
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> a(n);
    cout << LIS(0, a, -1);
    vector<vector<int>> dp(n, vector<int>(n + 1, -1)); // idx vary from [0..n-1] and prev vary from [-1....n-1]=>coordinate shift by 1==>[0...n] ==> n+1 size ===> DP[N][N+1];
    cout << LIS_memoize(0, a, -1, dp);
    return 0;
}
/*
Problem : Length of Longest Increasing Subsequence

Brute force : Generate all subsequences and then filter out increasing ones and return maximum length among them. ==> O(2^n)
Recurrence :
 1. express in terms of index;
 2. explore all possibilties (here either take it or not take it into the subsequence);
 3. return maximum(take,not_take);
 4. base case;

 Also since we are at index=idx, and if a[idx] is smaller than prev then definitely we can't take it.
 Hence keep a variable prev also as a parameter.
 See code.
*/
/*
Leetcode Link : https://leetcode.com/problems/longest-increasing-subsequence/description/
==> See Submission : Dec 25, 2022 11:53  ==> Just submitted LIS_memoize()  ==> TLE (Later solve using O(nlogn));
GFG Link : https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence-1587115620/1
==> See Submission : 2022-12-25 11:55:42	Time Limit Exceeded	cpp	15 / 111  ==> Just submitted LIS_memoize()  ==> TLE (Later solve using O(nlogn));


He submitted on Coding ninja ==> Got Runtime error ==> as N constraints are upto 10^5 (and that much size of 2D vector is not posible to construct);
                             ==> In further we will learn O(nlogn) solution
*/
