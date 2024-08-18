#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
int number_of_LIS(vector<int> &a)
{
    int n = a.size();
    vector<int> dp(n, 1);
    vector<int> cnt(n, 1); // cnt[i] denotes no. of subsequences of length dp[i] (ending at index i);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] < a[i])
            {
                if (dp[i] < 1 + dp[j])
                {
                    // dp[i] = max(dp[i], 1 + dp[j]);
                    dp[i] = 1 + dp[j];
                    cnt[i] = cnt[j]; // inherit;
                }
                else if (dp[i] == 1 + dp[j])
                    cnt[i] += cnt[j]; // increase the count;
            }
        }
    }
    int p = *max_element(dp.begin(), dp.end());
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (dp[i] == p)
            ans += cnt[i];
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
    cout << number_of_LIS(a);
    return 0;
}

/*
In video : Just did dry run on testcase : [1,5,4,3,2,6,7,10,8,9]
==> Just dry run the code on this testcase and will understand (see video for any doubt);
==> Same code of "DP42_part2.cpp" ==> LIS is used with slight modification and build cnt[] vector;
*/
/*
Leetcode link : https://leetcode.com/problems/number-of-longest-increasing-subsequence/description/
==> Just see latest submission : Dec 26, 2022 12:31          ==> Submitted number_of_LIS();
*/
/*
My solution (But wrong) :
1. Just consider the dp array formed in LIS() function.
2. Let p=*max_element(dp.begin(),dp.end());
3. Count the occurrences of p in dp array and that is answer. But this is wrong.
==> Try on this testcase : a=[1,3,5,4,7] ==> dp==>[1 2 3 3 4]    p=4 (max element) and its occurrence is only 1
but answer is 2 : [1, 3, 4, 7] and [1, 3, 5, 7].  (This method will fail when more than one LIS exist ending at index i itself);
*/