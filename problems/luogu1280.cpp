#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e4 + 5;
const	int INF = 0x3f3f3f3f;

inline int in()
{
	int k = 0, c = '\0';
	for( ; c > '9' || c < '0'; )
		c = getchar();
	for( ; c >= '0' && c <= '9'; )
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

struct Item
{
	int l, t;
} e[N];

int T, n, up, d[N];
int head[N], next[N];

int Search( int t )
{
	if( t >= up )
		return 0;
	if( d[t] )
		return d[t];
	if( !head[t] )
		return Search( t + 1 );
	int res = INF;
	for( int i = head[t]; i; i = next[i] )
	{
		int tmp = Search( e[i].l + e[i].t );
		res = min( res, tmp + e[i].t );
	}
	d[t] = res;
	return d[t];
}

int main()
{
	T = in(), n = in();
	for( int i = 1; i <= n; i ++ )
	{
		e[i].l = in(), e[i].t = in();
		next[i] = head[e[i].l];
		head[e[i].l] = i;
		up = max( up, e[i].l + e[i].t );
	}
	int ans = Search( 1 );
	printf( "%d\n", T - ans );
	return 0;
}
