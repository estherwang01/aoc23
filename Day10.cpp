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
#include <unordered_set>

using namespace std;  

vector<pair<int, int>> getDirs(char ch)
{
    pair<int, int> n = pair(-1, 0); 
    pair<int, int> w = pair(0, -1); 
    pair<int, int> e = pair(0, 1); 
    pair<int, int> s = pair(1, 0); 

    vector<pair<int, int>> dirs; 
    if(ch == '|'){
        dirs.push_back(n);
        dirs.push_back(s);  
    }
    else if(ch == '-'){
        dirs.push_back(e); 
        dirs.push_back(w); 
    }
    else if(ch == 'L'){
        dirs.push_back(e); 
        dirs.push_back(n); 
    }
    else if(ch == 'J'){
        dirs.push_back(n); 
        dirs.push_back(w); 
    }
    else if(ch == 'F'){
        dirs.push_back(e); 
        dirs.push_back(s); 
    }
    else if(ch == '7'){
        dirs.push_back(s); 
        dirs.push_back(w); 
    }
    return dirs; 
}


vector<pair<int, int>> getNeighbors(vector<vector<char>> lines, int x, int y){
    vector<pair<int, int>> neighbors; 
    vector<pair<int, int>> dirs = getDirs(lines[x][y]); 
    for(pair<int,int>& dir: dirs){
        pair<int, int> candidate = pair(x + dir.first, y +dir.second); 
        if(candidate.first >= 0 && candidate.second >= 0 && candidate.first < lines.size() && candidate.second < lines[0].size()){
            neighbors.push_back(candidate); 
        }
    }
    return neighbors; 
}

int main()
{
    ifstream f("day10input.txt"); 
    if(!f.is_open()){return 0;}
    vector<vector<char>> lines; 
    for (string line; getline(f, line); )
    {
        vector<char> row; 
        for(char ch: line){row.push_back(ch); }
        lines.push_back(row); 
    }

    pair<int, int> s; 
    for (size_t i = 0; i < lines.size(); ++i) {
        for (size_t j = 0; j < lines[i].size(); ++j) {
            if (lines[i][j] == 'S') {
                s = pair(i, j); 
                lines[i][j] = 'L'; //lmao i'm stupid and hardcoded this bc i couldn't figure out how else to do it!!!!!
            }
        }
    }
    set<pair<int, int>> seen; 
    seen.insert(s); 

    int part1 = 0; 
    vector<tuple<int, int, int>> q; 
    q.push_back(tuple(s.first, s.second, 0)); 
    while(!q.empty()){
        tuple<int, int, int> curr = q.front(); 
        q.erase(q.begin()); 
        part1 = get<2>(curr); 
        vector<pair<int, int>> neighbors = getNeighbors(lines, get<0>(curr), get<1>(curr)); 
        for(pair<int, int>& n: neighbors){
            if(seen.find(n) == seen.end()){
                seen.insert(n); 
                q.push_back(tuple(n.first, n.second, part1 + 1)); 
            }
        }
    }
    cout<<part1 << endl; 
    int part2 = 0; 

    for (size_t i = 0; i < lines.size(); ++i) {
        bool inside = false; 
        for (size_t j = 0; j < lines[i].size(); ++j) {
            char curr = lines[i][j]; 
            if(seen.find(pair(i,j)) != seen.end() && (curr =='|' || curr == 'F' || curr == '7')){inside = !inside; }
            if(inside && seen.find(pair(i,j))== seen.end()){part2++; }
        }
    }
    cout<<part2<<endl; 
    return 0; 
}
