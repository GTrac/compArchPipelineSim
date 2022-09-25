#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include "enums.h"

class instruction_event{
    private:
        stage_t stage;
        instruction_t instruction;
        signed int registers[3];

    public:
        instruction_event(instruction_t instruction, signed int registers[3]);

        void next_stage();

        stage_t get_stage();

        instruction_t get_instruction();  

        signed int get_registers(int i);

        void print_instruction();

};

#endif