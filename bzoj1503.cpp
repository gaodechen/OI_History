#include	<cstdio>
#include	<cstring>
#include	<iostream>
#include	<algorithm>

using	namespace	std;
const	int N = 1e5 + 5;

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

struct SplayTree
{
    struct Node
    {
        int key, size;
        Node *son[2], *pre;

        inline bool g()
        {
            return pre -> son[1] == this;
        }

        inline void SetChild(Node *p, bool c)
        {
            son[c] = p, p -> pre = this;
        }

        inline void PushUp()
        {
            size = son[0] -> size + son[1] -> size + 1;
        }
    };

    int tail;
    Node node[N], *root;

    SplayTree()
    {
        root = node -> son[0] = node -> son[1] = node -> pre = node;
    }

    inline Node *NewNode(int key)
    {
        Node *p = &node[++tail];
        p -> size = 1, p -> key = key;
        p -> son[0] = p -> son[1] = p -> pre = node;
        return p;
    }

    inline void Rotate(Node *a)
    {
        Node *p = a -> pre;
        bool g = a -> g();
        p -> pre -> SetChild(a, p -> g());
        p -> SetChild(a -> son[!g], g);
        a -> SetChild(p, !g);
        p -> PushUp();
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
        a -> PushUp();
        if(target == node)
            root = a;
        return ;
    }

    inline void Insert(int key)
    {
        if(root == node)
        {
            root = NewNode(key);
            return ;
        }
        Node *p = root, *a = NewNode(key);
        while(p -> son[key>p->key] != node)
            p = p -> son[key>p->key];
        p -> SetChild(a, key > p -> key);
        p -> PushUp();
        return (void) (Splay(a, node));
    }

    Node *Query(int k, Node *p)
    {
        if(p == node)
            return node;
        int s = p -> son[0] -> size + 1;
        if(s == k)
            return p;
        if(k > s)
            return Query(k - s, p -> son[1]);
        return Query(k, p -> son[0]);
    }
};

int main()
{
    SplayTree tree;
    int q, m, c, ans = 0, d = 0;
    q = in(), m = in();
    while(q --)
    {
        char buf[1];
        scanf("%s%d", buf, &c);
        // val' = val + sum[now] - sum[pos-1]
        // Let sum[now] = d, and we insert val - sum[pos-1] each time
        // Here, sum[now] *= -1...
        if(buf[0] == 'I')
        {
            if(c >= m)
                tree.Insert(c + d);
        }
        else if(buf[0] == 'F')
        {
            if(c > tree.root -> size)
                printf("-1\n");
            else
                printf("%d\n", tree.Query(tree.root -> size - c + 1, tree.root) -> key - d);
        }
        else if(buf[0] == 'S')
        {
            d += c;
            tree.Insert(m + d);
            ans += tree.root -> son[0] -> size;
            tree.root = tree.root -> son[1];
            tree.root -> pre = tree.node;
        }
        else if(buf[0] == 'A')
            d -= c;
    }
    printf("%d\n", ans);
    return 0;
}
