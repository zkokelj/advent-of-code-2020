#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>


int part_one(const std::vector<std::vector<std::string>>& file_content)
{
    int sum = 0;
    for(int i = 0; i < file_content.size(); i++)
    {
        std::set<char> s1;
        for(int j = 0; j < file_content[i].size(); j++)
        {
            for(char c : file_content[i][j])
            {
                s1.insert(c);
            } 
        }
        sum += s1.size();
    }
    return sum;
}

int part_two(const std::vector<std::vector<std::string>>& file_content)
{
    int sum = 0;
    for(int i = 0; i < file_content.size(); i++)
    {
        std::set<char> s1{};
        for(char c : file_content[i][0])
        {
            s1.insert(c);
        }
        for(int j = 1; j < file_content[i].size(); j++)
        {
            std::set<char> s2;
            for(char c : file_content[i][j])
            {
                s2.insert(c);
            }
            std::set<char> s3{};
            for(char c : s2)
            {
                if(s1.count(c))
                {
                    s3.insert(c);
                }
            }
            s1 = s3;
        }
        sum += s1.size();
    }
    return sum;
}

int main()
{
    std::ifstream file("input");
    std::vector<std::vector<std::string>> file_content{};
    std::vector<std::string> vec{};

    for(std::string line; std::getline(file, line);)
    {
        if(line.empty())
        {
            file_content.push_back(vec);
            vec = {};
            continue;
        }
        vec.push_back(line);
    }
    if (vec.size() > 0)
    {
        file_content.push_back(vec);
    }

   std::cout << part_one(file_content) << std::endl;
   std::cout << part_two(file_content) << std::endl;

}