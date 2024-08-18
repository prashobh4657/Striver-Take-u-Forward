#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
bool tabulation(string pattern, string text)
{
    // Convert solve2_memoize to 1-based indexing then convert it to tabulation;
    // We will make another function solve2_memoize_1_based_indexing(),tabulation(),tabulation_space_optmisation() later if time permits;
    // Till now I know recurrence structure and submitted using memoization that is sufficient;
}
bool solve2_memoize(int i, int j, string &pattern, string &text, vector<vector<int>> &dp)
{
    if (i < 0 && j < 0)
        return true;
    if (i < 0 && j >= 0)
        return false;
    if (j < 0 && i >= 0)
    {
        for (int ii = 0; ii <= i; ii++)
        {
            if (pattern[ii] != '*')
                return false;
        }
        return true; // take all start as empty strings;
    }
    if (dp[i][j] != -1)
        return dp[i][j];

    if (pattern[i] == text[j] || pattern[i] == '?')
        return dp[i][j] = solve2_memoize(i - 1, j - 1, pattern, text, dp);
    if (pattern[i] == '*')
        return dp[i][j] = (solve2_memoize(i - 1, j, pattern, text, dp) | solve2_memoize(i, j - 1, pattern, text, dp));
    return dp[i][j] = false;
}
bool solve2(int i, int j, string &pattern, string &text)
{
    if (i < 0 && j < 0)
        return true;
    if (i < 0 && j >= 0)
        return false;
    if (j < 0 && i >= 0)
    {
        for (int ii = 0; ii <= i; ii++)
        {
            if (pattern[ii] != '*')
                return false;
        }
        return true; // take all start as empty strings;
    }
    if (pattern[i] == text[j] || pattern[i] == '?')
        return solve2(i - 1, j - 1, pattern, text);
    if (pattern[i] == '*')
        return (solve2(i - 1, j, pattern, text) | solve2(i, j - 1, pattern, text));
    return false;
}
bool solve1(int i, int j, string &pattern, string &text)
{
    if (i < 0 && j < 0)
        return true;
    if (i < 0 && j >= 0)
        return false;
    if (j < 0 && i >= 0)
    {
        for (int ii = 0; ii <= i; ii++)
        {
            if (pattern[ii] != '*')
                return false;
        }
        return true; // take all start as empty strings;
    }
    if (pattern[i] == text[j] || pattern[i] == '?')
        return solve1(i - 1, j - 1, pattern, text);
    if (pattern[i] == '*')
    {
        bool ans = false;
        for (int x = 0; x <= j + 1; x++) //* can match 0 characters,1character,......j+1 characters (Since j is in 0-based indexing hence j+1 characters);
            ans = (ans | solve1(i - 1, j - x, pattern, text));
        return ans;
    }
    return false;
}
int32_t main()
{
    fio;
    int n, m;
    cin >> n >> m;
    string pattern, text;
    cin >> pattern >> text;
    cout << solve1(n - 1, m - 1, pattern, text) << endl;
    cout << solve2(n - 1, m - 1, pattern, text) << endl;
    vector<vector<int>> dp(n, vector<int>(m, -1));
    cout << solve2_memoize(n - 1, m - 1, pattern, text, dp) << endl;
    cout << tabulation(pattern, text) << endl;
    return 0;
}
/*
Coding ninja link : https://www.codingninjas.com/codestudio/problems/wildcard-pattern-matching_701650?leftPanelTab=0
Just see latest submissions : Submitted solve1(),solve2(),solve2_memoize();


GFG Link : https://practice.geeksforgeeks.org/problems/wildcard-pattern-matching/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
Just see latest submission : 2022-12-30 17:54:55	Correct	cpp	55 / 55  ==> (Same as solve2_memoize());

GFG Link : https://practice.geeksforgeeks.org/problems/wildcard-pattern-matching/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
Just see latest submission : 2022-12-30 18:11:06	Correct	cpp	181 / 181 ==> (Same as solve2_memoize());

Leetcode Link : https://leetcode.com/problems/regular-expression-matching/description/
=====> Don't know why giving error at 287th testcase (tried to submit solve2_memoize());
=====> Unambiguos behaviour at leetcode;
s = "aab", p = "c*a*b"
Output : false, Expected : true
Don't know why are they expecting true in this case while in case like "a" "c*" ==> they expect false;
s = "a", p = "c*"  Output : false, Expected : false
*/
/*
Why will it work ? In case when pattern[i]=='*'
    solve2(i-1,j) ==> Consider that * as empty string.
    solve2(i,j-1) ==> Keep star as it is (i itself), * absorb one character (j-1),
    (j-2,j-3,.....possibilities will be taken care in solve2(i,j-1) recursive call itself);
*/