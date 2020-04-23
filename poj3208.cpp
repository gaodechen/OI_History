#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef long long   data;

data d[15][4];
int f[4][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {3, 3, 3, 3, 3, 3, 0, 3, 3, 3},
    {3, 3, 3, 3, 3, 3, 1, 3, 3, 3},
    {3, 3, 3, 3, 3, 3, 2, 3, 3, 3}
};

int main(int argc, char **argv)
{
    d[0][0] = 1;
    for(int i = 1; i <= 15; i ++)
    {
        d[i][0] = (d[i - 1][0] + d[i - 1][1] + d[i - 1][2]) * 9;
        d[i][1] = d[i - 1][0], d[i][2] = d[i - 1][1];
        d[i][3] = d[i - 1][2] + d[i - 1][3] * 10;
    }
    int T; data n;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%lld", &n);
        int dig = 0, cur = 3;
        while(d[dig][3] < n) dig ++;
        while(dig)
        {
            data s = 0;
            for(int i = 0; i < 10; i ++)
            {
                data t = 0;
                for(int j = 3; j >= f[cur][i]; j --)
                    t += d[dig - 1][j];
                if(s + t >= n)
                {
                    printf("%d", i);
                    cur = f[cur][i];
                    break ;
                }
                s += t;
            }
            n -= s, dig --;
        }
        puts("");
    }
    return 0;
}
