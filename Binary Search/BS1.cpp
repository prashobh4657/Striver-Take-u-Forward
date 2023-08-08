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
int BS_Recursive(vector<int> &a, int low, int high, int target)
{
    int n = a.size();
    if (low > high)
        return -1;
    int mid = low + (high - low) / 2;
    if (a[mid] == target)
        return mid;
    else if (a[mid] < target)
        return BS_Recursive(a, mid + 1, high, target);
    return BS_Recursive(a, low, mid - 1, target);
}
int BS(vector<int> &a, int target)
{
    int n = a.size();
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (a[mid] == target)
            return mid;
        else if (a[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}
int32_t main()
{
    fio;
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    int target;
    cin >> target;
    cout << BS(a, target) << endl;
    cout << BS_Recursive(a, 0, a.size() - 1, target) << endl;
    return 0;
}
