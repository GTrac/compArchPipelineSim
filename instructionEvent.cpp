#include <iostream>
#include <string>
#include "instructionEvent.h"
#include "enums.h"


instruction_event::instruction_event(instruction_t instruction,signed char instruction_registers[3])
{
    this->stage = none;
    this->instruction = instruction;
    this->instruction_registers[0] = instruction_registers[0];
    this->instruction_registers[1] = instruction_registers[1];
    this->instruction_registers[2] = instruction_registers[2];
}

void instruction_event::next_stage()
{
    switch ( this->stage )
    {
        case none:
            this->stage = fetch;
            break;
        case fetch:
            this->stage = decode;
            break;
        case decode:
            this->stage = execute;
            break;
        case execute:
            this->stage = memory;
            break;
        case memory:
            this->stage = write;
            break;
        default:
            this->stage = none;
            std::cout << "ERROR: NON VALID STAGE" << std::endl;
            break;
    }
}

stage_t instruction_event::get_stage()
{
    return this->stage;
}

instruction_t instruction_event::get_instruction()
{
    return this->instruction;
}

        

