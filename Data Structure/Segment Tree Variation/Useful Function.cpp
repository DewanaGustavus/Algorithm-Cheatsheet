#include <bits/stdc++.h>
using namespace std;

struct segtreelazy{
    // regular segtree template
    #pragma region
    int n;
    vector<int> segment;
    vector<int> lazy;
    int init = int(); // initialize array value
    int operation(int a, int b) {
        // segment tree operation
        return a + b;
    }
    segtreelazy(vector<int> array){
        n = log2(array.size()-1) + 1;
        n = (1<<n);
        segment = vector<int>(2*n, init);
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
        segment[idx] += lazy[idx];
        if(idx < n){ // not leaf
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
    
    int get(int idx){
        propagate(idx);
        return segment[idx];
    }

    #pragma endregion

    // useful function
    void propagate_all() {
        for(int i=1;i<2*n;i++) {
            propagate(i);
        }
    }

    int get_idx(int idx) {
        // top down iterative traversal on idx
        int treeidx = 1;
        int l = 0;
        int r = n-1;
        while(l != r) {
            propagate(treeidx);
            int mid = (l + r) / 2;
            treeidx *= 2;
            if(idx > mid) {
                l = mid + 1;
                treeidx++;
            }else {
                r = mid;
            }
        }
        return get(idx + n);
    }

    int getminidx() {
        // top down finding first index same as minimum global in minimum query
        int idx = 1;
        int minall = get(1);
        while(idx < n) {
            idx *= 2;
            int left = get(idx);
            if(left != minall) {
                // go to right
                idx++;
                propagate(idx);
            }
        }
        return idx - n;
    }
    int find_idx() {

    }
    
};
