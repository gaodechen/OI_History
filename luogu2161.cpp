#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <set>

using   namespace   std;
typedef pair<int, int> Item;
const   int INF = 0x3f3f3f3f;

#define     l(a)        a.first
#define     r(a)        a.second

bool f(Item a, Item b)
{
    return !(r(a) < l(b) || l(a) > r(b));
}

int main(int argc, char **argv)
{
    int n;
    scanf("%d", &n);
    set<Item> S;
    S.insert(Item(-INF, -INF));
    S.insert(Item(INF, INF));
    for(int i = 1; i <= n; i ++)
    {
        char s[1]; int a, b, cnt = 0;
        scanf("%s%d%d", s, &a, &b);
        Item tmp = Item(a, b);
        set<Item>::iterator p;
        if(s[0] == 'A')
        {
            while(true)
            {
                p = S.lower_bound(tmp);
                if(f(*p, tmp)) {
                    cnt ++, S.erase(p);
                    continue ;
                } else if(p != S.begin()) {
                    if(f(*-- p, tmp)) {
                        cnt ++, S.erase(p);
                        continue ;
                    }
                }
                break ;
            }
            S.insert(tmp);
            printf("%d\n", cnt);
        }
        else
            printf("%d\n", S.size() - 2);
    }
    return 0;
}
