#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 4e5 + 5;
const   int K = 29;

struct Node
{
    int val;
    Node *son[2];
} *root_[N], **root = root_ + 1;

inline Node *NewNode(int k, Node *a, Node *b)
{
    static Node pool[N*32], *tail = pool;
    tail -> val = k, tail -> son[0] = a, tail -> son[1] = b;
    return tail ++;
}

Node *Insert(Node *p, int x, int k)
{
    if(k == -1)
        return NewNode(p -> val + 1, p -> son[0], p -> son[1]);
    if((1 << k) & x)
        return NewNode(p -> val + 1, p -> son[0], Insert(p -> son[1], x, k - 1));
    return NewNode(p -> val + 1, Insert(p -> son[0], x, k - 1), p -> son[1]);
}

int Query(Node *a, Node *b, int x, int k)
{
    if(k == -1)
        return 0;
    bool q = (1 << k) & x;
    if(b -> son[!q] -> val > a -> son[!q] -> val)
        return (1 << k) | Query(a -> son[!q], b -> son[!q], x, k - 1);
    else
        return Query(a -> son[q], b -> son[q], x, k - 1);
}

int n, ans, suf, a[N];

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d", &a[i]);
        a[i] ^= a[i-1];
    }
    root[-1] = NewNode(0, NULL, NULL);
    root[-1] -> son[0] = root[-1] -> son[1] = root[-1];
    for(int i = 0; i <= n; i ++)
        root[i] = Insert(root[i-1], a[i], K);
    for(int i = n - 1; i >= 0; i --)
    {
        ans = max(ans, suf + Query(root[-1], root[i], a[i], K));
        suf = max(suf, Query(root[i], root[n], a[i], K));
    }
    printf("%d\n", ans);
    return 0;
}
