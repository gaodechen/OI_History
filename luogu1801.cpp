#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 2e5 + 5;

struct Node
{
    int val, size;
    Node *son[2];
} *root;

inline Node *NewNode(int x)
{
    static Node pool[N], *T = pool;
    T -> val = x, T -> size = 1;
    return T ++;
}

inline void Insert(Node *p, int x)
{
    p -> size ++;
    if(p -> val == x)
        return ;
    bool g = x > p -> val;
    if(p -> son[g] == NULL)
        p -> son[g] = NewNode(x);
    else
        Insert(p -> son[g], x);
    return ;
}

inline int Query(Node *p, int k)
{
    if(k == 1) return p -> val;
    if(!p -> son[0]) return Query(p -> son[1], k - 1);
    int size = p -> son[0] -> size;
    if(size >= k) return Query(p -> son[0], k);
    if(size == k - 1) return p -> val;
    return Query(p -> son[1], k - size - 1);
}

int n, a[N], q[N];

int main(int argc, char **argv)
{
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &a[i]);
    for(int i = 1; i <= m; i ++)
        scanf("%d", &q[i]);
    root = NewNode(a[1]);
    int cur = 1;
    if(q[1] == 1)
    {
        printf("%d\n", a[1]);
        cur ++;
    }
    for(int i = 2; i <= n; i ++)
    {
        Insert(root, a[i]);
        while(i <= n && q[cur] == i)
        {
            printf("%d\n", Query(root, cur));
            cur ++;
        }
    }
    return 0;
}
