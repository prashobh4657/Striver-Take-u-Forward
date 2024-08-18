#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

int LIS_BS(vector<int> &a) // TC : O(Nlogn),  SC : O(N);
{
    int n = a.size();
    vector<int> temp;
    temp.push_back(a[0]);
    int length = 1;
    for (int i = 1; i < n; i++)
    {
        if (a[i] > temp.back())
        {
            temp.push_back(a[i]);
            length++;
        }
        else
        {
            int idx = lower_bound(temp.begin(), temp.end(), a[i]) - temp.begin();
            temp[idx] = a[i];
        }
    }
    return temp.size();
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << LIS_BS(a) << endl;
    return 0;
}

/*
Important point :
1. Here temp array is not LIS.
2. [1,7,8,4,5,6,-1,9]
   We come at i=0, since no subsequence till now hence make separate
   [1,
   We come at i=1, since a[i]=7 and before 7, 1 is there in array hence that can be placed hence just attach 7 to this subsequence itself (don't create a subsequence starting at index=i=1);
   [1,7]
   at i=2,
   [1,7,8]
   at i=3 ,a[i]=4 now before 4 only 1 can come hence make a separate LIS  (we can't just make a separate subseqence starting from 4 because 1 is also there before 4 in array hence just prepend it as well to get longest (greedily));s
   [1,7,8]
   [1,4]
   at i=4
   [1,7,8]
   [1,4,5]
   at i=5
   [1,7,8]
   [1,4,5,6]
   at i=6, -1 create a separate for it
   [1,7,8]
   [1,4,5,6]
   [-1]
   at i=7, 9 (just append 9 to all of them);
   [1,7,8,9]
   [1,4,5,6,9]
   [-1,9]
   out of these max length = 5.

Here is a trick : since we only need length (not actual LIS) hence no need to all these subsequences separately.
  we can just proceed like
  i=0 [1]
  i=1 [1,7]
  i=2 [1,7,8]
  i=3 [1,4,8]  (Just replace 7 with 4)  (These subsequence actually denotes 2 subsequences [1,4] and [1,7,8] as well);
  i=4 [1,4,5]  (just replace 8 with 5);
  i=5 [1,4,5,6]
  i=6 [-1,4,5,6]
  i=7 [-1,4,5,6,9]  ==>length 5 (This is not actual LIS but it will give length of LIS for sure);
*/
/*
Coding ninja link : https://www.codingninjas.com/codestudio/problems/longest-increasing-subsequence_1062665?leftPanelTab=0 
See Submission :  Correct Answer 11/11 Test cases Passed 80 / 80 0%  13ms  =====> LIS_BS() submitted.

GFG Link : https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence-1587115620/1
==> Just see latest submission 
*/
