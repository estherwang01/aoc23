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

int next(std::vector<int> line)
{
    if(line.empty()){return 0;}
    int lastElem = line.back(); 
    std::adjacent_difference(line.begin(), line.end(), line.begin()); 
    std::all_of(line.begin(), line.end(), [](int i) { return i==0; });
    return lastElem + next(std::vector<int>(line.begin() +1, line.end())); 
}

int main()
{
    //parse input 
    std::ifstream f("day9input.txt"); 
    if(!f.is_open()){return 0;}
    std::vector<std::vector<int>> lines; 
    for (std::string line; std::getline(f, line); )
    {
        std::istringstream string_stream(line);
        lines.emplace_back(std::istream_iterator<int>(string_stream), std::istream_iterator<int>());
    }

    int sum = 0; 
    int sum2 = 0; 
    for(std::vector<int>& line : lines)
    {
        if(line.empty()) {return 0;}
        sum += next(line); 
        std::reverse(line.begin(), line.end()); 
        sum2 += next(line); 
    }

    std::cout << sum << std::endl;
    std::cout << sum2 << std::endl;  
    return 0; 
}