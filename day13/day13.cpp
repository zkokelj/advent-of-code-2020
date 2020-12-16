#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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

int part_one(const std::vector<int>& buses, int timestamp)
{
    int min_difference = timestamp;
    int best_bus = 0;

    for(int b : buses)
    {
        if (timestamp % b == 0)
        {
            return 0;
        }

        int diff = (((timestamp/b)+1)*b) - timestamp;
        if (diff < min_difference)
        {
            min_difference = diff;
            best_bus = b;
        }
    }

    return min_difference*best_bus;
}

uint64_t part_two_slow(const std::vector<std::pair<int, int>>& buses)
{

    //TODO: Use Chinese Remainder theorem
    // https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/
    int biggest_value = 0;
    int biggest_index = 0;

    for(int i = 0; i < buses.size(); i++)
    {
        if(buses[i].first > biggest_value)
        {
            biggest_value = buses[i].first;
            biggest_index = buses[i].second;
        }
    }

    uint64_t t = biggest_value;
    uint64_t multiple = 100000000000000/biggest_value;
    uint64_t t0 = (biggest_value*multiple)-biggest_index;
    while(true)
    {

        t0 = (biggest_value*multiple)-biggest_index;
        multiple++;
        bool found = true;
        for(int i = 0; i < buses.size(); i++)
        {
            if(buses[i].second == biggest_index)
            {
                continue;
            }else if((t0+buses[i].second)%buses[i].first != 0)
            {
                found = false;
                break;
            }
        }


        if(found)
        {
            return t0;
        }

    }
    return 0;
}


std::vector<std::pair<int, int>> modular_equations(const std::vector<std::pair<int, int>>& buses)
{
    std::vector<std::pair<int, int>> r;

    for(auto b : buses)
    {
        r.push_back(std::make_pair( ((-b.second % b.first) + b.first) % b.first, b.first));
    }

    return r;
}

int64_t mod_pos(int64_t a, int64_t b)
{
    return ((a%b)+b)%b;
}


int64_t part_two(const std::vector<std::pair<int, int>>& buses)
{
    auto mes = modular_equations(buses);
    std::pair<int64_t, int64_t> r = std::make_pair(0, 1);

    for (auto me : mes)
    {
        int64_t coeficient = r.second;

        for(int64_t i = 1; i <= me.second; i++)
        {
            if (mod_pos(coeficient*i, me.second) == 1)
            {
                r = std::make_pair(mod_pos((me.first - r.first)*i, me.second) * r.second + r.first, r.second*me.second);
                break;
            }

        }
    }
    // std::cout << r.first << ", " << r.second << std::endl;
    return r.first;
}


int main()
{
    std::ifstream in("input",std::ios::in);
    int timestamp;
    std::string notes;

    in >> timestamp;
    in >> notes;

    auto tokens = tokenize(notes, ',');

    std::vector<int> buses;
    std::vector<std::pair<int, int>> buses2;

    int counter = 0;
    for (auto t: tokens)
    {
        if (t != "x")
        {
            int val = std::stoi(t);
            buses.push_back(val);
            buses2.push_back(std::make_pair(val, counter));
        }
        counter++;
    }

    std::cout << "Part one: " << part_one(buses, timestamp) << std::endl;
    std::cout << "Part two: " << part_two(buses2) << std::endl;

}