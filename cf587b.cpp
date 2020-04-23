#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>
#include    <vector>

using   namespace   std;
typedef long long   data;
const   int N = 1e6 + 5;
const   int MOD = 1e9 + 7;

data l, C, ans;
int n, k, last, a[N], pos[N], d[N][2];

bool cmp(const int &i, const int &j)
{
    return make_pair(a[i], i) < make_pair(a[j], j);
}

inline void f(int i, int j)
{
    data t = (C - j + 1LL) % MOD;
    if(i > last && l % (data) n)
        t = (t - 1LL + MOD) % MOD;
    data x = (t * (data) d[i][j&1]) % MOD;
    ans = (ans + x) % MOD;
    return ;
}

int main()
{
    cin >> n >> l >> k;
    C = l / (data) n;
    if(l % n) C ++;
    last = (data) (l - 1LL) % (data) n;
    // The last number of the last period
    k = min((data) k, C);
    for(int i = 0; i < n; i ++)
    {
        scanf("%d", &a[i]);
        pos[i] = i, d[i][1] = 1, f(i, 1);
    }
    sort(pos, pos + n, cmp);
    for(int j = 2; j <= k; j ++)
    {
        int tail = 0, p = j & 1, q = p ^ 1, sum = 0;
        // d[i][j]
        for(int t = 0; t < n; t ++)
        {
            int i = pos[t];
            while(tail < n && a[pos[tail]] <= a[i])
                sum = (sum + d[pos[tail++]][q]) % MOD;
            d[i][p] = sum;
            f(i, j);
        }
    }
    cout << (ans % MOD + MOD) % MOD << endl;
    return 0;
}

