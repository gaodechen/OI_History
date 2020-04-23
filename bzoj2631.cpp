#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
typedef unsigned int uint;
const   uint MOD = 51061;
const   int N = 100001;

inline uint in()
{
    uint k = 0, c = '\0';
    for(; c > '9' || c < '0';)
        c = getchar();
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return k;
}

inline uint f(uint x) {return x >= MOD ? x % MOD: x;}
inline void ADD(uint &a, uint b) {a = f(a + b);};
inline void MUL(uint &a, uint b) {a = f(a * b);};

bool rev[N];
uint mul[N], add[N], val[N], sum[N], size[N];
int son[N][2], pre[N];

// SplayTree Part

inline bool isRoot(int p) {return p != son[pre[p]][0] && p != son[pre[p]][1];}

inline void Mul(int p, uint M)
{
    // if(!p) return ;
    MUL(sum[p], M), MUL(val[p], M);
    MUL(mul[p], M), MUL(add[p], M);
    return ;
}

inline void Add(int p, uint A)
{
    ADD(sum[p], f(A * size[p]));
    ADD(val[p], A), ADD(add[p], A);
    return ;
}

inline void Update(int p)
{
    int l = son[p][0], r = son[p][1];
    sum[p] = f(sum[l] + sum[r] + val[p]);
    size[p] = f(size[l] + size[r] + 1);
    return ;
}

inline void PushDown(int p)
{
    int l = son[p][0], r = son[p][1];
    if(rev[p])
    {
        rev[p] = 0, rev[l] ^= 1, rev[r] ^= 1;
        swap(son[p][0], son[p][1]);
    }
    if(mul[p] != 1)
        Mul(son[p][0], mul[p]), Mul(son[p][1], mul[p]), mul[p] = 1;
    if(add[p])
        Add(son[p][0], add[p]), Add(son[p][1], add[p]), add[p] = 0;
    return ;
}

inline void Rotate(int x)
{
    int p = pre[x], g = son[p][1] == x;
    int y = son[x][g ^ 1], z = pre[p];
    if(son[z][0] == p)
        son[z][0] = x;
    else if(son[z][1] == p)
        son[z][1] = x;
    pre[x] = z, son[p][g] = y, pre[y] = p;
    son[x][g ^ 1] = p, pre[p] = x;
    return (void) (Update(p));
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
    return (void) (Update(p));
}

// Link-Cut Tree Part

inline void Access(int p)
{
    int last = 0;
    while(p != 0)
    {
        Splay(p), son[p][1] = last;
        Update(p), last = p, p = pre[p];
    }
    return ;
}

inline void MakeRoot(int p) {Access(p), Splay(p), rev[p] ^= 1;}
inline void Split(int p, int q) {MakeRoot(q), Access(p), Splay(p);};
inline void Link(int p, int q) {MakeRoot(p), pre[p] = q;}
inline void Cut(int p, int q) {Split(q, p), son[q][0] = pre[p] = 0;}

int main(int argc, char **argv)
{
    int n = in(), q = in();
    for(int i = 1; i <= n; i ++)
        sum[i] = val[i] = mul[i] = size[i] = 1;
    for(int i = 1; i < n; i ++)
        Link(in(), in());
    while(q --)
    {
        char buf[1]; int u, v;
        scanf("%s", buf);
        u = in(), v = in();
        if(buf[0] == '-')
            Cut(u, v), Link(in(), in());
        else if(buf[0] == '/')
        {
            Split(u, v);
            printf("%d\n", sum[u]);
        }
        else if(buf[0] == '*')
        {
            int x = in(); Split(u, v);
            if(x != 1) Mul(u, x);
        }
        else
        {
            int x = in(); Split(u, v);
            if(x) Add(u, x);
        }
    }
    return 0;
}

