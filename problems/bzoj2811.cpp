#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e5 + 9;
const   int S = 5e6 + 5;
 
char buf[S], *s;
 
inline int in()
{
    int k = 0;
    while( *s > '9' || *s < '0' )
        s ++;
    while( *s <= '9' && *s >= '0' )
    {
        k = k * 10 + *s - '0';
        s ++;
    }
    return k;
}

struct Item
{
	int l, r;
	
	Item( int l = 0, int r = 0 ): l( l ), r( r )
	{
    }
	
	bool operator < ( const Item &b ) const
	{
		if( l == b.l )
			return r < b.r;
		return l < b.l;
	}
} e1[N], e2[N], e[N];

bool mark[N];
int last[N], sum[N], ans[N], f[N];
int n, k, m, cnt1, cnt2, cnt, tot;

int main()
{
    int len = fread( buf, 1, S, stdin );
    buf[len] = '\0', s = buf;
    n = in(), k = in(), m = in();
	for( int i = 1; i <= m; i ++ )
	{
		int l, r, w;
        l = in(), r = in(), w = in();
		if( !w )
			e1[++cnt1].l = l - 1, e1[cnt1].r = r;
		else
			e2[++cnt2].l = l - 1, e2[cnt2].r = r;
	}
	sort( e1 + 1, e1 + cnt1 + 1 );
	int cur = 0;
	for( int i = 1; i <= cnt1; i ++ )
	{
		if( e1[i].r > cur )
		{
			for( int j = max( e1[i].l, cur ); j < e1[i].r; j ++ )
				mark[j] = 1;
			cur = e1[i].r;
		}
	}
	for( int i = 0; i < n; i ++ )
	{
		if( !mark[i] )
			sum[i+1] = sum[i] + 1;
		else
			sum[i+1] = sum[i];
	}
	cur = -1;
	for( int i = 0; i < n; i ++ )
	{
		if( !mark[i] )
			cur = i;
		last[i] = cur;
	}
	if( sum[n] == k )
	{
		for( int i = 0; i < n; i ++ )
			if( !mark[i] )
				printf( "%d\n", i + 1 );
		return 0;
	}
	sort( e2 + 1, e2 + cnt2 + 1 );
	cur = n + 1;
	for( int i = cnt2; i; i -- )
	{
		if( e2[i].r < cur )
		{
			e[++cnt] = e2[i];
			cur = e2[i].r;
		}
	}
	for( int i = 1; i <= cnt; i ++ )
	{
		if( sum[e[i].r] - sum[e[i].l] == 1 )
		{
			int x = last[e[i].r-1];
			if( !mark[x] )
			{
				ans[++tot] = x;
				mark[x] = 1;
			}
		}
	}
    sum[0] = 0;
	for( int i = 0; i < n; i ++ )
	{
		if( !mark[i] )
			sum[i+1] = sum[i] + 1;
		else
			sum[i+1] = sum[i];
	}
	cur = -1;
	for( int i = 0; i < n; i ++ )
	{
		if( !mark[i] )
			cur = i;
		last[i] = cur;
	}
	sort( ans + 1, ans + tot + 1 );
	cnt2 = 0;
	for( int i = cnt; i; i -- )
	{
		int a = lower_bound( ans + 1, ans + tot + 1, e[i].l ) - ans;
		int b = lower_bound( ans + 1, ans + tot + 1, e[i].r ) - ans;
		if( a == b )
			e2[++cnt2] = e[i];
	}
	for( int i = cnt2; i; i -- )
	{
		int x = last[e2[i].r-1];
		Item t = Item( x + 1, 0 );
		int p = lower_bound( e2 + 1, e2 + cnt2 + 1, t ) - e2;
		f[i] = f[p] + 1;
	}
	k -= tot, cur = -1;
	for( int i = 1, c = 0; i <= cnt2; i ++ )
	{
		if( e2[i].l > cur )
		{
			int x = last[e2[i].r-1], y = last[x-1];
			Item t = Item( y + 1, 0 );
			int p = lower_bound( e2 + 1, e2 + cnt2 + 1, t ) - e2;
			if( c + f[p] + 1 > k )
				ans[++tot] = x;
			cur = x;
			c ++;
		}
	}
	sort( ans + 1, ans + tot + 1 );
	if( tot == 0 )
		puts( "-1" );
	else for( int i = 1; i <= tot; i ++ )
		printf( "%d\n", ans[i] + 1 );
	return 0;
}
