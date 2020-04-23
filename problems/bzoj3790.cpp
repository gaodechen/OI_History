#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100005;

char S[N], s[N + N];
int f[N];

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

struct Interval
{
    int l, r;

    bool operator < (const Interval &b) const
    {
        return l < b.l || (l == b.l && r > b.r);
    }
} e[N + N];

int main(int argc, char **argv)
{
    while(scanf("%s", S) == 1)
    {
        s[0] = '$', s[1] = '#';
        int n = strlen(S);
        for(int i = 0; i < n; i ++)
            s[i + i + 2] = S[i], s[i + i + 3] = '#';
        Manacher(n = n + n + 2), n --;
        int cnt = 0;
        for(int i = 2; i < n; i ++)
            e[cnt ++] = (Interval) {i - f[i] + 1, i + f[i] - 1};
        sort(e, e + cnt);

        int ans = 0, cur = 1, p = 0;
        while(cur != n)
        {
            int r = 0;
            while(e[p].l <= cur && p < cnt)
                r = max(e[p].r, r), p ++;
            cur = r, ans ++;
        }
        printf("%d\n", ans - 1);
    }
    return 0;
}
