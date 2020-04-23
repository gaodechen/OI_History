#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 8e4 + 5;
const   int INF = 0x3f3f3f3f;

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
        int val;
        Node *son[2], *pre;

        inline bool g() {return pre -> son[1] == this;}
        inline void SetChild(Node *p, int c) {son[c] = p, p -> pre = this;}
    } node[N], *root;

    SplayTree() {root = node -> son[0] = node -> son[1] = node -> pre = node;}

    inline Node *NewNode(int k)
    {
        static Node *T = node + 1;
        T -> son[0] = T -> son[1] = T -> pre = node;
        T -> val = k;
        return T ++;
    }

    inline bool Empty() {return root == node;}

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

    inline void Insert(int k)
    {
        if(root == node)
        {
            root = NewNode(k);
            return ;
        }
        Node *p = root, *a = NewNode(k);
        while(p -> son[k > p -> val] != node)
            p = p -> son[k > p -> val];
        p -> SetChild(a, k > p -> val);
        return (void) (Splay(a, node));
    }

    inline void Delete(Node *p)
    {
        if(p != root)
            Splay(p, node);
        if(p -> son[0] == node && p -> son[1] == node)
            root = node;
        else if(p -> son[0] == node)
            root = p -> son[1], root -> pre = node;
        else if(p -> son[1] == node)
            root = p -> son[0], root -> pre = node;
        else
        {
            Node *prev = p -> son[0], *next = p -> son[1];
            while(prev -> son[1] != node)
                prev = prev -> son[1];
            Splay(prev, root);
            prev -> pre = node;
            prev -> SetChild(next, 1);
            root = prev;
        }
        return ;
    }

    inline Node *FindPrev()
    {
        Node *p = root -> son[0];
        if(p != node) while(p -> son[1] != node)
            p = p -> son[1];
        return p;
    }

    inline Node *FindNext()
    {
        Node *p = root -> son[1];
        if(p != node) while(p -> son[0] != node)
            p = p -> son[0];
        return p;
    }

    inline int Interface()
    {
        Node *L = FindPrev(), *R = FindNext();
        int x = root -> val, l = L -> val, r = R -> val;
        if((x - l <= r - x && L != node) || (L != node && R == node))
        {
            Delete(root), Delete(L);
            return x - l;
        }
        Delete(root), Delete(R);
        return r - x;
        return 0;
    }
} splay;

int main()
{
    int n = in(), type = -1, sum = 0;
    for(int i = 0; i < n; i ++)
    {
        int k = in(), x = in();
        splay.Insert(x);
        if(type == -1)
            type = k;
        else if(type ^ k)
        {
            sum += splay.Interface();
            if(sum >= 1000000)
                sum %= 1000000;
        }
        if(splay.Empty())
            type = -1;
    }
    printf("%d\n", sum);
    return 0;
}
