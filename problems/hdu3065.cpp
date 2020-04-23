#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <queue>

using   namespace   std;
const   int N = 1001, K = 26;

struct Node
{
    int id;
    Node *next[K], *fail;
};

Node *root, *poolTail, pool[N*50];

inline Node *NewNode()
{
    Node *p = poolTail ++;
    for(int i = 0; i < K; i ++)
        p -> next[i] = NULL;
    p -> fail = NULL, p -> id = 0;
    return p;
}

inline void Insert(char *s, int id)
{
    Node *p = root;
    for(; *s; s ++)
    {
        int x = *s - 'A';
        if(p -> next[x] == NULL)
            p -> next[x] = NewNode();
        p = p -> next[x];
    }
    p -> id = id;
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

int ans[N];

inline void Match(char *text)
{
    memset(ans, 0, sizeof(ans));
    Node *p = root;
    for(; *text != '\0'; text ++)
    {
        if(*text >= 'A' && *text <= 'Z')
        {
            int x = *text - 'A';
            while(p -> next[x] == NULL && p != root)
                p = p -> fail;
            p = p -> next[x];
            if(p == NULL) p = root;
            Node *temp = p;
            while(temp != root)
            {
                ans[temp -> id] ++;
                temp = temp -> fail;
            }
        }
        else
            p = root;
    }
    return ;
}

char pattern[N][51], text[2000001];

int main(int argc, char **argv)
{
    int n;
    while(scanf("%d%*c", &n) == 1)
    {
        poolTail = pool, root = NewNode();
        for(int i = 1; i <= n; i ++)
        {
            // scanf("%s", pattern[i]);
            gets(pattern[i]);
            Insert(pattern[i], i);
        }
        InitFail();
        gets(text);
        // scanf("%s", text);
        Match(text);
        for(int i = 1; i <= n; i ++) if(ans[i])
            printf("%s: %d\n", pattern[i], ans[i]);
    }
    return 0;
}

