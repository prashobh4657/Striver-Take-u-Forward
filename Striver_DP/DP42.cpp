#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int tabulation_space_optimisation(vector<int> &a) // TC : O(N^2), SC : O(2N);
{
    // dp[idx] only depend on dp[idx+1];
    int n = a.size();
    vector<int> next(n + 1, 0);
    vector<int> curr(n + 1, 0);
    next = curr;
    for (int idx = n - 1; idx >= 0; idx--)
    {
        for (int prev = idx - 1; prev >= -1; prev--)
        {
            int not_take = 0 + next[prev + 1];
            int take = INT_MIN;
            if (prev == -1 || a[prev] < a[idx])
                take = 1 + next[idx + 1];
            curr[prev + 1] = max(not_take, take);
        }
        next = curr;
    }
    return curr[-1 + 1];
}
int tabulation(vector<int> &a)
{
    int n = a.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int idx = n - 1; idx >= 0; idx--)
    {
        for (int prev = idx - 1; prev >= -1; prev--)
        {
            int not_take = 0 + dp[idx + 1][prev + 1]; // not just prev, it is prev+1 (Coordinate shift);
            int take = INT_MIN;
            if (prev == -1 || a[prev] < a[idx])
                take = 1 + dp[idx + 1][idx + 1];
            dp[idx][prev + 1] = max(not_take, take);
        }
    }
    return dp[0][-1 + 1];
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << tabulation(a) << endl;
    cout << tabulation_space_optimisation(a);
    return 0;
}
/*
Tabulation :
1. Declare dp of same size as that of memoization. Dp[n][n+1];
   but here increase one more row ==>dp[n+1][n+1];  as dp[n]=0 (irrespective of prev) (base case);
2. idx==>called 0 from main() in recursion (hence in recursion 0 to n-1 calculation happened) hence apply loop opposite ==> n-1 to 0.
prev ==> called -1 from main() in recursion (hence in recursion -1 to n-1 calculation happened) hence apply loop opposite ==> n-1 to -1;
         but carefully ==> prev can't be from n-1 to -1==> it is actually from idx-1 to -1;
3. copy the recurrence (follow coordinate shift as well)(and do slight changes)
*/
/*
Leetcode Link : https://leetcode.com/problems/longest-increasing-subsequence/ 
See Submission : Dec 25, 2022 13:16 ==> Submitted tabulation_space_optimisation();
GFG Link : https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence-1587115620/1 
==> See Submission : 2022-12-25 13:18:15	Correct	cpp	111 / 111 (But now this submission mostly give TLE) 
==> See DP43.cpp (Binary search approach) 
*/
