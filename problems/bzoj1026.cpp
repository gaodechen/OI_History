#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;

inline int ABS( int x )
{
    if( x < 0 )
        return -x;
    return x;
}

int l, r, d[16][16], dig[16];

inline int F( int n )
{
    int len = 0, ans = 0;
    while( n )
    {
        dig[++len] = n % 10;
        n /= 10;
    }
    for( int i = 1; i < len; i ++ )
        for( int j = 1; j <= 9; j ++ )
            ans += d[i][j];
    for( int i = 1; i < dig[len]; i ++ )
        ans += d[len][i];
    for(int i = len - 1; i; i --)
    {
        for(int j = 0; j < dig[i]; j ++)
            if(ABS(j - dig[i + 1]) >= 2)
                ans += d[i][j];
        if(ABS(dig[i + 1] - dig[i]) < 2)
            break ;
    }
    return ans;
}

int main(int argc, char **argv)
{
    scanf("%d%d", &l, &r);
    for(int i = 0; i <= 9; i ++)
        d[1][i] = 1;
    for(int i = 2; i <= 10; i ++)
        for(int j = 0; j <= 9; j ++)
            for(int k = 0; k <= 9; k ++)
                if(ABS(j - k) >= 2)
                    d[i][j] += d[i - 1][k];
    printf("%d\n", F(r + 1) - F(l));
    return 0;
}

