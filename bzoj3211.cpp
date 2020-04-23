#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<cmath>

using	namespace	std;
typedef const int & var;
typedef long long	data;
const	int N = 100005;
const	int BUF = 1024 * 1024 * 60;

data node[N];
char buf[BUF], *s;
int n, m, len, a[N], pre[N];

inline int GetInt()
{
	int res = 0;
	while( *s > '9' || *s < '0' )
		s ++;
	while( *s <= '9' && *s >= '0' )
	{
		res = res * ( data )10 + *s - '0';
		s ++;
	}
	return res;
}

int Find( int x )
{
	if( !pre[x] )
		pre[x] = x;
	else if( x != pre[x] )
		pre[x] = Find( pre[x] );
	return pre[x];
}

inline int lowbit( var p )
{
	return p & ( -p );
}

inline data Query( var p )
{
	data res = 0;
	for( int i = p; i > 0; i -= lowbit( i ) )
		res += node[i];
	return res;
}

inline void Insert( data x, var p )
{
	for( int i = p; i <= n; i += lowbit( i ) )
		node[i] += x;
	return ;
}

inline void Modify( var x, var y )
{
	for( int i = Find( x ); i <= y; i = Find( i + 1 ) )
	{
		data tmp = ( data )sqrt( a[i] );
		Insert( tmp - a[i], i );
		a[i] = tmp;
		if( a[i] <= 1 )
			pre[i] = Find( i + 1 );
	}
	return ;
}

int main()
{
	len = fread( buf, 1, BUF, stdin );
    buf[len] = '\0', s = buf;
	n = GetInt();
	for( int i = 1; i <= n; i ++ )
	{
		a[i] = GetInt();
		Insert( a[i], i );
		if( a[i] <= 1 )
			pre[i] = i + 1;
	}
	m = GetInt();
	for( int i = 0; i < m; i ++ )
	{
		int p, x, y;
		p = GetInt(), x = GetInt(), y = GetInt();
		if( x > y )
			swap( x, y );
		if( p == 1 )
			printf( "%lld\n", Query( y ) - Query( x - 1 ) );
		else
			Modify( x, y );
	}
	return 0;
}
