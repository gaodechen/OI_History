#include    <cstdio>
#include    <cstring>
#include    <iostream>

using   namespace   std;
const   int L = 4e5 + 5;
const   int MOD = 20071027;

int k, C, d[L]; char s[L];

struct Trie
{
    struct Node {int val; Node *son[26];} node[L], *T;
    inline Node *NewNode() {return T ++;}

    inline void Init()
    {
        for(Node *p = node; p < T; p ++)
        {
            p -> val = 0;
            for(int i = 0; i < 26; i ++)
                p -> son[i] = NULL;
        }
        T = node + 1;
    }

    inline void Insert(char *buf, int n)
    {
        Node *p = node;
        for(int i = 0; i < n; i ++)
        {
            int c = buf[i] - 'a';
            if(p -> son[c] == NULL)
                p -> son[c] = NewNode();
            p = p -> son[c];
        }
        p -> val = 1;
        return ;
    }

    inline int Query()
    {
        int n = strlen(s);
        memset(d, 0, sizeof(d));
        d[n] = 1;
        for(int i = n - 1; i >= 0; i --)
        {
            Node *p = node;
            for(int j = i; j < n; j ++)
            {
                if(p -> son[s[j]-'a'])
                {
                    p = p -> son[s[j]-'a'];
                    if(p -> val)
                    {
                        d[i] += d[j+1];
                        if(d[i] >= MOD) d[i] %= MOD;
                    }
                }
                else
                    break ;
            }
        }
        return d[0];
    }
} trie;

int main(int argc, char **argv)
{
    while(scanf("%s%d", s, &k) == 2)
    {
        trie.Init();
        while(k --)
        {
            char buf[100];
            scanf("%s", buf);
            int n = strlen(buf);
            trie.Insert(buf, n);
        }
        k = trie.Query();
        printf("Case %d: %d\n", ++ C, k);
    }
    return 0;
}

