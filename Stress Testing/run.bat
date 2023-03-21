@echo off
cd "d:\Coding\Competitive_Programming\C++\testing\"
g++ -O2 -std=c++17 -Wno-unused-result -Wshadow -Wall -o bruteforce _bruteforce.cpp
g++ -O2 -std=c++17 -Wno-unused-result -Wshadow -Wall -o generator _generator.cpp
g++ -O2 -std=c++17 -Wno-unused-result -Wshadow -Wall -o solution _solution.cpp
bash script.sh
