#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int tabulation(int n)
{
    vector<int> dp(n + 1);
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}
int recursive(int n)
{
    if (n == 0 || n == 1)
        return 1;
    return recursive(n - 1) + recursive(n - 2);
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    cout << recursive(n) << " " << tabulation(n) << endl;
    return 0;
}
// try all possible ways ==> Count ways or best way ==> recursion
/*
1. try to represent the problem in terms of index;
2. do all possible stuffs on that whatever possibilites you have in according to the problem statement;
3. sum of all stuffs ==> count all ways
   min(all stuff) ==> final min
*/

//Leetcode Question link : https://leetcode.com/problems/climbing-stairs/ 
//Just see latest submission (same as tabulation funtion);
