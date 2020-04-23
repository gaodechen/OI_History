#include    <cstdio>
#include    <iostream>

using   namespace   std;
const   int N = 1e5 + 5;

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

int n, m;

struct SplayTree
{
    struct Node
    {
        int key, rev, size;
        Node *son[2], *pre;

        inline bool g() {return pre -> son[1] == this;}
        inline void SetChild(Node *p, int c) {son[c] = p, p -> pre = this;}
        inline void Update() {size = son[0] -> size + son[1] -> size + 1;}

        inline void PushDown()
        {
            if(rev)
            {
                rev = 0, son[0] -> rev ^= 1, son[1] -> rev ^= 1;
                swap(son[0], son[1]);
            }
            return ;
        }
    } node[N], *root;

    SplayTree() {root = node -> son[0] = node -> son[1] = node -> pre = node;}

    inline Node *NewNode(int key)
    {
        static Node *T = node + 1;
        T -> son[0] = T -> son[1] = T -> pre = node;
        T -> key = key, T -> size = 1;
        return T ++;
    }

    inline void Rotate(Node *a)
    {
        Node *p = a -> pre;
        bool g = a -> g();
        p -> PushDown(), a -> PushDown();
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
        if(target == node)
            root = a;
        return ;
    }

    Node *BuildTree(int l, int r)
    {
        if(l > r)
            return node;
        if(l == r)
            return NewNode(l);
        int mid = (l + r) >> 1;
        Node *p = NewNode(mid);
        p -> SetChild(BuildTree(l, mid - 1), 0);
        p -> SetChild(BuildTree(mid + 1, r), 1);
        p -> Update();
        return p;
    }

    inline Node *Find(int k)
    {
        Node *p = root;
        p -> PushDown();
        while(p -> son[0] -> size != k)
        {
            if(p -> son[0] -> size > k)
                p = p -> son[0];
            else
            {
                k -= p -> son[0] -> size + 1;
                p = p -> son[1];
            }
            p -> PushDown();
        }
        return p;
    }

    void Reverse(int l, int r)
    {
        Node *a = Find(l - 1), *b = Find(r + 1);
        Splay(a, node), Splay(b, root);
        root -> son[1] -> son[0] -> rev ^= 1;
        return ;
    }

    void DFS(Node *a)
    {
        a -> PushDown();
        if(a -> son[0] != node)
            DFS(a -> son[0]);
        if(a -> key && a -> key != n + 1)
            printf("%d ", a -> key);
        if(a -> son[1] != node)
            DFS(a -> son[1]);
        return ;
    }
} tree;

int main()
{
    n = in(), m = in();
    tree.root = tree.BuildTree(0, n + 1);
    while(m --)
    {
        int l = in(), r = in();
        tree.Reverse(l, r);
    }
    tree.DFS(tree.root);
    return 0;
}
