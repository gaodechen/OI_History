#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 500005;

char S[N], s[N + N];
int f[N + N];

inline void Manacher(int n)
{
    int pos = 0, side = 0;
    f[0] = 1;
    for(int i = 1; i < n; i ++)
    {
        if(side > i)
            f[i] = min(side - i, f[pos + pos - i]);
        else
            f[i] = 1;
        while(s[i + f[i]] == s[i - f[i]])
            f[i] ++;
        if(i + f[i] > side)
            side = i + f[i], pos = i;
    }
    return ;
}

int n;

int main(int argc, char **argv)
{
    scanf("%d%s", &n, S);
    s[0] = '$', s[1] = '#';
    for(int i = 0; i < n; i ++)
        s[i + i + 2] = S[i], s[i + i + 3] = '#';
    Manacher(n = n + n + 2), n --;
    int ans = 0;
    for(int i = 2; i < n; i ++)
    {
        if(s[i] != '#') continue ;
        int j = max(0, i - f[i] / 2);
        if((j & 1) == 0) j ++;
        // Find the first j that j + f[j] >= i
        // (the longest one, also the first one which is legal)
        // in [i - f[i] / 2, i]
        // not strictly O(n) but runs very fast...
        // Optimize: as we can see, if j + f[j] < i, then j can be discard then
        // so we use UFS to maintain it
        // Or just use set to make it O(nlogn)
        while(j < i && j + f[j] < i)
            j += 2;
        if(j < i) ans = max(ans, (i - j) << 1);
    }
    printf("%d", ans);
    return 0;
}
