#include <iostream>
#include <fstream>
#include <vector>
#include <string>


std::string part_one(const std::vector<int>& data)
{
    int n = data.size();
    for (int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if (data[i] + data[j] == 2020)
            {
                return std::to_string(data[i] * data[j]);
            }
        }
    }

    return "";

}

std::string part_two(const std::vector<int>& data)
{
    int n = data.size();
    for (int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            for(int k = j+1; k < n; k++)
            {
                if (data[i] + data[j] + data[k] == 2020)
                {
                    return std::to_string(data[i] * data[j] * data[k]);
                }
            }
        }
    }

    return "";

}

int main(){
    // read data from input file and store it in data vector
    std::vector<int> data;
    std::ifstream DataFile("input");

    if (DataFile)
    {
        int value;
        // read the elements
        while (DataFile >> value)
        {
            data.push_back(value);
        }
    }

    // print result of part 1
    std::cout << part_one(data) << std::endl;
    
    // print result of part 2
    std::cout << part_two(data) << std::endl;

    return 0;
}