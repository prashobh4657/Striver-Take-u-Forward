#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

vector<int> print_LIS(vector<int> &a) // TC :O(n^2);
{
    int n = a.size();
    vector<int> dp(n, 1); // Fill with 1 as consider that element itself as a longest subsequence initially.
    vector<int> z(n, 1);  // z[i] denotes the index of previous element of subsequence which is ending at index i; (Just backtracking);
    for (int i = 0; i < n; i++)
        z[i] = i; // Initially are LIS of size = 1 hence ending at i itself;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] < a[i])
            {
                if (dp[i] < 1 + dp[j])
                {
                    //  dp[i] = max(dp[i], 1 + dp[j]);
                    dp[i] = 1 + dp[j];
                    z[i] = j;
                }
            }
        }
    }
    int p = max_element(dp.begin(), dp.end()) - dp.begin();
    vector<int> lis;
    while (p != z[p])
    {
        lis.push_back(a[p]);
        p = z[p];
    }
    lis.push_back(a[p]);
    reverse(lis.begin(), lis.end());
    return lis;
}
int LIS(vector<int> &a) // TC : O(n^2) , SC :O(n);
{
    int n = a.size();
    vector<int> dp(n, 1); // Fill with 1 as consider that element itself as a longest subsequence initially.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] < a[i])
                dp[i] = max(dp[i], 1 + dp[j]);
        }
    }
    return *max_element(dp.begin(), dp.end());
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << LIS(a) << endl;
    vector<int> lis = print_LIS(a);
    for (int i = 0; i < lis.size(); i++)
        cout << lis[i] << " ";
    cout << endl;
    return 0;
}
/*
LIS():
=>This is more optimised solution uses just 1D DP vector. (Another tabulation method)
=>This method is not intuitive to write. By this method printing LIS is super-easy.

=>dp[i] denotes length of longest LIS ends at index i;
=>finally answer would *max_element(dp.begin(),dp.end());
=>Hence just fill this dp array;
*/
/*
print_LIS():
=>same as LIS() with slight changes;
=>make an additional array z where z[i] denotes the previous index of element after which this ith element in come in LIS and LIS ends at index i;
*/
/*
Leetcode Link : https://leetcode.com/problems/longest-increasing-subsequence/description/
See Submission : Dec 25, 2022 13:47 ===> Submitted LIS() of this cpp file.
GFG Link : https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence-1587115620/1
==> See Submission : 2023-08-12 10:43:50	Time Limit Exceeded	cpp	1087 / 1120 (TLE)
==> See DP43.cpp (Binary search approach) 
*/
