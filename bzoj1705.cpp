#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int N = 100001;
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

int h[N], d[N][105], pos[N], nag[N];

int main(int argc, char **argv)
{
    int n = in(), C = in();
    memset(d, INF, sizeof(d));
    for(int i = 1; i <= n; i ++)
        h[i] = in();
    for(int i = 1; i <= 100; i ++)
        d[1][i] = i < h[1] ? INF : (h[1] - i) * (h[1] - i);
    for(int i = 2; i <= n; i ++)
    {
        nag[0] = INF, pos[101] = INF;
        for(int j = 1; j <= 100; j ++)
            nag[j] = min(nag[j - 1], d[i - 1][j] - j * C);
        for(int j = 100; j >= 1; j --)
            pos[j] = min(pos[j + 1], d[i - 1][j] + j * C);
        for(int j = h[i]; j <= 100; j ++)
        {
            int x = (j - h[i]) * (j - h[i]);
            d[i][j] = x + min(nag[j] + j * C, pos[j] - j * C);
        }
    }
    int ans = INF;
    for(int i = h[n]; i <= 100; i ++)
        ans = min(ans, d[n][i]);
    printf("%d\n", ans);
    return 0;
}
