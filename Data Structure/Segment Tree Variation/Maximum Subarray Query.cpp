#include <bits/stdc++.h>
using namespace std;

struct val_type {
    int seg, pref, suff, sum;
    val_type(int val) {
        seg = max(0, val);
        pref = max(0, val);
        suff = max(0, val);
        sum = val;
    }
};

struct segtreelazy{
    // segment tree lazy top down traversal
    // 0-indexing, left child is 2*i, right child is 2*i+1, parent is floor(i/2)
    // template for sum range
    int n;
    vector<val_type> segment;
    vector<int> lazy;
    val_type init = val_type(0); // initialize array value
    val_type operation(val_type a, val_type b) {
        // segment tree operation
        val_type ret(0);
        ret.sum = a.sum + b.sum;
        ret.seg = max({a.seg, b.seg, a.suff + b.pref});
        ret.pref = max(a.pref, a.sum + b.pref);
        ret.suff = max(b.suff, a.suff + b.sum);
        return ret;
    }
    segtreelazy(vector<int> array){
        n = log2(array.size()-1) + 1;
        n = (1<<n);
        segment = vector<val_type>(2*n, init);
        lazy = vector<int>(2*n, 0);
        build(array);
    }

    void build(vector<int> array){
        for(int i=0;i<array.size();i++){
            segment[i+n] = array[i];
        }
        for(int i=n-1;i>=1;i--){
            segment[i] = operation(segment[2*i], segment[2*i+1]);
        }
    }
    
    void propagate(int idx){
        if(lazy[idx] == 0)return ;
        // TODO
        segment[idx] = operation(segment[idx], val_type(lazy[idx]));
        if(idx < n){ // not leaf
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
    
    val_type get(int idx){
        propagate(idx);
        return segment[idx];
    }
    
    void add(int l, int r, int val){add(l,r,val,1,0,n-1);}
    void add(int l, int r, int val, int idx, int sl, int sr){
        if(l > sr || r < sl)return; // out of range
        else if(l <= sl && sr <= r)lazy[idx] += val;
        else{
            propagate(idx);
            int mid = (sl+sr)/2;
            add(l,r,val,2*idx,sl,mid);
            add(l,r,val,2*idx+1,mid+1,sr);
            segment[idx] = operation(get(2*idx), get(2*idx+1));
        }
    }

    val_type range_query(int l, int r){return range_query(l,r,1,0,n-1);}
    val_type range_query(int l, int r, int idx, int sl, int sr){
        if(l > sr || r < sl)return init; // out of range
        if(l <= sl && sr <= r)return get(idx);
        propagate(idx);
        int mid = (sl+sr)/2;
        return operation(range_query(l,r,2*idx,sl,mid), range_query(l,r,2*idx+1,mid+1,sr));
    }
};
