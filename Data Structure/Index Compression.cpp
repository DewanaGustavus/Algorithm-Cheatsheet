#include <bits/stdc++.h>
using namespace std;

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
