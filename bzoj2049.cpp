#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 1e4 + 5;

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

bool rev[N];
int pre[N], son[N][2];

inline bool isRoot(int p)
{
    return son[pre[p]][0] != p && son[pre[p]][1] != p;
}

inline void PushDown(int p)
{
    if(rev[p])
    {
        rev[p] ^= 1, rev[son[p][0]] ^= 1, rev[son[p][1]] ^= 1;
        swap(son[p][0], son[p][1]);
    }
    return ;
}

inline void Rotate(int x)
{
    int p = pre[x], g = x == son[p][1];
    int y = son[x][g ^ 1], z = pre[p];
    if(p == son[z][0])
        son[z][0] = x;
    else if(p == son[z][1])
        son[z][1] = x;
    pre[x] = z, son[p][g] = y, pre[y] = p;
    son[x][g^1] = p, pre[p] = x;
    return ;
}

inline void Splay(int p)
{
    PushDown(p);
    while(!isRoot(p))
    {
        int x = pre[p], y = pre[x];
        PushDown(y), PushDown(x), PushDown(p);
        if(isRoot(x))
            Rotate(p);
        else if((p == son[x][0]) ^ (x == son[y][0]))
            Rotate(p), Rotate(p);
        else
            Rotate(x), Rotate(p);
    }
    return ;
}

inline void Access(int p)
{
    int last = 0;
    while(p != 0)
    {
        Splay(p);
        son[p][1] = last, last = p, p = pre[p];
    }
    return ;
}

inline void MakeRoot(int p)
{
    Access(p), Splay(p), rev[p] ^= 1;
}

inline void Link(int p, int q)
{
    MakeRoot(p), pre[p] = q;
}

inline void Cut(int p, int q)
{
    MakeRoot(p), Access(q), Splay(q);
    son[q][0] = pre[p] = 0;
}

inline int Find(int p)
{
    Access(p), Splay(p);
    int r = p;
    while(son[r][0])
        r = son[r][0];
    return r;
}

int main()
{
    in(); int q = in();
    for(int i = 0; i < q; i ++)
    {
        char buf[8];
        scanf("%s", buf);
        int u = in(), v = in();
        if(buf[0] == 'Q')
        {
            bool r = Find(u) == Find(v);
            puts(r ? "Yes" : "No");
        }
        else if(buf[0] == 'C')
            Link(u, v);
        else
            Cut(u, v);
    }
    return 0;
}
