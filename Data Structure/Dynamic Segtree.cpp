#include <bits/stdc++.h>
using namespace std;

// template for sparse point update range sum query 1D and 2D
struct segtree{
    const static int init = 0;
    static int operation(int a, int b) {
        return a + b;
    }
    int l, r;
    int val = init;
    segtree *tl = nullptr, *tr = nullptr;
    segtree(int n){
        int tn = log2(n-1) + 1;
        tn = (1<<tn);
        l = 0;
        r = tn - 1;
    }
    segtree(int a, int b){
        l = a;
        r = b;
    }
    void make_child(){
        int mid = (l+r)/2;
        if(!tl)
            tl = new segtree(l, mid);
        if(!tr)
            tr = new segtree(mid+1, r);
    }
    void add(int idx, int v){
        if(l > idx || r < idx)return; // out bound
        if(l == idx && r == idx) {
            val = operation(val, v);
            return;
        }
        int mid = (l+r)/2;
        if(l <= idx && idx <= mid){
            if(!tl)tl = new segtree(l, mid);
            tl->add(idx, v);
        }else{
            if(!tr)tr = new segtree(mid+1, r);
            tr->add(idx, v);
        }
        val = operation(tl ? tl->val : init, tr ? tr->val : init);
    }
    int sum(int ql, int qr){
        if(ql > r || qr < l)return init;
        if(ql <= l && r <= qr)return val;
        int ans = operation(tl ? tl->sum(ql, qr) : init, 
                            tr ? tr->sum(ql, qr) : init);
        return ans;
    }
};

int bly, bry, blx, brx;
struct segtree2d{
    int yl, yr;
    int bl, br; // bound for y
    segtree *yseg = nullptr;
    segtree2d *tl = nullptr, *tr = nullptr;
    segtree2d(int a, int b){
        yl = a;
        yr = b;
        yseg = new segtree(blx, brx);
    }
    void make_child(){
        int mid = (yl + yr)/2;
        if(!tl)
            tl = new segtree2d(yl, mid);
        if(!tr)
            tr = new segtree2d(mid+1, yr);
    }
    void add(int x, int y, int v){
        if(yl > y || yr < y)return; // out bound
        yseg->add(x, v);
        if(yl == y && yr == y)return;
        int mid = (yl + yr)/2;
        if(yl <= y && y <= mid){
            if(!tl)tl = new segtree2d(yl, mid);
            tl->add(x, y, v);
        }else{
            if(!tr)tr = new segtree2d(mid+1, yr);
            tr->add(x, y, v);
        }
    }
    int sum(int x1, int y1, int x2, int y2){
        if(y1 > yr || y2 < yl)return 0;
        if(y1 <= yl && yr <= y2)return yseg->sum(x1, x2);
        int ans = segtree::operation(
            tl ? tl->sum(x1, y1, x2, y2) : segtree::init, 
            tr ? tr->sum(x1, y1, x2, y2) : segtree::init
        );
        return ans;
    }
};

segtree2d make_segtree2d(int n, int m){ // n = how much row(y), m = col(x)
    int tn = log2(n-1) + 1;
    tn = (1<<tn);
    bly = 0;
    bry = tn - 1;

    int tm = log2(m-1) + 1;
    tm = (1<<tm);
    blx = 0;
    brx = tm - 1;
    return segtree2d(0, bry);
}
