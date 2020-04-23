#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int P = 1e6 + 3;

inline int in()
{
	int k = 0, c = '\0';
	for(; c > '9' || c < '0';)
        c = getchar();
	for(; c >= '0' && c <= '9';)
	{
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k;
}

typedef long long data;

data fac[P], inv[P];

inline data M(data x)
{
    return x >= P ? x % P : x;
}

inline data C(int n, int m)
{
    return M(M(fac[n] * inv[m]) * inv[n - m]);
}

data Lucas(int n, int m)
{
    if(n < m) return 0;
    if(n < P && m < P) return C(n, m);
    // Must be Lucas() * Lucas(), as n < m!
    return M(Lucas(n / P, m / P) * Lucas(n % P, m % P));
}

int main(int argc, char **argv)
{
    fac[0] = 1, inv[1] = 1;
    for(int i = 1; i < P; i ++)
        fac[i] = M(fac[i - 1] * i);
    for(int i = 2; i < P; i ++)
        inv[i] = M((P - P / i) * inv[P % i]);
    inv[0] = 1;
    for(int i = 1; i < P; i ++)
        inv[i] = M(inv[i - 1] * inv[i]);
    int T = in();
    while(T --)
    {
        int n = in(), L = in(), R = in(), m = R - L + 1;
        printf("%d\n", (int) (Lucas(n + m, m) + P - 1) % P);
    }
    return 0;
}
