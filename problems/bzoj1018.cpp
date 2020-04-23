#include    <cstdio>
#include    <cstring>
#include    <iostream>
#include    <algorithm>

using   namespace   std;
const   int N = 1e5 + 5;

inline int in() {
    int k = 0, c = '\0';
    for(; c > '9' || c < '0';) {
        c = getchar();
    }
    for(; c >= '0' && c <= '9';) {
        k = k * 10 + c - '0';
        c = getchar();
    }
    return k;
}

int x1, x2, y1, y2;

struct Item {
    bool a[2][2], b[2];

    bool* operator [] (int p) {
        return a[p];
    }
};

inline Item Merge(Item x, Item y, bool p, bool q) {
    Item r;
    r.b[0] = x.b[0] | (x[0][0] & x[1][1] & p & q & y.b[0]);
    r.b[1] = y.b[1] | (y[0][0] & y[1][1] & p & q & x.b[1]);
    r[0][0] = (x[0][0] & y[0][0] & p) | (x[0][1] & y[1][0] & q);
    r[0][1] = (x[0][0] & y[0][1] & p) | (x[0][1] & y[1][1] & q);
    r[1][0] = (x[1][0] & y[0][0] & p) | (x[1][1] & y[1][0] & q);
    r[1][1] = (x[1][0] & y[0][1] & p) | (x[1][1] & y[1][1] & q);
    return r;
}

struct SegmentTree {
    typedef SegmentTree Node;

    Item a;
    bool side[2];
    Node *lson, *rson;

    inline Node *NewNode() {
        static Node pool[N<<1], *tail = pool;
        return tail ++;
    }

    void BuildTree(int l, int r) {
        if(l == r) {
            a[0][0] = a[1][1] = 1;
        } else {
            int mid = (l + r) >> 1;
            (lson = NewNode()) -> BuildTree(l, mid);
            (rson = NewNode()) -> BuildTree(mid + 1, r);
        }
        return ;
    }

    void Modify(int l, int r, int p, bool x) {
        int mid = (l + r) >> 1;
        if(mid == p && x1 == x2) {
            side[x1 == 1] = x;
            a = Merge(lson -> a, rson -> a, side[0], side[1]);
            return ;
        }
        if(l == r) {
            a[0][1] = a[1][0] = a.b[0] = a.b[1] = x;
            return ;
        }
        if(p <= mid) {
            lson -> Modify(l, mid, p, x);
        } else {
            rson -> Modify(mid + 1, r, p, x);
        }
        a = Merge(lson -> a, rson -> a, side[0], side[1]);
        return ;
    }

    Item Query(int l, int r, int L, int R)
    {
        if(l >= L && r <= R)
            return a;
        int mid = (l + r) >> 1;
        if(R <= mid) {
            return lson -> Query(l, mid, L, R);
        } if(L > mid) {
            return rson -> Query(mid + 1, r, L, R);
        }
        Item x = lson -> Query(l, mid, L, mid);
        Item y = rson -> Query(mid + 1, r, mid + 1, R);
        return Merge(x, y, side[0], side[1]);
    }
} seg;

int main() {
    int c = in();
    char buf[5];
    seg.BuildTree(1, c);
    while(scanf("%s", buf) && buf[0] != 'E') {
        x1 = in() - 1, y1 = in(), x2 = in() - 1, y2 = in();
        if(y1 > y2) {
            swap(x1, x2), swap(y1, y2);
        }
        if(buf[0] == 'A') {
            Item M = seg.Query(1, c, y1, y2);
            Item L = seg.Query(1, c, 1, y1);
            Item R = seg.Query(1, c, y2, c);
            bool flag = M[x1][x2];
            if(!flag) for(int i = 0; i < 2; i ++) {
                for(int j = 0; j < 2; j ++) {
                    if(M[i][j] && (i == x1 | L.b[1]) & (j == x2 | R.b[0])) {
                        flag = true;
                        break ;
                    }
                }
            }
            puts(flag ? "Y" : "N");
        } else {
           seg.Modify(1, c, y1, buf[0] == 'O');
        }
    }
    return 0;
}
