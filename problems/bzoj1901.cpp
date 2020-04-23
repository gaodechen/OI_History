#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 2e4 + 5;
const   int M = 2e6 + 5;

struct Node
{
    int lson, rson, val;
} node[M];

struct Item
{
    int type, a, b, k;
} oper[N];

inline int in()
{
	int k = 0, c = '\0', o = 1;
	for(; c > '9' || c < '0';)
    {
		c = getchar();
        if(c == '-')
            o = -1;
    }
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
    if(o == -1)
        return -k;
	return k;
}

int a[N], b[N], bit[N];
int n, m, q, size, root[N];

inline int lowbit(int x)
{
    return x & (-x);
}

void Insert(int pre, int &p, int l, int r, int x)
{
    p = ++ size;
    node[p] = node[pre];
    node[p].val ++;
    if(l == r)
        return ;
    int mid = (l + r) >> 1;
    if(x <= mid)
        Insert(node[pre].lson, node[p].lson, l, mid, x);
    else
        Insert(node[pre].rson, node[p].rson, mid + 1, r, x);
    return ;
}

void Update(int &p, int l, int r, int x, int k)
{
    if(!p)
        p = ++ size;
    node[p].val += k;
    if(l == r)
        return ;
    int mid = (l + r) >> 1;
    if(x <= mid)
        Update(node[p].lson, l, mid, x, k);
    else
        Update(node[p].rson, mid + 1, r, x, k);
    return ;
}

inline void Modify(int p, int x)
{
    for(int t = p; t <= n; t += lowbit(t))
        Update(bit[t], 1, m, a[p], -1);
    a[p] = x;
    for(int t = p; t <= n; t += lowbit(t))
        Update(bit[t], 1, m, x, 1);
    return ;
}

int L[N], R[N];

inline int Query(int l, int r, int k)
{
    int x = 1, y = 1;
    L[1] = root[l-1], R[1] = root[r];
    for(int p = l - 1; p; p -= lowbit(p))
        L[++ x] = bit[p];
    for(int p = r; p; p -= lowbit(p))
        R[++ y] = bit[p];
    l = 1, r = m;
    while(l < r)
    {
        int cnt = 0, mid = (l + r) >> 1;
        for(int i = 1; i <= x; i ++)
            cnt -= node[node[L[i]].lson].val;
        for(int i = 1; i <= y; i ++)
            cnt += node[node[R[i]].lson].val;
        if(cnt >= k)
        {
            for(int i = 1; i <= x; i ++)
                L[i] = node[L[i]].lson;
            for(int i = 1; i <= y; i ++)
                R[i] = node[R[i]].lson;
            r = mid;
        }
        else
        {
            for(int i = 1; i <= x; i ++)
                L[i] = node[L[i]].rson;
            for(int i = 1; i <= y; i ++)
                R[i] = node[R[i]].rson;
            l = mid + 1;
            k -= cnt;
        }
    }
    return b[l];
}

int main()
{
    char buf[2];
    n = in(), q = in();
    for(int i = 1; i <= n; i ++)
        a[i] = b[i] = in();
    m = n;
    for(int i = 1; i <= q; i ++)
    {
        scanf("%s", buf);
        oper[i].type = buf[0] == 'C';
        oper[i].a = in(), oper[i].b = in();
        if(oper[i].type)
            b[++m] = oper[i].b;
        else
            oper[i].k = in();
    }
    sort(b + 1, b + m + 1);
    for(int i = 1; i <= n; i ++)
    {
        a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
        Insert(root[i-1], root[i], 1, m, a[i]);
    }
    for(int i = 1; i <= q; i ++)
    {
        if(oper[i].type)
        {
            oper[i].b = lower_bound(b + 1, b + m + 1, oper[i].b) - b;
            Modify(oper[i].a, oper[i].b);
        }
        else
            printf("%d\n", Query(oper[i].a, oper[i].b, oper[i].k));
    }
    return 0;
}
