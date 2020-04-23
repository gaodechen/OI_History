#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <queue>

using   namespace   std;
typedef long long   data;
const   int N = 2e5 + 5;
const   int M = 1e6 + 5;

inline data in()
{
	data k = 0; int c = '\0';
	for(; c > '9' || c < '0';)
		c = getchar();
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

int n, sig, head[N], head_[N];
struct Edge {int v, next;} e[M+M];

inline void AddEdge(int u, int v)
{
    e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
    e[++sig].v = u, e[sig].next = head_[v], head_[v] = sig;
}

queue<int> q;
bool inq[N];
data s[N], k[N], f[N], d[N];

int main()
{
    scanf("%d", &n);
    for(int i = 1, r; i <= n; i ++)
    {
        s[i] = in(), k[i] = in();
        scanf("%d", &r);
        while(r --)
            AddEdge(i, in());
    }
    for(int i = 1; i <= n; i ++)
        q.push(i), d[i] = k[i], inq[i] = 1;
    for(int u = 1; u <= n; u ++)
        for(int i = head[u]; i; i = e[i].next)
            f[u] += k[e[i].v];
    while(!q.empty())
    {
        int u = q.front();
        q.pop(), inq[u] = 0;
        data x = f[u] + s[u];
        if(d[u] > x)
        {
            for(int i = head_[u]; i; i = e[i].next)
            {
                int v = e[i].v;
                f[v] = f[v] - d[u] + x;
                if(!inq[v])
                    inq[v] = 1, q.push(v);
            }
            d[u] = x;
        }
    }
    printf("%lld", d[1]);
    return 0;
}
