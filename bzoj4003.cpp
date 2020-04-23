#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <vector>

using namespace	std;
typedef long long data;

inline data in()
{
	data k = 0; int c = '\0', f = 1;
	for(; c > '9' || c < '0';)
        if((c = getchar()) == '-')
            f = 0;
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return f ? k : -k;
}

const int N = 300005;

#define Deepth(p) (p ? p -> dep : 0)

struct Node
{
    data key, k, b;
    int idx, dep;
    Node *l, *r;

    inline void Modify(data K, data B)
    {
        key = key * K + B, k *= K, b = K * b + B;
    }

    inline void PushDown()
    {
        if(k == 1 && b == 0) return ;
        if(l) l -> Modify(k, b);
        if(r) r -> Modify(k, b);
        k = 1, b = 0;
        return ;
    }
} node[N];

Node *root[N];

Node *Merge(Node *a, Node *b)
{
    if(a == NULL) return b;
    if(b == NULL) return a;
    if(a -> key > b -> key) swap(a, b);
    a -> PushDown();
    a -> r = Merge(a -> r, b);
    if(Deepth(a -> r) > Deepth(a -> l))
        swap(a -> l, a -> r);
    a -> dep = Deepth(a -> r) + 1;
    return a;
}

int n, m, ans1[N], ans2[N];
data h[N], f[N], a[N], s[N];
int pre[N], deg[N], dep[N], Q[N];

int main(int argc, char **argv)
{
    n = in(), m = in();
    memset(ans2, -1, sizeof(ans2));
    for(int i = 1; i <= n; i ++)
        h[i] = in();
    for(int i = 2; i <= n; i ++)
    {
        pre[i] = in(), f[i] = in(), a[i] = in();
        deg[pre[i]] ++, dep[i] = dep[pre[i]] + 1;
    }
    for(int i = 1; i <= m; i ++)
    {
        node[i].key = in(), node[i].k = 1, node[i].idx = i;
        s[i] = in(), root[s[i]] = Merge(root[s[i]], node + i);
    }
    int front = 0;
    for(int i = 1; i <= n; i ++)
        if(!deg[i])
            Q[++ front] = i;
    while(front)
    {
        int u = Q[front --];
        while(root[u] && root[u] -> key < h[u])
        {
            ans1[u] ++, ans2[root[u] -> idx] = dep[s[root[u] -> idx]] - dep[u];
            root[u] -> PushDown(), root[u] = Merge(root[u] -> l, root[u] -> r);
        }
        if(root[u])
        {
            if(f[u]) root[u] -> Modify(a[u], 0);
            else root[u] -> Modify(1, a[u]);
        }
        if(pre[u])
        {
            root[pre[u]] = Merge(root[pre[u]], root[u]);
            if(-- deg[pre[u]] == 0) Q[++ front] = pre[u];
        }
    }
    for(int i = 1; i <= n; i ++)
        printf("%d\n", ans1[i]);
    for(int i = 1; i <= m; i ++)
        printf("%d\n", ans2[i] == -1 ? dep[s[i]] + 1 : ans2[i]);
    return 0;
}

