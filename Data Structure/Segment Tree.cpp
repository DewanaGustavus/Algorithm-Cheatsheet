#include <bits/stdc++.h>
using namespace std;

struct segtree{
    // segment tree bottom up traversal
    // 0-indexing, left child is 2*i, right child is 2*i+1, parent is floor(i/2)
    // template for sum range
    int n;
    vector<int> segment;
    int init = 0; // initialize array value
    int operation(int a, int b){return a+b;} // segment tree operation
    segtree(vector<int> array){
        n = log2(array.size()-1) + 1;
        n = (1<<n);
        segment = vector<int>(2*n, init);
        for(int i=0;i<array.size();i++){
            add(i, array[i]);
        }
    }
    void add(int idx, int val){
        idx += n;
        segment[idx] += val;
        for(idx/=2;idx>=1;idx/=2){
            segment[idx] = operation(segment[2*idx], segment[2*idx + 1]); 
        }
    }
    int sum(int l, int r) {
        l += n;
        r += n;
        int ans = init;
        while (l <= r) {
            if (l%2 == 1) ans = operation(ans, segment[l++]);
            if (r%2 == 0) ans = operation(ans, segment[r--]);
            l /= 2; r /= 2;
        }
        return ans;
    }
};

struct segtreelazy{
    // segment tree lazy top down traversal
    // 0-indexing, left child is 2*i, right child is 2*i+1, parent is floor(i/2)
    // template for sum range
    int n;
    vector<int> segment;
    vector<int> lazy;
    int init = 0; // initialize array value
    int operation(int a, int b){return a+b;} // segment tree operation
    segtreelazy(vector<int> array){
        n = log2(array.size()-1) + 1;
        n = (1<<n);
        segment = vector<int>(2*n, init);
        lazy = vector<int>(2*n, init);
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
        int LOG = log2(idx);
        int mult = n / (1 << LOG); // add multiplier for sum query
        segment[idx] += mult * lazy[idx];
        if(idx < n){ // not leaf
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = init;
    }
    
    int get(int idx){
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

    int sum(int l, int r){return sum(l,r,1,0,n-1);}
    int sum(int l, int r, int idx, int sl, int sr){
        if(l > sr || r < sl)return init; // out of range
        if(l <= sl && sr <= r)return get(idx);
        propagate(idx);
        int mid = (sl+sr)/2;
        return operation(sum(l,r,2*idx,sl,mid), sum(l,r,2*idx+1,mid+1,sr));
    }
};


struct segtree2d{
    int n, m;
    vector<vector<int>> segment;
    int init = 0;
    int operation(int a, int b){return a + b;}

    segtree2d(vector<vector<int>> mat){
        n = log2(mat.size() - 1) + 1;
        n = (1 << n);
        m = log2(mat[0].size() - 1) + 1;
        m = (1 << m);
 
        segment = vector<vector<int>>(2*n, vector<int>(2*m));
        for(int i=0;i<mat.size();i++){
            for(int j=0;j<mat[i].size();j++){
                add(i,j,mat[i][j]);
            }
        }
    }
    void add1d(int idxy, int x, int val, int idx, int sl, int sr){
        if(sl > x || sr < x)return;
        segment[idxy][idx] = operation(segment[idxy][idx], val);
        if(sl == x && sr == x)return;
        int mid = (sl + sr)/2;
        if(sl <= x && x <= mid)add1d(idxy, x, val, 2*idx, sl, mid);
        else add1d(idxy, x, val, 2*idx+1, mid+1, sr);
    }
    void add(int x, int y, int val){add2d(x, y, val, 1, 0, n-1);}
    void add2d(int x, int y, int val, int idx, int sl, int sr){
        if(sl > y || sr < y)return;
        add1d(idx, x, val, 1, 0, m-1);
        if(sl == y && sr == y)return;
        int mid = (sl + sr)/2;
        if(sl <= y && y <= mid)add2d(x, y, val, 2*idx, sl, mid);
        else add2d(x, y, val, 2*idx+1, mid+1, sr);
    }
    int sum1d(int idxy, int x1, int x2, int idx, int sl, int sr){
        if(x1 > sr || x2 < sl)return init;
        if(x1 <= sl && sr <= x2)return segment[idxy][idx];
        int mid = (sl + sr)/2;
        return operation(sum1d(idxy, x1, x2, 2*idx, sl, mid), sum1d(idxy, x1, x2, 2*idx+1, mid+1, sr));
    }
    int sum(int x1, int y1, int x2, int y2){return sum2d(x1, y1, x2, y2, 1, 0, n-1);}
    int sum2d(int x1, int y1, int x2, int y2, int idx, int sl, int sr){
        if(y1 > sr || y2 < sl)return init;
        if(y1 <= sl && sr <= y2)return sum1d(idx, x1, x2, 1, 0, m-1);
        int mid = (sl + sr)/2;
        return operation(sum2d(x1, y1, x2, y2, 2*idx, sl, mid), sum2d(x1, y1, x2, y2, 2*idx+1, mid+1, sr));
    }
};
