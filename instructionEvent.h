#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include <string>


class instruction_event{
    private:
        std::string stage;
        std::string instruction;
        signed int registers[3];

    public:
        instruction_event(std::string instruction, signed int registers[3]);

        void next_stage();

        std::string get_stage();

        std::string get_instruction();  

        signed int get_registers(int i);

        void print_instruction();

};

#endif