#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
int tabulation_space_optimisation(string &s1, string &s2)
{
    // dp[i] denotes dp[i-1];
    int n = s1.size();
    int m = s2.size();
    vector<double> curr(m, 0);
    vector<double> prev(m, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (s1[i] == s2[j])
            {
                double a;
                if (j - 1 >= 0)
                {
                    if (i - 1 >= 0)
                        a = prev[j - 1];
                    else
                        a = 0; // j is right but i<0 hit in recursion return 0;
                }
                else
                    a = 1; // j-1 < 0 (Hence going call for (i-1,j) j<0 ==> hence will return 1);
                double b;
                if (i - 1 >= 0)
                    b = prev[j];
                else
                    b = 0;
                curr[j] = a + b;
            }
            else
            {
                double p;
                if (i - 1 >= 0)
                    p = prev[j];
                else
                    p = 0;
                curr[j] = p;
            }
        }
        prev = curr;
    }
    return (int)curr[m - 1];
}
int tabulation(string &s1, string &s2)
{
    int n = s1.size();
    int m = s2.size();
    vector<vector<double>> dp(n, vector<double>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (s1[i] == s2[j])
            {
                double a;
                if (j - 1 >= 0)
                {
                    if (i - 1 >= 0)
                        a = dp[i - 1][j - 1];
                    else
                        a = 0; // j is right but i<0 hit in recursion return 0;
                }
                else
                    a = 1; // j-1 < 0 (Hence going call for (i-1,j) j<0 ==> hence will return 1);
                double b;
                if (i - 1 >= 0)
                    b = dp[i - 1][j];
                else
                    b = 0;
                dp[i][j] = a + b;
            }
            else
            {
                double p;
                if (i - 1 >= 0)
                    p = dp[i - 1][j];
                else
                    p = 0;
                dp[i][j] = p;
            }
        }
    }
    return (int)dp[n - 1][m - 1];
}
int solve_memoize(string &s1, string &s2, int i, int j, vector<vector<int>> &dp) // TC :O(nm) , SC :O(nm) +O(n+m)(recursive stack space);
{
    if (j < 0)
        return 1;
    if (i < 0)
        return 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    if (s1[i] == s2[j])
        return dp[i][j] = solve_memoize(s1, s2, i - 1, j - 1, dp) + solve_memoize(s1, s2, i - 1, j, dp);

    return dp[i][j] = solve_memoize(s1, s2, i - 1, j, dp);
}
int solve(string &s1, string &s2, int i, int j) // Hypothesis : Return answer for substring s1[0...i] and s2[0....j];  //TC:O(exponential)(2^n,2^m), SC: O(N+M);
{
    if (j < 0) // s2 string is completely matched hence got 1 way.
        return 1;
    if (i < 0) // s2 is string is not exhausted (s2 is still left) now no way to find remaining s2 in s1 (as s1 exhausted);
        return 0;
    if (s1[i] == s2[j])
        return solve(s1, s2, i - 1, j - 1) + solve(s1, s2, i - 1, j);

    return solve(s1, s2, i - 1, j);
}
int32_t main()
{
    fio;
    int n, m;
    cin >> n >> m;
    string s1, s2;
    cin >> s1 >> s2;
    cout << solve(s1, s2, n - 1, m - 1) << endl;
    vector<vector<int>> dp(n, vector<int>(m, -1));
    cout << solve_memoize(s1, s2, n - 1, m - 1, dp) << endl;
    cout << tabulation(s1, s2) << endl;
    cout << tabulation_space_optimisation(s1, s2) << endl;
    return 0;
}
/*
We will be solving 3 leetcode hard problems based on string matching (DP on strings);
Problem link : https://leetcode.com/problems/distinct-subsequences/

Submitted ==> solve_memoize(),tabulation(),tabulation_space_optimisation() ==> ({Accepted});
==> Just see 3 accepted submissions (each corresponding to one of these 3 functions)


Important points :
1. Tabulation() part ignored :
   He did tabulation using 1-based indexing so for that he changed memoization code as well but i ignored that
   I did tabulation my-self (by observation == it is simple)
   (clearly in recursive call (i,j) depends on (i-1,j-1) or (i-1,j) means previous row values hence just filled table row-wise
   keeping base-cases in mind. (If i-1,j-1 becoming invalid then give proper value to variable a,b,p as per recursion);
2. In tabulation, when i submitted (even in video as well) ==> it is giving run-time error (even if in question it is mentioned
   that answer will fit in 32-bit integer) (even after converting to long long int same error) so converted to DP matrix into double datatype
   and finally return the answer after typecasting it to (int) same i did and it worked fine);
3. In tabulation_space_optimisation(),
   Since there is no filling of rows specially (base-cases) hence just copy-pasted the code of tabulation() and
   changed dp[i-1]==>prev and dp[i]==>curr;
   and prev,curr are vectors of double datatype;
4. After tabulation_space_optimisation ==> he told one more optimisation  =======> IGNORED (FOR NOW) (We will see in future if time permits);
*/
// Just see recurrence structure and base-case, and then you will able to generate all functions solve(),solve_memoize(),tabulation(),tabulation_space_optimisation();