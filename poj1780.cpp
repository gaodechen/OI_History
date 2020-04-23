#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e6 + 5;

bool vis[N];
int ans[N], head[N], stack[N];
int n, k, mod, sig, top, tik;

struct Edge
{
    int v, next;
} e[N];

inline void AddEdge( int u, int v )
{
    e[++sig].v = v, e[sig].next = head[u], head[u] = sig;
    return ;
}

void DFS( int u )
{
    int i;
    top = 0, stack[++top] = u;
    while( top )
    {
        u = stack[top--];
        for( i = head[u]; i; i = e[i].next )
        {
            if( !vis[i] )
            {
                vis[i] = 1;
                stack[++top] = u;
                stack[++top] = e[i].v;
                goto Mark;
            }
        }
        // When backtracing to u again
        ans[++tik] = u;
Mark: ;
    }
    return ;
}

int main()
{
    while( scanf( "%d", &n ) && n )
    {
        if( n == 1 )
        {
            printf( "0123456789\n" );
            continue ;
        }
        k = 1, tik = sig = 0;
        for( int i = 1; i < n; i ++ )
            k *= 10;
        cout << k << endl;
        mod = k / 10;
        memset( vis, 0, sizeof( vis ) );
        memset( head, 0, sizeof( head ) );
        for( int i = 0; i < k; i ++ )
        {
            int x = i % mod;
            for( int y = 9; y >= 0; y -- )
                AddEdge( i, x * 10 + y );
        }
        DFS( 0 );
        for( int i = 1; i < n - 1; i ++ )
            ans[++tik] = 0;
        for( int i = tik; i; i -- )
            printf( "%d", ans[i] % 10 );
        printf( "\n" );
    }
    return 0;
}
