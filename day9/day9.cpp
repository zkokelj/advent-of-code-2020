#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

unsigned long long sum_list(const std::vector<unsigned long long>& numbers, int start, int end)
{
    unsigned long long sum = 0;
    for(int i = start; i < end; i++)
    {
        sum += numbers[i];
    }
    return sum;
}

std::tuple<unsigned long long, unsigned long long> return_min_max(const std::vector<unsigned long long>& numbers, int start, int end)
{
    unsigned long long min = numbers[start];
    unsigned long long max = numbers[start];

    for(int i = start; i < end; i++)
    {
        if (numbers[i] < min)
        {
            min = numbers[i];
        }else if(numbers[i] > max)
        {
            max = numbers[i];
        }
    }
    return std::make_tuple(min, max);
}

std::tuple<unsigned long long, int> part_one(const std::vector<unsigned long long>& numbers, int preamble)
{
    for(int i =preamble; i < numbers.size(); i++)
    {
        unsigned long long number = numbers[i];

        bool found = false;
        for(int j = i-preamble; j < i; j++)
        {
            for(int k = i-preamble; k < i; k++)
            {
                if(numbers[j]+numbers[k] == number)
                {
                    found = true;
                    break;
                }
                if (found)
                {
                    break;
                }
            }
        }
        if (!found)
        {
            return std::make_tuple(number, i);
        }
    }

    return std::make_tuple(0, 0);
}

unsigned long long part_two(const std::vector<unsigned long long>& numbers, int index)
{
    unsigned long long n = numbers[index];

    unsigned long long min;
    unsigned long long max;

    for(int i = 0; i < index; i++)
    {
        for(int j = i+1; j < index; j++)
        {
            unsigned long long sum = sum_list(numbers, i, j);
            if (sum == n)
            {
                std::tie(min, max) = return_min_max(numbers, i, j);
                return min+max;
            }else if(sum > n)
            {
                break;
            }
        }
    }

    return 0;
}


int main()
{
   std::vector<unsigned long long> numbers;
   std::ifstream in("input",std::ios::in);
   unsigned long long number; // to hold each number
	
    //Read number with >> operator
    while (in >> number)
    {
        //Add number to the vector
        numbers.push_back(number);
	}
    in.close(); // close file stream

    unsigned long long n;
    int index;
    std::tie(n, index) = part_one(numbers, 25);

    std::cout << "Part one: " << n << " at inde: " << index << std::endl;

    //std::cout << "Sum: " << sum_list(numbers, 0, 3) << std::endl;
    unsigned long long min;
    unsigned long long max;
    std::tie(min, max) = return_min_max(numbers, 0, 3);

    //std::cout << min << " and " << max << std::endl;

    std::cout << "Part two: " << part_two(numbers, index);
}