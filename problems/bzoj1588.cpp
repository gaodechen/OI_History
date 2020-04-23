#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e5 + 5;
const	int INF = 0x3f3f3f3f;

int n, q, ans, tot, root;
int pre[N], key[N], son[N][2];

inline void NewNode( int &p, int f, int k )
{
	p = ++ tot, pre[p] = f, key[p] = k;
	son[p][0] = son[p][1] = 0;
	return ;
}

inline void Rotate( int x, int k )
{
	int y = pre[x];
	son[y][!k] = son[x][k];
	pre[son[x][k]] = y;
	if( pre[y] )
		son[pre[y]][son[pre[y]][1]==y] = x;
	pre[x] = pre[y];
	son[x][k] = y;
	pre[y] = x;
	return ;
}

inline void Splay( int p, int k )
{
	while( pre[p] != k )
	{
		int y = pre[p];
		if( pre[y] == k )
			Rotate( p, son[y][0] == p );
		else
		{
			int k_ = son[pre[y]][0] == y;
			if( son[y][k_] == p )
				Rotate( p, !k_ ), Rotate( p, k_ );
			else
				Rotate( y, k_ ), Rotate( p, k_ );
		}
	}
	if( k == 0 )
		root = p;
	return ;
}

inline int Insert( int k )
{
	int p = root;
	while( son[p][k>key[p]] )
	{
		if( key[p] == k )
		{
			Splay( p, 0 );
			return 0;
		}
		p = son[p][k>key[p]];
	}
	NewNode( son[p][k>key[p]], p, k );
	Splay( son[p][k>key[p]], 0 );
	return 1;
}

inline int GetPre( int p )
{
	int k = p;
	p = son[p][0];
	if( p == 0 )
		return INF;
	while( son[p][1] )
		p = son[p][1];
	return key[k] - key[p];
}

inline int GetSuf( int p )
{
	int k = p;
	p = son[p][1];
	if( p == 0 )
		return INF;
	while( son[p][0] )
		p = son[p][0];
	return key[p] - key[k];
}

int main()
{
	while( scanf( "%d", &n ) != EOF )
	{
		ans = tot = root = 0;
		for( int i = 1; i <= n; i ++ )
		{
			if( scanf( "%d", &q ) == EOF )
				q = 0;
			if( i == 1 )
			{
				ans += q;
				NewNode( root, 0, q );
				continue ;
			}
			if( Insert( q ) == 0 )
				continue ;
			ans += min( GetPre( root ), GetSuf( root ) );
		}
		printf( "%d\n", ans );
	}
	return 0;
}
