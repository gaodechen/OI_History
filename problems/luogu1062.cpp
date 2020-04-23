#include	<cstdio>
#include	<iostream>

using	namespace	std;

int main()
{
	int k, n;
	long long s = 0, base = 1;
	// Luogu requires int
	cin >> k >> n;
	while( n > 0 )
	{
		if( n & 1 )
			s += base;
		n >>= 1;
		base *= k;
	}
	cout << s << endl;
	return 0;
}
