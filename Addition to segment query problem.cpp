// There is an array of n elements, initially filled with zeros. You need to write a data structure that processes two types of queries:
// 1. add to the segment from l to r−1 the number v (input: 1 l r v)
// 2. find the current value of element i (input: 2 i)

#include <iostream>
#include <bits/stdc++.h>
#include <string.h>

using namespace std;

typedef long long int ll;
#define FASTIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

void solve();

void update(ll node, ll l, ll r, ll s, ll e, ll seg[], ll val)
{
    if (l >= s && r <= e)
    {
        seg[node] += val;
        return;
    }
    ll mid = (l + r) / 2;
    if (s <= mid)
    {
        update(node * 2, l, mid, s, e, seg, val);
    }
    if (e > mid)
    {
        update(node * 2 + 1, mid + 1, r, s, e, seg, val);
    }
}

ll result(ll node, ll l, ll r, ll seg[], ll ind)
{
    if (l == r)
    {
        return seg[node];
    }
    ll mid = (l + r) / 2, ans = seg[node];
    if (ind <= mid)
    {
        ans += result(node * 2, l, mid, seg, ind);
    }
    else
    {
        ans += result(node * 2 + 1, mid + 1, r, seg, ind);
    }
    return ans;
}

int main()
{
    FASTIO
    ll i, j, n, m, q, l, r, v;
    cin >> n >> m;
    for (i = 1; i < n; i *= 2)
        ;
    n = i;
    ll seg[n * 2] = {};
    while (m--)
    {
        cin >> q;
        if (q == 1)
        {
            cin >> l >> r >> v;
            update(1, 0, n - 1, l, r - 1, seg, v);
        }
        else
        {
            cin >> i;
            cout << result(1, 0, n - 1, seg, i) << endl;
        }
    }
    return 0;
}
