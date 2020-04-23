#include    <cstdio>

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main(int argc, char **argv)
{
    long long n, m;
    scanf("%lld%lld", &n, &m);
    n ++, m ++;
    long long k = n * m, ans = k * (k - 1) * (k - 2) / 6;
    ans -= n * m * (m - 1) * (m - 2) / 6;
    ans -= m * n * (n - 1) * (n - 2) / 6;
    for(int i = 1; i < n; i ++)
        for(int j = 1; j < m; j ++)
            ans -= 2LL * (gcd(i, j) - 1) * (m - j) * (n - i);
    printf("%lld\n", ans);
    return 0;
}
