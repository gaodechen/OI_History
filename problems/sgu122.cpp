#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1005;

int n, p, seq[N];
bool vis[N], G[N][N];

inline int Get(int u) {
    for(int i = 1; i <= n; i ++)
        if(G[u][i] && !vis[i])
            return i;
    return 0;
}

inline void Expand() {
    while(true) {
        int v = Get(seq[p-1]);
        if(v == 0) break ;
        seq[p++] = v, vis[v] = 1;
    }
    return ;
}

inline void Interface()
{
    while(true) {
        Expand(), reverse(seq, seq + p), Expand();
        if(!G[seq[0]][seq[p-1]]) {
            for(int i = 1; i < p - 1; i ++) {
                if(G[seq[i+1]][seq[0]] && G[seq[i]][seq[p-1]]) {
                    reverse(seq + i + 1, seq + p);
                    break ;
                }
            }
        }
        if(p == n) break ;
        for(int i = 0; i < p; i ++) {
            int v = 0;
            for(int j = 1; j <= n; j ++) {
                if(G[seq[i]][j] && !vis[j]) {
                    v = j;
                    break ;
                }
            }
            if(v) {
                reverse(seq, seq + i);
                reverse(seq + i, seq + p);
                seq[p++] = v, vis[v] = true;
                break ;
            }
        }
    }
    return ;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        int v; char c;
        while(~scanf("%d%c", &v, &c)) {
            G[i][v] = 1;
            if(c == '\n') break ;
        }
    }
    seq[p++] = 1, vis[1] = 1;
    Interface();
    for(int i = 0; i < p; i ++) {
        if(seq[i] == 1) {
            int u = i;
            for(int j = 0; j < p; j ++) {
                printf("%d ", seq[u++]);
                if(u == p) u = 0;
            }
            break ;
        }
    }
    puts("1");
    return 0;
}
