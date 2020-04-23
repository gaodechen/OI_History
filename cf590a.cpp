#include    <cstdio>
#include    <cstring>
#include    <iostream>

#define     REP(i, l, r)    for(int i = l; i <= r; i ++)

using   namespace   std;
const   int N = 5e5 + 5;

int n, a[N], b[N];

int main()
{
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", a + i);
    REP(i, 2, n) b[i] = a[i - 1] ^ a[i];
    int ans = 0;
    for(int i = 1, j; i <= n; i = j + 1)
    {
        j = i;
        while(j <= n && b[j]) j ++;
        ans = max(ans, (j - i) >> 1);
        REP(k, i, j - 1) b[k] = 0;
        if((j - i) & 1) b[(i + j) >> 1] = 1;
    }
    printf("%d\n", ans);
    int p = a[1];
    REP(i, 1, n)
    {
        printf("%d ", p);
        p ^= b[i + 1];
    }
    return 0;
}

