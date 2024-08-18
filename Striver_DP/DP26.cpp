#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
vector<vector<int>> LCS_tabulation(string &s, string &t) // TC : O(nm), SC : O(nm);
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
    // return dp[n][m];
    return dp;
}
string printLCS(string &s, string &t) // O(n+m);
{
    vector<vector<int>> dp = LCS_tabulation(s, t); // taken from LCS.cpp;
    int n = s.size(), m = t.size();
    int i = n, j = m;
    string ans;
    while (i >= 1 && j >= 1)
    {
        if (s[i - 1] == t[j - 1])
        {
            ans.push_back(s[i - 1]);
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
int32_t main()
{
    fio;
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    cout << printLCS(s, t) << endl;
    return 0;
}
