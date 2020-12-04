#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

struct password_struct
{
    int min;
    int max;
    char policy_char;
    std::string password;
};

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

int part_one(const char* filename)
{
    auto file_lines = read_file_line_by_line(filename);
    
    int valid_passwords{0};
    std::regex regex("([0-9]*)-([0-9]*) ([a-z]|[A-Z]|[0-9]): (.*)");
    std::smatch matches;

    for (int i = 0; i < file_lines.size(); i++)
    {
        if (std::regex_search(file_lines[i], matches, regex))
        {
            // std::cout << matches[0] << std::endl;
            int min_n = std::stoi(matches[1]);
            int max_n = std::stoi(matches[2]);
            char policy = matches[3].str()[0];
            std::string password = matches[4];

            int counter = 0;
            for (char c : password)
            {
                if(c == policy)
                {
                    counter++;
                }
            }

            if(counter>= min_n && counter <= max_n)
            {
                valid_passwords++;
            }
        }
    }

    return valid_passwords;
}

int part_two(const char* filename)
{
    auto file_lines = read_file_line_by_line(filename);
    int valid_passwords{0};
    std::regex regex("([0-9]*)-([0-9]*) ([a-z]|[A-Z]|[0-9]): (.*)");
    std::smatch matches;

    for (int i = 0; i < file_lines.size(); i++)
    {
        if (std::regex_search(file_lines[i], matches, regex))
        {
            // std::cout << matches[0] << std::endl;
            int min_n = std::stoi(matches[1]);
            int max_n = std::stoi(matches[2]);
            char policy = matches[3].str()[0];
            std::string password = matches[4];

            if ((password[min_n-1] == policy || password[max_n-1] == policy) && !(password[min_n-1] == policy && password[max_n-1] == policy))
            {
                valid_passwords++;
            }
        }
    }

    return valid_passwords;
}

int main()
{
    int valid1 = part_one("input");
    std::cout << valid1 << std::endl;

    int valid2 = part_two("input");
    std::cout << valid2 << std::endl;
}