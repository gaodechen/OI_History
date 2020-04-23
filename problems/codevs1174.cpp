#include	<cstdio>
#include	<iostream>

using	namespace	std;
const	int N = 10;

int a[N][N];
int val[9][9] = { { 6, 6, 6, 6,  6, 6, 6, 6, 6 },
	   			  { 6, 7, 7, 7,  7, 7, 7, 7, 6 },
				  { 6, 7, 8, 8,  8, 8, 8, 7, 6 },
				  { 6, 7, 8, 9,  9, 9, 8, 7, 6 },
				  { 6, 7, 8, 9, 10, 9, 8, 7, 6 },
			      { 6, 7, 8, 9,  9, 9, 8, 7, 6 },
				  { 6, 7, 8, 8,  8, 8, 8, 7, 6 },
				  { 6, 7, 7, 7,  7, 7, 7, 7, 6 },
			      { 6, 6, 6, 6,  6, 6, 6, 6, 6 } };

int main()
{
	for( int i = 1; i <= 9; i ++ )
		for( int j = 1; j <= 9; j ++ )
			scanf( "%d", &a[i][j] );
	return 0;
}
