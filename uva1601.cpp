#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include	<queue>

using	namespace	std;
const	int N = 20, M = 400;

char maze[N][N];
int w, h, n, c1, c2, s[3], t[3], G[M][M], d[M][M][M], out[M];
int next[][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }, { 0, 0 } };

inline bool CheckPos( int i, int j )
{
	return i >= 0 && j >= 0 && i < h && j < w;
}

inline int GetIndex( int i, int j )
{
	return i * w + j;
}

inline void GetPos( int k, int &i, int &j )
{
	j = k % w, i = ( k - j ) / w;
	return ;
}

inline int HashPos( int a, int b, int c )
{
	return ( a << 16 ) | ( b << 8 ) | c;
}

bool cmp( const int &a, const int &b )
{
	int x, y, m, n;
	GetPos( a, x, y ), GetPos( b, m, n );
	return maze[x][y] < maze[m][n];
}

inline void Emit( int i, int j )
{
	int k = GetIndex( i, j );
	for( int d = 0; d < 5; d ++ )
	{
		int i_ = i + next[d][0];
		int j_ = j + next[d][1];
		if( CheckPos( i_, j_ ) && maze[i_][j_] != '#' )
			G[k][out[k]++] = GetIndex( i_, j_ );
	}
	return ;
}

inline bool CheckStep( int a, int b, int a_, int b_ )
{
	return a != b && !( a == b_ && b == a_ );
}

int Search()
{
	queue< int > q;
	q.push( HashPos( s[0], s[1], s[2] ) );
	d[s[0]][s[1]][s[2]] = 0;
	while( !q.empty() )
	{
		int u = q.front(); q.pop();
		int a = ( u >> 16 ) & 0xff, b = ( u >> 8 ) & 0xff, c = u & 0xff;
		if( a == t[0] && b == t[1] && c == t[2] )
			return d[a][b][c];
		for( int i = 0; i < out[a]; i ++ )
		{
			int a_ = G[a][i];
			for( int j = 0; j < out[b]; j ++ )
			{
				int b_ = G[b][j];
				if( !CheckStep( a, b, a_, b_ ) )
					continue ;
				for( int k = 0; k < out[c]; k ++ )
				{
					int c_ = G[c][k];
					if( !CheckStep( a, c, a_, c_ ) || !CheckStep( b, c, b_, c_ ) )
						continue ;
					if( d[a_][b_][c_] != -1 )
						continue ;
					d[a_][b_][c_] = d[a][b][c] + 1;
					q.push( HashPos( a_, b_, c_ ) );
				}
			}
		}
	}
	return -1;
}

int main()
{
	freopen( "in_", "r", stdin );
	while( scanf( "%d%d%d\n", &w, &h, &n ) == 3 && n )
	{
		c1 = 0, c2 = 0;
		s[0] = s[1] = s[2] = 0;
		t[0] = t[1] = t[2] = 0;
		memset( G, 0, sizeof( G ) );
		memset( d, -1, sizeof( d ) );
		memset( out, 0, sizeof( out ) );
		for( int i = 0; i < h; i ++ )
			fgets( maze[i], 20, stdin );
		for( int i = 0; i < h; i ++ )
		{
			for( int j = 0; j < w; j ++ )
			{
				if( maze[i][j] != '#' )
				{
					if( islower( maze[i][j] ) )
						s[c1++] = GetIndex( i, j );
					else if( isupper( maze[i][j] ) )
						t[c2++] = GetIndex( i, j );
					Emit( i, j );
				}
			}
		}
		sort( s, s + c1, cmp );
		sort( t, t + c2, cmp );
		if( c1 < 3 )
			out[0] ++;
		printf( "%d\n", Search() );
	}
	return 0;
}
