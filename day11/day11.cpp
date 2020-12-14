#include <iostream>
#include <vector>
#include <string>
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

int neighbour_count(const std::vector<std::string>& input, int x, int y)
{
    int neihgbout_counter = 0;
    for(int i = x-1; i <= x+1; i++)
    {
        for(int j = y-1; j <= y+1; j++)
        {
            if(i < 0 || j < 0 || i >= input.size() || j >= input[0].size() || (i == x && j == y))
            {
                continue;
            }

            if(input[i][j] == '#')
            {
                neihgbout_counter++;
            }
        }
    }
    return neihgbout_counter;
}

int count_occupied(const std::vector<std::string>& input)
{
    int counter = 0;
    for(auto s : input)
    {
        for(auto c : s)
        {
            if(c == '#')
            {
                counter++;
            }
        }
    }
    return counter;
}

void print_vector_strings(const std::vector<std::string>& input)
{
    for(auto s: input)
    {
        std::cout << s << std::endl;
    }
}

int look_in_direction(const std::vector<std::string>& input, int x, int y, int dx, int dy)
{
    int i = x+dx;
    int j = y+dy;
    // std::cout << "Look in direction: " << i << ", " << j << std::endl;
    while(i >= 0 && j >= 0 && i < input.size() && j < input[0].size())
    {
        if(input[i][j] == 'L')
        {
            return 0;
        }else if(input[i][j] == '#')
        {
            return 1;
        }
        i += dx;
        j += dy;
    }

    return 0;
}

int count_visible_occupied(const std::vector<std::string>& input, int x, int y)
{
    int counter = 0;

    // std::cout << "x: " << x << " y: " << y << std::endl;

    counter += look_in_direction(input, x, y, 0, 1);
    counter += look_in_direction(input, x, y, 1, 0);
    counter += look_in_direction(input, x, y, -1, 0);
    counter += look_in_direction(input, x, y, 0, -1);
    counter += look_in_direction(input, x, y, 1, 1);
    counter += look_in_direction(input, x, y, -1, -1);
    counter += look_in_direction(input, x, y, -1, 1);
    counter += look_in_direction(input, x, y, 1, -1);
    return counter;

}

int part_one(std::vector<std::string> input)
{
    int seats_occupied = 0;
    std::vector<std::string> newinput = input; // make a copy
    do {
        input = newinput;
        for(int i = 0; i < input.size(); i++)
        {
            for(int j = 0; j < input[i].size(); j++)
            {
                if(input[i][j] == 'L' && neighbour_count(input, i, j) == 0)
                {
                    newinput[i][j] = '#';
                }else if(input[i][j] == '#' && neighbour_count(input, i, j) >= 4)
                {
                    newinput[i][j] = 'L';  
                }
            }
        }

    }while(input != newinput);

    return count_occupied(newinput);
}

int part_two(std::vector<std::string> input)
{
    int seats_occupied = 0;
    std::vector<std::string> newinput = input; // make a copy
    do {
        input = newinput;
        for(int i = 0; i < input.size(); i++)
        {
            for(int j = 0; j < input[i].size(); j++)
            {
                if(input[i][j] == 'L' && count_visible_occupied(input, i, j) == 0)
                {
                    newinput[i][j] = '#';
                }else if(input[i][j] == '#' && count_visible_occupied(input, i, j) >= 5)
                {
                    newinput[i][j] = 'L';  
                }
            }
        }

    }while(input != newinput);

    return count_occupied(newinput);
}

int main()
{
    std::vector<std::string> input = read_file_line_by_line("input");
    
    std::cout << "Part1: " << part_one(input) << std::endl;
    std::cout << "Part2: " << part_two(input) << std::endl;

}