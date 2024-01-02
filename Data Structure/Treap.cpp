#include <bits/stdc++.h>
using namespace std;

// treap struct define
// implicit index, 0-indexing
// maxidx(left) < idx < minidx(right)
typedef struct node* treap;
struct node {
    int value, priority, cnt, sum;
    bool reversed;
    treap l, r;
    node(int val) {
        value = val;
        priority = rand();
        cnt = 1;
        sum = val;
        reversed = false;
    }
};

// treap basic function
int get_cnt(treap t) {
    return t ? t->cnt : 0;
}

void update_val(treap t) {
    if(!t) return ;
    t->cnt = 1;
    t->sum = t->value;
    if(t->l) { 
        t->cnt += t->l->cnt;
        t->sum += t->l->sum;
    }
    if(t->r) {
        t->cnt += t->r->cnt;
        t->sum += t->r->sum;
    }
}

void propagate(treap t) {
    if(t && t->reversed) {
        t->reversed = false;
        swap(t->l, t->r);
        if(t->l) t->l->reversed ^= true;
        if(t->r) t->r->reversed ^= true;
    }
}

// MAGIC function
// don't try to understand, you can't
// just assume this magic works perfectly fine
void merge(treap &t, treap l, treap r) {
    propagate(l);
    propagate(r);
    if(!l || !r)
        t = l ? l : r;
    else if(l->priority > r->priority)
        merge(l->r, l->r, r),  t = l;
    else
        merge(r->l, l, r->l),  t = r;
    update_val(t);
}

void split(treap t, treap &l, treap &r, int idx, int prev_idx = 0) {
    if(!t)
        return void( l = r = 0 );
    propagate(t);
    int curr_idx = prev_idx + get_cnt(t->l);
    if(idx <= curr_idx)
        split(t->l, l, t->l, idx, prev_idx),  r = t;
    else
        split(t->r, t->r, r, idx, curr_idx + 1),  l = t;
    update_val(t);
}

void heapify(treap t) {
    if(!t) return;
    treap maxpriority = t;
    if(t->l && t->l->priority > maxpriority->priority)
        maxpriority = t->l;
    if(t->r && t->r->priority > maxpriority->priority)
        maxpriority = t->r;
    if(maxpriority != t) {
        swap(t->priority, maxpriority->priority);
        heapify(maxpriority);
    }
}

treap build(vector<int> &array, int l=-1, int r=-1) {
    if(l == -1) {
        l = 0;
        r = (int)array.size() - 1;
    }
    if(r < l) return NULL;
    int mid = (l + r) / 2;
    treap t = new node(array[mid]);
    t->l = build(array, l, mid - 1);
    t->r = build(array, mid + 1, r);
    heapify(t);
    update_val(t);
    return t;
}

// treap operation
// ! not tested well
void get_range(treap t, int l, int r, treap &tl, treap &tm, treap &tr) {
    int length = r - l + 1;
    split(t, tl, tm, l);
    split(tm, tm, tr, length);
}

void change(treap &t, int idx, int val) {
    treap tl, tm, tr;
    get_range(t, idx, idx, tl, tm, tr);
    tm->value = val;
    merge(t, tl, tm);
    merge(t, t, tr);
}

void insert(treap &t, int idx, int val) {
    treap tl, tr;
    split(t, tl, tr, idx);
    treap tm = new node(val);
    merge(t, tl, tm);
    merge(t, t, tr);
}

void remove(treap &t, int idx) {
    treap tl, tm, tr;
    get_range(t, idx, idx, tl, tm, tr);
    treap tmp = tm;
    merge(t, tl, tr);
    delete tmp;
}

void reverse(treap t, int l, int r) {
    treap tl, tm, tr;
    get_range(t, l, r, tl, tm, tr);
    tm->reversed ^= true;
    merge(t, tl, tm);
    merge(t, t, tr);
}

int range_sum(treap t, int l, int r) {
    treap tl, tm, tr;
    get_range(t, l, r, tl, tm, tr);
    int sum = tm->sum;
    merge(t, tl, tm);
    merge(t, t, tr);
    return sum;
}

void print_treap(treap t) {
    if(!t) return;
    propagate(t);
    print_treap(t->l);
    cout << t->value << " ";
    print_treap(t->r);
}

