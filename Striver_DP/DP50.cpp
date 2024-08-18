#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int tabulation(int c, int n, vector<int> &cuts) // TC:O(c^3) and SC:O(c^2);
{
    vector<vector<int>> dp(c + 2, vector<int>(c + 2, 0)); // loop can access c+1 hence c+2 for safety;
    // Copy the base case; ==> i>j then 0 that is already done as dp already filled with 0;
    /* We are calling solve(1,c) hence
            i going from 1--->c hence apply loop opposite (n-->1)
            j going from c--->1 hence apply loop opposite (1-->n)
    */
    // Copy the recurrence part;
    for (int i = c; i >= 1; i--)
    {
        for (int j = 1; j <= c; j++)
        {
            if (i > j) // base case;
                continue;
            // copy the recurrence;
            int ans = INT_MAX;
            for (int k = i; k <= j; k++)
            {
                int cost = cuts[j + 1] - cuts[i - 1] + dp[i][k - 1] + dp[k + 1][j];
                ans = min(ans, cost);
            }
            dp[i][j] = ans;
        }
    }
    return dp[1][c];
}
int solve_memoize(int i, int j, vector<int> &cuts, vector<vector<int>> &dp) // TC : O(c*c*c)= O(c^3) (c^2 states, for each state loop hence O(c^3)), SC: O(c^2)+ stack-space;
{
    if (i > j)
        return 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    int ans = INT_MAX;
    for (int k = i; k <= j; k++)
    {
        int cost = cuts[j + 1] - cuts[i - 1] + solve_memoize(i, k - 1, cuts, dp) + solve_memoize(k + 1, j, cuts, dp);
        ans = min(ans, cost);
    }
    return dp[i][j] = ans;
}
int solve(int i, int j, vector<int> &cuts) // TC : Exponential
{
    // Consider stick from index=i to j; //[i index (wrt to original stick) of left cut of stick and j (index) of right cut of stick]
    if (i > j)
        return 0;
    int ans = INT_MAX;
    for (int k = i; k <= j; k++)
    {
        int cost = cuts[j + 1] - cuts[i - 1] + solve(i, k - 1, cuts) + solve(k + 1, j, cuts);
        ans = min(ans, cost);
    }
    return ans;
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    int c;
    cin >> c;
    vector<int> cuts(c);
    for (int i = 0; i < c; i++)
        cin >> cuts[i];

    // Doing this as left cut of initial stick is at index=0 and last cut = n (feel) (Also 1 <= cuts[i] <= n - 1 given hence definitely cuts[i] will not have 0 and n in it);
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());
    cout << solve(1, c, cuts) << endl;

    vector<vector<int>> dp(c + 1, vector<int>(c + 1, -1)); //[i,j] can have values from 0 to c only;
    cout << solve_memoize(1, c, cuts, dp) << endl;
    cout << tabulation(c, n, cuts) << endl;
    return 0;
}

/*
Problem : https://leetcode.com/problems/minimum-cost-to-cut-a-stick/description/

Some important points :
1. We have array [1,3,4,5] and n=7, if we make a cut at 4 then [1,3] and [5] then will solving these segments independently work?
2. Yes, if array is sorted : if you cut at 4 then stick would be [0,1,2,3,4] [4,5,6,7] (Now cuts[] parition ==> [1,3] [5])
   clearly 3 is not dependent of 5 as position=3,5 are in different sticks.
3. No, if array is not sorted like if array given is [1,3,4,5,2] then if parition is done at 4
   then stick would be : [0,1,2,3,4] [4,5,6,7] (Now cuts[] parition ==> [1,3] [5,2])
   Here parition [1,3] [5,2] dependent on each other because 1,3,2 belong to one part of stick.

   Hence keep array sorted.


Submissions
1. Dec 23, 2022 10:50  ==> solve() ==> TLE
2. Dec 23, 2022 10:56  ==> solve_memoize() ==> Accepted
3. Dec 23, 2022 11:42  ==> tabulation() ==> Accepted;


Coding ninja link : https://www.codingninjas.com/codestudio/problems/cost-to-cut-a-chocolate_3208460?leftPanelTab=0
1. Just see latest submission : tabulation() is submitted;
   (Other two functions can also be submitted in same way as on leetcode, so not doing that part now (same striver did and got accepted on Coding ninja hence no need) )
*/
