#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 65, INF = 0x3f3f3f3f;

int n, sum, ans, len[N], mark[N];

bool DFS( int d, int l, int p, int q )
{
	if( q == n )
		return true;
	int tmp = -1;
	for( int i = p; i <= n; i ++ )
	{
		if( mark[i] || len[i] == tmp )
			continue ;
		mark[i] = 1;
		if( l + len[i] == d )
		{
			if( DFS( d, 0, 1, q + 1 ) )
				return true;
			else
				tmp = len[i];
		}
		else if( l + len[i] < d )
		{
			if( DFS( d, l + len[i], i + 1, q + 1 ) )
				return true;
			else
				tmp = len[i];
		}
		mark[i] = 0;
		if( l == 0 )
			break ;
	}
	return false;
}

int main()
{
	while( scanf( "%d", &n ) == 1 && n )
	{
		sum = 0;
		memset( mark, 0, sizeof( mark ) );
		for( int i = 1; i <= n; i ++ )
		{
			scanf( "%d", &len[i] );
			sum += len[i];
		}
		sort( len + 1, len + n + 1, greater< int >() );
		for( int d = len[1]; d <= sum; d ++ )
		{
			if( sum % d == 0 && DFS( d, 0, 1, 0 ) )
			{
				ans = d;
				break ;
			}
		}
		printf( "%d\n", ans );
	}
	return 0;
}

/*
#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <queue>
#include    <vector>

using	namespace	std;
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

int n, len[65], D, K;
bool vis[65];

bool DFS(int l, int p, int Count)
{
    if(Count == K || p > n) return true;
    int prev = -1;
    for(int i = p; i <= n; i ++)
    {
        if(vis[i] || len[i] + l > D || prev == len[i]) continue ;
        vis[i] = 1;
        if(len[i] + l == D) {
            if(DFS(0, 1, Count + 1)) return true;
        } else {
            if(DFS(len[i] + l, p + 1, Count)) return true;
        }
        vis[i] = 0, prev = len[i];
        if(l == 0 || len[i] == D) return false;
    }
    return false;
}

bool f[3001];

int main(int argc, char **argv)
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int n_;
    while(scanf("%d", &n_) && n_)
    {
        int sum = 0; n = 0;
        memset(f, 0, sizeof(f));
        memset(vis, 0, sizeof(vis));
        for(int i = 1, x; i <= n_; i ++)
        {
            if((x = in()) > 50) continue ;
            len[++ n] = x, sum += x;
        }
        f[0] = 1;
        for(int i = 1; i <= n; i ++)
            for(int j = sum; j; j --)
                f[j] |= f[j - len[i]];
        sort(len + 1, len + n + 1, greater<int>());
        for(D = len[1]; D <= sum; D ++)
        {
            K = sum / D;
            if(sum % D == 0 && f[D] && DFS(0, 1, 0))
            {
                printf("%d\n", D);
                break ;
            }
        }
    }
    return 0;
}
 */
