#include    <cstdio>
#include    <iostream>

#define     rep(i, k)       for(int i = 1; i <= k; i ++)

const   int M = 600;

inline int in() {
    int k = 0, c = '\0';
    for(; c > '9' || c < '0';)
        c = getchar();
    for(; c >= '0' && c <= '9';) {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return k;
}

int n, m, u[M], v[M], pre[M], pos[M];

int Find(int u) {
    if(u != pre[u])
        pre[u] = Find(pre[u]);
    return pre[u];
}

void Union(int u, int v) {
    pre[Find(v)] = Find(u);
}

inline bool Check(int i, int j) {
    return u[i] < u[j] && u[j] < v[i] && v[i] < v[j];
}

int main() {
    int T = in();
    while(T --)
    {
        n = in(), m = in();
        if(m > 3 * n - 6) {
            rep(i, m) in(), in();
            rep(i, n) in();
            puts("NO");
            continue ;
        }
        rep(i, m) u[i] = in(), v[i] = in();
        rep(i, m + m) pre[i] = i;
        rep(i, n) pos[in()] = i;
        rep(i, m) {
            u[i] = pos[u[i]], v[i] = pos[v[i]];
            if(u[i] > v[i])
                std::swap(u[i], v[i]);
        }
        rep(i, m) rep(j, i - 1)
            if(Check(i, j) || Check(j, i))
                Union(i, j + m), Union(j, i + m);
        rep(i, m + m) Find(i);
        bool flag = true;
        rep(i, m) {
            if(pre[i] == pre[i+m]) {
                flag = false;
                break ;
            }
        }
        puts(flag ? "YES" : "NO");
    }
    return 0;
}
