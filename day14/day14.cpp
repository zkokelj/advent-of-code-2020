#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

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

void to_binary(int arr[], uint64_t n)
{
    for(int i = 0; i < 36; i++)
    {
        arr[i] = 0;
    }

    int c = 0; 
    while (n > 0) { 
        if(c >= 36)
        {
            std::cout << "ERROR" << std::endl;
            return;
        }
        // storing remainder in binary array 
        arr[35-c] = n % 2; 
        n = n / 2; 
        c++; 
    } 
}

uint64_t from_binary(int arr[])
{
    uint64_t res = 0;
    uint64_t power = 1;

    for(int i = 35; i >= 0; i--)
    {
        res += arr[i] * power;
        power *= 2;
    }

    return res;
}

uint64_t part_one(const std::vector<std::string>& file)
{
    std::unordered_map<int, uint64_t> numbers = {};

    std::string mask = "";
    for (auto l: file)
    {
        size_t m = l.find("mask = ");
        if(m != std::string::npos)
        {
            mask = l.substr(m + 7);
        }else
        {
            size_t bs = l.find("[")+1;
            size_t be = l.find("]");
            size_t ns = l.find("= ")+2;

            int memory = std::stoi(l.substr(bs, be-bs));
            int number = std::stoi(l.substr(ns));

            int arr[36];
            to_binary(arr, number);
            for(int i = 0; i < 36; i++)
            {
                if (mask[i] == '1')
                {
                    arr[i] = 1;
                }else if(mask[i] == '0')
                {
                    arr[i] = 0;
                }
            }
            numbers[memory] = from_binary(arr);

        }    
    }

    uint64_t total = 0;
    for(auto& x : numbers)
    {
        total += x.second;
    }
        
    return total;
}

uint64_t part_two(const std::vector<std::string>& file)
{
    std::unordered_map<std::string, uint64_t> memory = {};

    std::string mask = "";
    for (auto l: file)
    {
        
        size_t m = l.find("mask = ");
        if(m != std::string::npos)
        {
            mask = l.substr(m + 7);
        }else
        {
            size_t bs = l.find("[")+1;
            size_t be = l.find("]");
            size_t ns = l.find("= ")+2;

            int memory_n = std::stoi(l.substr(bs, be-bs));
            int number_n = std::stoi(l.substr(ns));

            std::string result = mask;
            // Step one: convert address to something with Xs (in our case we used value 2)
            int arr[36];
            to_binary(arr, memory_n);

            for(int i = 0; i < 36; i++)
            {
             
                if(mask[i] == '0' && arr[i] == 1)
                {
                    result[i] = '1';
                }
            }

            // Step two: generate all addresses!
            std::vector<std::string> all_addresses;
            all_addresses.push_back("");
            for(char c : result)
            {
                if(c != 'X')
                {
                    for(int i = 0; i < all_addresses.size(); i++)
                    {
                        all_addresses[i] += c;
                    }
                }else
                {
                    std::vector<std::string> new_addresses;
                    for(int i = 0; i < all_addresses.size(); i++)
                    {
                        new_addresses.push_back(all_addresses[i]+'0');
                        new_addresses.push_back(all_addresses[i]+'1');
                    }
                    all_addresses = new_addresses;
                }
            }

            // Step three: Adjust the value of memory
            for(auto& address : all_addresses)
            {
                memory[address] = number_n;
            }
        }    
    }

    // Step four: count all
    uint64_t total = 0;
    for(auto& x : memory)
    {
        total += x.second;
    }
    return total;
}


int main()
{

    auto file = read_file_line_by_line("input");  

    std::cout << "Part1: " << part_one(file) << std::endl;
    std::cout << "Part2: " << part_two(file) << std::endl;


}