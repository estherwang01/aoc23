#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>

using namespace std; 

vector<pair<int, int>> galaxies; 
vector<int> expandedRows; 
vector<int> expandedCols; 


auto distance(pair<int, int> g1, pair<int, int> g2, int expansionFactor)
{
    auto dist = 0LL; 
    if(g1.first > g2.first){
        auto temp = g1; 
        g1 = g2; 
        g2 = temp; 
    }
    for(int row = g1.first; row < g2.first; row++){
        if(expandedRows[row]){dist += expansionFactor; }
        else{dist++; }
    }

    if(g1.second > g2.second){
        auto temp = g1; 
        g1 = g2; 
        g2 = temp; 
    }
    for(int col = g1.second; col < g2.second; col++){
        if(expandedCols[col]){dist += expansionFactor; }
        else{dist++; }
    }
    return dist; 
}

int main()
{
    ifstream f("day11input.txt"); 
    if(!f.is_open()){return 0;}
    string line;
    for (auto row = 0;  getline(f, line); row++)
    {
        bool seen = false; 
        while(expandedCols.size() < line.length()) expandedCols.push_back(true); 

        for(auto col =0; col<line.length(); col++){
            if(line[col] == '#'){
                galaxies.push_back(pair(row, col)); 
                expandedCols[col] = false; 
                seen = true; 
            }
        }
        expandedRows.push_back(!seen); 
    }

    auto total = 0LL; 
    auto total2 = 0LL; 
    for(int i =0; i<galaxies.size()-1; i++){
        for(int j = i+1; j<galaxies.size(); j++){
            total += distance(galaxies[i], galaxies[j], 2); 
            total2 += distance(galaxies[i], galaxies[j], 1000000); 
        }
    }
    cout<<total<<endl; 
    cout<<total2<<endl; 
    return 0; 
}