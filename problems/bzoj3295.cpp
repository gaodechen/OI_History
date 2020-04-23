#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef long long   data;
const   int N = 1e5 + 5;
const   int M = 5e6 + 5;

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

data invSum;
int n, m, size, L[N], R[N], a[N];
int pre[N], suf[N], bit[N], pos[N];
int root[N], lson[M], rson[M], val[M];

inline int lowbit(int x)
{
    return x & (-x);
}

inline void BIT_Insert(int p)
{
    for(; p <= n; p += lowbit(p))
        bit[p] ++;
    return ;
}

inline int BIT_Sum(int p)
{
    int r = 0;
    for(; p; p -= lowbit(p))
        r += bit[p];
    return r;
}

void Update(int &p, int l, int r, int x)
{
    if(!p)
        p = ++ size;
    val[p] ++;
    if(l != r)
    {
        int mid = (l + r) >> 1;
        if(x <= mid)
            Update(lson[p], l, mid, x);
        else
            Update(rson[p], mid + 1, r, x);
    }
    return ;
}

inline int Query1(int p, int q, int x)
{
    int a = 0, b = 0, sum = 0;
    for(int i = p; i; i -= lowbit(i))
        L[a++] = root[i];
    for(int i = q; i; i -= lowbit(i))
        R[b++] = root[i];
    int l = 1, r = n;
    while(l != r)
    {
        int mid = (l + r) >> 1;
        if(x <= mid)
        {
            for(int i = 0; i < a; i ++)
                sum -= val[rson[L[i]]], L[i] = lson[L[i]];
            for(int i = 0; i < b; i ++)
                sum += val[rson[R[i]]], R[i] = lson[R[i]];
            r = mid;
        }
        else
        {
            for(int i = 0; i < a; i ++)
                L[i] = rson[L[i]];
            for(int i = 0; i < b; i ++)
                R[i] = rson[R[i]];
            l = mid + 1;
        }
    }
    return sum;
}

inline int Query2(int p, int q, int x)
{
    int a = 0, b = 0, sum = 0;
    for(int i = p; i; i -= lowbit(i))
        L[a++] = root[i];
    for(int i = q; i; i -= lowbit(i))
        R[b++] = root[i];
    int l = 1, r = n;
    while(r - l)
    {
        int mid = (l + r) >> 1;
        if(x > mid)
        {
            for(int i = 0; i < a; i ++)
                sum -= val[lson[L[i]]], L[i] = rson[L[i]];
            for(int i = 0; i < b; i ++)
                sum += val[lson[R[i]]], R[i] = rson[R[i]];
            l = mid + 1;
        }
        else
        {
            for(int i = 0; i < a; i++)
                L[i] = lson[L[i]];
            for(int i = 0; i < b; i ++)
                R[i] = lson[R[i]];
            r = mid;
        }
    }
    return sum;
}

int main()
{
    n = in(), m = in();
    for(int i = 1; i <= n; i ++)
    {
        a[i] = in(), pos[a[i]] = i;
        pre[i] = BIT_Sum(n) - BIT_Sum(a[i] - 1);
        BIT_Insert(a[i]);
        invSum += pre[i];
    }
    memset(bit, 0, sizeof(bit));
    for(int i = n; i >= 1; i --)
    {
        suf[i] = BIT_Sum(a[i]);
        BIT_Insert(a[i]);
    }
    while(m --)
    {
        int k = pos[in()], d1, d2;
        printf("%lld\n", invSum);
        d1 = Query1(0, k - 1, a[k]);
        d2 = Query2(k, n, a[k]);
        invSum -= pre[k] + suf[k] - d1 - d2;
        for(int i = k; i <= n; i += lowbit(i))
            Update(root[i], 1, n, a[k]);
    }
    return 0;
}
