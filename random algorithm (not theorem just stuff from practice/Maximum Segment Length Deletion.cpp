#include <bits/stdc++.h>
using namespace std;

#define range(i,s,e)        for(int i=s;i<e;i++)
#define fors(var,arr)       for(auto &var:arr)
#define fastIO              ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define inputarr(arr,am)    int arr[am];fors(num,arr)cin>>num;
#define input2(a,b)         int a,b;cin>>a>>b;
#define prints(var)         cout<<(var)<<" ";


int32_t main(){
    // from https://cses.fi/problemset/task/1163
    fastIO

    input2(k,n)
    inputarr(arr,n)
    
    set<pair<int,int>> segment; // reversed for lowerbound
    set<int, greater<int>> maximum;
    map<int,int> cnt;
    segment.insert({k,0});
    maximum.insert(0);
    maximum.insert(k);
    cnt[0]++;
    cnt[k]++;
    range(i,0,n){
        int x = arr[i];
        auto tmp = segment.lower_bound({x,0});
        pair<int,int> delseg = *tmp;
        swap(delseg.first, delseg.second);
        segment.erase(tmp);
        int len = delseg.second - delseg.first;
        if(--cnt[len] == 0){
            maximum.erase(len);  
        }
        
        pair<int,int> left = {delseg.first, x};
        pair<int,int> right = {x, delseg.second};

        if(left.first <= left.second){
            len = left.second - left.first;
            swap(left.first, left.second);
            segment.insert(left);
            cnt[len]++;
            maximum.insert(len);
        }
        if(right.first <= right.second){
            len = right.second - right.first;
            swap(right.first, right.second);
            segment.insert(right);
            cnt[len]++;
            maximum.insert(len);
        }
        prints(*maximum.begin())

    }


    return 0;
}