#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <map>
#include    <cmath>
#include    <queue>
#include    <vector>

using namespace	std;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> Pair;
typedef long long data;

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

const int N = 100005, B = 26;

struct Item
{
    int c, l, r;
} q[505];

int cL[B], cR[N], C[N], Cnt[B];
char S[N];
int sum[B][N], a[N], n, K, L, R, ans;

inline void Interface1()
{
    memset(cL, -1, sizeof(cL));
    memset(cR, INF, sizeof(cR));
    for(int k = 0; k < K; k ++)
    {
        int l = q[k].l, r = q[k].r, c = q[k].c;
        cL[c] = max(cL[c], l), cR[c] = min(cR[c], r);
        Cnt[c] ++;
    }
    for(int c = 0; c < B; c ++)
        if(cL[c] > cR[c])
            return (void) (printf("0\n"));
    for(int i = 1; i <= n; i ++)
    {
        for(int j = i + 1; j <= n; j ++)
        {
            int cnt = 0;
            for(int c = 0; c < B; c ++)
            {
                if(cR[c] == -1) continue ;
                int d = sum[c][j] - sum[c][i - 1];
                if(d >= cL[c] && d <= cR[c]) cnt += Cnt[c];
            }
            if(cnt >= L && cnt <= R) ans ++;
        }
    }
    printf("%d\n", ans);
    return ;
}

inline void Interface2()
{
    for(int i = 1; i <= n; i ++)
    {
        for(int j = i + 1; j <= n; j ++)
        {
            int cnt = 0;
            for(int k = 0; k < K; k ++)
            {
                int c = q[k].c, l = q[k].l, r = q[k].r;
                int d = sum[c][j] - sum[c][i - 1];
                if(d >= l && d <= r) cnt ++;
            }
            if(cnt >= L && cnt <= R) ans ++;
        }
    }
    printf("%d\n", ans);
    return ;
}

int main(int argc, char **argv)
{
    freopen("letter.in", "r", stdin);
    freopen("letter.out", "w", stdout);
    scanf("%s", S + 1);
    n = strlen(S + 1), K = in(), L = in(), R = in();
    for(int i = 1; i <= n; i ++)
        a[i] = S[i] - 'a';
    for(int i = 0; i < K; i ++)
    {
        char buf[2];
        scanf("%s", buf);
        int c = buf[0] - 'a', l = in(), r = in();
        q[i] = (Item) {c, l, r};
    }
    for(int i = 1; i <= n; i ++)
    {
        for(int j = 0; j < B; j ++)
        {
            sum[j][i] = sum[j][i - 1];
            if(j == a[i]) sum[j][i] ++;
        }
    }
    if(K == L && K == R)
        Interface1();
    else
        Interface2();
    return 0;
}

