#include    <cstdio>
#include    <iostream>

using    namespace    std;
const    int N = 121;

int n, d[N][N];

int main()
{
    for(int i = 1; i < N; i ++)
        d[i][1] = d[1][i] = d[0][i] = 1;
    for(int i = 2; i < N; i ++)
    {
        for(int j = 2; j < N; j ++)
        {
            if(i < j)
                d[i][j] = d[i][i];
            else
                d[i][j] = d[i - j][j] + d[i][j - 1];
        }
    }
    while(scanf("%d", &n) == 1)
        printf("%d\n", d[n][n]);
    return 0;
}
