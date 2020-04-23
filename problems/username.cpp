#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <cmath>
#include    <queue>
#include    <vector>

using namespace	std;
const int INF = 0x3f3f3f3f;
typedef long long data;
typedef pair<data, data> Hash;

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

const int N = 400005;

char buf[N];
int A[N], v[N], X[N], Y[N], sa[N], height[N], *Rank;

inline bool cmp(int *p, int a, int b, int l)
{
    return p[a] == p[b] && p[a + l] == p[b + l];
}

inline void InitSA(int n, int m)
{
    int *x = X, *y = Y;

    for(int i = 0; i < m; i ++) v[i] = 0;
    for(int i = 0; i < n; i ++) v[x[i] = A[i]] ++;
    for(int i = 1; i < m; i ++) v[i] += v[i - 1];
    for(int i = 0; i < n; i ++) sa[-- v[x[i]]] = i;

    for(int k = 1; k <= n; k <<= 1)
    {
        int p = 0;
        for(int i = n - 1; i >= n - k; i --) y[p ++] = i;
        for(int i = 0; i < n; i ++) if(sa[i] >= k) y[p ++] = sa[i] - k;

        for(int i = 0; i < m; i ++) v[i] = 0;
        for(int i = 0; i < n; i ++) v[x[y[i]]] ++;
        for(int i = 1; i < m; i ++) v[i] += v[i - 1];
        for(int i = n - 1; i >= 0; i --) sa[-- v[x[y[i]]]] = y[i];

        swap(x, y), p = 1, x[sa[0]] = 0;
        for(int i = 1; i < n; i ++)
        {
            if(cmp(y, sa[i], sa[i - 1], k)) x[sa[i]] = p - 1;
            else x[sa[i]] = p ++;
        }

        if((m = p) >= n) break ;
    }

    return (void) (Rank = X);
}

inline void InitHeight(int n)
{
    int k = 0;
    for(int i = 0; i < n; i ++)
        Rank[sa[i]] = i;
    for(int i = 0; i < n; i ++)
    {
        if(k != 0) k --;
        if(!Rank[i]) continue ;
        int j = sa[Rank[i] - 1];
        while(A[i + k] == A[j + k]) k ++;
        height[Rank[i]] = k;
    }
    return ;
}

int d[N][20], P[N];

inline void InitRMQ(int n)
{
    for(int i = 0; i < n; i ++)
        d[i][0] = height[i];
    for(int j = 1; j <= P[n]; j ++)
        for(int i = 0; i + (1 << j) - 1 < n; i ++)
            d[i][j] = min(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
    return ;
}

inline int RMQ(int l, int r)
{
    int k = P[r - l + 1];
    return min(d[l][k], d[r - (1 << k) + 1][k]);
}

inline int LCP(int a, int b)
{
    a = Rank[a], b = Rank[b];
    if(a > b) swap(a, b);
    return RMQ(a + 1, b);
}

struct SegmentTree
{
    struct Node
    {
        int val;
        Node *lson, *rson;
    } *root[N];

    Node pool[N * 20];

    inline Node *NewNode(Node *a, Node *b)
    {
        static Node *T = pool;
        T -> lson = a, T -> rson = b;
        return T ++;
    }

    inline void Initialize()
    {
        root[0] = NewNode(NULL, NULL);
        root[0] -> lson = root[0] -> rson = root[0];
        return ;
    }

    Node *Insert(Node *p, int l, int r, int x)
    {
        Node *a = NewNode(p -> lson, p -> rson);
        a -> val = p -> val + 1; 
        if(l == r) return a;
        int mid = (l + r) >> 1;
        if(x <= mid)
            a -> lson = Insert(p -> lson, l, mid, x);
        else
            a -> rson = Insert(p -> rson, mid + 1, r, x);
        return a;
    }

    int Query(Node *a, Node *b, int l, int r, int L, int R)
    {
        if(L == l && R == r)
            return b -> val - a -> val;
        int mid = (l + r) >> 1;
        if(R <= mid)
            return Query(a -> lson, b -> lson, l, mid, L, R);
        if(L > mid)
            return Query(a -> rson, b -> rson, mid + 1, r, L, R);
        int A = Query(a -> lson, b -> lson, l, mid, L, mid);
        int B = Query(a -> rson, b -> rson, mid + 1, r, mid + 1, R);
        return A + B;
    }
} T;

inline void PUTS(int x, int L)
{
    for(int i = x; i < L; i ++)
        putchar(A[i]);
    cout << endl;
    return ;
}

int length[N / 2], pos[N / 2];

int main(int argc, char **argv)
{
    freopen("username.in", "r", stdin);
    // freopen("username.out", "w", stdout);
    int n = in(), Q = in(), L = 0;
    P[0] = -1;
    for(int i = 1; i < N; i ++)
        P[i] = P[i - 1] + ((i & (i - 1)) == 0);
    for(int i = 0; i < n; i ++)
    {
        scanf("%s", buf);
        length[i] = strlen(buf);
        if(i) A[L ++] = '}';
        pos[i] = L;
        for(int j = 0; j < length[i]; j ++)
            A[L ++] = buf[j];
    }
    pos[n] = L;
    InitSA(L, 128), InitHeight(L), InitRMQ(L);
    T.Initialize();
    for(int i = 0; i < L; i ++)
        T.root[i + 1] = T.Insert(T.root[i], 0, L, Rank[i]);
    while(Q --)
    {
        int qL = in(), qR = in(), p = in() - 1, i = pos[p];
        qL = pos[qL - 1], qR = pos[qR];
        int l = 0, r = Rank[i], sideL, sideR;
        while(l < r)
        {
            int mid = (l + r) >> 1;
            if(LCP(sa[mid], i) >= length[p])
                r = mid;
            else
                l = mid + 1;
        }
        sideL = l, l = Rank[i], r = L - 1;
        while(l < r)
        {
            int mid = (l + r + 1) >> 1;
            if(LCP(sa[mid], i) >= length[p])
                l = mid;
            else
                r = mid - 1;
        }
        sideR = l;
        printf("%d\n", T.Query(T.root[qL], T.root[qR], 0, L, sideL, sideR));
    }
    return 0;
}
