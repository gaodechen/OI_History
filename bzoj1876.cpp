#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
typedef long long   data;
const   data K = 10000000000;
const   int N = 10001;
const   int L = 10;

data x[N], y[N];

inline void Transform(data a[], int *seg)
{
    int n = seg[0];
    reverse(seg + 1, seg + n + 1);
    data t = 0, l = 1;
    for(int i = 1; i <= n; i ++)
    {
        t += seg[i] * l, l *= 10;
        if(i % L == 0)
            a[++a[0]] = t, t = 0, l = 1;
    }
    if(t) a[++a[0]] = t;
    return ;
}

int seg[N];

inline void Input()
{
    int c; seg[0] = 0;
    while(c = getchar(), isdigit(c))
        seg[++seg[0]] = c - '0';
    Transform(x, seg);
    while(c = getchar(), !isdigit(c));
    seg[0] = 0;
    seg[++seg[0]] = c - '0';
    while(c = getchar(), isdigit(c))
        seg[++seg[0]] = c - '0';
    Transform(y, seg);
    return ;
}

inline void Print(data *a)
{
    printf("%lld", a[a[0]]);
    for(int i = a[0] - 1; i >= 1; i --)
        printf("%010lld", a[i]);
    puts("");
}

inline bool cmp(data *a, data *b)
{
    if(a[0] != b[0]) return a[0] < b[0];
    int l = a[0];
    while(a[l] == b[l] && l > 1) l --;
    return a[l] < b[l];
}

inline void Minus(data* &a, data* &b)
{
    bool g = cmp(a, b);
    if(g) swap(a, b);
    for(int i = 1; i <= a[0]; i ++) a[i] -= b[i];
    for(int i = 1; i <= a[0]; i ++)
        if(a[i] < 0) a[i + 1] --, a[i] += K;
    data &l = a[0];
    while(!a[l] && l > 1) l --;
    return ;
}

inline void mul(data *a, data *b)
{
    data c[N] = {0};
    c[0] = a[0] + b[0] - 1;
    for(int i = 1; i <= a[0]; i ++)
        for(int j = 1; j <= b[0]; j ++)
            c[i+j-1] += a[i] * b[j];
    for(int i = 1; i <= c[0]; i ++)
        if(c[i] >= K) c[i + 1] += c[i] / K, c[i] %= K;
    if(c[c[0] + 1]) c[0] ++;
    memcpy(a, c, sizeof(data) * (c[0] + 1));
    return ;
}

inline void div(data *a)
{
    int l = a[0], p = 0;
    if(a[a[0]] < 2) l --;
    for(int i = a[0]; i >= 1; i --)
    {
        if(p) a[i] = a[i] + K;
        p = a[i] & 1, a[i] >>= 1;
    }
    a[0] = l;
    return ;
}

data p[5] = {1, 2}, del[N] = {1, 1}, *a = x, *b = y;

#define     f(a)        (a[0] == 1 && a[1] == 0)

int main(int argc, char **argv)
{
    Input();
    while(!f(a) && !f(b))
    {
        bool oddA = a[1] & 1, oddB = b[1] & 1;
        if(oddA && oddB)
            Minus(a, b);
        else if(!oddA && !oddB)
            div(a), div(b), mul(del, p);
        else if(oddA && !oddB)
            div(b);
        else if(!oddA && oddB)
            div(a);
    }
    if(f(a))
        mul(b, del), Print(b);
    else
        mul(a, del), Print(a);
    return 0;
}
