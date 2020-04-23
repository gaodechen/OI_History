#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;

char buf[1 << 15], *S = buf, *T = buf;

#define GetChar() (S == T && (T = (S = buf) + fread(buf, 1, 1 << 15, stdin), S == T) ? 0 : *S ++)

inline int in()
{
	int k = 0, c = '\0';
	for(; c > '9' || c < '0';)
        c = GetChar();
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = GetChar();
	}
	return k;
}

const int K = 101, M = K * K, INF = 0x3f3f3f3f;

struct Lesson
{
    int m, l, a, next;
} e[K];

struct Slope
{
    int a, t;

    bool operator < (const Slope &r) const
    {
        return a < r.a || (a == r.a && t < r.t);
    }
} g[M];

int head[M], opt[K], f[M][K];

int main(int argc, char **argv)
{
    int T = in(), S = in(), N = in();
    for(int i = 1; i <= S; i ++)
    {
        e[i].m = in(), e[i].l = in(), e[i].a = in();
        e[i].next = head[e[i].m], head[e[i].m] = i;
    }
    for(int i = 1; i <= N; i ++)
        g[i].a = in(), g[i].t = in();
    sort(g + 1, g + N + 1);
    memset(f, 128, sizeof(f));
    memset(opt, INF, sizeof(opt));
    for(int i = 1; i <= N; i ++)
        if(opt[g[i].a])
            opt[g[i].a] = min(opt[g[i].a], g[i].t);
    for(int i = 1; i <= 100; i ++)
        if(opt[i] == INF) opt[i] = opt[i - 1];
    f[0][1] = 0;
    for(int t = 0; t <= T; t ++)
    {
        for(int r = 1; r <= 100; r ++)
        {
            f[t + 1][r] = max(f[t + 1][r], f[t][r]);
            f[t + opt[r]][r] = max(f[t + opt[r]][r], f[t][r] + 1);
            for(int i = head[t]; i; i = e[i].next)
                f[t + e[i].l][e[i].a] = max(f[t + e[i].l][e[i].a], f[t][r]);
        }
    }
    int r = 0;
    for(int i = 1; i <= 100; i ++)
        r = max(r, f[T][i]);
    printf("%d", r);
    return 0;
}
