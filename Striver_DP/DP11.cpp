#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int tabulation_space_optimisation(int i, int j, vector<vector<int>> &matrix)
{
    int n = matrix.size();
    vector<int> next_row(n, 0);
    vector<int> curr(n, 0);
    for (int j = 0; j < n; j++)
        curr[j] = matrix[n - 1][j];
    next_row = curr;
    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = i; j >= 0; j--)
        {
            int down = matrix[i][j] + next_row[j];
            int diagonal_down = matrix[i][j] + next_row[j + 1];
            curr[j] = min(down, diagonal_down);
        }
        next_row = curr;
    }
    return curr[0];
}
int tabulation(int i, int j, vector<vector<int>> &matrix) // TC : O(n*n), SC : O(n^2)
{
    int n = matrix.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int j = 0; j < n; j++) // Fill last row;
        dp[n - 1][j] = matrix[n - 1][j];

    for (int i = n - 2; i >= 0; i--) // Fill remaining rows
    {
        for (int j = i; j >= 0; j--)
        {
            int down = matrix[i][j] + dp[i + 1][j];
            int diagonal_down = matrix[i][j] + dp[i + 1][j + 1];
            dp[i][j] = min(down, diagonal_down);
        }
    }
    return dp[0][0];
}

int triangle_memoize(int i, int j, vector<vector<int>> &matrix, vector<vector<int>> &dp) // TC :O(n*n), SC : O(n^2)
{
    if (i == matrix.size() - 1)
        return matrix[i][j];

    if (dp[i][j] != -1)
        return dp[i][j];
    int down = matrix[i][j] + triangle_memoize(i + 1, j, matrix, dp);
    int diagonal_down = matrix[i][j] + triangle_memoize(i + 1, j + 1, matrix, dp);
    return dp[i][j] = min(down, diagonal_down);
}
int triangle(int i, int j, vector<vector<int>> &matrix) // Return minimum cost from (0,0) to (last row (any column)); // TC : 2^(n*(n+1)/2), SC : O(n);
{
    if (i == matrix.size() - 1)
        return matrix[matrix.size() - 1][j];

    int down = matrix[i][j] + triangle(i + 1, j, matrix);
    int diagonal_down = matrix[i][j] + triangle(i + 1, j + 1, matrix);
    return min(down, diagonal_down);
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<vector<int>> matrix(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= i + 1; j++) // ith row has (i+1) elements;
        {
            int temp;
            cin >> temp;
            matrix[i].push_back(temp);
        }
    }

    cout << triangle(0, 0, matrix);
    vector<vector<int>> dp(n, vector<int>(n, -1));
    cout << triangle_memoize(0, 0, matrix, dp);
    cout << tabulation(0, 0, matrix);
    cout << tabulation_space_optimisation(0, 0, matrix);
    return 0;
}

/*
If we make hypothesis like this solve(i,j,matrix) will return minimum cost from (0,0) to (i,j);
(Like previous questions we did (In them destination is fix like (n-1,m-1) maze questions));

If we do like this then from main() we need call solve(p,q,matrix) where (p,q)
is p=n-1 and for all values of q; (because destination can be any one of them); (all indcies of last row can be destination);

int solve(int i, int j, vector<vector<int>> &matrix) //Recursive function;
{
    if (i == 0)
        return matrix[0][j];

    int up = matrix[i][j] + solve(i - 1, j, matrix);
    int down = matrix[i][j] + solve(i - 1, j - 1, matrix);
    return min(up, down);
}
in main():
  int ans=INT_MAX;
  for(int j=0;j<n;j++) //in last row we will have n columns (hence loop must run n times);
  ans=min(ans,solve(n-1,j,matrix)); //Like this we need to call solve (for all possible destinations in this hypothesis);

So let's change the hypothesis and follow hypothesis as in above code in this cpp file (Same hypothesis discussed in video);
*/

/* Coding ninja link : https://www.codingninjas.com/codestudio/problems/triangle_1229398?leftPanelTab=0
===> Submitted : uniquePaths_memoize() then tabulation() then  tabulation_space_optimisation() all got submitted;
===> Just see there latest 3 submissions same as uniquePaths_memoize(), tabulation(), tabulation_space_optimisation() respectively;
*/
