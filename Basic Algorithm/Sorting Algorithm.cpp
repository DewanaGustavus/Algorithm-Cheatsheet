#include <bits/stdc++.h>
using namespace std;

int binarysearch(vector<int> array, int target){
    // Time Complexity : O(log(n))
    int length = array.size();
    int low = 0;
    int high = length-1;

    while(low<=high){
        int mid = (low+high)/2;
        int num = array[mid];

        if(target==num)return mid;
        else if(target<num)high=mid-1;
        else low=mid+1;
    }
    return -1;
}

void simplebinarysearch(){
    vector<int> arr;
    int n;
    int check = [](int x){
        return 1;
    };


    int low = 0;
    int high = n-1;
    while(low<=high){
        int mid = (low+high)/2;
        if(check(mid))low=mid+1;
        else high=mid-1;
    }
}

int countcommon(vector<int> A, vector<int> B){
    // Time Complexity : O(n log(n)) sort + O(n) run
    int lena = A.size();
    int lenb = B.size();
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    int count = 0;
    int i=0, j=0;
    while(i<lena && j<lenb){
        if(A[i]<B[j])i++;
        else if(A[i]>B[j])j++;
        else{
            count++;
            i++;j++;
        }
    }
    return count;
}

int maximumlinesweep(vector<pair<int,int>> schedule){
    // Time Complexity : O(n log(n))
    priority_queue<int, vector<int>, greater<int>> leftsweep;
    priority_queue<int, vector<int>, greater<int>> rightsweep;
    for(auto tmp : schedule){
        leftsweep.push(tmp.first);
        rightsweep.push(tmp.second);
    }
    int maxi = 0;
    int curr = 0;

    while(!leftsweep.empty()){
        int left = leftsweep.top();
        while(!leftsweep.empty() && leftsweep.top() == left){
            curr++;
            leftsweep.pop();
        }
        while(!rightsweep.empty() && rightsweep.top() < left){
            curr--;
            rightsweep.pop();
        }
        maxi = max(maxi, curr);
    }
    return maxi;
}

int taskschedulinglinesweep(vector<pair<int,int>> schedulearray){
    // Time Complexity : O(n log(n))
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> schedule; // {end, start}
    for(auto tmp : schedulearray){
        schedule.push({tmp.second, tmp.first});
    }
    
    int count = 0;
    int right = 0;
    while(!schedule.empty()){
        while(!schedule.empty() && schedule.top().second < right)schedule.pop();
        if(!schedule.empty()){
            right = schedule.top().first;
            count ++;
            schedule.pop();
        }
    }
    return count;
}
