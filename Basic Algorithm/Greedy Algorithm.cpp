#include <bits/stdc++.h>
using namespace std;

int taskscheduling(vector<pair<int,int>> task){
    // Time Complexity : O(n^2)
    sort(task.begin(),task.end());
    int amount = task.size();
    const int inf = 1e9;
    int idx=-1;
    int currlimit=-inf;
    int count=0;
    int minidx;
    int minimum;
    while(idx<amount){
        minimum=inf; 
        for(int i=idx+1;i<amount;i++)
            if(minimum>task[i].second && task[i].first>currlimit){
                minimum=task[i].second;
                minidx=i;
            }

        if(minimum!=inf){
            currlimit = minimum;
            idx=minidx;
            count++;
        }else break;
    }
    return count;
}

int minimizesum(vector<int> array){
    // Time Complexity : O(n log(n)) sort + O(n) run
    sort(array.begin(),array.end());
    int length = array.size();
    int median = array[length/2];
    
    int total = 0;
    for(int num:array)total += abs(median-num);
    
    return total;
}

float minimizesum2(vector<int> array){
    // minimize absolute value different sum(squared)
    // Time Complexity : O(n log(n)) sort + O(n) run
    sort(array.begin(),array.end());
    int length = array.size();
    float temptotal = accumulate(array.begin(), array.end(),0);
    float average = temptotal/length;
    
    float total = 0;
    for(int num:array)total += abs(average-num) * abs(average-num);
    
    return total;
}
