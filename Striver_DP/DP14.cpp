#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
bool tabulation_space_optimisation(vector<int> &a, int k)
{
    int n = a.size();
    vector<bool> curr(k + 1, false);
    curr[0] = true; // first column values are true;
    if(a[0]<=k)curr[a[0]] = true;
    vector<bool> prev(k + 1, false);
    prev = curr; // first row done;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= k; j++) // Since we not filled 0th column manually hence taking it here into consideration;
        {
            if (j == 0) // first column all values are true;
                curr[j] = true;
            else
            {
                bool not_take = prev[j];
                bool take = false;
                if (a[i] <= j)
                    take = prev[j - a[i]];
                curr[j] = (not_take || take);
            }
        }
        prev = curr;
    }
    return curr[k];
}
bool tabulation(vector<int> &a, int k)
{
    int n = a.size();
    vector<vector<bool>> dp(n, vector<bool>(k + 1, false)); // n vary from [0..n-1] and k[0..k] ==> dp[n][k+1];

    for (int i = 0; i < n; i++) // Base case k==0 (Fill first column);
        dp[i][0] = true;

    /*Intead of this loop, we can just write ====> dp[0][a[0]]=true; (Simple observation);
        for (int j = 0; j <= k; j++) // Base case : Fill first row
        {
            if (a[0] == j) // a[0]==k (here j is our k);
                dp[0][j] = true;
        }
    */
    if(a[0]<=k) dp[0][a[0]] = true; // Mark j=a[0] in first row;  (If condition is slightly imp in case when a[0]>k then accessing dp[0][a[0]] is error) (Or else you apply loop as commented above which is more intuitive);
                                    // This if-condition is imp to pass the ans on leetcode. 
    // fill remaining matrix;
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            bool not_take = dp[i - 1][j];
            bool take = false;
            if (a[i] <= j)
                take = dp[i - 1][j - a[i]];
            dp[i][j] = (not_take || take);
        }
    }
    return dp[n - 1][k];
}
bool solve_memoize(int idx, vector<int> &a, int k, vector<vector<int>> &dp)
{
    if (k == 0)
        return true;
    if (idx == 0)
        return (a[0] == k);
    if (dp[idx][k] != -1)
        return dp[idx][k];
    bool not_take = solve_memoize(idx - 1, a, k, dp);
    bool take = false;
    if (a[idx] <= k)
        take = solve_memoize(idx - 1, a, k - a[idx], dp);
    return dp[idx][k] = (not_take || take);
}
bool solve(int idx, vector<int> &a, int k)
{
    if (k == 0)
        return true;
    if (idx == 0)
        return (a[0] == k);
    bool not_take = solve(idx - 1, a, k);
    bool take = false; // logically false as won't affect answer; (If a[idx]>k)
    if (a[idx] <= k)
        take = solve(idx - 1, a, k - a[idx]);
    return not_take || take;
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int k;
    cin >> k;
    cout << solve(n - 1, a, k) << endl;
    vector<vector<int>> dp(n, vector<int>(k + 1, -1)); // n vary from [0..n-1] and k[0..k] ==> dp[n][k+1]; (Here it can't be of bool type as -1 can't be stored into that);
    cout << solve_memoize(n - 1, a, k, dp) << endl;
    cout << tabulation(a, k) << endl;
    cout << tabulation_space_optimisation(a, k) << endl;
    return 0;
}
/*
Coding ninja link : https://www.codingninjas.com/codestudio/problems/subset-sum-equal-to-k_1550954?leftPanelTab=0
==> Just see latest 4 submissions ==> Submitted solve() (TLE), solve_memoize(),tabulation(),tabulation_space_optimisation() {Accepted};
    (No need to see them actually ==> it gurantees that code written in above cpp file are absolutely correct);
GFG link : https://practice.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1
==> Just see latest submission ===> Tabulation() submitted;
*/
