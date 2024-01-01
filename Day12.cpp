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


uint64_t getCount(string& springs, vector<int>& counts, int curr, int currCount, int processed,  vector<vector<vector<uint64_t>>>& dp){
    //curr is the character you're processing, currCount is how many damaged springs we've dealt with, processed = index into counts
    if(curr == springs.size()) {
        uint64_t res; 
        if(counts.size() == processed) res =  1LL; //valid path for assignment 
        else res =  0LL; //invalid assignment 
        dp[curr][currCount][processed] = res; 
        return res; 
    }
    else if(dp[curr][currCount][processed] != -1LL) return dp[curr][currCount][processed]; //memo
    else if(springs[curr] == '#'){
        uint64_t res = getCount(springs, counts, curr+1, currCount+1, processed, dp); 
        dp[curr][currCount][processed] = res; 
        return res; 
    }
    else if(springs[curr] == '.' || processed == counts.size()){
        uint64_t res; 
        if(processed < counts.size() && currCount == counts[processed]){ //move onto next sequence
            res = getCount(springs, counts, curr+1, 0LL, processed+1, dp); 
        }
        else if(currCount == 0){
            res = getCount(springs, counts, curr+1, 0LL, processed, dp); //do nothing 
        }
        else{
            res = 0LL; //you done fucked up 
        }
        dp[curr][currCount][processed] = res; 
        return res;
    }
    else{ //problematic question marks 
        //can interpret as a damaged spring: 
        uint64_t damaged = getCount(springs, counts, curr+1, currCount +1, processed, dp); 
        //can interpret as a fine spring IF current count lines up 
        uint64_t operational = 0; 
        if(currCount == counts[processed]) operational = getCount(springs, counts, curr+1, 0, processed+1, dp); 
        else if(currCount == 0) operational = getCount(springs, counts, curr+1, 0, processed, dp); 

        uint64_t res = damaged + operational; 
        dp[curr][currCount][processed] = res; 
        return res; 
    }
}

string replace(string prev){
    size_t spacePosition = prev.find(' ');
    string line = prev.substr(0, spacePosition); 
    string num = prev.substr(spacePosition+1); 

    return line + "?" + line + "?" + line + "?" + line + "?" + line + " " + num + "," + num + "," + num + "," + num + "," + num; 
}

int main()
{
    ifstream f("day12input.txt"); 
    if(!f.is_open()){return 0;}
    string line; 
    auto total = 0LL; 
    while(getline(f, line)){
        line = replace(line); 
        istringstream iss(line);
        string springs;
        iss >> springs;
        vector<int> numbers;
        int num;
        while (iss >> num) {
            numbers.push_back(num);
            if (iss.peek() == ',') {
                iss.ignore();
            }
        }
        springs = springs + "."; 
        vector<vector<vector<uint64_t>>> dp; 
        //outer dimension: length of line 
        //middle dimension: length of line (upper bound) 
        //inside dimension: length of counts 
        for(int i =0; i <= springs.length(); i++){
            vector<vector<uint64_t>> middle; 
            for(int j =0; j<= springs.length(); j++){
                vector<uint64_t> inner; 
                for(int k =0; k <= numbers.size(); k++){
                    inner.push_back(-1LL); 
                }
                middle.push_back(inner); 
            }
            dp.push_back(middle); 
        }

        uint64_t curr = getCount(springs, numbers, 0LL, 0LL, 0LL, dp); 
        // cout << curr << endl; 
        total += curr; 
    }
    cout << total << endl; 
    return 0; 
}