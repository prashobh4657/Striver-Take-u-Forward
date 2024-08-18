#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
template <typename T>
istream &operator>>(istream &input, vector<T> &v)
{
    for (auto &i : v)
        cin >> i;
    return input;
}
template <typename T>
ostream &operator<<(ostream &output, vector<T> &v)
{
    for (auto &i : v)
        cout << i << " ";
    return output;
}
int tabulation_space_optimisation(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);
    for (int j = 0; j <= m; j++)
        prev[j] = j;
    for (int i = 1; i <= n; i++)
    {
        curr[0] = i; // Important base condition;
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                curr[j] = prev[j - 1];
            else
                curr[j] = 1 + min({prev[j], curr[j - 1], prev[j - 1]});
        }
        prev = curr;
    }
    return curr[m];
}
int tabulation(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;
    for (int j = 0; j <= m; j++)
        dp[0][j] = j;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = 0 + dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
        }
    }
    return dp[n][m];
}
int solve_memoize(int i, int j, string &s1, string &s2, vector<vector<int>> &dp) // TC : O(nm) , SC : O(nm) + O(n+m);
{
    if (i == 0)
        return j;
    if (j == 0)
        return i;

    if (dp[i][j] != -1)
        return dp[i][j];
    if (s1[i - 1] == s2[j - 1])
        return dp[i][j] = 0 + solve_memoize(i - 1, j - 1, s1, s2, dp);
    return dp[i][j] = 1 + min({solve_memoize(i - 1, j - 1, s1, s2, dp), solve_memoize(i - 1, j, s1, s2, dp), solve_memoize(i, j - 1, s1, s2, dp)});
}
int solve(int i, int j, string &s1, string &s2) // TC : exponential (3^n) , SC : O(n+m) (stack space)  ==> Overlapping subproblems;
{
    if (i < 0)
        return j + 1;
    if (j < 0)
        return i + 1;
    if (s1[i] == s2[j])
        return 0 + solve(i - 1, j - 1, s1, s2);
    return 1 + min({solve(i - 1, j - 1, s1, s2), solve(i - 1, j, s1, s2), solve(i, j - 1, s1, s2)});
}
int32_t main()
{
    fio;
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size(), m = s2.size();
    cout << solve(n - 1, m - 1, s1, s2) << endl;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    cout << solve_memoize(n - 1, m - 1, s1, s2, dp) << endl;
    cout << tabulation(s1, s2) << endl;
    cout << tabulation_space_optimisation(s1, s2) << endl;
    return 0;
}
/*
string s1,s2 ==> size n,m
In worst case : delete all elements then insert whatever is requried ==> n+m steps.

Given strings s1 [0....i],s2[0....j]
==> if last character same then
        0+f(i-1,j-1);
    else
        1+f(i,j-1) //insert;
        1+f(i-1,j) //delete;
        1+f(i-1,j-1) //replace;
*/
/*
Here we will do coordinate shift in solve() and then memoize and then tabulate;
*/

/*
Coding ninja link : https://www.codingninjas.com/codestudio/problems/edit-distance_630420?leftPanelTab=0
==> Just see latest submissions ==> (All 4 functions submitted);

GFG link : https://practice.geeksforgeeks.org/problems/edit-distance3702/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
==> Just see latest submission ==> (tabulation() submitted);

Leetcode link : https://leetcode.com/problems/edit-distance/description/
==> Just see latest submission ==> (tabulation() submitted);

*/
