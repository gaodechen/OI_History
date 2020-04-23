#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<stack>

#define		set( p, k )		memset( p, k, sizeof( p ) )
#define		cpy( p, k )		memcpy( p, k, sizeof( k ) )

using	namespace	std;
const	int N = 5e4 + 5;

char buf[2];
bool vis[N];
int n, m, q, sig, inx, a, b, c;
int val[N], head[N], son[N], pre[N], cur[N];
int size[N], dep[N], top[N], pos[N], node[N];


inline int lowbit( int x )
{
	return x & ( -x );
}

inline void Insert( int p, int w )
{
	for( int i = p; i <= n; i += lowbit( i ) )
		node[i] += w;
	return ;
}

inline void TreeModify( int l, int r, int w )
{
	Insert( l, w );
	Insert( r + 1, -w );
	return ;
}

inline int TreeQuery( int p )
{
	int res = 0;
	for( int i = p; i > 0; i -= lowbit( i ) )
		res += node[i];
	return res;
}

struct Edge
{
	int v, next;
} e[N*2];

inline void AddEdge( int u, int v )
{
	e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
	return ;
}

void PrevDFS()
{
	set( vis, 0 );
	cpy( cur, head );
	stack< int > s;
	s.push( 1 );
	while( !s.empty() )
	{
		int u = s.top();
		if( !vis[u] )
		{
			dep[u] = dep[pre[u]] + 1;
			size[u] = 1, vis[u] = 1;
		}
		bool flag = false;
		for( int i = cur[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( !vis[v] )
			{
				s.push( v );
				cur[u] = e[i].next;
				pre[v] = u, flag = true;
				break ;
			}
		}
		if( flag ) continue ;
		for( int i = head[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( v != pre[u] )
			{
				size[u] += size[v];
				if( size[v] > size[son[u]] )
					son[u] = v;
			}
		}
		s.pop();
	}
	return ;
}

void NextDFS()
{
	set( vis, 0 );
	cpy( cur, head );
	stack< int > s;
	s.push( 1 );
	top[1] = 1;
	while( !s.empty() )
	{
		int u = s.top();
		if( !vis[u] )
		{
			pos[u] = ++ inx;
			vis[u] = 1;
		}
		bool flag = false;
		if( son[u] && !vis[son[u]] )
		{
			int v = son[u];
			flag = true;
			s.push( v );
			top[v] = top[u];
			continue ;
		}
		for( int i = cur[u]; i; i = e[i].next )
		{
			int v = e[i].v;
			if( v != pre[u] && v != son[u] )
			{
				s.push( v );
				top[v] = v;
				cur[u] = e[i].next;
				flag = true;
				break ;
			}
		}
		if( flag )
			continue ;
		s.pop();
	}
	return ;
}

void Modify( int u, int v, int w )
{
	int a = top[u], b = top[v];
	while( a != b )
	{
		if( dep[a] < dep[b] )
		{
			swap( a, b );
			swap( u, v );
		}
		TreeModify( pos[a], pos[u], w );
		u = pre[a];
		a = top[u];
	}
	if( dep[u] > dep[v] )
		swap( u, v );
	TreeModify( pos[u], pos[v], w );
	return ;
}

int main()
{
	while( scanf( "%d%*d%d", &n, &q ) == 2 )
	{
		sig = inx = 0;
		set( top, 0 ), set( dep, 0 );
		set( pre, 0 ), set( top, 0 );
		set( son, 0 ), set( head, 0 );
		set( size, 0 ), set( node, 0 );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &val[i] );
		for( int i = 1; i < n; i ++ )
		{
			scanf( "%d%d", &a, &b );
			AddEdge( a, b );
			AddEdge( b, a );
		}
		PrevDFS(), NextDFS();
		for( int i = 1; i <= n; i ++ )
			TreeModify( pos[i], pos[i], val[i] );
		for( int i = 0; i < q; i ++ )
		{
			scanf( "%s", buf );
			if( buf[0] == 'Q' )
			{
				scanf( "%d", &a );
				printf( "%d\n", TreeQuery( pos[a] ) );
			}
			else
			{
				scanf( "%d%d%d", &a, &b, &c );
				if( buf[0] == 'D' )
					c = -c;
				Modify( a, b, c );
			}
		}
	}
	return 0;
}
