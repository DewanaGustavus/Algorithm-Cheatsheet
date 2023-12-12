#include <bits/stdc++.h>
using namespace std;
  
#define range(i,s,e)        for(int i=s;i<e;i++)
#define range2(i,s,e)       for(int i=s;i>=e;i--)
#define fors(var,arr)       for(auto &var:arr)
#define fastIO              ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define input2(a,b)         int a,b;cin>>a>>b;
#define inputvec(vec,am)    vector<int> vec(am);fors(num,vec)cin>>num;
#define print(var)          cout<<(var)<<endl;
#define int long long
#define vi vector<int>

struct segment {
    int seg, pref, suff, sum;
    segment(int val) {
        seg = max(0LL, val);
        pref = max(0LL, val);
        suff = max(0LL, val);
        sum = val;
    }
};

segment combine(segment s1, segment s2) {
    segment newseg(0);
    newseg.sum = s1.sum + s2.sum;
    newseg.seg = max({s1.seg, s2.seg, s1.suff + s2.pref});
    newseg.pref = max(s1.pref, s1.sum + s2.pref);
    newseg.suff = max(s2.suff, s1.suff + s2.sum);
    return newseg;
}

struct segtree {
    int n;
    vector<segment> segments;
    segtree(vi &arr){
        n = arr.size();
        n = log2(n-1) + 1;
        n = 1 << n;
        segments = vector<segment>(2 * n, 0);
        build(arr);
    }

    void build(vi &arr) {
        range(i,0,arr.size()) {
            segments[i + n] = segment(arr[i]);
        }
        range2(i,n-1,1) {
            segments[i] = combine(segments[2*i], segments[2*i+1]);
        }
    }

    void update(int idx, int val) {
        idx += n;
        segments[idx] = segment(val);
        idx /= 2;
        while(idx >= 1) {
            segments[idx] = combine(segments[2*idx], segments[2*idx+1]);
            idx /= 2;
        }
    }
};

int32_t main() {
    fastIO
    // https://cses.fi/problemset/task/1190/
    
    input2(n,q)
    inputvec(a, n)
    segtree st(a);
    range(i,0,q) {
        input2(k,x)
        st.update(k-1,x);
        print(st.segments[1].seg)
    }

    return 0;
}


