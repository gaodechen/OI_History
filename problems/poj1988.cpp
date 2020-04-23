#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 3e4 + 5;

int n, father[N], sum[N], dis[N];

int Find( int a )
{
	if( a != father[a] )
	{
		int t = father[a];
		father[a] = Find( father[a] );
		dis[a] += dis[t];
	}
	return father[a];
}

void Union( int a, int b )
{
	a = Find( a ), b = Find( b );
	father[a] = b;
	dis[a] += sum[b];
	sum[b] += sum[a];
	return ;
}

int main()
{
	for( int i = 1; i < N; i ++ )
		father[i] = i, sum[i] = 1;
	scanf( "%d", &n );
	while( n -- )
	{
		int a, b; char s[2];
		scanf( "%s%d", s, &a );
		if( s[0] == 'M' )
		{
			scanf( "%d", &b );
			Union( a, b );
		}
		else
		{
			Find( a );
			printf( "%d\n", dis[a] );
		}
	}
	return 0;
}
