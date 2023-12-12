#include <bits/stdc++.h>
using namespace std;
 
#define range(i,s,e)        for(int i=s;i<e;i++)
#define fors(var,arr)       for(auto &var:arr)
#define fastIO              ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define inputarr(arr,am)    int arr[am];fors(num,arr)cin>>num;
#define input(var)          int var;cin>>var;
#define print(var)          cout<<(var)<<endl;

int32_t main(){
    // from https://codeforces.com/contest/722/problem/C
    fastIO

    input(n)
    inputarr(arr,n)
    int pref[n+1]={};
    range(i,0,n)pref[i+1] = pref[i]+arr[i];

    set<pair<int,int>> segment; // reversed for lowerbound
    set<int, greater<int>> maximum;
    map<int,int> cnt;
    segment.insert({n,1});
    maximum.insert(0);
    maximum.insert(pref[n]);
    cnt[0]++;
    cnt[pref[n]]++;
    range(i,0,n){
        input(x)
        auto tmp = segment.lower_bound({x,0});
        pair<int,int> delseg = *tmp;
        swap(delseg.first, delseg.second);
        segment.erase(tmp);
        int sum = pref[delseg.second] - pref[delseg.first-1];
        if(--cnt[sum] == 0){
            maximum.erase(sum);  
        }
        
        pair<int,int> left = {delseg.first, x-1};
        pair<int,int> right = {x+1, delseg.second};

        if(left.first <= left.second){
            sum = pref[left.second] - pref[left.first-1];
            swap(left.first, left.second);
            segment.insert(left);
            cnt[sum]++;
            maximum.insert(sum);
        }
        if(right.first <= right.second){
            sum = pref[right.second] - pref[right.first-1];
            swap(right.first, right.second);
            segment.insert(right);
            cnt[sum]++;
            maximum.insert(sum);
        }
        print(*maximum.begin())
    }


    return 0;
}