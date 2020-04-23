#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using namespace	std;
typedef long long data;

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

const int N = 700001;

int W[N];

int main(int argc, char **argv)
{
    int n = in();
    data maxNum = 0, secMax = 0;
    for(int i = 1; i <= n; i ++)
        W[i] = in();
    for(int i = n; i >= 1; i --)
    {
        data w = secMax + W[i];
        if(w >= maxNum)
        {
            secMax = maxNum;
            maxNum = w;
        }
    }
    printf("%lld %lld", maxNum, secMax);
    return 0;
}

