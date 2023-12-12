#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/count-of-subarrays-having-exactly-k-distinct-elements/
int atMostK(vector<int>& arr, int k){
    // TIme Complexity : O(n) with two pointer
    int n = arr.size();
    map<int,int> mp;
    int cnt = 0;
    int l = 0;
    for(int r=0;r<n;r++){
        if(mp[arr[r]]++ == 0)cnt++;
        while(cnt>k)
            if(--mp[arr[l++]] == 0)cnt--;
        cnt += r - l + 1;
    }
    return cnt;
}
 
int exactlyK(vector<int>& arr, int k){
    if(k == 0)return atMostK(arr, 0);
    return (atMostK(arr, k) - atMostK(arr, k - 1));
}