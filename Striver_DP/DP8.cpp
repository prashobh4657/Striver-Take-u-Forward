#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int tabulation_space_optimisation(int n, int m)
{
    // dp[i][j]=dp[i-1][j] (UP) + dp[i][j-1] (LEFT);
    // We are traversing row-wise (By applying little brain you can space optimise it);
    vector<int> prev(m, 0);
    for (int i = 0; i < n; i++)
    {
        vector<int> curr(m, 0);
        for (int j = 0; j < m; j++)
        {
            if (i == 0 && j == 0)
                curr[j] = 1;
            else
            {
                int up = 0;
                int left = 0;
                if (i > 0)
                    up = prev[j];
                if (j > 0)
                    left = curr[j - 1];
                curr[j] = up + left;
            }
        }
        prev = curr;
    }
    return prev[m - 1];
}
int tabulation(int n, int m) // TC : O(nm) and SC : O(nm);
{
    // dp[i][j] denotes no. of unique paths from (0,0) to (n,m);
    vector<vector<int>> dp(n, vector<int>(m, -1));
    dp[0][0] = 1;
    for (int j = 1; j < m; j++) // Here dp[0][j]=dp[-1][j]+dp[0][j-1] (but dp[-1][j] not exist hence take it 0);
        dp[0][j] = dp[0][j - 1];
    for (int i = 1; i < n; i++)
        dp[i][0] = dp[i - 1][0];
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    }
    return dp[n - 1][m - 1];
    /*Alter : write code like this : Single loop;
      for(int i=0;i<n;i++)
      {
        for(int j=0;j<m;j++)
        {
            if(i==0&&j==0)dp[0][0]=1;
            else
            {
                int up,left;  up=left=0;
                if(i-1>=0)up=dp[i-1][j];
                if(j-1>=0)left=dp[i][j-1];
                dp[i][j]=up+left;
            }
        }
      }
    */
}
int uniquePaths_memoize(int n, int m, vector<vector<int>> &dp) // TC: O(nm), SC : O((n-1)+(m-1))+O(nm)(dp 2d vector);
{
    if (n == 0 && m == 0)
        return dp[0][0] = 1;
    if (n < 0 || m < 0)
        return 0;

    if (dp[n][m] != -1)
        return dp[n][m];
    int up = uniquePaths_memoize(n - 1, m, dp);
    int down = uniquePaths_memoize(n, m - 1, dp);
    return dp[n][m] = up + down;
}
int uniquePaths(int n, int m) // return no. of unique path from (0,0) to (n,m);   ==> TC : (2^(mn)) (for every-cell 2 possibility), SC : O(path length);
{
    if (n == 0 && m == 0)
        return 1;
    if (n < 0 || m < 0)
        return 0;
    int up = uniquePaths(n - 1, m);
    int down = uniquePaths(n, m - 1);
    return up + down;
}
int32_t main()
{
    fio;
    int n, m;
    cin >> n >> m;
    cout << uniquePaths(n - 1, m - 1) << endl;
    vector<vector<int>> dp(n, vector<int>(m, -1));
    cout << uniquePaths_memoize(n - 1, m - 1, dp) << endl;
    cout << tabulation(n, m) << endl;
    cout << tabulation_space_optimisation(n, m) << endl;
    return 0;
}

/*
Coding ninja link : https://www.codingninjas.com/codestudio/problems/total-unique-paths_1081470?leftPanelTab=0
===> Submitted : uniquePaths_memoize() then tabulation() then  tabulation_space_optimisation() all got submitted;
===> Just see submissions there same as uniquePaths_memoize(), tabulation(), tabulation_space_optimisation() respectively;
===> Memoized function is updated in this file after getting dp insight; (That is also submitted there);
*/
/*Also see LQN 62. ==> On that question : I submitted solution only using combinatorics (Don't submit all these solutions there)
  Also see LQN 63. ==> On that question : (Approach 2 in LQN 63.) : dp[i][j] denotes no. of unique path from (i,j) to (n-1,m-1)
                                          but here in our this cpp file dp[i][j] denotes no. of unique path from (0,0) to (i,j)
                                          both are same but the one which is discussed in this cpp file is more intuitive (as
                                          it comes from recursion-->memoization-->tabulation);
*/
