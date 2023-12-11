#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <numeric>


using namespace std; 

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int steps(string start, unordered_map<string, pair<string, string>> next, vector<char> insns){
    int index = 0; 
    int cnt = 0; 
    string curr = start; 
    while(curr.back() != 'Z'){
        char insn = insns[index]; 
        if(insn == 'L'){curr = next[curr].first; }
        else{curr = next[curr].second; }
        cnt++; 
        index++; 
        if(index >= insns.size()){index = 0;}
    }
    return cnt; 
}

int main()
{
    ifstream f("day8input.txt"); 
    if(!f.is_open()){return 0;}
    string firstline, dummy, line; 
    getline(f, firstline); 
    vector<char> insns(firstline.begin(), firstline.end()); 
    getline(f, dummy); 

    unordered_map<string, pair<string, string>> next;
    vector<string> starts; 

    while(getline(f, line)){
        string key, value1, value2; 
        istringstream iss(line); 
        if(iss >> key >> ws && getline(iss, dummy, '(') &&  getline(iss, value1, ',')  && iss >> ws && getline(iss, value2, ')')){
            next[key] = pair(value1, value2); 
            if(key.back() == 'A'){starts.push_back(key);}
        }
    }
    
    int p1 = steps("AAA", next, insns); 
    cout << p1 << endl; 

    vector<int64_t> cycles; 
    for(string start: starts){cycles.push_back(steps(start, next, insns)); }

    auto lcm = [](int64_t a, int64_t b) {return (a / gcd(a, b)) * b;}; 

    int64_t p2 = 1;
    for (auto &cycle: cycles){p2 = lcm(p2, cycle);}
    cout << p2 << endl; 
    return 0; 
}