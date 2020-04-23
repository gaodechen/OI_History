#include    <cstdio>
#include    <cstring>
#include    <iostream>

using	namespace	std;
const   int N = 3e4 + 5;
const   int INF = 0x3f3f3f3f;

inline int in()
{
	int k = 0, c = '\0', f = 1;
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

bool rev[N];
int pre[N], val[N], sum[N], son[N][2];

inline bool isRoot(int u) {return son[pre[u]][0] != u && son[pre[u]][1] != u;}
inline void Update(int u) {sum[u] = sum[son[u][0]] + sum[son[u][1]] + val[u];}
inline void PushDown(int u) {if(rev[u]) rev[son[u][0]] ^= 1, rev[son[u][1]] ^= 1, rev[u] = 0, swap(son[u][0], son[u][1]);}

inline void Rotate(int x)
{
    int p = pre[x], z = pre[p], g = x == son[p][1], y = son[x][g ^ 1];
    if(p == son[z][0]) son[z][0] = x; else if(p == son[z][1]) son[z][1] = x;
    pre[x] = z, son[p][g] = y, pre[y] = p, son[x][g ^ 1] = p, pre[p] = x;
    return (void) (Update(p));
}

inline void Splay(int p)
{
    PushDown(p);
    while(!isRoot(p))
    {
        int x = pre[p], y = pre[x];
        PushDown(y), PushDown(x), PushDown(p);
        if(isRoot(x))
            Rotate(p);
        else if((p == son[x][0]) ^ (x == son[y][0]))
            Rotate(p), Rotate(p);
        else
            Rotate(x), Rotate(p);
    }
    return (void) (Update(p));
}

inline void Access(int u) {for(int p = 0; u; u = pre[u]) Splay(u), son[u][1] = p, p = u;}
inline void MakeRoot(int u) {Access(u), Splay(u), rev[u] ^= 1;}
inline void Link(int u, int v) {MakeRoot(u), pre[u] = v;}
inline int Find(int u) {Access(u), Splay(u); while(son[u][0]) u = son[u][0]; return u;}

int main(int argc, char **argv)
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int n = in();
    for(int i = 1; i <= n; i ++)
        val[i] = sum[i] = in();
    int Q = in();
    while(Q --)
    {
        char s[10]; int u, v;
        scanf("%s", s), u = in(), v = in();
        if(s[0] == 'b')
        {
            int x = Find(u), y = Find(v);
            if(x == y) puts("no");
            else puts("yes"), Link(u, v);
        }
        else if(s[0] == 'p')
            Splay(u), val[u] = v, Update(u);
        else
        {
            int x = Find(u), y = Find(v);
            if(x != y) puts("impossible");
            else
            {
                MakeRoot(u), Access(v), Splay(v);
                printf("%d\n", sum[v]);
            }
        }
    }
    return 0;
}
