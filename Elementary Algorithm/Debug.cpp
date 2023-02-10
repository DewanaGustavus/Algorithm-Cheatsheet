#include <bits/stdc++.h>
using namespace std;

int randint(){return rand()%10;}
char randchar(){return ((rand()%26)+'a');}
void debug(){cout<<"executed"<<endl;}

// Execution Time Analyze & Debugging
#define time()              chrono::high_resolution_clock::now()
#define time_start          using namespace chrono;auto START=time();
#define time_end            printf("Time taken by algorithm: %d microseconds\n",duration_cast<microseconds>(time()-START).count());
#define debug               cout<<"debug"<<endl;