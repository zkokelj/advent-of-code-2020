#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

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
}