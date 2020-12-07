#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

struct BagNumberPair
{
    std::string name;
    int n;
};

class Bag
{
public:
    std::string name;
    std::vector<BagNumberPair> content;
    //constructor
    Bag (const std::string& name_p): name(std::move(name_p))
    {
    }

    void addBagNumberPair(const BagNumberPair& p)
    {
        content.push_back(p);
    }

    std::string objectToString()
    {
        std::string r = name + "---> ";
        for(BagNumberPair bnp : content)
        {
            r +=  bnp.name + ": " + std::to_string(bnp.n) + ";  ";
        }
        return r;
    }



};

int part_one(const std::vector<std::string> file_content)
{
    std::vector<Bag> bags;

    for(std::string s : file_content)
    {
        std::istringstream iss(s);
        std::vector<std::string> tokens;
        std::copy(std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>(),
        //std::ostream_iterator<std::string>(std::cout, "\n"));
        std::back_inserter(tokens));

        Bag tmp = Bag(tokens[0]+ " " + tokens[1]);

        if (tokens[4] == "no")
        {
            continue;
        }

        for(int j=4; j < tokens.size(); j+=4)
        {
            BagNumberPair bnp;
            bnp.n = std::stoi(tokens[j]);
            bnp.name =  tokens[j+1] + " " + tokens[j+2];
            tmp.addBagNumberPair(bnp);
        }
        bags.emplace_back(tmp);
    }

    std::vector<std::string> stack;
    std::vector<Bag> holds_sg;
    stack.emplace_back("shiny gold");
    for (int i = 0; i < stack.size(); i++)
    {
        for (Bag b : bags)
        {
            for (BagNumberPair bnp : b.content)
            {
                if (bnp.name == stack[i])
                {
                    holds_sg.emplace_back(b);
                    if(std::find(stack.begin(), stack.end(), b.name) == stack.end())
                    {
                        stack.emplace_back(b.name);
                    }
                }
            }
        }
    }


    return stack.size()-1;
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

int main()
{
    auto file_content = read_file_line_by_line("input");


    std::cout << part_one(file_content) << std::endl;

}