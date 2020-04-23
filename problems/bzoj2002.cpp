#include    <cstdio>
#include    <cstring>
#include    <iostream>
 
using   namespace   std;
const   int N = 2e5 + 5;
 
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
 
int n, m, pre[N], son[N][2], size[N];
 
inline bool isRoot(int p)
{
    return p != son[pre[p]][0] && p != son[pre[p]][1];
}
 
inline void Update(int p)
{
    return (void) (size[p] = size[son[p][0]] + size[son[p][1]] + 1);
}
 
inline void Rotate(int x)
{
    int p = pre[x], g = x == son[p][1];
    int y = son[x][g^1], z = pre[p];
    if(p == son[z][0])
        son[z][0] = x;
    else if(p == son[z][1])
        son[z][1] = x;
    pre[x] = z, son[p][g] = y, pre[y] = p;
    son[x][g^1] = p, pre[p] = x;
    return (void) (Update(p));
}

inline void Splay(int p)
{
    while(!isRoot(p))
    {
        int x = pre[p], y = pre[x];
        if(isRoot(x))
            Rotate(p);
        else if((p == son[x][0]) ^ (x == son[y][0]))
            Rotate(p), Rotate(p);
        else
            Rotate(x), Rotate(p);
    }
    return (void) (Update(p));
}
 
inline void Access(int p)
{
    for(int i = 0; p; i = p, p = pre[p])
    {
        Splay(p);
        son[p][1] = i;
        Update(p);
    }
    return ;
}
 
inline void Operate(int p, int q)
{
    Access(p), Splay(p);
    pre[son[p][0]] = 0, pre[p] = q, son[p][0] = 0;
    return (void) (Update(p));
}
 
inline int Query(int p)
{
    Access(p), Splay(p);
    return size[son[p][0]] + 1;
}
 
int main(int argc, char **argv)
{
    n = in();
    for(int i = 1, k; i <= n; i ++)
    {
        k = i + in();
        if(k > n) k = 0;
        pre[i] = k;
        if(k && !son[k][1])
            son[k][1] = i;
    }
    for(int i = 1; i <= n; i ++)
        if(!son[i][1])
            Splay(i);
    m = in();
    while(m --)
    {
        int c = in();
        if(c == 1)
            printf("%d\n", Query(in() + 1));
        else
        {
            int a = in(), b = in();
            Operate(a + 1, a + b + 1 <= n ? a + b + 1 : 0);
        }
    }
    return 0;
}
