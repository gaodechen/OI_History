#include    <cstdio>
#include    <cstring>
#include    <iostream>
 
using   namespace   std;
const   int N = 5e5 + 5;
 
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

struct Edge {int v, w, next;} e[N<<1];
 
int n, root, head[N], d[N];
long long ans;
 
inline void AddEdge(int u, int v, int w)
{
    static int sig = 0;
    e[++sig].v = v, e[sig].w = w;
    e[sig].next = head[u], head[u] = sig;
}

bool ins[N];
int stack[N], pre[N], top;
 
void DFS(int root)
{
    stack[top = 1] = root;
    while(top)
    {
        int u = stack[top--];
        if(!ins[u]) {
            stack[++ top] = u, ins[u] = 1;
            for(int i = head[u]; i; i = e[i].next) {
                int v = e[i].v;
                if(v != pre[u]) {
                    pre[v] = u, stack[++top] = v;
                }
            }
        } else {
            for(int i = head[u]; i; i = e[i].next) {
                int v = e[i].v;
                if(v != pre[u]) {
                    d[u] = max(d[u], d[v] + e[i].w);
                }
            }
            for(int i = head[u]; i; i = e[i].next) {
                int v = e[i].v;
                if(v != pre[u])
                    ans += d[u] - e[i].w - d[v];
            }
        }
    }
    return ;
}
 
int main(int argc, char **argv)
{
    n = in(), root = in();
    for(int i = 1; i < n; i ++)
    {
        int u = in(), v = in(), w = in();
        AddEdge(u, v, w), AddEdge(v, u, w);
    }
    DFS(root);
    printf("%lld\n", ans);
    return 0;
}
