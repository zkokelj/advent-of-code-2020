#include <iostream>
#include <fstream>
#include <vector>


unsigned long long part_one(const std::vector<unsigned long long>& numbers, int preamble)
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
            return number;
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

    std::cout << "Part one: " << part_one(numbers, 25) << std::endl;

}