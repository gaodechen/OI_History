#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 1005;
const int INF = 0x3f3f3f3f;

int n, cnt;
bool val[N];
int fail[N], son[N][4], hash[256];

inline void Insert(char *s)
{
    int l = strlen(s), p = 0;
    for(int i = 0; i < l; i ++)
    {
        int c = hash[(int) s[i]];
        if(son[p][c] == -1)
            son[p][c] = cnt ++;
        p = son[p][c];
    }
    val[p] = 1;
    return ;
}

inline void InitFail()
{
    queue<int> q;
    for(int i = 0; i < 4; i ++)
    {
        if(son[0][i] == -1)
            son[0][i] = 0;
        else
            q.push(son[0][i]);
    }
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        val[u] |= val[fail[u]];
        for(int i = 0; i < 4; i ++)
        {
            if(son[u][i] == -1)
                son[u][i] = son[fail[u]][i];
            else
            {
                fail[son[u][i]] = son[fail[u]][i];
                q.push(son[u][i]);
            }
        }
    }
    return ;
}

char buf[N];
int d[N][N];

int main(int argc, char **argv)
{
    hash['A'] = 0, hash['G'] = 1, hash['C'] = 2, hash['T'] = 3;
    int Q = 0;
    while(scanf("%d", &n) == 1 && n)
    {
        cnt = 1;
        memset(son, -1, sizeof(son));
        memset(val, 0, sizeof(val));
        memset(fail, 0, sizeof(fail));
        for(int i = 0; i < n; i ++)
        {
            scanf("%s", buf);
            Insert(buf);
        }
        scanf("%s", buf + 1);
        InitFail();
        n = strlen(buf + 1);
        memset(d, INF, sizeof(d));
        d[0][0] = 0;
        for(int i = 0; i < n; i ++)
        {
            for(int u = 0; u < cnt; u ++)
            {
                for(int c = 0; c < 4; c ++)
                {
                    int v = son[u][c];
                    if(val[v]) continue ;
                    d[i + 1][v] = min(d[i + 1][v], d[i][u] + (hash[(int) buf[i + 1]] != c));
                }
            }
        }
        int ans = INF;
        for(int i = 0; i < cnt; i ++)
            ans = min(ans, d[n][i]);
        printf("Case %d: %d\n", ++ Q, ans == INF ? -1 : ans);
    }
    return 0;
}
