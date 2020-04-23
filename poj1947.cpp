#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<vector>

using	namespace	std;
const	int N = 200;

vector< int > e[N];
int n, p, ans, d[N][N];

int DFS( int u, int pre )
{
	int sum = 1;
	d[u][1] = (int) e[u].size();
	for(int i = 0; i < ( int )e[u].size(); i ++)
	{
		int &v = e[u][i];
		if( v == pre )
			continue ;
		sum += DFS( v, u );
		for(int j = sum; j; j --)
			for(int i = 1; i <= j; i ++)
				d[u][j] = min(d[u][j], d[u][j - i] + d[v][i] - 1);
	}
	return sum;
}

int main()
{
	scanf( "%d%d", &n, &p );
	memset(d, 0x3f, sizeof(d));
	for( int i = 1; i < n; i ++ )
	{
		int u, v;
		scanf( "%d%d", &u, &v );
		e[u].push_back( v );
	}
	DFS( 1, 1 );
	ans = d[1][p];
	for( int i = 2; i <= n; i ++ )
		ans = min(ans, d[i][p] + 1);
    for(int i = 1; i <= n; i ++)
    {
        cout << i << " ";
        for(int j = 0; j <= 3; j ++)
            cout << d[i][j] << " ";
        cout << endl;
    }
	printf( "%d\n", ans );
	return 0;
}
