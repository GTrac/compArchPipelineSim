#include <iostream>
#include <string>
#include "instructionEvent.h"


instruction_event::instruction_event(std::string instruction,signed int registers[3])
{
    this->stage = "fetch";
    this->instruction = instruction;
    this->registers[0] = registers[0];
    this->registers[1] = registers[1];
    this->registers[2] = registers[2];
}

void instruction_event::next_stage()//fetch>decode>execute>write
{
    if(this->stage == "fetch")
    {
        this->stage = "decode";
    }
    else if(this->stage == "decode")
    {
        this->stage = "execute";
    }
    else if(this->stage == "execute")
    {
        this->stage = "write";
    }
    else if(this->stage == "write")
    {
        std::cout << "ERROR NO STAGE AFTER WRITE" << std::endl;
    }
}

std::string instruction_event::get_stage()
{
    return this->stage;
}

std::string instruction_event::get_instruction()
{
    return this->instruction;
}

        
signed int instruction_event::get_registers(int i)
{
    return this->registers[i];
}

void instruction_event::print_instruction()
{
    if(this->instruction == "stall" | this->instruction == "halt"){
        std::cout << "(" << this->instruction << ")";
    }else{
        std::cout << "(" << this->instruction << " ";
        std::cout << this->registers[0] << " ";
        std::cout << this->registers[1] << " ";
        std::cout << this->registers[2] << ")";
    }
     
}
