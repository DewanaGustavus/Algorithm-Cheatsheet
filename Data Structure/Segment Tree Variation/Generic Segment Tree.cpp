#include <bits/stdc++.h>
using namespace std;

struct val_type {
    int minval;
    val_type(int val = INT_MIN) {
        minval = val;
    }
};

struct segtreelazy{
    // generic segtree lazy template
    int n;
    vector<val_type> segment;
    vector<int> lazy;
    val_type init = val_type(); // initialize array value
    val_type operation(val_type a, val_type b) {
        // segment tree operation
        val_type ret;
        ret.minval = min(a.minval, b.minval);
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
            segment[i+n] = val_type(array[i]);
        }
        for(int i=n-1;i>=1;i--){
            segment[i] = operation(segment[2*i], segment[2*i+1]);
        }
    }
    
    void propagate(int idx){
        if(lazy[idx] == 0)return ;
        int LOG = log2(idx);
        int mult = n / (1 << LOG); // add multiplier for sum query
        segment[idx].minval += lazy[idx];
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
