#include	<cstdio>
#include	<cstring>
#include	<iostream>

using	namespace	std;
const	int N = 5e3 + 7;

int n, m, rear;
int pre[N], rank[N], head[N], next[N], t[N];

inline int InsertHash( int key )
{
	int h = key % N;
	int u = head[h];
	while( u != -1 )
	{
		if(t[u] == key)
			return u;
		u = next[u];
	}
	t[rear] = key;
	next[rear] = head[h];
	head[h] = rear ++;
	return rear - 1;
}

inline int Find( int x )
{
	if( x != pre[x] )
	{
		int t = pre[x];
		pre[x] = Find( pre[x] );
		rank[x] ^= rank[t];
	}
	return pre[x];
}

inline bool Union( int x, int y, int d )
{
	int x_ = Find( x ), y_ = Find( y );
	if( x_ == y_ )
	{
		if( ( rank[x] ^ rank[y] ) != d )
			return false;
		return true;
	}
	rank[y_] = rank[x] ^ rank[y] ^ d;
	pre[y_] = x_;
	return true;
}

int main()
{
	scanf( "%d%d", &n, &m );
	rear = 0;
	memset( head, -1, sizeof( head ) );
	for( int i = 0; i < N; i ++ )
		pre[i] = i, rank[i] = 0;
	int i;
	for( i = 0; i < m; i ++ )
	{
		char s[5]; int a, b, d = 0;
		scanf( "%d%d%s", &a, &b, s );
		a = InsertHash( a - 1 );
		b = InsertHash( b );
		if( s[0] == 'o' )
			d = 1;
		if( !Union( a, b, d ) )
			break ;
	}
	printf( "%d\n", i );
	return 0;
}
