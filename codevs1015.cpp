#include	<cstdio>
#include	<iostream>

using	namespace	std;

char t;
string s;
int a1, b1, a2, b2, p;

void GetExp( int l, int r, int &a, int &b )
{
	int o = 1, n = 0;
	for( int i = l; i < r; i ++ )
	{
		if( s[i] == '+' || s[i] == '-' )
		{
			b += o * n;
			o = s[i] == '+' ? 1 : -1;
			n = 0;
		}
		else
		{
			if( isdigit( s[i] ) )
				n = n * 10 + s[i] - '0';
			else
			{
				t = s[i];
				a = o * n;
				o = n = 0;
			}
		}
	}
	b += o * n;
	return ;
}

int main()
{
	cin >> s;
	p = s.find( '=' );
	GetExp( 0, p, a1, b1 );
	GetExp( p + 1, s.length(), a2, b2 );
	printf( "%c=%.3lf\n", t, 1.0 * ( b2 - b1 ) / ( a1 - a2 ) );
	return 0;
}
