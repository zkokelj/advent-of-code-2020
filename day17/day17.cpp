#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

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

class Point
{
public:
    int x, y, z;
    Point(int _x, int _y, int _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    void PrintPoint() const 
    {
        std::cout << "Point: " << x << ", " << y << ", " << z << std::endl;
    }

    bool operator==(const Point& other) const 
    {
        return (x == other.x && y == other.y && z == other.z);
    }
};

// hash function for unordered_map
struct hash_f
{
    std::size_t operator() (const Point& p) const
    {
        std::size_t h1 = std::hash<int>()(p.x);
        std::size_t h2 = std::hash<int>()(p.y);
        std::size_t h3 = std::hash<int>()(p.z);
 
        return h1 ^ h2 ^ h3;
    }
};

int getNeighbourActivePoints(const std::vector<Point> active, Point p, int max)
{
    int counter = 0;
    std::vector<Point> neghbourPoints;
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            for(int k = -1; k <= 1; k++)
            {
                if(i == 0 && j == 0 && k == 0)
                    continue;

                neghbourPoints.push_back(Point(p.x+i, p.y+j, p.z+k));
            }
        }
    }

    std::cout << "Number of neigbout points: " << neghbourPoints.size() << std::endl;
    std::cout << "Number of active points: " << active.size() << std::endl;

    for(auto& p1 : neghbourPoints)
    {
        for(auto& p2 : active)
        {
            if(p1 == p2)
            {
                p1.PrintPoint();
                counter++;
                break;
            }
                
        }
    }

    return counter;
}

int part_one(const std::vector<Point>& initialActivePoints)
{
    std::vector<Point> activePoints = initialActivePoints;
    
    // 6 iterations
    for(int i = 0; i < 6; i++)
    {
        std::unordered_map<Point, int, hash_f> marked;

        // we only need to check around activated points
        for(Point& p: activePoints)
        {
            // now look around them in three directions (distance 1)
            for(int x_i = -1; x_i <= 1; x_i++)
            {
                for(int y_i = -1; y_i <= 1; y_i++)
                {
                    for(int z_i = -1; z_i <= 1; z_i++)
                    {
                        if(z_i == y_i && x_i == y_i && x_i == 0)
                            continue;
                        
                        marked[Point(p.x+x_i, p.y+y_i, p.z+z_i)]++;
                    }
                }
            }
        }

        //new activated points
        std::vector<Point> new_activated;
        for(auto& element: marked)
        {
            if(element.second == 3)
            {
                new_activated.push_back(element.first);
            }

            if(element.second == 2)
            {
                for(auto& ap: activePoints)
                {
                    if(element.first == ap)
                    {
                        new_activated.push_back(element.first);
                        break;
                    }
                }
            }
        }

        activePoints = new_activated;
    }

    return activePoints.size();
}


int main()
{
    std::vector<std::string> initialState = read_file_line_by_line("input");

    std::vector<Point> activePoints;

    for(int i = 0; i < initialState.size(); i++)
    {
        for(int j = 0; j < initialState[i].size(); j++)
        {
            // # means active point
            if(initialState[i][j] == '#')
            {
                activePoints.push_back(Point(i, j, 0));
            }
        }
    }

    std::cout << "Part1: " << part_one(activePoints) << std::endl;
    // std::cout << "Part2: " << part_one(initialState) << std::endl;
}