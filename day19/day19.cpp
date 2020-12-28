#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

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

std::vector<int> match2(const std::string& line, const std::unordered_map<int, std::vector<std::vector<int>>>& rules, const std::unordered_map<int, char>& endRules, int rule=0, int index=0)
{
    if(index == line.size())
        return std::vector<int>{};
    
    if(endRules.find(rule) != endRules.end())
    {
        if(line[index] == endRules.at(rule))
        {
            return std::vector<int>{ index +1 };
        }
        return std::vector<int>{};
    }else
    {
        std::vector<int> matches = {};
        auto allIndirectRules = rules.at(rule);

        for(auto& indRules : allIndirectRules)
        {
            std::vector<int> sub_matches = {index};
            for(auto& sub_rule: indRules)
            {
                std::vector<int> new_matches = {};
                
                for(auto idx : sub_matches)
                {
                    auto tmp = match2(line, rules, endRules, sub_rule, idx);
                    new_matches.insert(new_matches.end(), tmp.begin(), tmp.end());
                }
                sub_matches = new_matches;
            }
            matches.insert(matches.end(), sub_matches.begin(), sub_matches.end());
        }
        return matches;
    }

    return std::vector<int>{};

}

int part_one(const std::vector<std::string>& input, int sep, const std::unordered_map<int, std::vector<std::vector<int>>>& rules, const std::unordered_map<int, char>& endRules)
{

    int count = 0;
    for(int i = sep+1; i < input.size(); i++)
    {
        std::vector<int>  m = match2(input[i], rules, endRules);
        for(auto el: m)
        {
            if(input[i].size() == el)
            {
                count += 1;
                break;
            }
        }
    }

    return count;
}


int main()
{
    std::vector<std::string> lines = read_file_line_by_line("input");

    std::unordered_map<int, std::vector<std::vector<int>>> rules;
    std::unordered_map<int, char> endRules;

    int separator = 0;
    for(int i = 0; i < lines.size(); i++)
    {
        if(lines[i] == "")
        {
            separator = i;
            break;
        }

        // parse rules and save them to unordered maps
        size_t bs = lines[i].find(":");
        int number = std::stoi(lines[i].substr(0, bs));
        size_t exact_char = lines[i].find("\"");
        if(exact_char != std::string::npos)
        {
            endRules[number] = lines[i][exact_char+1];
        }else
        {
            size_t or_separator = lines[i].find("|");
            std::vector<std::vector<int>> vec;

            if(or_separator == std::string::npos)
            {
                std::string first = lines[i].substr(bs+1);
                std::vector<std::string> vecs = tokenize(first, ' ');
                std::vector<int> ints;
                for(auto a: vecs)
                    ints.push_back(std::stoi(a));
                vec.push_back(ints);
            }else{
                std::string first = lines[i].substr(bs+1, or_separator - bs-1);
                std::string second = lines[i].substr(or_separator+1);
                std::vector<int> ints1;
                std::vector<int> ints2;
                std::vector<std::string> vecs1 = tokenize(first, ' ');
                std::vector<std::string> vecs2 = tokenize(second, ' ');
                
                for(auto& a: vecs1)
                    ints1.push_back(std::stoi(a));

                for(auto& a: vecs2)
                    ints2.push_back(std::stoi(a));

                vec.push_back(ints1);
                vec.push_back(ints2);
            }
            rules[number] = vec;
        }     
    }

    // Now we have all the rules in unordered maps
    std::cout << "Part1: " << part_one(lines, separator, rules, endRules) << std::endl;

}