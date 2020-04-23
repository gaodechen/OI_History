#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

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

int price[51][11], d[5000001];

int main(int argc, char **argv)
{
    int S = in(), D = in(), M = in();
    for(int i = 1; i <= S; i ++)
        for(int j = 1; j <= D; j ++)
            price[i][j] = in();
    for(int i = 2; i <= D; i ++)
    {
        for(int j = 0; j <= M; j ++)
            d[j] = j;
        for(int s = 1; s <= S; s ++)
        {
            int c = price[s][i - 1], p = price[s][i];
            for(int k = c; k <= M; k ++)
            {
                int t = d[k - c] + p;
                if(t > d[k]) d[k] = t;
            }
        }
        M = d[M];
    }
    printf("%d", M);
    return 0;
}
