#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 5e4 + 5;
const   int M = 5e5 + 5;
const   int INF = 0x3f3f3f3f;

inline int in()
{
	int k = 0, c = '\0';
	for( ; c > '9' || c < '0'; )
		c = getchar();
	for( ; c >= '0' && c <= '9'; )
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

struct Node
{
    int val, l, r;
    Node *lson, *rson;

    inline Node *NewNode()
    {
        static Node pool[N<<1], *tail = pool;
        return tail ++;
    }

    inline void PushUp()
    {
        return (void) (val = min(lson -> val, rson -> val));
    }

    inline void BuildTree(int l, int r)
    {
        this -> l = l, this -> r = r;
        if(l != r)
        {
            int mid = (l + r) >> 1;
            (lson = NewNode()) -> BuildTree(l, mid);
            (rson = NewNode()) -> BuildTree(mid + 1, r);
        }
        return (void) (val = INF);
    }

    inline void Update(int p, int k)
    {
        if(l == r)
            val = k;
        else
        {
            int mid = (l + r) >> 1;
            if(p <= mid)
                lson -> Update(p, k);
            else
                rson -> Update(p, k);
            PushUp();
        }
        return ;
    }

    inline int Query(int L, int R)
    {
        if(L <= l && R >= r)
            return val;
        int mid = (l + r) >> 1;
        int a = INF, b = INF;
        if(L <= mid)
            a = lson -> Query(L, R);
        if(R > mid)
            b = rson -> Query(L, R);
        return min(a, b);
    }
} *root = NULL;

int n, m, d[N];

int main()
{
    n = in(), m = in();
    d[1] = 0;
    memset(d, 0x3f, sizeof(d));
    root = root -> NewNode();
    root -> BuildTree(1, n);
    root -> Update(1, 0);
    for(int i = 1; i <= m; i ++)
    {
        int l = in(), r = in();
        int k = root -> Query(l, r);
        if(k < INF)
        {
            d[r] = min(d[r], k + 1);
            root -> Update(r, d[r]);
        }
    }
    printf("%d\n", d[n]);
    return 0;
}
