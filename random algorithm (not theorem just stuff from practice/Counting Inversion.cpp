#include <bits/stdc++.h>
using namespace std;

#define range(i,s,e)        for(int i=s;i<e;i++)


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


struct IndexCompression{
    vector<int> idxcomp;
    int n;
    IndexCompression(vector<int>& value){
        n = value.size();
        idxcomp = vector<int>(n);
        for(int i=0;i<n;i++)
            idxcomp[i] = value[i];
        sort(idxcomp.begin(), idxcomp.end());
        idxcomp.erase(unique(idxcomp.begin(), idxcomp.end()), idxcomp.end());
        n = idxcomp.size();
    }

    int idx(int x){
        int index = lower_bound(idxcomp.begin(), idxcomp.end(), x) - idxcomp.begin();
        if(index == n || idxcomp[index] != x)return -1;
        return index;
    }
};

int countInversion(vector<int> &a) {
    int n = a.size();
    IndexCompression ic(a);
    vector<int> dummy(n);
    range(i,0,n) {
        dummy[ic.idx(a[i])]++;
    }
    segtree st(dummy);

    int inversion = 0;
    range(i,0,n) {
        st.add(ic.idx(a[i]), -1);
        inversion += st.sum(0, ic.idx(a[i]) - 1);
    }
    return inversion;
}


int main() {
    int n; cin >> n;
    vector<int> a(n);
    range(i,0,n) cin >> a[i];

    int ans = countInversion(a);
    cout << ans << endl;
}