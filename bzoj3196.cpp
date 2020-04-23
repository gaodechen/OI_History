#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>
#include    <set>
#include    <stl>
#include    <map>
#include    <cmath>
#include    <queue>
#include    <vector>

#define     inc(i, n)       for(int i = 1; i <= n; i ++)
#define     dec(i, n)       for(int i = n; i >= 1; i --)
#define     foreach(u)      for(int i = head[u]; i; i = e[i].next)

using namespace	std;
const int INF = 0x3f3f3f3f;
const int N = 50001, K = 40;
typedef pair<int, int> Item;
typedef long long data;

inline int in()
{
    int k = 0, c = '\0', f = 1;
    for(; c > '9' || c < '0';)
        if((c = getchar()) == '-')
            f = 0;
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return f ? k : -k;
}

struct SNode
{
    int key, size, Count;
    SNode *son[2], *pre;

    inline bool g() {return pre -> son[1] == this;}
    inline void SetChild(SNode *a, int c) {this -> son[c] = a, a -> pre = this;}
    inline void Update() {size = son[0] -> size + son[1] -> size + Count;}
};

inline SNode *Extract(int key)
{
    static SNode pool[N * K], *T = pool;
    return T ++;
}

struct SplayTree
{
    SNode *null, *root;

    inline SNode *NewNode(int key)
    {
        SNode *T = Extract(key);
        T -> son[0] = T -> son[1] = T -> pre = null;
        T -> size = T -> Count = 1, T -> key = key;
        return T;
    }

    inline void Initialize()
    {
        null = Extract(-1), null -> son[0] = null -> son[1] = null -> pre = null, root = null;
    }

    inline void Rotate(SNode *a)
    {
        SNode *p = a -> pre;
        bool g = a -> g();
        p -> pre -> SetChild(a, p -> g());
        p -> SetChild(a -> son[!g], g);
        a -> SetChild(p, !g);
        return (void) (p -> Update());
    }

    inline void Splay(SNode *a, SNode *target)
    {
        while(a -> pre != target)
        {
            if(a -> pre -> pre == target)
                Rotate(a);
            else
            {
                if(a -> pre -> g() == a -> g())
                    Rotate(a -> pre), Rotate(a);
                else
                    Rotate(a), Rotate(a);
            }
        }
        a -> Update();
        if(target == null)
            root = a;
        return ;
    }

    inline void Find(SNode *p, int key)
    {
        while(p -> key != key && p != null)
            p = p -> son[key > p -> key];
        return (void) (Splay(p, null));
    }

    inline void Delete(SNode *p)
    {
        if(root -> Count > 1)
        {
            root -> Count --, root -> Update();
            return ;
        }
        if(p -> son[0] == null && p -> son[1] == null)
            root = null;
        else if(p -> son[0] == null)
            root = p -> son[1], root -> pre = null;
        else if(p -> son[1] == null)
            root = p -> son[0], root -> pre = null;
        else
        {
            SNode *prev = p -> son[0], *next = p -> son[1];
            while(prev -> son[1] != null)
                prev = prev -> son[1];
            Splay(prev, root), prev -> pre = null;
            prev -> SetChild(next, 1);
            root = prev, root -> Update();
        }
        return ;
    }

    inline void Insert(SNode *p, int key)
    {
        if(root == null)
            return (void) (root = NewNode(key));
        SNode *prev = p -> pre;
        while(p != null)
        {
            if(p -> key == key)
            {
                p -> Count ++, Splay(p, null);
                return ;
            }
            prev = p, p = p -> son[key > p -> key];
        }
        SNode *a = NewNode(key);
        prev -> SetChild(a, key > prev -> key);
        prev -> Update(), Splay(a, null);
        return ;
    }

    inline int LessCount(int key)
    {
        SNode *p = root;
        int r = 0;
        while(p != null)
        {
            if(p -> key > key)
                p = p -> son[0];
            else
            {
                r += p -> Count + p -> son[0] -> size;
                p = p-> son[1];
            }
        }
        return r;
    }

    inline int FindPrecursor(int key)
    {
        SNode *p = root;
        int r = -1;
        while(p != null)
        {
            if(p -> key < key) r = max(r, p -> key);
            p = p -> son[p -> key < key];
        }
        return r;
    }

    inline int FindSuccessor(int key)
    {
        SNode *p = root;
        int r = INF;
        while(p != null)
        {
            if(p -> key > key) r = min(r, p -> key);
            p = p -> son[p -> key <= key];
        }
        return r;
    }
};

int n, Q, a[N];

struct SegmentTree
{
    typedef SegmentTree Node;

    Node *lson, *rson;
    SplayTree splay;

    inline Node *NewNode()
    {
        static Node pool[N << 1], *T = pool;
        return T ++;
    }

    void BuildTree(int l, int r)
    {
        if(l != r)
        {
            int mid = (l + r) >> 1;
            (lson = NewNode()) -> BuildTree(l, mid);
            (rson = NewNode()) -> BuildTree(mid + 1, r);
        }
        splay.Initialize();
        for(int i = l; i <= r; i ++)
            splay.Insert(splay.root, a[i]);
        return ;
    }

    int QueryRank(int l, int r, int L, int R, int k)
    {
        if(l >= L && r <= R)
            return splay.LessCount(k);
        int mid = (l + r) >> 1, a = 0, b = 0;
        if(R <= mid)
            a = lson -> QueryRank(l, mid, L, R, k);
        else if(L > mid)
            b = rson -> QueryRank(mid + 1, r, L, R, k);
        else
        {
            a = lson -> QueryRank(l, mid, L, mid, k);
            b = rson -> QueryRank(mid + 1, r, mid + 1, R, k);
        }
        return a + b;
    }

    void ReplaceNumber(int l, int r, int p, int k)
    {
        if(l == r)
            return (void) (splay.root -> key = k);
        int mid = (l + r) >> 1;
        if(p <= mid)
            lson -> ReplaceNumber(l, mid, p, k);
        else
            rson -> ReplaceNumber(mid + 1, r, p, k);
        splay.Find(splay.root, a[p]);
        splay.Delete(splay.root);
        splay.Insert(splay.root, k);
        return ;
    }

    int FindPrecursor(int l, int r, int L, int R, int k)
    {
        if(l >= L && r <= R)
            return splay.FindPrecursor(k);
        int mid = (l + r) >> 1, a = -1, b = -1;
        if(R <= mid)
            a = lson -> FindPrecursor(l, mid, L, R, k);
        else if(L > mid)
            b = rson -> FindPrecursor(mid + 1, r, L, R, k);
        else
        {
            a = lson -> FindPrecursor(l, mid, L, mid, k);
            b = rson -> FindPrecursor(mid + 1, r, mid + 1, R, k);
        }
        return a > b ? a : b;
    }

    int FindSuccessor(int l, int r, int L, int R, int k)
    {
        if(l >= L && r <= R)
            return splay.FindSuccessor(k);
        int mid = (l + r) >> 1, a = INF, b = INF;
        if(R <= mid)
            a = lson -> FindSuccessor(l, mid, L, R, k);
        else if(L > mid)
            b = rson -> FindSuccessor(mid + 1, r, L, R, k);
        else
        {
            a = lson -> FindSuccessor(l, mid, L, mid, k);
            b = rson -> FindSuccessor(mid + 1, r, mid + 1, R, k);
        }
        return a < b ? a : b;
    }
} seg;

inline int QueryKthNumber(int L, int R, int k)
{
    int l = 1, r = (int) 1e8;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(seg.QueryRank(1, n, L, R, mid) < k)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

int main(int argc, char **argv)
{
    n = in(), Q = in();
    for(int i = 1; i <= n; i ++)
        a[i] = in();
    seg.BuildTree(1, n);
    while(Q --)
    {
        int opt = in();
        if(opt == 1)
        {
            int l = in(), r = in(), k = in();
            printf("%d\n", seg.QueryRank(1, n, l, r, k - 1) + 1);
        }
        else if(opt == 2)
        {
            int l = in(), r = in(), k = in();
            printf("%d\n", QueryKthNumber(l, r, k));
        }
        else if(opt == 3)
        {
            int p = in(), k = in();
            seg.ReplaceNumber(1, n, p, k);
            a[p] = k;
        }
        else if(opt == 4)
        {
            int l = in(), r = in(), k = in();
            printf("%d\n", seg.FindPrecursor(1, n, l, r, k));
        }
        else
        {
            int l = in(), r = in(), k = in();
            printf("%d\n", seg.FindSuccessor(1, n, l, r, k));
        }
    }
    return 0;
}
