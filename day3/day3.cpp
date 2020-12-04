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

uint32_t part_one(const std::vector<std::string>& grid, int right, int down)
{
    int grid_height = grid.size();
    int grid_length = grid[0].size();
    int position_x = 0;
    int position_y = 0;
    int trees_encountered = 0;
    
    while (position_y < grid_height)
    {
        // check if we are on a tree
        if (grid[position_y][position_x] == '#')
        {
            trees_encountered++;
        }
        
        // update position
        position_x = (position_x+right) % grid_length;
        position_y+=down;
    }
    return trees_encountered;
}

uint64_t part_two(const std::vector<std::string>& grid)
{
    return part_one(grid, 1, 1) * part_one(grid, 3, 1) * part_one(grid, 5, 1) * part_one(grid, 7, 1) * part_one(grid, 1, 2);
}

int main()
{
    std::vector<std::string> grid = read_file_line_by_line("input");
    std::cout << part_one(grid, 3, 1) << std::endl;
    std::cout << part_two(grid) << std::endl;
}

