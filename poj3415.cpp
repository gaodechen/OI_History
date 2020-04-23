#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
typedef long long data;
const int N = 200010;

char S[N];
int *Rank, A[N], X[N], Y[N], v[N];
int sa[N], height[N];

inline bool cmp(int *p, int a, int b, int l)
{
    return p[a] == p[b] && p[a + l] == p[b + l];
}

inline void InitSA(int n, int m)
{
    int *x = X, *y = Y;

    for(int i = 0; i < m; i ++) v[i] = 0;
    for(int i = 0; i < n; i ++) v[x[i] = A[i]] ++;
    for(int i = 1; i < m; i ++) v[i] += v[i - 1];
    for(int i = 0; i < n; i ++) sa[-- v[x[i]]] = i;

    for(int k = 1; k <= n; k <<= 1)
    {
        int p = 0;
        for(int i = n - 1; i >= n - k; i --) y[p ++] = i;
        for(int i = 0; i < n; i ++) if(sa[i] >= k) y[p ++] = sa[i] - k;

        for(int i = 0; i < m; i ++) v[i] = 0;
        for(int i = 0; i < n; i ++) v[x[y[i]]] ++;
        for(int i = 1; i < m; i ++) v[i] += v[i - 1];
        for(int i = n - 1; i >= 0; i --) sa[-- v[x[y[i]]]] = y[i];

        swap(x, y), p = 1, x[sa[0]] = 0;
        for(int i = 1; i < n; i ++)
        {
            if(cmp(y, sa[i], sa[i - 1], k)) x[sa[i]] = p - 1;
            else x[sa[i]] = p ++;
        }

        if((m = p) >= n) break ;
    }

    return (void) (Rank = x);
}

inline void InitHeight(int n)
{
    int k = 0;
    for(int i = 0; i < n; i ++)
        Rank[sa[i]] = i;
    for(int i = 0; i < n; i ++)
    {
        if(k != 0) k --;
        if(!Rank[i]) continue ;
        int j = sa[Rank[i] - 1];
        while(S[i + k] == S[j + k]) k ++;
        height[Rank[i]] = k;
    }
    return ;
}

data stack[N], C[N];

inline data Interface(int n, int m, int K)
{
    int top = 0;
    data ans = 0, tot = 0, cont;

    for(int i = 0; i < n; i ++)
    {
        if(height[i] < K)
        {
            top = 0, tot = 0LL;
            continue ;
        }
        cont = 0;
        if(sa[i - 1] > m)
            cont = 1, tot += height[i] - K + 1;
        while(top && stack[top] >= height[i])
        {
            if(C[top])
            {
                tot -= C[top] * (stack[top] - height[i]);
                cont += C[top];
            }
            top --;
        }
        stack[++ top] = height[i], C[top] = cont;
        if(sa[i] < m) ans += tot;
    }

    for(int i = 0; i < n; i ++)
    {
        if(height[i] < K)
        {
            top = 0, tot = 0LL;
            continue ;
        }
        cont = 0;
        if(sa[i  - 1] < m)
            cont = 1, tot += height[i] - K + 1;
        while(top && stack[top] >= height[i])
        {
            if(C[top])
            {
                tot -= C[top] * (stack[top] - height[i]);
                cont += C[top];
            }
            top --;
        }
        stack[++ top] = height[i], C[top] = cont;
        if(sa[i] > m) ans += tot;
    }
    return ans;
}

int main(int argc, char **argv)
{
    int K, n_, n;
    while(scanf("%d", &K) == 1 && K)
    {
        memset(sa, 0, sizeof(sa));
        memset(X, 0, sizeof(X));
        memset(Y, 0, sizeof(Y));
        memset(height, 0, sizeof(height));

        scanf("%s", S), n_ = strlen(S), S[n_] = '$';
        scanf("%s", S + n_ + 1), n = strlen(S);
        for(int i = 0; i < n; i ++) A[i] = S[i];
        InitSA(n, 128), InitHeight(n);

        data ans = Interface(n, n_, K);
        printf("%I64d\n", ans);
    }
    return 0;
}
