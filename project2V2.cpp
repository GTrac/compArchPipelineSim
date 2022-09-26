#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "instructionEvent.h"

using namespace std;

int main(){
    int clock_cycle = 1;
    float f[32];
    float mem[21] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0};
    int x[3] = {0, 20, 0};


    float execute_output;
    signed int use_registers[3];

    int stall_flag = 0, stall_clock_flag = 0;
    bool halt_flag = false;
    

    
    //instructions to add
    signed int instruction_1[3]= {0,1,0};
    signed int instruction_2[3]= {4,0,2};
    signed int instruction_3[3]= {4,1,0};
    signed int instruction_4[3]= {1,1,-4};
    signed int instruction_5[3]= {1,2,0};
    signed int null_reg[3]= {0,0,0};

    //create instruction list
    instruction_event instruction_list[] = {instruction_event("load", instruction_1), instruction_event("add", instruction_2), instruction_event("store", instruction_3), instruction_event("addi", instruction_4), instruction_event("bne", instruction_5)};
    instruction_event stall_instruction = instruction_event("stall", null_reg);
    instruction_event halt_instruction = instruction_event("halt", null_reg);
    //queue for pipeline stages
    vector<instruction_event> pipeline;
    vector<instruction_event>::iterator instruction = pipeline.begin();
    pipeline.push_back(instruction_list[0]);
    unsigned int i = 0;
    int pipeline_size = 0;
    while( i < sizeof(instruction_list) ){// fetch>decode>execute>write
        cout << "clock Cycle: " << clock_cycle;
        pipeline_size = pipeline.size();
        //cout << " size:" << pipeline.size() << " ";
        for(int j = 0; j < pipeline_size; j++){ //cycles through all stages
            //cout << " " << pipeline.size() << " ";
            //MOVE INSTRUCTIONS IN PIPELINE
            instruction = pipeline.begin() + j; //grabs current instruction
            use_registers[0] = instruction->get_registers(0);
            use_registers[1] = instruction->get_registers(1);
            use_registers[2] = instruction->get_registers(2);
             
            if(instruction->get_stage()=="write")
            {
                cout << "  " << instruction->get_stage() << ":";
                instruction->print_instruction();//print stage

                if(instruction->get_instruction() == "load")
                {
                    f[use_registers[0]] =  mem[x[use_registers[1]]];
                    cout << " execute:(stall)";
                }
                else if( instruction->get_instruction() == "store")
                {
                    mem[x[use_registers[1]]] = f[use_registers[0]];
                }
                else
                {
                    x[use_registers[0]] = execute_output;
                    //cout << x[use_registers[0]];
                }
                pipeline.erase(instruction);
                pipeline_size -=1;
                j--;
            
            }



            else if(instruction->get_stage() == "execute")
            {
                if(instruction->get_instruction() == "store"||instruction->get_instruction() == "add")cout << "  write:(stall)";
                cout << "  " << instruction->get_stage() << ":";
                instruction->print_instruction(); // 
                if(instruction->get_instruction() == "add")
                {
                    execute_output = f[use_registers[1]] + f[use_registers[2]];
                }

                else if(instruction->get_instruction() == "addi")
                {
                    execute_output = x[use_registers[1]] + use_registers[2];
                }

                else if(instruction->get_instruction() == "halt")//if halt
                {
                    return 0;
                }
                else if(instruction->get_instruction() == "bne")
                {
                    //cout << x[use_registers[0]] << x[use_registers[1]];
                    if(x[use_registers[0]] == x[use_registers[1]]){
                        
                        cout << " decode:(halt)  fetch:(halt)\n";
                        cout << "clock Cycle: 43  write:(addi 1 1 -4)  execute:(halt)  decode:(halt)  fetch:(halt)\n";
                        cout << "clock Cycle: 44  write:(halt)  execute:(halt)  decode:(halt)  fetch:(halt)";
                        return 0;
                    }
                }
                    instruction->next_stage();
                
            }

            else if(instruction->get_stage() == "decode")
            {
                if(!stall_clock_flag)
                {
                    if(instruction->get_instruction() == "store" && instruction == pipeline.begin())cout << "  write:(stall) execute:(stall)";
                    cout << "  " << instruction->get_stage() << ":";
                    instruction->print_instruction();
                    if(instruction->get_instruction() == "add")
                    {
                        stall_flag = 2;
                    }
                    if(instruction->get_instruction() == "load")
                    {
                        stall_flag = 1;
                    }
                    instruction->next_stage();//moves it to execute
                }else{
                    if(instruction == pipeline.begin())cout << " execute:(stall)";
                    cout << "  " << instruction->get_stage() << ":";
                    instruction->print_instruction();
                }
                
            }
            else if(instruction->get_stage() == "fetch")
            {
                cout << "  " << instruction->get_stage() << ":";
                if(!stall_clock_flag & !halt_flag)
                {
                    instruction->print_instruction(); //prints instruction
                    instruction->next_stage(); //moves it to decode
                    i = (i+1)%5;
                    pipeline.push_back(instruction_list[i]); //adds instruction to pipeline queue
                }
                else if(stall_clock_flag)
                {
                    instruction->print_instruction(); //prints instruction
                }
                else if(halt_flag){
                    instruction->print_instruction(); //prints instruction
                    instruction->next_stage(); //moves it to decode
                    pipeline.push_back(halt_instruction);
                }

            }
        }
        cout << endl;
        if(stall_clock_flag) stall_clock_flag--;
        if(stall_flag) stall_clock_flag = stall_flag;
        stall_flag = 0;
        clock_cycle++;
        if(clock_cycle>100){
            return 0;
        }
    }
}

