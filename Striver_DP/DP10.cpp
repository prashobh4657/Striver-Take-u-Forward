#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int tabulation_space_optimisation(int n, int m, vector<vector<int>> &matrix)
{
    vector<int> prev(m, 0);
    for (int i = 0; i < n; i++)
    {
        vector<int> curr(m, 0);
        for (int j = 0; j < m; j++)
        {
            if (i == 0 && j == 0)
                curr[0] = matrix[0][0];
            else
            {
                int up, left;
                up = left = matrix[i][j];
                if (i - 1 >= 0)
                    up += prev[j];
                else
                    up += 1e9;
                if (j - 1 >= 0)
                    left += curr[j - 1];
                else
                    left += 1e9;
                curr[j] = min(left, up);
            }
        }
        prev = curr;
    }
    return prev[m - 1];
}
int tabulation(int n, int m, vector<vector<int>> &matrix)
{
    vector<vector<int>> dp(n, vector<int>(m, -1)); // dp[i][j] denotes minimum from (0,0) to (i,j);
    dp[0][0] = matrix[0][0];

    // First row;
    for (int j = 1; j < m; j++)
        dp[0][j] = matrix[0][j] + dp[0][j - 1];
    // First column;
    for (int i = 1; i < n; i++)
        dp[i][0] = matrix[i][0] + dp[i - 1][0];

    // Remaining matrix;
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
            dp[i][j] = matrix[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
    }
    return dp[n - 1][m - 1];

    /*Alter : write code like this : Single loop;
      for(int i=0;i<n;i++)
      {
        for(int j=0;j<m;j++)
        {
            if(i==0&&j==0)dp[0][0]=matrix[0][0];
            else
            {
                int up,left;
                up=left=matrix[i][j];
                if(i-1>=0)up+=dp[i-1][j];
                else up+=1e9;
                if(j-1>=0)left+=dp[i][j-1];
                else left+=1e9;
                dp[i][j]=min(up,left);
            }
        }
      }
    */
}
int min_path_sum_memoize(int i, int j, vector<vector<int>> &matrix, vector<vector<int>> &dp)
{
    if (i < 0 || j < 0)
        return 1e9;
    if (i == 0 && j == 0)
        return matrix[0][0];
    if (dp[i][j] != -1)
        return dp[i][j];

    int up = matrix[i][j] + min_path_sum_memoize(i - 1, j, matrix, dp);
    int left = matrix[i][j] + min_path_sum_memoize(i, j - 1, matrix, dp);
    return dp[i][j] = min(up, left);
}
int min_path_sum(int i, int j, vector<vector<int>> &matrix) // return minimum path sum from (0,0) to (i,j);
{
    if (i < 0 || j < 0) // invalid;
        return INT_MAX; // INT_MAX will give error (overflow) on coding ninja hence return any other large value like 10^9;
    if (i == 0 && j == 0)
        return matrix[0][0];

    int up = matrix[i][j] + min_path_sum(i - 1, j, matrix);
    int left = matrix[i][j] + min_path_sum(i, j - 1, matrix);
    return min(up, left);
}
int32_t main()
{
    fio;
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> matrix(n, vector<int>(m));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                cin >> matrix[i][j];
        }
        cout << min_path_sum(n - 1, m - 1, matrix) << endl;
        vector<vector<int>> dp(n, vector<int>(m, -1));
        cout << min_path_sum_memoize(n - 1, m - 1, matrix, dp) << endl;
        cout << tabulation(n, m, matrix) << endl;
        cout << tabulation_space_optimisation(n, m, matrix) << endl;
    }
    return 0;
}

/*
Coding ninja link : https://www.codingninjas.com/codestudio/problems/minimum-path-sum_985349?leftPanelTab=0
===> Submitted : min_path_sum_memoize() then tabulation() then  tabulation_space_optimisation() all got submitted;
===> Just see there latest 3 submissions same as min_path_sum_memoize, tabulation(), tabulation_space_optimisation() respectively;
*/
/*
    Also see LQN 64. ==> On that question : (Just see latest submissoin) ==> dp[i][j] denotes no. of minimum path sum from
                                          (i,j) to (n-1,m-1) but here in our this cpp file dp[i][j] denotes minimum path sum from
                                          (0,0) to (i,j) both are same but the one which is discussed in this cpp file is more intuitive
                                          (as it comes from recursion-->memoization-->tabulation);
    Also GFG Link : https://practice.geeksforgeeks.org/problems/path-in-matrix3805/1
                    ==> Just see latest submission;
                    ==> Just change min ==> max everywhere (In LQN 64. wonderful tabulation code).
*/
