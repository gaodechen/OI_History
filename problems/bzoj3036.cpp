#include    <cstdio>
#include    <cstring>
#include    <queue>

using   namespace   std;
const   int N = 1e5 + 5;

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

struct Edge {int v, w, next;} e[N+N];

double f[N];
int head[N], inDeg[N], deg[N];

inline void AddEdge(int u, int v, int w)
{
    static int sig = 0;
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
}

int main()
{
    int n = in(), m = in();
    for(int i = 0; i < m; i ++)
    {
        int u = in(), v = in(), w = in();
        AddEdge(v, u, w), deg[u] ++;
    }
    memcpy(inDeg, deg, sizeof(deg));
    queue<int> q;
    q.push(n);
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        if(deg[u]) f[u] /= deg[u];
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            f[v] += f[u] + e[i].w;
            if(-- inDeg[v] == 0)
                q.push(v);
        }
    }
    printf("%.2lf\n", f[1]);
    return 0;
}
