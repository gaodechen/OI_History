#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <queue>

using   namespace   std;
const   int B = 51;
const   int K = 26;
const   int N = 10001;
const   int A = 1000001;

struct Node
{
    int val;
    Node *next[K], *fail;
};

Node *root, *poolTail, pool[N * K];

inline Node *NewNode()
{
    Node *p = poolTail ++;
    for(int i = 0; i < K; i ++)
        p -> next[i] = NULL;
    p -> val = 0, p -> fail = NULL;
    return p;
}

inline void Insert(char *s)
{
    Node *p = root;
    for(; *s; s ++)
    {
        int x = *s - 'a';
        if(p -> next[x] == NULL)
            p -> next[x] = NewNode();
        p = p -> next[x];
    }
    p -> val ++;
    return ;
}

inline void InitFail()
{
    queue<Node *> q;
    q.push(root);
    while(!q.empty())
    {
        Node *p = q.front(); q.pop();
        for(int i = 0; i < K; i ++)
        {
            if(p -> next[i] == NULL) continue ;
            p -> next[i] -> fail = root;
            Node *temp = p -> fail;
            while(temp)
            {
                if(temp -> next[i])
                {
                    p -> next[i] -> fail = temp -> next[i];
                    break ;
                }
                temp = temp -> fail;
            }
            q.push(p -> next[i]);
        }
    }
    return ;
}

inline int Match(char *text)
{
    Node *p = root;
    int i = 0, r = 0;
    while(text[i])
    {
        int x = text[i ++] - 'a';
        while(p -> next[x] == NULL && p != root)
            p = p -> fail;
        if(p -> next[x])
            p = p -> next[x];
        else
            continue ;
        Node *temp = p;
        while(temp != root && temp -> val != -1)
        {
            r += temp -> val;
            temp -> val = -1;
            temp = temp -> fail;
        }
    }
    return r;
}

int main(int argc, char **argv)
{
    int T, n;
    char text[A], pattern[B];
    scanf("%d", &T);
    while(T --)
    {
        poolTail = pool, root = NewNode();
        scanf("%d", &n), getchar();
        while(n --)
        {
            scanf("%s", pattern);
            Insert(pattern);
        }
        scanf("%s", text);
        InitFail();
        printf("%d\n", Match(text));
    }
    return 0;
}
