#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 5e5 + 10;
const   int INF = 0x3f3f3f3f;

inline int in()
{
    int k = 0, c = '\0', f = 1;
    for(; c > '9' || c < '0';)
    {
        c = getchar();
        if(c == '-')
            f = 0;
    }
    for(; c >= '0' && c <= '9';)
    {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return f ? k : -k;
}

inline int abs(int x)
{
    return x < 0 ? -x : x;
}

struct SegmentTree
{
    typedef SegmentTree Node;

    int val;
    Node *lson, *rson;

    inline Node *NewNode()
    {
        static Node pool[N<<1], *tail = pool;
        return tail ++;
    }

    inline void Update()
    {
        return (void) (val = min(lson -> val, rson -> val));
    }

    void BuildTree(int l, int r, int *a, int n)
    {
        if(l == r)
            val = l < n ? abs(a[l] - a[l+1]) : INF;
        else
        {
            int mid = (l + r) >> 1;
            (lson = NewNode()) -> BuildTree(l, mid, a, n);
            (rson = NewNode()) -> BuildTree(mid + 1, r, a, n);
            Update();
        }
        return ;
    }

    void Modify(int l, int r, int x, int val)
    {
        if(l == r)
            this -> val = val;
        else
        {
            int mid = (l + r) >> 1;
            if(x <= mid)
                lson -> Modify(l, mid, x, val);
            else
                rson -> Modify(mid + 1, r, x, val);
            Update();
        }
        return ;
    }
} *segRoot;

struct SplayTree
{
    struct Node
    {
        int val;
        Node *son[2], *pre;

        inline bool g()
        {
            return pre -> son[1] == this;
        }

        inline void SetChild(Node *p, int c)
        {
            son[c] = p, p -> pre = this;
        }
    } node[N << 1], *root;

    SplayTree()
    {
        root = node -> son[0] = node -> son[1] = node -> pre = node;
    }

    inline Node *NewNode(int k)
    {
        static int tail = 1;
        Node *p = node + tail ++;
        p -> son[0] = p -> son[1] = p -> pre = node, p -> val = k;
        return p;
    }

    inline void Rotate(Node *a)
    {
        Node *p = a -> pre;
        bool g = a -> g();
        p -> pre -> SetChild(a, p -> g());
        p -> SetChild(a -> son[!g], g);
        a -> SetChild(p, !g);
        return ;
    }

    inline void Splay(Node *a, Node *target)
    {
        while(a -> pre != target)
        {
            if(a -> pre -> pre == target)
                Rotate(a);
            else
            {
                if(a -> g() == a -> pre -> g())
                    Rotate(a -> pre), Rotate(a);
                else
                    Rotate(a), Rotate(a);
            }
        }
        if(target == node)
            root = a;
        return ;
    }

    inline int Insert(int k)
    {
        int r = INF;
        Node *p = root, *t = node;
        while(p != node)
        {
            r = min(r, abs(k - p -> val));
            if(p -> val == k)
                return r;
            t = p, p = p -> son[k>p->val];
        }
        p = NewNode(k);
        t -> SetChild(p, k > t -> val);
        return r;
    }

    Node *BuildTree(int l, int r, int *a)
    {
        int mid = (l + r) >> 1;
        Node *p = NewNode(a[mid]);
        if(l < r)
        {
            p -> SetChild(BuildTree(l, mid - 1, a), 0);
            p -> SetChild(BuildTree(mid + 1, r, a), 1);
        }
        return p;
    }
} splay;

int n, m, a[N], a_[N], last[N];
int minG = INF, minS = INF;

int main(int argc, char **argv)
{
    freopen("in", "r", stdin);
    n = in(), m = in();
    for(int i = 1; i <= n; i ++)
        a[i] = in(), a_[i] = a[i], last[i] = a[i];
    sort(a_ + 1, a_ + n + 1);
    for(int i = 1; i < n ; i ++)
        minS = min(minS, abs(a_[i] - a_[i+1]));

    segRoot = segRoot -> NewNode();
    segRoot -> BuildTree(1, n, a, n);
    splay.root = splay.BuildTree(1, n, a_);

    while(m --)
    {
        char buf[15];
        scanf("%s", buf);
        if(buf[0] == 'I')
        {
            int p = in(), x = in();
            if(p < n)
                segRoot -> Modify(1, n, p, abs(a[p + 1] - x));
            minG = min(minG, abs(last[p] - x));
            minS = min(minS, splay.Insert(x));
            last[p] = x;
        }
        else if(buf[4] == 'G')
            printf("%d\n", min(minG, segRoot -> val));
        else
            printf("%d\n", minS);
    }
    return 0;
}
