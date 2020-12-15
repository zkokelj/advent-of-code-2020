#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

int part_one(const std::vector <std::pair<char, int>>& input)
{
    int x = 0;
    int y = 0;
    int orientation = 1; // east

    int counter = 0;

    for (auto e : input)
    {
        counter++;

        if(e.first == 'N')
        {
            y += e.second;
        }
        else if(e.first == 'S')
        {
            y -= e.second;
        }
        else if(e.first == 'W')
        {
            x -= e.second;
        }
        else if(e.first == 'E')
        {
            x += e.second;
        }else if(e.first == 'L') // turn left
        {
            orientation = (orientation + 4 - e.second/90)%4;   
        }else if(e.first == 'R') // turn right
        {
            orientation = (orientation + 4 + e.second/90)%4;
        }
        else if(e.first == 'F')
        {
            if(orientation == 0)
            {
                y += e.second;
            }
            else if(orientation == 1)
            {
                x += e.second;
            }
            else if(orientation == 2)
            {
                y -= e.second;
            }
            else if(orientation == 3)
            {
                x -= e.second;
            }
        }
    }


    return std::abs(x) + std::abs(y);
}

std::pair<int, int> rotateWaypoint(int degees, int wx, int wy)
{
    // turn for 90 degrees each time in a loop
    for(int i = 0; i < degees; i++)
    {
        int tmp = wy;
        wy = - wx;
        wx = tmp;
    }
    return std::make_pair(wx, wy);
}

int part_two(const std::vector <std::pair<char, int>>& input)
{
    int way_x = 10;
    int way_y = 1;

    int x = 0;
    int y = 0;
    int orientation = 1; // east

    int counter = 0;

    for (auto e : input)
    {
        counter++;

        if(e.first == 'N')
        {
            way_y += e.second;
        }
        else if(e.first == 'S')
        {
            way_y -= e.second;
        }
        else if(e.first == 'W')
        {
            way_x -= e.second;
        }
        else if(e.first == 'E')
        {
            way_x += e.second;
        }else if(e.first == 'L') // turn left
        {
            auto tmp = rotateWaypoint(4-e.second/90, way_x, way_y);
            way_x = tmp.first;
            way_y = tmp.second;
        }else if(e.first == 'R') // turn right
        {
            auto tmp = rotateWaypoint(e.second/90, way_x, way_y);
            way_x = tmp.first;
            way_y = tmp.second;
        }
        else if(e.first == 'F')
        {
            x += way_x * e.second;
            y += way_y * e.second;
        }
    }


    return std::abs(x) + std::abs(y);
}


int main()
{
    std::vector <std::pair<char, int>> input;
    std::ifstream in("input",std::ios::in);
    std::string x;

    //Read number with >> operator
    while (in >> x)
    {
        //Add number to the vector
        input.push_back(std::make_pair(x[0], std::stoi(x.substr(1))));
    }

    in.close(); // close file stream

    std::cout << "Part1: " << part_one(input) << std::endl;
    std::cout << "Part2: " << part_two(input) << std::endl;

}