#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

std::vector<std::string> tokenize(const std::string& s, const char delim)
{
    size_t start;
    size_t end = 0;
    std::vector<std::string> result;
 
    while ((start = s.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = s.find(delim, start);
        result.push_back(s.substr(start, end - start));
    }

    return result;
}

int part_one(const std::vector<std::string> in_vec)
{
    std::unordered_map<int, int> last_app = {};
    int count = 0;
    int number_to_be_spoken = 0;

    for(auto s : in_vec)
    {
        last_app[std::stoi(s)] = count;
        count++;
    }

    while (count < 30000000-1)
    {
        auto f = last_app.find(number_to_be_spoken);
        if(f != last_app.end())
        {
            int next_number = count - f->second;
            last_app[number_to_be_spoken] = count;
            number_to_be_spoken = next_number;
        }else{
            last_app[number_to_be_spoken] = count;
            number_to_be_spoken = 0;
        }
        count++;
    }
    
    return number_to_be_spoken;
}

int main()
{
    std::ifstream in("input",std::ios::in);
    std::string input;
    in >> input;

    std::vector<std::string> in_vec = tokenize(input, ',');

    std::cout << "Part one: " << part_one(in_vec) << std::endl;

}