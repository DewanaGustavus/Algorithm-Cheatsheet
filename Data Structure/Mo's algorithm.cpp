#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5+1;
const int sqrtn = sqrt(maxn) + 1;
int s[maxn] = {};
int cnt = 0;

struct querytype{
    int l, r, idx;
    bool operator < (querytype x)const{
        pair<int,int> p1 = {l/sqrtn, r};
        pair<int,int> p2 = {x.l/sqrtn, x.r};
        return p1 < p2;
    }
};

void insert(int num){
    if(s[num]++ == 0)cnt++;
}

void del(int num){
    if(s[num]-- == 1)cnt--;
}

int main(){
    int n,q;
    cin>>n>>q;
    vector<querytype> querys;
    int arr[n];
    for(int& num : arr)cin>>num;
    
    for(int i=0;i<q;i++){
        int l,r;
        cin>>l>>r;
        l--;r--;
        querytype qi = {l,r,i};
        querys.push_back(qi);
    }

    sort(querys.begin(), querys.end());
    
    int idx = 1;
    map<int,int> indexcomp;
    for(int& num : arr){
        if(indexcomp[num] == 0)indexcomp[num] = idx++;
        num = indexcomp[num];
    }
    int ans[q];
    int l=0,r=-1;
    for(auto quer : querys){
        while(l > quer.l)insert(arr[--l]);
        while(r < quer.r)insert(arr[++r]);
        while(l < quer.l)del(arr[l++]);
        while(r > quer.r)del(arr[r--]);
        ans[quer.idx] = cnt;
    }
    
    for(int i=0;i<q;i++){
        cout << ans[i] << endl;
    }


    return 0;
}