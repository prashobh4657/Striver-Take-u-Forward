#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define mod 1000000007
#define endl "\n"
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
template <typename T>
istream &operator>>(istream &input, vector<T> &v)
{
    for (auto &i : v)
        cin >> i;
    return input;
}
template <typename T>
ostream &operator<<(ostream &output, vector<T> &v)
{
    for (auto &i : v)
        cout << i << " ";
    return output;
}
int lowerBound(vector<int> &a, int x)
{
    int n = a.size();
    int low = 0, high = n - 1;
    int ans = n;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (a[mid] >= x)
        {
            ans = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    return ans;
}
int upperBound(vector<int> &a, int x)
{
    int n = a.size();
    int low = 0, high = n - 1;
    int ans = n;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (a[mid] > x)
        {
            ans = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    return ans;
}
int32_t main()
{
    fio;
    return 0;
}
// Lower Bound: https://bit.ly/43967G5 ==> Just see latest submission (Exactly above codes submitted);
// Upper Bound: https://bit.ly/3IoKGce ==> Just see latest submission (Exactly above codes submitted);
// Search Insert Position: https://bit.ly/3ocI0HW ==> Just see latest submission
// Floor and Ceil: https://www.codingninjas.com/studio/problems/ceiling-in-a-sorted-array_1825401 
