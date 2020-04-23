#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<queue>

using	namespace	std;
const	int N = 4e5 + 3;

struct State
{
	int a[10], dis, pos;
	bool operator == ( const State &b ) const
	{
		for( int i = 0; i < 9; i ++ )
			if( a[i] != b.a[i] )
				return 0;
		return 1;
	}
} table[N];

int head[N], next[N], tick = 2;
int t[10] = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };
int d[][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

inline int Hash( const State &p )
{
	int res = 0;
	for( int i = 0; i < 9; i ++ )
		res += res * 10 + p.a[i];
	return res % N;
}

inline int HashCheck( int k )
{
	int h = Hash( table[k] );
	int u = head[h];
	while( u )
	{
		if( table[k] == table[u] )
			return 0;
		u = next[u];
	}
	return h;
}

inline void HashInsert( int k )
{
	int h;
	if( ( h = HashCheck( k ) ) )
	{
		next[k] = head[h];
		head[h] = k;
	}
	return ;
}

int Search()
{
	queue< int > q;
	HashInsert( 1 );
	q.push( 1 );
	while( !q.empty() )
	{
		int u = q.front(); q.pop();
		if( table[u] == table[2] )
			return table[u].dis;
		int &flag = table[u].pos;
		int x = flag / 3, y = flag - 3 * x;
		for( int i = 0; i < 4; i ++ )
		{
			State v = table[u];
			int x_ = x + d[i][0], y_ = y + d[i][1];
			if( x_ < 3 && x_ >= 0 && y_ < 3 && y_ >= 0 )
			{
				int flag_ = 3 * ( x + d[i][0] ) + y + d[i][1];
				swap( v.a[flag], v.a[flag_] );
				v.pos = flag_;
				v.dis = table[u].dis + 1;
				table[++tick] = v;
				if( HashCheck( tick ) )
				{
					q.push( tick );
					HashInsert( tick );
				}
				else
					tick --;
			}
		}
	}
	return 0;
}

int main()
{
	for( int i = 0; i < 9; i ++ )
	{
		int c = getchar();
		table[1].a[i] = c - '0';
		if( table[1].a[i] == 0 )
			table[1].pos = i;
		table[2].a[i] = t[i];
	}
	printf( "%d\n", Search() );
	return 0;
}
