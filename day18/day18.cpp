#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>

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

long solveEquation(std::deque<std::string> equation)
{
    
    while(equation.size() > 1)
    {
        long o1;
        long o2;
        std::string op;

        // no parenthesis - get operant directly
        if(equation.front() != "(")
        {
            o1 = std::stol(equation.front());
            equation.pop_front();
        }
        // paranthesis -> store everything between them in new deque
        else{
            int count_brackets = 0;
            equation.pop_front(); // we know it it parenthesis, so just pop it
            std::deque<std::string> newEq;
            while (count_brackets > 0 || equation.front() != ")")
            {
                if(equation.front() == "(")
                {
                    count_brackets++;
                }else if(equation.front() == ")")
                {
                    count_brackets--;
                }
                newEq.push_back(equation.front());
                equation.pop_front();
            }
            equation.pop_front();
            o1 = solveEquation(newEq);
        }

        // now we need operator
        op = equation.front();
        equation.pop_front();

        // For the second operant it is exactly the same as for the first one

        // no parenthesis
        if(equation.front() != "(")
        {
            o2 = std::stol(equation.front());
            equation.pop_front();
        }
        // paranthesis -> store everything between them in new deque
        else{
            int count_brackets = 0;
            equation.pop_front(); // we know it it parenthesis, so just pop it
            std::deque<std::string> newEq;
            while (count_brackets > 0 || equation.front() != ")")
            {
                if(equation.front() == "(")
                {
                    count_brackets++;
                }else if(equation.front() == ")")
                {
                    count_brackets--;
                }
                newEq.push_back(equation.front());
                equation.pop_front();
            }
            equation.pop_front();
            o2 = solveEquation(newEq);
        }

        // we should have two elements in the deque
        if(op == "*")
        {
            equation.push_front(std::to_string(o1*o2));
        }
        else if(op == "+")
        {
            equation.push_front(std::to_string(o1+o2));
        }

    }

    return std::stol(equation.front());
}

// adition has higher precedence than multiplication
long solveEquation2(std::deque<std::string> equation)
{
    std::deque<std::string> mulOnlyEquation;

    while(equation.size() > 1)
    {
        long o1;
        long o2;
        std::string op;

        // no parenthesis - get operant directly
        if(equation.front() != "(")
        {
            o1 = std::stol(equation.front());
            equation.pop_front();
        }
        // paranthesis -> store everything between them in new deque
        else{
            int count_brackets = 0;
            equation.pop_front(); // we know it it parenthesis, so just pop it
            std::deque<std::string> newEq;
            while (count_brackets > 0 || equation.front() != ")")
            {
                if(equation.front() == "(")
                {
                    count_brackets++;
                }else if(equation.front() == ")")
                {
                    count_brackets--;
                }
                newEq.push_back(equation.front());
                equation.pop_front();
            }
            equation.pop_front();
            o1 = solveEquation2(newEq);
        }

        // now we need operator
        op = equation.front();
        equation.pop_front();

        // For the second operant it is exactly the same as for the first one

        // no parenthesis
        if(equation.front() != "(")
        {
            o2 = std::stol(equation.front());
            equation.pop_front();
        }
        // paranthesis -> store everything between them in new deque
        else{
            int count_brackets = 0;
            equation.pop_front(); // we know it it parenthesis, so just pop it
            std::deque<std::string> newEq;
            while (count_brackets > 0 || equation.front() != ")")
            {
                if(equation.front() == "(")
                {
                    count_brackets++;
                }else if(equation.front() == ")")
                {
                    count_brackets--;
                }
                newEq.push_back(equation.front());
                equation.pop_front();
            }
            equation.pop_front();
            o2 = solveEquation2(newEq);
        }

        // we should have two elements in the deque
        if(op == "*")
        {
            equation.push_front(std::to_string(o2));
            mulOnlyEquation.push_back(std::to_string(o1));
            mulOnlyEquation.push_back(op);
        }
        else if(op == "+")
        {
            equation.push_front(std::to_string(o1+o2));
        }

    }

    mulOnlyEquation.push_back(equation.front());
    equation.pop_front();

    return solveEquation(mulOnlyEquation);
}


int64_t part_one(const std::vector<std::string>& lines)
{
    int64_t sum = 0;
    for(auto& line: lines)
    {
        std::deque<std::string> equation;
        for(char c: line)
        {
            if (c == ' ')
                continue;
            equation.push_back(std::string(1, c));
        }

        sum += solveEquation(equation);
    }
    return sum;
}

int64_t part_two(const std::vector<std::string>& lines)
{
    int64_t sum = 0;
    for(auto& line: lines)
    {
        std::deque<std::string> equation;
        for(char c: line)
        {
            if (c == ' ')
                continue;
            equation.push_back(std::string(1, c));
        }

        sum += solveEquation2(equation);
    }
    return sum;
}

int main()
{
    std::vector<std::string> input_lines = read_file_line_by_line("input");

    std::cout << "Part1: \n" << part_one(input_lines) << std::endl;
    std::cout << "Part2: \n" << part_two(input_lines) << std::endl;
    

}
