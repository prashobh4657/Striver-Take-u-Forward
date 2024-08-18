#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int tabulation_space_optimisation(int n, vector<int> &price)
{
    // dp[i] only depends on dp[i-1] (current row depends on previous row);
    // vector<vector<int>> dp(n, vector<int>(n + 1, 0));
    vector<int> prev(n + 1), curr(n + 1);
    for (int j = 0; j <= n; j++) // Base case; (idx==0) (Fill first row);
        curr[j] = j * price[0];
    prev = curr;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            int not_take = 0 + prev[j];
            int take = INT_MIN;
            if (i + 1 <= j)
                take = price[i] + curr[j - (i + 1)];
            curr[j] = max(take, not_take);
        }
        prev = curr;
    }
    return curr[n];
}
int tabulation(int n, vector<int> &price)
{
    vector<vector<int>> dp(n, vector<int>(n + 1, 0));
    for (int j = 0; j <= n; j++) // Base case; (idx==0) (Fill first row);
        dp[0][j] = j * price[0];

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            int not_take = 0 + dp[i - 1][j];
            int take = INT_MIN;
            if (i + 1 <= j)
                take = price[i] + dp[i][j - (i + 1)];
            dp[i][j] = max(take, not_take);
        }
    }
    return dp[n - 1][n];
}
int solve_memoize(int idx, int N, vector<int> &price, vector<vector<int>> &dp) // Returns answer for array [0..idx];
{
    if (idx == 0)
        return N * price[0];
    if (dp[idx][N] != -1)
        return dp[idx][N];
    int not_take = 0 + solve_memoize(idx - 1, N, price, dp);
    int take = INT_MIN;
    if (idx + 1 <= N)
        take = price[idx] + solve_memoize(idx, N - (idx + 1), price, dp);
    return dp[idx][N] = max(take, not_take);
}
int solve(int idx, int N, vector<int> &price) // Returns answer for array [0..idx];
{
    if (idx == 0)
        return N * price[0];

    int not_take = 0 + solve(idx - 1, N, price);
    int take = INT_MIN;
    if (idx + 1 <= N)    //Need to take decision whether to cut rod of length idx+1 or not;
        take = price[idx] + solve(idx, N - (idx + 1), price);
    return max(take, not_take);
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> price(n);
    for (int i = 0; i < n; i++)  //price[i] denotes price of segment of length (i+1);
        cin >> price[i];
    int W;
    cin >> W;
    cout << solve(n - 1, n, price) << endl;
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    cout << solve_memoize(n - 1, n, price, dp) << endl;
    cout << tabulation(n, price) << endl;
    cout << tabulation_space_optimisation(n, price) << endl;
    return 0;
}

/*
Coding ninja link : https://www.codingninjas.com/codestudio/problems/rod-cutting-problem_800284?leftPanelTab=0
==> Just see latest 4 submissions ==> Submitted solve() (TLE), solve_memoize(),tabulation(),tabulation_space_optimisation() {Accepted};

GFG link : https://practice.geeksforgeeks.org/problems/rod-cutting0840/1
==> Just see latest submission : ==> tabulation_space_optimisation() submitted.
*/
