#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

struct InstructionLine
{
    std::string instr;
    int val;
};


int part_one(const std::vector<InstructionLine>& instructions)
{
    int accumulator = 0;
    bool access_control[instructions.size()] = { false };
    int instruction_pointer = 0;

    while (instruction_pointer < instructions.size())
    {
        InstructionLine current = instructions[instruction_pointer];
        if (access_control[instruction_pointer])
        {
            // in a loop!
            return accumulator;
        }
        // mark that we were here
        access_control[instruction_pointer] = true;

        // do described things with the instructions
        if (current.instr == "jmp")
        {
            instruction_pointer += current.val;
        }else if(current.instr == "acc")
        {
            accumulator += current.val;
            instruction_pointer++;
        }else if(current.instr == "nop")
        {
            instruction_pointer++;
        }

    }
    return accumulator;
}

int part_two(std::vector<InstructionLine> instrs)
{
    //loop over all instructions and change one...
    for(int i = 0; i < instrs.size(); i++)
    {   
        std::vector<InstructionLine> instructions = instrs; // make a deep copy of vector
        //prevent changing acc
        if(instructions[i].instr == "acc")
        {
            continue;
        }else if(instructions[i].instr == "jmp")
        {
            //std::cout << "jmp->nop: " << i << std::endl;
            instructions[i].instr = "nop";
        }else if(instructions[i].instr == "nop"){
            //std::cout << "nop->jmp: " << i << std::endl;
            instructions[i].instr = "jmp";   
        }

        int accumulator = 0;
        bool access_control[instructions.size()] = { false };
        int instruction_pointer = 0;

        while (instruction_pointer < instructions.size())
        {
            InstructionLine current = instructions[instruction_pointer];
            if (access_control[instruction_pointer])
            {
                // in a loop -> try next combination!
                break;
            }
            // mark that we were here
            access_control[instruction_pointer] = true;

            // do described things with the instructions
            if (current.instr == "jmp")
            {
                instruction_pointer += current.val;
            }else if(current.instr == "acc")
            {
                accumulator += current.val;
                instruction_pointer++;
            }else if(current.instr == "nop")
            {
                instruction_pointer++;
            }
        }

        // we came to the end
        if(instruction_pointer == instructions.size())
        {
            return accumulator;
        }
    }
    return -1;
}

int main()
{
    // read file into list of InstructionLine structs
    std::ifstream file{};
    file.open("input");
    if (!file.is_open())
    {
        throw std::runtime_error("Specified file not found.");
    }

    std::vector<InstructionLine> result;
    std::string buffer;

    while (std::getline(file, buffer)) {
        //std::cout << buffer << std::endl;

        // split by space
        std::vector<std::string> tokens;
        std::istringstream iss(buffer);
        std::copy(std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>(),
        std::back_inserter(tokens));

        result.emplace_back(InstructionLine{tokens[0], std::stoi(tokens[1])});
        
    }

    // run part one
    std::cout << "Part1: " << part_one(result) << std::endl;

    //run part two
    std::cout << "Part2: " << part_two(result) << std::endl;

}