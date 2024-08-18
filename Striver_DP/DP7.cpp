#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int tabulation_space_optimisation(int n, vector<vector<int>> &v) // TC : O(N*4*3), SC : O(4);
{
    // By carefully observing for calculating dp[i][j] we just need dp[i-1][j] hence just previous row hence
    // no need to store entire 2D matrix, just store previous vector;
    vector<int> dp(3);
    dp[0] = max(v[0][1], v[0][2]);
    dp[1] = max(v[0][0], v[0][2]);
    dp[2] = max(v[0][0], v[0][1]);
    for (int i = 1; i < n; i++)
    {
        vector<int> temp(3, 0);
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (j != k)
                    temp[j] = max(temp[j], v[i][k] + dp[k]);
            }
        }
        dp = temp;
    }
    return max({dp[0], dp[1], dp[2]});
}
int tabulation(int n, vector<vector<int>> &v)
{
    vector<vector<int>> dp(n, vector<int>(3, -1)); // Same 2D vector we will try to build as that got build using recursion;
    // dp[i][j] denotes answer of array from index 0 to index i (and virtually task j is performed on index i+1);
    // Build first row : (That got build using base case of recursion);
    dp[0][0] = max(v[0][1], v[0][2]);
    dp[0][1] = max(v[0][0], v[0][2]);
    dp[0][2] = max(v[0][0], v[0][1]);
    for (int i = 1; i < n; i++) // ith day;
    {
        for (int j = 0; j < 3; j++) // having jth task as last;
        {
            // Now fill dp[i][j];
            for (int k = 0; k < 3; k++) // except j perform all;
            {
                if (j != k)
                    dp[i][j] = max(dp[i][j], v[i][k] + dp[i - 1][k]);
            }
        }
    }
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //         cout << dp[i][j] << " ";
    //     cout << endl;
    // }
    return max({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
}
// TC:  O(3N) (for every day, 4 last values are possilbe 0,1,2,-1 (actually 0,1,2 only but let's assume))
//      so O(4N or 3N) and for each of these states 3 times loop hence overall O(3N)*3
int solve1(int n, int last, vector<vector<int>> &v, vector<vector<int>> &dp) //  SC : O(3N) (DP 2D vector) + O(N) (recursive stack space);
{
    if (n == 0)
    {
        int mx = 0;
        for (int i = 0; i < 3; i++)
        {
            if (i != last)
                mx = max(mx, v[0][i]);
        }
        if (last != -1)
            dp[n][last] = mx;
        return mx;
    }
    int mx = 0;
    for (int i = 0; i < 3; i++)
    {
        if (i != last)
        {
            if (dp[n - 1][i] != -1)
                mx = max(mx, v[n][i] + dp[n - 1][i]);
            else
                mx = max(mx, v[n][i] + solve1(n - 1, i, v, dp));
        }
    }
    if (last != -1)
        dp[n][last] = mx;
    return mx;
}
int recursive_memoization(int n, vector<vector<int>> &v)
{
    vector<vector<int>> dp(n, vector<int>(3, -1)); // Only n and last is changing in recursion hence 2D DP and last can have 3 values 0,1,2 hence n*3 2D vector;
    int z = solve1(n - 1, -1, v, dp);
    return z;
}
int solve(int n, int last, vector<vector<int>> &v)
{
    if (n == 0)
    {
        int mx = 0;
        for (int i = 0; i < 3; i++)
        {
            if (i != last)
                mx = max(mx, v[0][i]);
        }
        return mx;
    }
    int mx = 0;
    for (int i = 0; i < 3; i++)
    {
        if (i != last)
            mx = max(mx, v[n][i] + solve(n - 1, i, v));
    }
    return mx;
}
int recursive(int n, vector<vector<int>> &v) // return answer for the array considering from index 0 to n;
{
    return solve(n - 1, -1, v);
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<vector<int>> v(n, vector<int>(3));
    for (int i = 0; i < n; i++)
        cin >> v[i][0] >> v[i][1] >> v[i][2];
    cout << recursive(n, v) << endl;
    cout << recursive_memoization(n, v) << endl;
    cout << tabulation(n, v) << endl;
    cout << tabulation_space_optimisation(n, v) << endl;
    return 0;
}

// Link : https://www.codingninjas.com/codestudio/problems/ninja-s-training_3621003?leftPanelTab=0 
// Just see latest submission (Exactly same function used : int tabulation_space_optimisation(int n, vector<vector<int>> &v) ) 
