#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <queue>
#include    <vector>

#define     foreach(u)     for(int i = head[u]; i; i = e[i].next)

using	namespace	std;
const   int INF = 0x3f3f3f3f;
typedef pair<int, int> Item;
typedef long long   data;

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

/*
   struct Edge {int v, next;};

   int sig, head[N];

   inline void AddEdge(int u, int v)
   {
   e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
   }
   */

const   int N = 300, M = 2000;

int D[N], P[N], d[N][M], pre[N][M];
vector<int> ans;

void Print(int m, int j)
{
    if(!m) return ;
    Print(m - 1, j + D[pre[m][j]] - P[pre[m][j]]);
    ans.push_back(pre[m][j]);
    return ;
}

inline bool Selected(int i, int j, int k)
{
    while(i)
    {
        if(pre[i][j + M] == k) return true;
        j += D[pre[i][j + M]] - P[pre[i][j + M]], i --;
    }
    return false;
}

int main(int argc, char **argv)
{
#define LOCAL
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int T = 0, n, m;
    while(scanf("%d%d", &n, &m) == 2 && n)
    {
        for(int i = 1; i <= n; i ++)
            P[i] = in(), D[i] = in();
        memset(d, 128, sizeof(d));
        memset(pre, 0, sizeof(pre));
        d[0][0 + M] = 0;
        for(int i = 1; i <= m; i ++)
        {
            for(int j = -400; j <= 400; j ++)
            {
                if(d[i - 1][j + M] < 0) continue ;
                for(int k = 1; k <= n; k ++)
                {
                    int Q = D[k] - P[k], x = d[i - 1][j + M] + D[k] + P[k];
                    if(x > d[i][j - Q + M] && !Selected(i - 1, j, k))
                        d[i][j - Q + M] = x, pre[i][j - Q + M] = k;
                }
            }
        }

        int p = 0, q = -1;
        while(d[m][p + M] < 0 && p < M) p ++;
        while(d[m][q + M] < 0 && q > -M) q --;
        ans.clear();
        if(p < -q) Print(m, p + M);
        else if(p > -q) Print(m, q + M);
        else Print(m, d[m][p + M] > d[m][q + M] ? p + M : q + M);
        int sumP = 0, sumD = 0;
        sort(ans.begin(), ans.end());
        for(int i = 0; i < m; i ++)
            sumP += P[ans[i]], sumD += D[ans[i]];
        printf("Jury #%d\n", ++ T);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", sumP, sumD);
        for(int i = 0; i < m; i ++)
            printf(" %d", ans[i]);
        puts("\n");
    }
    return 0;
}
