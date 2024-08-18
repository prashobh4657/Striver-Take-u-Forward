#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
int longest_common_Substring_tabulation_space_optmisation(string &s, string &t)
{
    // Just take prev,curr; (Since dp[i] depends on dp[i-1] only); (That code i am not writing now but can be written easily);
}
int longest_common_Substring_tabulation(string &s, string &t) // TC : O(nm), SC : O(nm);
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
                dp[i][j] = 0; // Just make this 0;
        }
    }
    // return dp[n][m];
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, *max_element(dp[i].begin(), dp[i].end()));
    return ans;
}
int32_t main()
{
    fio;
    return 0;
}
// Why actual LCS code is not working?
// Just a small change; (Just make 0 in else-case); and just return maximum element of matrix instead of dp[n][m];
// longest_common_Substring_tabulation() ==> Full code is same as LCS_tabulation();
// GFG Link : https://practice.geeksforgeeks.org/problems/longest-common-substring1452/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
// Just see latest submission : Submitted longest_common_Substring_tabulation();
