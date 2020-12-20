#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>
#include <unordered_map>
#include <algorithm>

struct Condition
{
    std::string name;
    std::vector<std::tuple<int, int>> conditions;
};


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

int part_one(const std::vector<Condition>& conditions, const std::vector<std::vector<int>>& tickets)
{
    int sum = 0;

    // tickets[0] = my ticker, others are nearby tickets
    for(int i = 1; i < tickets.size(); i++)
    {
        for(int n: tickets[i])
        {
            bool valid = false;
            // Now check every condition
            for(auto c : conditions)
            {
                for(auto ci : c.conditions)
                {
                    if(n >= std::get<0>(ci) && n <= std::get<1>(ci))
                    {
                        valid = true;
                        break;
                    }
                }
                if(valid)
                    break;
            }
            if(valid == false)
                sum += n;
        }
    }
    return sum;
}

uint64_t part_two(const std::vector<Condition>& conditions, const std::vector<std::vector<int>>& tickets)
{
    std::vector<std::vector<int>> valid_tickets;
    for(int i = 1; i < tickets.size(); i++)
    {
        bool valid_ticket = true;
        for(int n: tickets[i])
        {
            bool valid = false;
            // Now check every condition
            for(auto c : conditions)
            {
                for(auto ci : c.conditions)
                {
                    if(n >= std::get<0>(ci) && n <= std::get<1>(ci))
                    {
                        valid = true;
                        break;
                    }
                }
                if(valid)
                    break;
            }
            if(valid == false)
            {
                valid_ticket = false;
                break;
            }
        }
        if(valid_ticket)
            valid_tickets.push_back(tickets[i]);
    }

    std::unordered_map<std::string, std::vector<int>> possibilties;
    for (auto c: conditions)
    {
        possibilties[c.name] = std::vector<int>();
        int param_size = tickets[0].size();
        for(int i = 0; i < param_size; i++)
        {
            // if i-th field is possible for condition c
            bool possible = true;
            // check all valid tickets
            for(auto t: valid_tickets)
            {
                // check all conditions in c (if anyone can satisfy it is OK)
                bool any_possible = false;
                for (auto c1: c.conditions)
                {
                    if(t[i] >= std::get<0>(c1) &&  t[i] <= std::get<1>(c1))
                    {
                        // std::cout << "possible: " << t[i] << "for: " << std::get<0>(c1) << ", " << std::get<1>(c1) << std::endl;
                        any_possible = true;
                    }
                }
                // if none is possible then i-t field is not right for condition c
                if (!any_possible)
                        possible = false;
            }
            if (possible)
                possibilties[c.name].push_back(i);
        }
    }

    for(auto a: possibilties)
    {
        std::cout << a.first << ": ";
        for(auto x: a.second)
            std::cout << x << ", ";
        std::cout << std::endl;
    }
    std::vector<std::tuple<std::string, int>> decoded;
    while (possibilties.size() > 0)
    {
        std::string to_remove;
        int used_possibility;
        for(auto& p: possibilties)
        {
            if(p.second.size() == 1)
            {
                // add to decoded
                used_possibility = p.second[0];
                to_remove = p.first;
                decoded.push_back(std::make_tuple(p.first, used_possibility));
                // remove from other vectors

                for(auto& p2: possibilties)
                {
                    std::vector<int>::iterator position = std::find(p2.second.begin(), p2.second.end(), used_possibility);
                    if(position != p2.second.end())
                        p2.second.erase(position);
                }
                break;
            }
        }
        possibilties.erase(to_remove);
    }

    std::cout << "#########################" << std::endl;
    for(auto x: decoded)
        std::cout << std::get<0>(x) << " -> " << std::get<1>(x) << std::endl;

    // search for fields that start with the word departure and multiply these values from my ticket
    uint64_t result = 1;
    for(auto& x : decoded)
    {   
        if(std::get<0>(x).find("departure") == 0)
            result *=  tickets[0][std::get<1>(x)];
    }

    return result;
}

int main()
{
    // read the input into conditions, my ticket, other tickets
    std::vector<Condition> conditions;
    std::vector<std::vector<int>> tickets; //my ticker is always the first ticker in the vector

    std::vector<std::string> lines = read_file_line_by_line("input");
    
    bool conditions_input = true;

    for(int i = 0; i < lines.size(); i++)
    {
        if (conditions_input)
        {
            std::size_t found = lines[i].find(":");
            if(found == std::string::npos)
            {
                conditions_input = false;
                continue;
            }

            std::string condition_name = lines[i].substr(0, found);
            std::vector<std::tuple<int, int>> condition_vector;

            //std::cout << "condition name: " << condition_name << "; line: " <<lines[i] <<std::endl;
            std::string conditions_string = lines[i].substr(found+2);
            auto ll = tokenize(conditions_string, ' ');
            for (auto l : ll)
            {
                if(l == "or")
                    continue;
                
                auto num = tokenize(l, '-');
                condition_vector.push_back(std::make_tuple(std::stoi(num[0]), std::stoi(num[1])));
            }

            Condition c1 = {condition_name, condition_vector};
            conditions.push_back(c1);

        }else{
            if(lines[i] == "your ticket:" || lines[i] == "nearby tickets:" || lines[i] == "")
                continue;
            
            auto tn = tokenize(lines[i], ',');
            std::vector<int> v;
            for (auto n: tn)
            {
                v.push_back(std::stoi(n));
            }
            tickets.push_back(v);
        }
    }

    std::cout << "Part1: " << part_one(conditions, tickets) << std::endl;
    std::cout << "Part2: " << part_two(conditions, tickets) << std::endl;

}