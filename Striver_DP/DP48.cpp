#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int MCM_tabulation(vector<int> &a)
{
    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    // As per base-condition for i==j ==> dp[i][j]=0;
    for (int i = 0; i < n; i++)
        dp[i][i] = 0;
    /* Since we called for f(1,N-1) hence
    ==> i must be going from 1 -- -- > n - 1 hence we will apply i loop oppposite n - 1 to 1(bottom - up);
    ==> j must be going from N-1-->0 hence we will apply j loop from 0 to n-1 (but wait we know i is always left of j hence j loop practically must be from i+1 to n-1 that's it);
    ==> Just copy the recurrence part; */
    for (int i = n - 1; i >= 1; i--)
    {
        for (int j = i + 1; j <= n - 1; j++)
        {
            // Copy the recurrence part;
            int answer = INT_MAX;
            for (int k = i; k <= j - 1; k++)
            {
                int temp = dp[i][k] + dp[k + 1][j]; // MCM(a, i, k) + MCM(a, k + 1, j);
                temp += (a[i - 1] * a[k] * a[j]);
                answer = min(answer, temp);
            }
            dp[i][j] = answer;
        }
    }
    return dp[1][n - 1];
}
int MCM_Memoize(vector<int> &a, int i, int j, vector<vector<int>> &dp) // TC : O(N*N*N) ==>O(N^3) , SC : O(N) (recursion stack space);
{
    if (i >= j)
        return 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    int answer = INT_MAX;
    for (int k = i; k <= j - 1; k++)
    {
        int temp = MCM_Memoize(a, i, k, dp) + MCM_Memoize(a, k + 1, j, dp);
        temp += (a[i - 1] * a[k] * a[j]);
        answer = min(answer, temp);
    }
    return dp[i][j] = answer;
}
int MCM(vector<int> &a, int i, int j) // TC : Exponential
{
    if (i >= j) // This is most invalid situation;
        return 0;
    int answer = INT_MAX;
    for (int k = i; k <= j - 1; k++) // Scheme A;
    {
        int temp = MCM(a, i, k) + MCM(a, k + 1, j); // for any fix k (at this level) we have only one way of multiply all matrices;
        temp += (a[i - 1] * a[k] * a[j]);           // Now let’s multiply resultant matrix of (i,k) and (k+1,j); (for that multiplication cost is arr[i-1]*arr[k]*arr[j])
        answer = min(answer, temp);                 // for this fix k (for this way partitioning) our minimum cost to multiply all matrices is temp;
    }
    return answer;
}

int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << MCM(a, 1, n - 1); // Pass i=1 and j=n-1 (imp as per our scheme);
    vector<vector<int>> dp(n, vector<int>(n, -1));
    cout << MCM_Memoize(a, 1, n - 1, dp);
    cout << MCM_tabulation(a);
    return 0;
}
/*
Problem : https://www.codingninjas.com/codestudio/problems/matrix-chain-multiplication_975344?leftPanelTab=0
===> Just see latest 3 submission same as MCM(), MCM_Memoize(), MCM_tabulation() having score : 14.4,72,80 respectively;


GFG Link :  https://practice.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article 
==> Submission 1 : 2022-12-23 09:25:56	Correct	cpp	127 / 127  (Same as MCM_Memoize())
==> Submission 2 : 2022-12-23 09:27:57	Correct	cpp	127 / 127  (Same as MCM_tabulation())
*/
