#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>

int part_one(const std::vector<int>& vec)
{
    int adapters1 = 0;
    int adapters3 = 0;

    for (int i = 0; i < vec.size()-1; i++)
    {
        if(i == 0)
        {
            if (vec[0] == 1)
            {
                adapters1++;
            }else if(vec[0] == 3)
            {
                adapters3++;
            }
        }

        if(vec[i] + 1 == vec[i+1])
        {
            adapters1++;
        }else if(vec[i] +3 == vec[i+1])
        {
            adapters3++;
        }
    }
    adapters3++;
    std::cout << "Adapters1: " << adapters1 << " Adapters3: " << adapters3 << std::endl;
    return adapters1 * adapters3;
}

uint64_t part_two(std::vector<int>& vec)
{   
    vec.push_back(vec[vec.size()-1]+3);
    std::unordered_map<int, uint64_t> memo = { {0, 1} };

    std::unordered_map<int, uint64_t>::iterator it;
    int largest_index = 0;

    for (int x : vec)
    {
        uint64_t part1 = 0;
        it = memo.find(x-3);
        if (it != memo.end())
        {
            part1 = it->second;
        }

        uint64_t part2 = 0;
        it = memo.find(x-2);
        if (it != memo.end())
        {
            part2 = it->second;
        }

        uint64_t part3 = 0;
        it = memo.find(x-1);
        if (it != memo.end())
        {
            part3 = it->second;
        }

        memo.insert({x, part1+part2+part3});
        largest_index = x;
    }
    it = memo.find(largest_index);
    if (it != memo.end())
    {
        return it->second;
    }
    // this should never happen
    return -1;
}

int main()
{
    std::vector<int> numbers;
    std::ifstream in("input",std::ios::in);
    int number; // to hold each number
	
    //Read number with >> operator
    while (in >> number)
    {
        //Add number to the vector
        numbers.push_back(number);
	}
    in.close(); // close file stream
    
    std::sort(numbers.begin(), numbers.end()); 

    std::cout << "Part1: " << part_one(numbers) << std::endl;

    std::cout << "Part2: " << part_two(numbers) << std::endl;
}