#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
typedef unsigned long long data;
const   int N = 100010, M = 8000000;
const   int H = 131, MOD = 100007;

inline int in()
{
	int k = 0, c = '\0';
	for(; c > '9' || c < '0';)
		c = getchar();
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

data val[N];
int head[N], next[N], ind;

int HashInsert(data k)
{
    int t = k % MOD;
    for(int i = head[t]; i; i = next[i])
        if(val[i] == k)
            return i;
    val[++ind] = k;
    next[ind] = head[t];
    head[t] = ind;
    return ind;
}

int HashFind(data k)
{
    int t = k % MOD;
    for(int i = head[t]; i; i = next[i])
        if(val[i] == k)
            return i;
    return 0;
}

data h[N];
int n, m, k, size, a[N];
int root[N], lson[M], rson[M], sum[M];

void Insert(int &p, int pre, int l, int r, int x)
{
    p = ++ size;
    sum[p] = sum[pre] + 1;
    lson[p] = lson[pre];
    rson[p] = rson[pre];
    if(l == r)
        return ;
    int mid = (l + r) >> 1;
    if(x <= mid)
        Insert(lson[p], lson[pre], l, mid, x);
    else
        Insert(rson[p], rson[pre], mid + 1, r, x);
    return ;
}

bool Query(int a, int b, int l, int r, int x)
{
    if(l == r)
        return sum[b] > sum[a];
    if(sum[b] - sum[a] == 0)
        return 0;
    int mid = (l + r) >> 1;
    if(x <= mid)
        return Query(lson[a], lson[b], l, mid, x);
    return Query(rson[a], rson[b], mid + 1, r, x);
}

int main()
{
    n = in(), m = in(), k = in();
    for(int i = 1; i <= n; i ++)
        a[i] = in();
    data tmp = 1;
    for(int i = 1; i <= k; i ++)
        tmp *= H;
    for(int i = 1; i <= n; i ++)
        h[i] = h[i-1] * H + a[i];
    for(int i = n; i >= k; i --)
    {
        h[i] = h[i] - h[i-k] * tmp;
        HashInsert(h[i]);
    }
    for(int i = k; i <= n; i ++)
    {
        int x = HashFind(h[i]);
        Insert(root[i], root[i-1], 1, ind, x);
    }
    while(m --)
    {
        data s = 0;
        int l = in(), r = in(), x;
        for(int j = 0; j < k; j ++)
            s = s * H + in();
        x = HashFind(s);
        if(x && r - l + 1 >= k && Query(root[l+k-2], root[r], 1, ind, x))
            puts("No");
        else
            puts("Yes");
    }
    return 0;
}
