#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 100007;

int a[N], sum[N], l[N + N], r[N + N];

int main(int argc, char **argv)
{
    int n, b, p;
    scanf("%d%d", &n, &b);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d", &a[i]);
        if(a[i] == b) p = i;
        else if(a[i] > b) a[i] = 1;
        else a[i] = -1;
    }
    l[n] = 1, r[n] = 1;
    for(int i = p - 1; i >= 1; i --)
        sum[i] = sum[i + 1] + a[i], l[sum[i] + n] ++;
    for(int i = p + 1; i <= n; i ++)
        sum[i] = sum[i - 1] + a[i], r[sum[i] + n] ++;
    int ans = 0;
    for(int i = -n; i <= n; i ++)
        ans += l[i + n] * r[-i + n];
    printf("%d\n", ans);
    return 0;
}
