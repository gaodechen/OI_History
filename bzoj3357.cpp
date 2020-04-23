#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <map>

using	namespace	std;
const   int N = 2e3 + 5;

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

int a[N], f[N][N];

int main(int argc, char **argv)
{
    int n = in();
    if(n == 1)
        return puts("1"), 0;
    for(int i = 1; i <= n; i ++)
        a[i] = in();
    for(int i = 1; i <= n; i ++)
    {
        map<int, int> M;
        for(int j = 1; j < i; j ++)
        {
            int t = a[j] + a[j] - a[i];
            if(M.count(t))
                f[i][j] = f[j][M[t]] + 1;
            else
                f[i][j] = 2;
            M[a[j]] = j;
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j < i; j ++)
            ans = max(ans, f[i][j]);
    printf("%d\n", ans);
    return 0;
}
