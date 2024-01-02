#include <bits/stdc++.h>
using namespace std;

struct val_type {
    vector<int> range_vector;
    val_type(int val = 0) {
        range_vector = vector<int>(1, val);
    }
};

struct segtreelazy{
    // Merge Sort Tree
    int n;
    vector<val_type> segment;
    vector<int> lazy;
    val_type init = val_type(); // initialize array value
    val_type operation(val_type a, val_type b) {
        // segment tree operation
        val_type ret;
        ret.range_vector = vector<int>(a.range_vector.size() + b.range_vector.size());
        int i = 0;
        int j = 0;
        int k = 0;
        while(i < a.range_vector.size() && j < b.range_vector.size()) {
            if(a.range_vector[i] <= b.range_vector[j]) {
                ret.range_vector[k++] = a.range_vector[i++];
            }else {
                ret.range_vector[k++] = b.range_vector[j++];
            }
        }

        while(i < a.range_vector.size()) {
            ret.range_vector[k++] = a.range_vector[i++];
        }

        while(j < b.range_vector.size()) {
            ret.range_vector[k++] = b.range_vector[j++];
        }
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

    int count_range(int l, int r, int ql, int qr){return count_range(l,r,ql,qr,1,0,n-1);}
    int count_range(int l, int r, int ql, int qr, int idx, int sl, int sr){
        if(l > sr || r < sl)return 0; // out of range
        if(l <= sl && sr <= r) {
            auto itl = lower_bound(segment[idx].range_vector.begin(), segment[idx].range_vector.end(), ql);
            auto itr = upper_bound(segment[idx].range_vector.begin(), segment[idx].range_vector.end(), qr);
            return distance(itl, itr);
        }
        int mid = (sl+sr)/2;
        return count_range(l,r,ql,qr,2*idx,sl,mid) + count_range(l,r,ql,qr,2*idx+1,mid+1,sr);
    }
};
