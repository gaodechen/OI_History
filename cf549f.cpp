#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

inline int in()
{
    int k = 0, c = '\0', f = 1;
    for(; c > '9' || c < '0';)
        if((c = getchar()) == '-')
            f = 0;
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return f ? k : -k;
}

const int N = 3e5 + 5;

int a[N], sum[N], n, K;

inline int Query(int l, int r, int x)
{
    return upper_bound(a + l, a + r + 1, x) - lower_bound(a + l, a + r + 1, x);
}

int Divide(int l, int r)
{
    if(l == r) return 0;
    int maxPos = -1, R = 0;
    for(int i = l; i <= r; i ++)
        if(maxPos == -1 || a[maxPos] < a[i])
            maxPos = i;
    R += Divide(l, maxPos - 1);
    R += Divide(maxPos + 1, r);
    for(int i = l; i < maxPos; i ++)
        R += Query(maxPos + 1, r, sum[i - 1] - a[maxPos]);
    return R;
}

int main(int argc, char **argv)
{
    freopen("in", "r", stdin);
    n = in(), K = in();
    for(int i = 1; i <= n; i ++)
        a[i] = in(), sum[i] = (sum[i - 1] + a[i]) % K;
    printf("%d", Divide(1, n));
    return 0;
}
