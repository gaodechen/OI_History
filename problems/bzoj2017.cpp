#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int INF = 0x3f3f3f3f;

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

const int N = 2001;

int n, c[N], d[N][N];

int main(int argc, char **argv)
{
    n = in();
    for(int i = 1; i <= n; i ++)
        c[n - i + 1] = in();
    for(int i = 2; i <= n; i ++)
        c[i] += c[i - 1];
    for(int i = 1; i <= n; i ++)
    {
        int minNum = INF;
        for(int j = 1; j <= n; j ++)
        {
            // d[i][j] = sum[i] - min(d[i - k][k]) k = min(i, 2 * j)
            int t = 2 * j - 1;
            if(t <= i)
                minNum = min(minNum, d[i - t][t]);
            t = 2 * j;
            if(t <= i)
                minNum = min(minNum, d[i - t][t]);
            d[i][j] = c[i] - minNum;
        }
    }
    printf("%d", d[n][1]);
    return 0;
}
