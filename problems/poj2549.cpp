#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <queue>
#include    <vector>

using	namespace	std;
const   int INF = 0x7fffffff;

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

const   int N = 1001, MOD = 99991, M = 1000000;

int n, sig, a[N], head[M], next[M];
long long val[M], A[M], B[M];

inline void Insert(int x, int y)
{
    int a = ((x % MOD + y % MOD) % MOD + MOD) % MOD;
    val[++ sig] = x + y, A[sig] = x, B[sig] = y;
    next[sig] = head[a], head[a] = sig;
    return ;
}

inline bool Find(int x, int y)
{
    int a = ((x % MOD - y % MOD) % MOD + MOD) % MOD;
    for(int i = head[a]; i; i = next[i])
        if(val[i] == x - y && ((A[i] != x && B[i] != y && A[i] != y && B[i] != x)))
            return true;
    return false;
}

int main(int argc, char **argv)
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    while(scanf("%d", &n) && n)
    {
        sig = 0;
        memset(next, 0, sizeof(next));
        memset(head, 0, sizeof(head));
        for(int i = 0; i < n; i ++)
            a[i] = in();
        sort(a, a + n);
        for(int i = 0; i < n; i ++)
            for(int j = i + 1; j < n; j ++)
                Insert(a[i], a[j]);
        int r = -INF; bool flag = false;
        for(int i = n; i >= 0; i --)
            for(int j = 0; j < n; j ++)
                if(i != j && Find(a[i], a[j]))
                    flag = true, r = max(a[i], r);
        if(!flag) puts("no solution");
        else printf("%d\n", r);
    }
    return 0;
}
