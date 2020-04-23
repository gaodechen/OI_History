#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace	std;
const int C = 51, N = 101, B = 1e8;

bool val[N];
int fail[N], hash[500], son[N][C];
int n, root, cnt;

inline void Insert(char *s)
{
    int l = strlen(s), p = root;
    for(int i = 0; i < l; i ++)
    {
        int c = hash[(int) s[i] + 128];
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
    for(int i = 0; i < n; i ++)
    {
        if(son[root][i] == -1)
            son[root][i] = root;
        else
        {
            fail[son[root][i]] = root;
            q.push(son[root][i]);
        }
    }
    while(!q.empty())
    {
        int p = q.front(); q.pop();
        val[p] |= val[fail[p]];
        for(int i = 0; i < n; i ++)
        {
            if(son[p][i] == -1)
                son[p][i] = son[fail[p]][i];
            else
            {
                fail[son[p][i]] = son[fail[p]][i];
                q.push(son[p][i]);
            }
        }
    }
    return ;
}

struct BigInteger
{
    int a[N], len;

    BigInteger(int x = 0) {memset(a, 0, sizeof(a)), a[0] = x, len = 1;}

    BigInteger operator + (const BigInteger &b)
    {
        BigInteger r;
        int t = max(len, b.len);
        for(int i = 0; i < t; i ++)
            r.a[i] = a[i] + b.a[i];
        for(int i = 0; i < t; i ++)
        {
            if(r.a[i] >= B)
            {
                r.a[i + 1] += r.a[i] / B;
                r.a[i] %= B;
            }
        }
        r.len = t + (r.a[t] != 0);
        return r;
    }

    inline void Print()
    {
        printf("%d", a[len - 1]);
        for(int i = len - 2; i >= 0; i --)
            printf("%08d", a[i]);
        puts("");
        return ;
    }

} f[N][N], ans;

char s[N];

int main(int argc, char **argv)
{
    int m, p;
    scanf("%d%d%d\n", &n, &m, &p);
    gets(s);
    for(int i = 0; i < n; i ++)
        hash[(int) s[i] + 128] = i;
    memset(son, -1, sizeof(son));
    root = cnt ++;
    while(p --)
    {
        scanf("%s", s);
        Insert(s);
    }
    InitFail();
    f[0][0] = BigInteger(1);
    for(int i = 0; i < m; i ++)
    {
        for(int u = 0; u < cnt; u ++)
        {
            for(int k = 0; k < n; k ++)
            {
                int v = son[u][k];
                if(val[v]) continue ;
                f[i + 1][v] = f[i + 1][v] + f[i][u];
            }
        }
    }
    ans = 0;
    for(int i = 0; i < cnt; i ++)
        ans = ans + f[m][i];
    ans.Print();
    return 0;
}
