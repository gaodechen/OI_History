#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long data;
const int N = 110005;
const data K = 131;

char buf[N];
data pow[N];
int n, Q;

struct SplayTree
{
    struct Node
    {
        Node *son[2], *pre;
        char val;
        int size;
        data hash;

        inline bool g()
        {
            return pre -> son[1] == this;
        }

        inline void SetChild(Node *p, int c)
        {
            son[c] = p, p -> pre = this;
        }

        inline void Update()
        {
            int a = son[0] -> size, b = son[1] -> size;
            data A = son[0] -> hash, B = son[1] -> hash;
            size = a + b + 1, hash = A + val * pow[a] + B * pow[a + 1];
            return ;
        }
    };

    Node pool[N], *null, *root;

    SplayTree()
    {
        root = null = pool;
        null -> son[0] = null -> son[1] = null -> pre = null;
    }

    inline Node *NewNode(char val = 0)
    {
        static Node *T = pool + 1;
        T -> val = val, T -> hash = val, T -> size = 1;
        T -> pre = T -> son[0] = T -> son[1] = null;
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

    inline void Splay(Node *p, Node *target)
    {
        while(p -> pre != target)
        {
            if(p -> pre -> pre == target)
                Rotate(p);
            else
            {
                if(p -> pre -> g() == p -> g())
                    Rotate(p -> pre), Rotate(p);
                else
                    Rotate(p), Rotate(p);
            }
        }
        if(target == null) root = p;
        return (void) (p -> Update());
    }

    Node *Build(int l, int r)
    {
        if(l > r) return null;
        int mid = (l + r) >> 1;
        Node *a = NewNode(buf[mid]);
        a -> SetChild(Build(l, mid - 1), 0);
        a -> SetChild(Build(mid + 1, r), 1);
        a -> Update();
        return a;
    }

    // Find the Kth node on Splay
    // As we add a node[0], so k needn't - 1
    // In fact, it returns the k + 1 node

    inline Node *Find(int k)
    {
        Node *p = root;
        while(p -> son[0] -> size != k)
        {
            if(p -> son[0] -> size > k)
                p = p -> son[0];
            else
            {
                k -= p -> son[0] -> size + 1;
                p = p -> son[1];
            }
        }
        return p;
    }

    inline data Hash(int l, int r)
    {
        Node *a = Find(l - 1);
        Node *b = Find(r + 1);
        Splay(a, null), Splay(b, a);
        return b -> son[0] -> hash;
    }

    inline void Insert(int a, char c)
    {
        Splay(Find(a), null);
        if(root -> son[1] == null)
        {
            root -> son[1] = NewNode(c);
            root -> Update();
            return ;
        }
        Splay(Find(a + 1), root);
        root -> son[1] -> SetChild(NewNode(c), 0);
        root -> son[1] -> Update(), root -> Update();
        return ;
    }

    inline void Modify(int a, char c)
    {
        Splay(Find(a), null);
        root -> val = c, root -> Update();
        return ;
    }

    void DFS(Node *p)
    {
        if(p -> son[0] != null) DFS(p -> son[0]);
        cout << p -> val;
        if(p -> son[1] != null) DFS(p -> son[1]);
        return ;
    }
} splay;

inline int Query(int a, int b)
{
    int l = 0, r = min(n - a, n - b) + 1;
    while(l < r)
    {
        int mid = (l + r + 1) >> 1;
        if(splay.Hash(a, a + mid - 1) == splay.Hash(b, b + mid - 1))
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}

int main(int argc, char **argv)
{
    scanf("%s", buf + 1);
    n = strlen(buf + 1), pow[0] = 1;
    for(int i = 1; i < N; i ++)
        pow[i] = pow[i - 1] * K;
    buf[0] = buf[n + 1] = '$', buf[n + 2] = 0;
    splay.root = splay.Build(0, n + 1);

    scanf("%d", &Q);

    while(Q --)
    {
        char cmd[2];
        scanf("%s", cmd);
        if(cmd[0] == 'Q')
        {
            int x, y;
            scanf("%d%d", &x, &y);
            printf("%d\n", Query(x, y));
        }
        else if(cmd[0] == 'I')
        {
            int p;
            scanf("%d%s", &p, cmd);
            splay.Insert(p, cmd[0]);
            n ++;
        }
        else
        {
            int p;
            scanf("%d%s", &p, cmd);
            splay.Modify(p, cmd[0]);
        }
    }

    return 0;
}
