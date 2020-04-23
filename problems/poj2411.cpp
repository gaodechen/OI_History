#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef long long   data;
const   int N = 12, M = 1 << 12;

int n, m;
data d[N][M], sum;

void Search(int i, int j, int s) {
    if(j == m) {
        d[i][s] += sum;
        return ;
    }
    Search(i, j + 1, s);
    if(j <= m - 2 && !(s & (1 << j)) && !(s & (1 << (j + 1))))
        Search(i, j + 2, s | (1 << j) | (1 << (j + 1)));
    return ;
}

int main() {
    while(scanf("%d%d", &n, &m) && n)
    {
        if(n < m) swap(n, m);
        sum = 1;
        memset(d, 0, sizeof( d ));
        Search(1, 0, 0);
        for(int i = 2; i <= n; i ++) {
            for(int j = 0; j < (1 << m); j ++) {
                if(d[i - 1][j]) sum = d[i - 1][j];
                else continue ;
                Search(i, 0, ~j & ((1 << m) - 1));
            }
        }
        printf("%lld\n", d[n][(1 << m)-1]);
    }
    return 0;
}
