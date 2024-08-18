#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int tabulation_space_optimisation(int n, int m, vector<vector<int>> matrix)
{
    // 1D DP --> two variables O(1);
    // 2D DP --> 1D vector;
    // 3D DP --> 2D;
    // clearly in tabulation code : dp[i][j1+d1][j+d2] required dp[i+1][j1+d1][j2+d2]; (Just next 2D vector);
    // Just making slight changes in tabulation code;
    vector<vector<int>> curr(m, vector<int>(m, -1));
    vector<vector<int>> prev(m, vector<int>(m, -1));
    for (int j1 = 0; j1 < m; j1++)
    {
        for (int j2 = 0; j2 < m; j2++)
        {
            if (j1 == j2)
                curr[j1][j2] = matrix[n - 1][j1];
            else
                curr[j1][j2] = matrix[n - 1][j1] + matrix[n - 1][j2];
        }
    }
    prev = curr;
    for (int i = n - 2; i >= 0; i--) // Fill other rows of 3D vector
    {
        for (int j1 = 0; j1 < m; j1++)
        {
            for (int j2 = 0; j2 < m; j2++)
            {
                int ans = INT_MIN;
                for (int d1 = -1; d1 <= 1; d1++)
                {
                    for (int d2 = -1; d2 <= 1; d2++)
                    {
                        if (j1 + d1 >= 0 && j1 + d1 < m && j2 + d2 >= 0 && j2 + d2 < m)
                            ans = max(ans, prev[j1 + d1][j2 + d2]); // dp[i+1]=prev
                        else
                            ans = max(ans, (int)-1e8);
                    }
                }
                if (j1 == j2)
                    ans += matrix[i][j1];
                else
                    ans += matrix[i][j1] + matrix[i][j2];
                curr[j1][j2] = ans; // dp[i]=curr; (Remove dp[i] and replace with curr)
            }
        }
        prev = curr; // Add this line;
    }
    return curr[0][m - 1];
}
int tabulation(int n, int m, vector<vector<int>> matrix)
{
    // dp[i][j][k] denotes minimum cost when alice start from (i,j) and bob start from (i,k) (Both start from ith row) to last row;
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
    // let's write for base-case;
    // for last row ==> dp[n-1][][] other two parameter will vary;

    // Fill last row of 3D vector; (Since that last row is itself 2D vector hence 2-nested loop);
    for (int j1 = 0; j1 < m; j1++)
    {
        for (int j2 = 0; j2 < m; j2++)
        {
            if (j1 == j2)
                dp[n - 1][j1][j2] = matrix[n - 1][j1];
            else
                dp[n - 1][j1][j2] = matrix[n - 1][j1] + matrix[n - 1][j2];
        }
    }

    for (int i = n - 2; i >= 0; i--) // Fill other rows of 3Dvector
    {
        for (int j1 = 0; j1 < m; j1++)
        {
            for (int j2 = 0; j2 < m; j2++)
            {
                // Now here just copy paste from recurrence function :
                int ans = INT_MIN;
                for (int d1 = -1; d1 <= 1; d1++)
                {
                    for (int d2 = -1; d2 <= 1; d2++)
                    {
                        if (j1 + d1 >= 0 && j1 + d1 < m && j2 + d2 >= 0 && j2 + d2 < m) // just adding this condition (for out-of boundary);
                            ans = max(ans, dp[i + 1][j1 + d1][j2 + d2]);                // ans = max(ans, solve_memoize(i + 1, j1 + d1, j2 + d2, matrix, dp));
                        else
                            ans = max(ans, (int)-1e8);
                    }
                }
                if (j1 == j2)
                    ans += matrix[i][j1];
                else
                    ans += matrix[i][j1] + matrix[i][j2];
                dp[i][j1][j2] = ans; // return dp[i][j1][j2] = ans;
            }
        }
    }
    return dp[0][0][m - 1];
}
int solve_memoize(int i, int j1, int j2, vector<vector<int>> &matrix, vector<vector<vector<int>>> &dp) // TC : O(9*n*m*m), SC:O(9*n*m*m) (DP 3D vector)  +O(N)(recursion stack)
{
    // Out of boundary base case :
    if (i < 0 || j1 >= matrix[0].size() || j2 >= matrix[0].size())
        return -1e8; // Don't return INT_MIN (as it will get add to some no. may be -ve-ve = v. negative = run-time error (wrong));
    if (i == matrix.size() - 1)
    {
        if (j1 == j2)
            return matrix[i][j1];
        else
            return matrix[i][j1] + matrix[i][j2];
    }
    if (dp[i][j1][j2] != -1)
        return dp[i][j1][j2];
    int ans = INT_MIN;
    for (int d1 = -1; d1 <= 1; d1++)
    {
        for (int d2 = -1; d2 <= 1; d2++)
            ans = max(ans, solve_memoize(i + 1, j1 + d1, j2 + d2, matrix, dp));
    }
    if (j1 == j2)
        ans += matrix[i][j1];
    else
        ans += matrix[i][j1] + matrix[i][j2];
    return dp[i][j1][j2] = ans;
}
int solve(int i, int j1, int j2, vector<vector<int>> &matrix) // TC : every time alice has 3 options(3^n) and bob has also same (3^n) = 9^n;, SC : O(N) (auxilary stack space);
{
    // Out of boundary base case :
    if (i < 0 || j1 >= matrix[0].size() || j2 >= matrix[0].size())
        return -1e8; // Don't return INT_MIN (as it will get add to some no. may be -ve-ve = v. negative = run-time error (wrong));
    if (i == matrix.size() - 1)
    {
        if (j1 == j2)
            return matrix[i][j1];
        else
            return matrix[i][j1] + matrix[i][j2];
    }
    int ans = INT_MIN;
    for (int d1 = -1; d1 <= 1; d1++)
    {
        for (int d2 = -1; d2 <= 1; d2++)
            ans = max(ans, solve(i + 1, j1 + d1, j2 + d2, matrix));
    }
    if (j1 == j2)
        ans += matrix[i][j1];
    else
        ans += matrix[i][j1] + matrix[i][j2];
    return ans;
}
int32_t main()
{
    fio;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));
    cout << solve(0, 0, m - 1, matrix) << endl;
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1))); // dp[n][m][m];
    cout << solve_memoize(0, 0, m - 1, matrix, dp) << endl;
    cout << tabulation(n, m, matrix) << endl;
    cout << tabulation_space_optimisation(n, m, matrix) << endl;

    return 0;
}
/*
1. we have fixed starting point and variable ending point
2. greedy will not work
3. we have to consider all possibilties (path traced by alice and bob together);
   ==> we can't write recurrence independently for alice and bob because in their path there can be multiple common cells
       then we need to eliminate that much chocolates (that would be highly complex);
4. Hence we will write a recurrence in which alice and bob both move together.
5. Rules :
      ==> Express in terms (i1,j1) and (i2,j2) as both will be moving
      ==> explore all paths   / | \
      ==> take maximum among all;
      Since here starting point is fixed hence write recurrence (just like problem triangle) : hypothesis : (i,j) to last
      because ending point can be any point in the last row; (any column);
6. both we will in the same row every-time; (Both will make one step and that will lead them to next row); ==> Hence i1=i2=i;
7. Alice have 3 possibilities and bob also have 3 possibilities ==> in total 3*3 possibilities in total (when both together) = 9 paths;
   =======> Hence just manually write all those 9 possiblities;
   Let's do this things using for-loop (for generating these 9 possibilities);
      actually i--->i+1 (for sure)
      j can be j-1,j,j+1 hence (loop -1 to 1);
*/

/*
Coding ninja link : https://www.codingninjas.com/codestudio/problems/ninja-and-his-friends_3125885?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=0
===> Submitted : solve() then solve_memoize() then tabulation() then tabulation_space_optimisation() and all got submitted (Recursive ones got TLE);
===> Just see there latest 4 submissions same as solve(),solve_memoize(), tabulation(), tabulation_space_optimisation() respectively;

Leetcode Link : https://leetcode.com/problems/cherry-pickup-ii/description/
==> Just see latest submission (solve_memoize() submitted)
GFG Link : https://practice.geeksforgeeks.org/problems/chocolates-pickup/1?page=1&sortBy=newest&query=page1sortBynewest
==> Just see latest submission (solve_memoize() submitted)
*/
