#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <queue>

using   namespace   std;
const   int N = 10001;

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

struct Function
{
    int a, b, c;

    inline int axis() {return -b / (a + a);}
    inline int f(int x) {return a * x * x + b * x + c;}
} g[N];

int n, m;
priority_queue<int> largeHeap;
priority_queue<int, vector<int>, greater<int> > smallHeap;

int main()
{
    n = in(), m = in();
    for(int i = 1; i <= n; i ++)
        g[i] = (Function) {in(), in(), in()};
    for(int i = 1; i <= n; i ++)
    {
        int axis = g[i].axis(), p = max(1, axis);
        while(p)
        {
            int f = g[i].f(p ++);
            if((int) largeHeap.size() < m)
                largeHeap.push(f), smallHeap.push(f);
            else if(largeHeap.top() >= f)
                largeHeap.pop(), smallHeap.push(f);
            else break ;
        }
        p = max(1, axis);
        while(p > 1)
        {
            int f = g[i].f(-- p);
            if((int) largeHeap.size() < m)
                largeHeap.push(f), smallHeap.push(f);
            else if(largeHeap.top() >= f)
                largeHeap.pop(), smallHeap.push(f);
            else break ;
        }
    }
    while(m --)
    {
        printf("%d ", smallHeap.top());
        smallHeap.pop();
    }
    return 0;
}
