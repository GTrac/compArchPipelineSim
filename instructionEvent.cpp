#include <iostream>
#include <string>
#include "instructionEvent.h"


instruction_event::instruction_event(std::string instruction,signed int registers[3])
{
    this->stage = none;
    this->instruction = instruction;
    this->registers[0] = registers[0];
    this->registers[1] = registers[1];
    this->registers[2] = registers[2];
}

void instruction_event::next_stage()
{
    switch ( this->stage )
    {
        case none:
            this->stage = "fetch";
            break;
        case fetch:
            this->stage = "decode";
            break;
        case decode:
            this->stage = "execute";
            break;
        case execute:
            this->stage = "memory";
            break;
        case memory:
            this->stage = "write";
            break;
        default:
            this->stage = "none";
            std::cout << "ERROR: NON VALID STAGE" << std::endl;
            break;
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
