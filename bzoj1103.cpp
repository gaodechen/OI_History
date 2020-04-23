#include    <cstdio>
#include    <cstring>

using   namespace   std;
const   int N = 250001;

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

struct Edge {int v, next;} e[N+N];

int n, m, sig, head[N];

inline void AddEdge(int u, int v)
{
    e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
}

int node[N+N];

inline int lowbit(int x) {return x & (-x);}

inline void Modify(int p, int x)
{
    for(; p <= n + n; p += lowbit(p))
        node[p] += x;
}

inline int Query(int p)
{
    int r = 0;
    for(; p; p -= lowbit(p))
        r += node[p];
    return r;
}

int tik, pos1[N], pos2[N];

inline void DFS() {
    int stack[N] = {0}, pre[N], top;
    stack[top = 1] = 1, pre[1] = 1;
    while(top) {
        int u = stack[top--];
        if(!pos1[u]) {
            stack[++top] = u;
            pos1[u] = ++ tik;
            for(int i = head[u]; i; i = e[i].next) {
                int v = e[i].v;
                if(v != pre[u]) {
                    stack[++top] = v;
                    pre[v] = u;
                }
            }
        }
        else
            pos2[u] = ++ tik;
    }
    return ;
}

int main()
{
    n = in();
    for(int i = 1; i < n; i ++)
    {
        int u = in(), v = in();
        AddEdge(u, v), AddEdge(v, u);
    }
    DFS();
    m = in();
    for(int i = 1; i <= n; i ++)
        Modify(pos1[i], 1), Modify(pos2[i], -1);
    for(int i = 0; i < n + m - 1; i ++)
    {
        char buf[1];
        scanf("%s", buf);
        if(buf[0] == 'A')
        {
            in(); int x = in();
            Modify(pos1[x], -1);
            Modify(pos2[x], 1);
        }
        else
            printf("%d\n", Query(pos1[in()]) - 1);
    }
    return 0;
}
