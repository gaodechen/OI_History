#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using namespace	std;
typedef long long data;

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

const int N = 1e5 + 5;
const int B = 131;
const int MOD = 1000007;

int n, k, sum[N][31];
int C, head[MOD], next[MOD], Key[MOD];
data val[N];

inline data Hash(int i)
{
    data r = 0;
    for(int j = 0; j < k; j ++)
        r = r * B + sum[i][j];
    return r;
}

inline int M(data x)
{
    return x >= MOD ? x % MOD : x;
}

inline int HashInsert(data x, int key)
{
    int p = M(M(x % MOD) + MOD);
    if(head[p] == -1)
    {
        Key[++ C] = key, val[C] = x;
        next[C] = head[p], head[p] = C;
        return -1;
    }
    for(int i = head[p]; i != -1; i = next[i])
        if(val[i] == x)
            return Key[i];
    Key[++ C] = key, val[C] = x;
    next[C] = head[p], head[p] = C;
    return -1;
}

int main(int argc, char **argv)
{
    memset(head, -1, sizeof(head));
    n = in(), k = in();
    Key[0] = head[0] = val[0] = 0;
    for(int i = 1; i <= n; i ++)
    {
        int x = in();
        for(int j = 0; j < k; j ++)
            sum[i][j] = x & 1, x >>= 1;
    }
    for(int i = 1; i <= n; i ++)
        for(int j = 0; j < k; j ++)
            sum[i][j] += sum[i - 1][j];
    int ans = 0;
    for(int i = 1; i <= n; i ++)
    {
        for(int j = k - 1; j >= 0; j --)
            sum[i][j] -= sum[i][0];
        data key = Hash(i);
        int l = HashInsert(key, i);
        if(l != -1)
           ans = max(ans, i - l);
    }
    printf("%d", ans);
    return 0;
}
