#include <bits/stdc++.h>
using namespace std;

void template_CP(){
    // int query;cin>>query;
    // int amount;cin>>amount;
    // int arr[amount];
    // for(int&num:arr)cin>>num;
    // Get-Content .\testcase.txt | .\CP.exe
}

void algorithm_time_taken(){
    // only template code for determine algorithm time taken
    // pass this code to the main code
    #include <chrono>
    using namespace std::chrono;
    auto start = high_resolution_clock::now();


    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by algorithm: "
            << duration.count() << " microseconds" << endl;
}

void function_time_taken(void (*function)(void)){
    // take void function as argument
    #include <chrono>
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    function();

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
            << duration.count() << " microseconds" << endl;
}

void readfromfile(){
    // taking cin input from file
    std::ifstream in("testcase.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

}