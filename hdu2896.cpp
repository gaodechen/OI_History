#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

struct Node
{
    int val;
    Node *fail, *next[94];
};

Node *root, *poolTail, pool[200 * 500];

inline Node *NewNode()
{
    Node *p = poolTail ++;
    p -> val = 0, p -> fail = NULL;
    for(int i = 0; i < 94; i ++)
        p -> next[i] = NULL;
    return p;
}

inline void Insert(char *s, int k)
{
    int l = strlen(s);
    Node *p = root;
    for(int i = 0; i < l; i ++)
    {
        int c = s[i] - 33;
        if(p -> next[c] == NULL)
            p -> next[c] = NewNode();
        p = p -> next[c];
    }
    p -> val = k;
    return ;
}

inline void InitFail()
{
    queue<Node *> q;
    q.push(root);
    while(!q.empty())
    {
        Node *p = q.front(); q.pop();
        for(int i = 0; i < 94; i ++)
        {
            if(p -> next[i] == NULL) continue ;
            p -> next[i] -> fail = root;
            Node *g = p -> fail;
            while(g != NULL)
            {
                if(g -> next[i])
                {
                    p -> next[i] -> fail = g -> next[i];
                    break ;
                }
                g = g -> fail;
            }
            q.push(p -> next[i]);
        }
    }
    return ;
}

bool used[501];

inline bool Match(char *buf, int n, int k)
{
    int l = strlen(buf), Count = 0;
    Node *p = root;
    memset(used, 0, sizeof(used));
    for(int i = 0; i < l; i ++)
    {
        int c = buf[i] - 33;
        while(p -> next[c] == NULL && p != root)
            p = p -> fail;
        if(p -> next[c])
            p = p -> next[c];
        else
            continue ;
        Node *g = p;
        while(g != root)
        {
            if(g -> val)
            {
                used[g -> val] = 1;
                if(++ Count == 3) break ;
            }
            g = g -> fail;
        }
        if(Count == 3) break ;
    }
    if(!Count) return false;
    printf("web %d:", k);
    for(int i = 1; i <= n; i ++)
        if(used[i])
            printf(" %d", i);
    puts("");
    return true;
}

char buf[10001];

int main(int argc, char **argv)
{
    int n, m;
    while(scanf("%d", &n) == 1)
    {
        poolTail = pool, root = NewNode();
        for(int i = 1; i <= n; i ++)
        {
            scanf("%s", buf);
            Insert(buf, i);
        }
        InitFail();
        int ans = 0;
        scanf("%d", &m);
        for(int i = 1; i <= m; i ++)
        {
            scanf("%s", buf);
            if(Match(buf, n, i))
                ans ++;
        }
        printf("total: %d\n", ans);
    }
    return 0;
}
