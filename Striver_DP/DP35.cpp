#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
int solve(vector<int> &a) // TC: O(N), SC: O(1)
{
    int mn = a[0];
    int profit = 0;
    int ans = 0;
    for (int i = 1; i < a.size(); i++)
    {
        // Here mn denotes min[0....i-1];
        if (mn < a[i])
            ans = max(ans, a[i] - mn);
        mn = min(mn, a[i]);
    }
    return ans;
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << solve(a);
    return 0;
}
// DP on stocks
/*
6 problems
==> Space optimisation is important in these questions from interview perspective;

==> It is important to buy first before selling.
==> Concept : If you are selling on the ith day then you will buy on that day having value=min[0...i-1];
*/