#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e5 + 5;

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

inline char inChar()
{
    int c = '\0';
    while(!((c = getchar()) >= 'A' && c <= 'Z'));
    return c;
}

namespace SplayTree
{
    struct Node
    {
        Node *pre, *son[2];
        int val, size, num;

        inline bool g() {return pre -> son[1] == this;}
        inline void SetChild(Node *a, int c) {this -> son[c] = a, a -> pre = this;}
        inline void Update() {size = son[0] -> size + son[1] -> size + 1;}
    };

    Node node[N], *null = node;

    inline void Initialize()
    {
        null -> son[0] = null -> son[1] = null -> pre = node;
    }

    inline Node *NewNode(int num, int val)
    {
        static Node *T = node + 1;
        T -> son[0] = T -> son[1] = T -> pre = null;
        T -> size = 1, T -> num = num, T -> val = val;
        return T ++;
    }

    inline void Rotate(Node *a)
    {
        Node *p = a -> pre;
        bool g = a -> g();
        p -> pre -> SetChild(a, p -> g());
        p -> SetChild(a -> son[!g], g);
        a -> SetChild(p, !g);
        return (void) (p -> Update());
    }

    inline void Splay(Node *a, Node *target)
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
        return ;
    }

    inline void Insert(Node *&p, Node *a)
    {
        Node *next = p, *last = null;
        while(next != null)
        {
            last = next;
            if(a -> val < next -> val)
                next = next -> son[0];
            else
                next = next -> son[1];
        }
        if(a -> val < last -> val)
            last -> SetChild(a, 0);
        else
            last -> SetChild(a, 1);
        last -> Update();
        Splay(last, null);
        return (void) (p = last);
    }

    void Merge(Node *a, Node *&p)
    {
        if(a -> son[0] != null) Merge(a -> son[0], p);
        if(a -> son[1] != null) Merge(a -> son[1], p);
        return (void) (Insert(p, a));
    }
    
    int QueryTree(Node *a, int k)
    {
        if(k > a -> size)
            return -1;
        while(a != null)
        {
            if(k <= a -> son[0] -> size)
                a = a -> son[0];
            else if(k == a -> son[0] -> size + 1)
                return a -> num;
            else
                k -= a -> son[0] -> size + 1, a = a -> son[1];
        }
        return -1;
    }
};

namespace Operate
{
    using namespace SplayTree;

    Node *root[N];
    int pre[N], a[N];

    int Find(int x)
    {
        if(x != pre[x])
            pre[x] = Find(pre[x]);
        return pre[x];
    }

    inline void Unite(int x, int y)
    {
        int a = Find(x), b = Find(y);
        if(a == b) return ;
        if(root[a] -> size < root[b] -> size)
            pre[a] = b, Merge(root[a], root[b]);
        else
            pre[b] = a, Merge(root[b], root[a]);
        return ;
    }

    inline int Query(int x, int k)
    {
        return QueryTree(root[Find(x)], k);
    }

    inline void Interface()
    {
        int n = in(), m = in();
        for(int i = 1; i <= n; i ++)
            pre[i] = i, root[i] = NewNode(i, a[i] = in());
        for(int i = 0; i < m; i ++)
            Unite(in(), in());
        int q = in();
        while(q --)
        {
            char s = inChar();
            int a = in(), b = in();
            if(s == 'B')
                Unite(a, b);
            else
                printf("%d\n", Query(a, b));
        }
        return ;
    }
};

int main(int argc, char **argv)
{
    SplayTree::Initialize();
    Operate::Interface();
    return 0;
}
