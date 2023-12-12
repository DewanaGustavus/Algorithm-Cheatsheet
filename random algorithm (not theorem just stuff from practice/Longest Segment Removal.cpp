#include <bits/stdc++.h>
using namespace std;
 
#define range(i,s,e)        for(int i=s;i<e;i++)
#define fors(var,arr)       for(auto &var:arr)
#define fastIO              ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define inputvec(vec,am)    vector<int> vec(am);fors(num,vec)cin>>num;
#define input(var)          int var;cin>>var;
#define print(var)          cout<<(var)<<endl;

#define segmentL tuple<int,int,int>
#define segmentI tuple<int,int,int>

int32_t main(){
    // https://codeforces.com/contest/899/problem/E
    fastIO
    
    input(n)
    inputvec(arr,n)
    set<segmentL> ds; // sort by len, {-len, idx, val}
    set<segmentI> ds2; // sort by idx, {idx, val, len}

    int cnt = 1;
    int last = arr[0];
    range(i,1,n){
        if(arr[i] == last){
            cnt++;
        }else{
            ds.insert({-cnt, i-cnt, last});
            ds2.insert({i-cnt, last, cnt});
            cnt = 1;
            last = arr[i];
        }
    }
    ds.insert({-cnt, n-cnt, last});
    ds2.insert({n-cnt, last, cnt});

    int ans = 0;
    while(!ds.empty()){
        ans++;
        segmentL best = *(ds.begin());
        int bidx, bval, blen;
        tie(blen, bidx, bval) = best;
        blen = -blen;
        segmentI besti = make_tuple(bidx, bval, blen);

        auto left = ds2.lower_bound(besti);
        auto right = ds2.lower_bound(besti);
        right++;
        if(left != ds2.begin() && right != ds2.end()){
            left--;
            int vl, vr;
            int idxa, idxb, lena, lenb;
            tie(idxa, vl, lena) = (*left);
            tie(idxb, vr, lenb) = (*right);

            if(vl == vr){
                int nidx = idxa;
                int nlen = lena + lenb;

                segmentL ttmp = {-lena, idxa, vl};
                segmentL ttmp2 = {-lenb, idxb, vl};
                segmentI tmp = (*left);
                segmentI tmp2 = (*right);

                ds.erase(ttmp);
                ds.erase(ttmp2);
                ds2.erase(tmp);
                ds2.erase(tmp2);

                segmentL newsl = make_tuple(-nlen, nidx, vl);
                segmentI newsi = make_tuple(nidx, vl, nlen);

                ds.insert(newsl);
                ds2.insert(newsi);
            }
        }

        ds.erase(best);
        ds2.erase(besti);
    }
    
    print(ans)
    
    return 0;
}
