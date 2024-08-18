#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int LCS_tabulation_space_optimisation(string &s, string &t)
{
    // dp[i] depends on dp[i-1]; //Also dp[i][j] depends on dp[i][j-1] so that is fine as j-1 will be filled first; Hence curr,prev vector can optimise;
    int n = s.size();
    int m = t.size();
    vector<int> curr(m + 1, 0);
    vector<int> prev = curr;
    for (int i = 1; i <= n; i++) // fill remaining rows;
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
                curr[j] = 1 + prev[j - 1];
            else
                curr[j] = max(prev[j], curr[j - 1]);
        }
        prev = curr;
    }
    return curr[m];
}
int LCS_tabulation(string &s, string &t) // TC : O(nm), SC : O(nm);
{
    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}
int LCS_memoize(int i, int j, string &s, string &t, vector<vector<int>> &dp) // TC : O(nm), SC : O(nm) (DP matrix)+ O(n+m) (recursion stack space);
{
    if (i == 0 || j == 0)
        return 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    if (s[i - 1] == t[j - 1])
        return dp[i][j] = 1 + LCS_memoize(i - 1, j - 1, s, t, dp);
    return dp[i][j] = max(LCS_memoize(i - 1, j, s, t, dp), LCS_memoize(i, j - 1, s, t, dp));
}
int LCS(int i, int j, string &s, string &t) // Return answer for considering string s[0...i] and t[0...j];
{
    if (i < 0 || j < 0)
        return 0;
    if (s[i] == t[j])
        return 1 + LCS(i - 1, j - 1, s, t);
    return max(LCS(i - 1, j, s, t), LCS(i, j - 1, s, t));
}
int32_t main()
{
    fio;
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    cout << LCS(n - 1, m - 1, s, t) << endl;
    // Co-ordinate shift; (So that base i<0 and j<0 can accomodated in table itself as these values also calculate some dp[i][j])
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    cout << LCS_memoize(n, m, s, t, dp) << endl; // Change 1 : Just change i<0||j<0  ====> i==0||j==0  and Change 2 : s[i]==t[j] ====> s[i-1]==t[j-1]  (Here we will pass f(n)(m));
    cout << LCS_tabulation(s, t) << endl;        // (Basically dp[i][j] denotes answer for string s[0...i-1] and t[0...j-1])
    cout << LCS_tabulation_space_optimisation(s, t) << endl;
    return 0;
}
/* 
Here LCS_memoize(),LCS_tabulation(),LCS_tabulation_space_optimisation() ===> These codes are wrt to Coordinate shift;
I intially did LCS_memoize(),LCS_tabulation(),LCS_tabulation_space_optimisation() (all these) wrt LCS()
(in which i<0 and j<0 is base condition) but that is not much good (that is intuitive but not good)
==> Because in tabulation a lot condition need to write if i-1>=0 and j-1>=0 and all that.
Hence just follow above codes; Above LCS() is normal, other are wrt to coordinate shift.
LCS_memoize is recursive code that you can learn (Here hypothesis is returns answer for string s[0...i-1],t[0...j-1]).
Coordinate shift is also easy ==> Just 2 changes done as explained in code comments;
and just tabulate it to get LCS_tabulation(),LCS_tabulation_space_optimisation()
*/
/*
Coding ninja link : https://www.codingninjas.com/codestudio/problems/longest-common-subsequence_1063255?leftPanelTab=0
==> Just see submissions : Submitted LCS_memoize(),LCS_tabulation(),LCS_tabulation_space_optimisation()  ==> Accepted;
(No need to see actually, it submitted gurantees that above cpp code is absolutely correct);

GFG Link : https://practice.geeksforgeeks.org/problems/longest-common-subsequence-1587115620/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
==> Just see latest submission;
*/
