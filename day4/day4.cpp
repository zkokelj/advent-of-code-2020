#include <iostream>
#include <regex>
#include <fstream>
#include <string>

bool check_validity(const std::string& key, const std::string& value)
{
    if(key == "byr")
    {
        int year = std::stoi(value);
        if (year < 1920 || year > 2002)
        {
            return false;
        }
    }else if(key == "iyr")
    {
        int year = std::stoi(value);
        if (year < 2010 || year > 2020)
        {
            return false;
        }
    }else if(key == "eyr")
    {
        int year = std::stoi(value);
        if (year < 2020 || year > 2030)
        {
            return false;
        }
    }else if(key == "hgt")
    {
        if(value.substr(value.length() - 2 ) == "cm")
        {
            int height = std::stoi(value.substr(0, value.length()-2));
            if (height < 150 || height > 193)
            {
                return false;
            }
        }
        else if(value.substr(value.length() - 2 ) == "in")
        {
            int height = std::stoi(value.substr(0, value.length()-2));
            if (height < 59 || height > 76)
            {
                return false;
            }
        }

    }else if(key == "hcl")
    {
        if(value[0] != '#' || value.length() != 7)
        {
            return false;
        }
        std::regex re("#([0-9a-f]{6})");
        std::smatch matches;
        if (!std::regex_search(value, matches, re))
        {
            return false;
        }
    }else if(key == "ecl")
    {

        if (!(value.find("amb") != std::string::npos || value.find("blu") != std::string::npos || value.find("brn") != std::string::npos 
        || value.find("gry") != std::string::npos || value.find("grn") != std::string::npos || value.find("hzl") != std::string::npos
        || value.find("oth") != std::string::npos))
        {
            return false;
        }
    }else if(key == "pid")
    {
        if (!(regex_match(value.cbegin(), value.cend(), std::regex("[0-9]{9}+"))))
        {
            return false;
        }
    }

    return true;
}

int part_one(const std::vector<std::string>& passports)
{
    int valid = 0;
    std::regex regex("([a-z]+):");
    std::smatch matches;
    for(int i = 0; i < passports.size(); i++)
    {
        bool byr = false, iyr = false, eyr = false, hgt = false, hcl = false, ecl = false, pid = false;
        byr = passports[i].find("byr:") != std::string::npos;
        iyr = passports[i].find("iyr:") != std::string::npos;
        eyr = passports[i].find("eyr:") != std::string::npos;
        hgt = passports[i].find("hgt:") != std::string::npos;
        hcl = passports[i].find("hcl:") != std::string::npos;
        ecl = passports[i].find("ecl:") != std::string::npos;
        pid = passports[i].find("pid:") != std::string::npos;

        if (byr && iyr && eyr && hgt && hcl && ecl && pid)
        {
            valid++;
        }

    }

    return valid;
}

int part_two(const std::vector<std::string>& passports)
{
    int valid = 0;
    const std::regex regex("([a-zA-Z0-9_]+):([^\r\n\t\f\v ]+)");
    for(const std::string& passport: passports)
    {
        std::vector<std::string> tmp;
        tmp.push_back(passport);
        if (part_one(tmp) != 1)
        {
            continue;
        }

        std::smatch match;
        std::string::const_iterator search(passport.cbegin());
        bool valid_all = true;
        while (regex_search(search, passport.cend(), match, regex))
        {
            //std::cout << match[1] << " - " << match[2] << " is: " << check_validity(match[1].str(), match[2].str()) << std::endl; 
            valid_all &= check_validity(match[1].str(), match[2].str());
            
            search = match.suffix().first;
        }
        if (valid_all)
        {
            valid++;
            //std::cout << passport << std::endl;
        }
    }
    return valid;
}


int main()
{
    std::ifstream file("input");
    std::vector<std::string> passports{};
    std::string passport{};

    for(std::string line; std::getline(file, line);)
    {
        if(line.empty())
        {
            passports.push_back(passport);
            passport = "";
            continue;
        }else if (passport.length() > 0)
        {
            passport += " ";
        }

        passport += line;
    }
    // check the last one and include it if the file doesn't end with empty line
    if (passport.length() > 0)
    {
        passports.push_back(passport);
    }
    
    std::cout << part_one(passports) << std::endl;
    std::cout << part_two(passports) << std::endl;

}