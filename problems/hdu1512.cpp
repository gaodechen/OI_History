#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int N = 100001;

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

struct Node
{
    int val;
    Node *lson, *rson, *pre;
} *node[N];

Node pool[N], *T;

inline Node *NewNode(int val)
{
    T -> val = val, T -> pre = T -> lson = T -> rson = NULL;
    return T ++;
}

Node *Merge(Node *a, Node *b)
{
    if(a == NULL && b == NULL) return NULL;
    if(a == NULL) return b;
    if(b == NULL) return a;
    if(a -> val < b -> val) swap(a, b);
    a -> rson = Merge(a -> rson, b);
    a -> rson -> pre = a;
    swap(a -> lson, a -> rson);
    return a;
}

inline Node *Modify(Node *p)
{
    Node *a = p -> lson, *b = p -> rson;
    if(a) a -> pre = NULL;
    if(b) b -> pre = NULL;
    p -> lson = p -> rson = NULL, p -> val >>= 1;
    return Merge(p, Merge(a, b));
}

inline Node *Find(Node *p)
{
    while(p -> pre != NULL)
        p = p -> pre;
    return p;
}

int main(int argc, char **argv)
{
    int n, Q;
    while(scanf("%d", &n) == 1)
    {
        T = pool;
        for(int i = 1; i <= n; i ++)
            node[i] = NewNode(in());
        Q = in();
        while(Q --)
        {
            int u = in(), v = in();
            Node *a = Find(node[u]), *b = Find(node[v]);
            if(a == b)
            {
                puts("-1");
                continue ;
            }
            a = Modify(a), b = Modify(b);
            printf("%d\n", Merge(a, b) -> val);
        }
    }
    return 0;
}
