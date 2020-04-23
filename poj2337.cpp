#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

using	namespace	std;
typedef pair< int ,int > P;
const	int N = 1e3 + 5, M = 26;

string str[M];
vector< P > e[N];
vector< string > list;
int t, n, father[N], out[M], in[M], vis[M][M];

int Find( int u )
{
	if( u != father[u] )
		father[u] = Find( father[u] );
	return father[u];
}

void Union( int u, int v )
{
	father[Find(v)] = Find( u );
	return ;
}

void DFS( int u )
{
	for( int i = 0; i < ( int )e[u].size(); i ++ )
	{
		int v = e[u][i].first;
		if( !vis[u][v] )
		{
			vis[u][v] = 1;
			DFS( v );
			list.push_back( str[e[u][i].second] );
		}
	}
	return ;
}

int main()
{
	freopen( "a.in", "r", stdin );
	scanf( "%d", &t );
	while( t -- )
	{
		scanf( "%d", &n );
		for( int i = 0; i < M; i ++ )
			father[i] = i;
		memset( in, 0, sizeof( in ) );
		memset( out, 0, sizeof( out ) );
		for( int i = 0; i < n; i ++ )
			cin >> str[i];
		for( int i = 0; i < n; i ++ )
		{
			int u = str[i][0] - 'a';
			int v = str[i][str[i].length()-1] - 'a';
			Union( u, v );
			in[v] ++;
			out[u] ++;
		}
		int flag = -1, t1 = 0, t2 = 0, s;
		for( int i = 0; i < M; i ++ )
		{
			if( out[i] > in[i] )
			{
				s = i;
				t1 ++;
			}
			else if( in[i] > out[i] )
				t2 ++;
		}
		if( flag == -1 || !( ( t1 == 1 && t2 == 1 ) || ( !t1 && !t2 ) ) )
		{
			printf( "***\n" );
			break ;
		}
		DFS( s );
		for( int i = ( int )list.size() - 1; i + 1; i -- )
			cout << list[i] << endl;
	}
	return 0;
}
