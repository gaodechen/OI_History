#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 5e4 + 5;

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

struct Item
{
    int l, r, id;
    bool operator < (const Item &b) const {return r < b.r;}
} q[200001];

inline int lowbit(int x) {return x & (-x);}

int a[N], bit[N], ans[200001], head[1000001];

int main(int argc, char **argv)
{
    int n = in();
    for(int i = 1; i <= n; i ++) a[i] = in();
    int Q = in();
    for(int i = 1; i <= Q; i ++) q[i].l = in(), q[i].r = in(), q[i].id = i;
    sort(q + 1, q + Q + 1);
    q[Q + 1].r = -1;
    for(int i = 1, j = 1; i <= n && j <= Q; i ++)
    {
        for(int p = i; p <= n; p += lowbit(p)) bit[p] ++;
        if(head[a[i]]) for(int p = head[a[i]]; p <= n; p += lowbit(p)) bit[p] --;
        head[a[i]] = i; int sum = 0;
        for(int p = i; p; p -= lowbit(p)) sum += bit[p];
        for(; q[j].r == i; j ++)
        {
            int tmp = 0;
            for(int p = q[j].l - 1; p; p -= lowbit(p)) tmp += bit[p];
            ans[q[j].id] = sum - tmp;
        }
    }
    for(int i = 1; i <= Q; i ++)
        printf("%d\n", ans[i]);
    return 0;
}
