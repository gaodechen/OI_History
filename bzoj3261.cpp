#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int N = 600006;
const   int M = 14000000;
const   int K = 24;

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
    Node *son[2];
};

Node *root[N];

inline Node *NewNode(int val, Node *a, Node *b)
{
    static Node pool[M], *tail = pool;
    tail -> val = val, tail -> son[0] = a, tail -> son[1] = b;
    return tail ++;
}

inline Node *Insert(Node *p, int x, int k)
{
    if(k == -1)
        return NewNode(p -> val + 1, root[0], root[0]);
    if((1 << k) & x)
        return NewNode(p -> val + 1, p -> son[0], Insert(p -> son[1], x, k - 1));
    return NewNode(p -> val + 1, Insert(p -> son[0], x, k - 1), p -> son[1]);
}

inline int Query(Node *a, Node *b, int x, int k)
{
    int r = 0;
    for(int i = K; i >= 0; i --)
    {
        bool q = (1 << i) & x;
        if(b -> son[!q] -> val > a -> son[!q] -> val)
        {
            a = a -> son[!q], b = b -> son[!q];
            r |= (1 << i);
        }
        else
            a = a -> son[q], b = b -> son[q];
    }
    return r;
}

int n, m, sum;

int main()
{
    n = in(), m = in();
    root[0] = NewNode(0, NULL, NULL);
    root[0] -> son[0] = root[0] -> son[1] = root[0];
    root[1] = Insert(root[0], 0, K);
    for(int i = 1; i <= n; i ++)
    {
        sum = sum ^ in();
        root[i + 1] = Insert(root[i], sum, K);
    }
    while(m --)
    {
        char buf[1];
        scanf("%s", buf);
        if(buf[0] == 'A')
        {
            sum ^= in(), n ++;
            root[n + 1] = Insert(root[n], sum, K);
        }
        else
        {
            int l = in() - 1, r = in(), x = in() ^ sum;
            int ans = Query(root[l], root[r], x, K);
            printf("%d\n", ans);
        }
    }
    return 0;
}
