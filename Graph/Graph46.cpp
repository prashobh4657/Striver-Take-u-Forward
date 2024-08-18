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
class DisjointSet
{
    vector<int> rank, parent, size;

public:
    DisjointSet(int n)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }
    int findUPar(int node)
    {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }
    void unionByRank(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
            return;
        if (rank[ulp_u] < rank[ulp_v])
            parent[ulp_u] = ulp_v;
        else if (rank[ulp_v] < rank[ulp_u])
            parent[ulp_v] = ulp_u;
        else
        {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
    void unionBySize(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
            return;
        if (size[ulp_u] < size[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};
int32_t main()
{
    fio;
    DisjointSet ds(7);
    ds.unionByRank(1, 2);
    ds.unionByRank(2, 3);
    ds.unionByRank(4, 5);
    ds.unionByRank(6, 7);
    ds.unionByRank(5, 6);
    if (ds.findUPar(3) == ds.findUPar(7)) // if 3 and 7 same or not
        cout << "Same\n";
    else
        cout << "Not same\n";
    ds.unionByRank(3, 7);
    if (ds.findUPar(3) == ds.findUPar(7))
        cout << "Same\n";
    else
        cout << "Not same\n";

    DisjointSet ds1(7);
    ds1.unionBySize(1, 2);
    ds1.unionBySize(2, 3);
    ds1.unionBySize(4, 5);
    ds1.unionBySize(6, 7);
    ds1.unionBySize(5, 6);
    if (ds1.findUPar(3) == ds1.findUPar(7)) // if 3 and 7 same or not
        cout << "Same\n";
    else
        cout << "Not same\n";
    ds1.unionBySize(3, 7);
    if (ds1.findUPar(3) == ds1.findUPar(7))
        cout << "Same\n";
    else
        cout << "Not same\n";
    return 0;
}
/*
Given a graph.
If you are asked does node x and y belong to same component?
==> Manually apply dfs starting from node x and if in b/w y is traversed then yes else no.
==> Time complexity would be O(n);
==> Disjoint set data structure ==> Do this in O(1).
==> These are generally used in dynamic graphs.
==> It provides two functions ==> union (by size or by rank), find_parent();
==> We will discuss first union by rank.
*/
/*
Make two vectors
1. rank (intialised to 0)
2. parent (intialised to i itself) {parent[i]=i}
Union(u,v)
1. Find ultimate parent of u and v. let it be pu and pv.
2. Find rank of pu and pv.
3. connect smaller rank to larger rank together and update parent and rank vector accordingly.


Now to answer does x and y belong to same component?
==> Find ultimate parent of x and y. If they are same means they belong to same component else do not.
==> To find ulitmate parent log(n) complexity. Here more optimisation will be applied that is path compression.
==> Let say chain is like this a-->b-->c-->d  since we know a will be ultimate parent for all of these nodes.
    Hence on connecting new node to this component we will just connect that node to ultimate parent only.
    Let (d,e);
    So no need to connect link b/w d and e.
    Since d know his ultimate parent is a hence for e also ultimate parent will be a.
    Hence, parent[e]=a;

    Hence basically b,c,d all will directly connect to a itself.
    There is no sense of link b/w b and c and c and d like that.

    But we will not make any changes to rank. Its functioning will remain same as that was before applying optimisation.
    Since it can't be reduced to hence it is called as rank not height.

Time complexity of union : O(4*alpha) ==> as good as ==> O(constant) which is like  O(1);
                           O(4*alpha) has big mathematics derivation (Not imp);



// Line 41 ==> return parent[node]=findUPar(parent[node]); Itself is doing path compression as we are storing result in parent[node]
               similar to DP.
*/

/*
Why connecting smaller rank component to larger rank component?
==> To find ultimate parent of nodes it would be easy. Tree would be balanced somewhat.
==> It reduce travel time.
*/

// Union by Size is more intuitive
// TC : Same as TC of Union = O(4*alpha) = O(1).