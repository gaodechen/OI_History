#include    <cstdio>
#include    <cstring>
#include    <iostream>
 
using   namespace   std;
typedef unsigned int ui;
typedef unsigned long long ull;
const   int N = 1e5 + 5;
 
inline ui in()
{
    ui k = 0; int c = '\0';
    for(; c > '9' || c < '0';)
        c = getchar();
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return k;
}
 
int n; ui MOD;
 
inline ui f(ull x)
{
    return x >= MOD ? x % MOD : x;
}
 
struct SegmentTree
{
    typedef SegmentTree Node;
 
    ui add, mul, val;
    Node *A, *B;
 
    inline Node *NewNode()
    {
        static Node pool[N<<1], *T = pool;
        return T ++;
    }
 
    inline void Update() {val = f(A -> val + B -> val);}
 
    inline void PushDown(int l, int r, int mid)
    {
        // mul == 0...
        if(mul > 1 || mul == 0)
        {
            A -> mul = f((ull) A -> mul * mul), B -> mul = f((ull) B -> mul * mul);
            A -> add = f((ull) A -> add * mul), B -> add = f((ull) B -> add * mul);
            A -> val = f((ull) A -> val * mul), B -> val = f((ull) B -> val * mul);
            mul = 1;
        }
        if(add)
        {
            A -> add = f((ull) A -> add + add), B -> add = f((ull) B -> add + add);
            A -> val = f((ull) A -> val + (ull) add * (mid - l + 1));
            B -> val = f((ull) B -> val + (ull) add * (r - mid));
            add = 0;
        }
        return ;
    }
 
    inline void BuildTree(int l, int r)
    {
        mul = 1;
        if(l == r)
            return (void) (val = f(in()));
        int mid = (l + r) >> 1;
        (A = NewNode()) -> BuildTree(l, mid);
        (B = NewNode()) -> BuildTree(mid + 1, r);
        return (void) (Update());
    }
 
    inline void Multiply(int l, int r, int L, int R, ui k)
    {
        if(l >= L && r <= R)
        {
            val = f((ull) val * k);
            add = f((ull) add * k);
            mul = f((ull) mul * k);
            return ;
        }
        int mid = (l + r) >> 1;
        PushDown(l, r, mid);
        if(L <= mid)
            A -> Multiply(l, mid, L, R, k);
        if(R > mid)
            B -> Multiply(mid + 1, r, L, R, k);
        return (void) (Update());
    }
 
    inline void Add(int l, int r, int L, int R, ui k)
    {
        if(l >= L && r <= R)
        {
            val = f(val + (ull) (r - l + 1) * k);
            add = f(add + k);
            return ;
        }
        int mid = (l + r) >> 1;
        PushDown(l, r, mid);
        if(L <= mid)
            A -> Add(l, mid, L, R, k);
        if(R > mid)
            B -> Add(mid + 1, r, L, R, k);
        return (void) (Update());
    }
 
    inline ui Query(int l, int r, int L, int R)
    {
        if(l >= L && r <= R)
            return val;
        int mid = (l + r) >> 1;
        ui sum = 0;
        PushDown(l, r, mid);
        if(L <= mid)
            sum = f(sum + A -> Query(l, mid, L, R));
        if(R > mid)
            sum = f(sum + B -> Query(mid + 1, r, L, R));
        return sum;
    }
} seg;
 
int main()
{
    n = in(), MOD = in();
    seg.BuildTree(1, n);
    int q = in();
    while(q --)
    {
        int k = in(), l = in(), r = in();
        if(k == 1)
            seg.Multiply(1, n, l, r, in());
        else if(k == 2)
            seg.Add(1, n, l, r, in());
        else
            printf("%d\n", seg.Query(1, n, l, r));
    }
    return 0;
}
