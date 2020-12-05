#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

std::vector<std::string> read_file_line_by_line(const char* filename)
{
    std::ifstream file{};
    file.open(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Specified file not found.");
    }

    std::vector<std::string> result;
    std::string buffer;

    while (std::getline(file, buffer)) {
        result.push_back(buffer);
    }
    return result;
}

int calculate(const std::string& s)
{
    int min = 0;
    int max = 127;

    for(int i = 0; i < 7; i++)
    {
        if (s[i] == 'F')
        {
            max = (min+max)/2;
        }else if (s[i] == 'B')
        {
            min = (min+max+1)/2;
        }

    }

    int min2 = 0;
    int max2 = 7;
    for(int i = 7; i < 10; i++){
        if (s[i] == 'R')
        {
            min2 = (min2+max2+1)/2;
        }else if(s[i] == 'L')
        {
            max2 = (min2+max2)/2;
        }
    }
    //std::cout << min2 << " - " << max2 << std::endl;

    return min*8+min2; 
}

int part_one(const std::vector<std::string> &codes){
    int max = 0;
    for(std::string code : codes)
    {
        int r = calculate(code);
        if (r > max)
        {
            max = r;
        }
    }
    return max;
}

int part_two(const std::vector<std::string> &codes)
{
    std::vector<int> seats;
    for(std::string code : codes)
    {
        seats.push_back(calculate(code));
    }
    std::sort(seats.begin(), seats.end()); 

    for(int i = 0; i < seats.size()-1; i++)
    {
        if(seats[i]+1 != seats[i+1])
        {
            return seats[i]+1;
        }
    }
    return 0;
}

int main()
{
    auto file_content = read_file_line_by_line("input");
    std::cout << part_one(file_content) << std::endl;
    //std::cout << calculate(file_content[0]) << std::endl;
    std::cout << part_two(file_content) << std::endl;


}