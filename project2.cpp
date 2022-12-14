#include <deque>
#include <iostream>
#include <chrono>
#include <ctime> 
#include <vector>
#include <string>
#include <list>
#include "instructionEvent.h"

using namespace std;

int main(){
    long int clock_cycle = 1;
    float f[32];
    float mem[21] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0};
    int x[3] = {0, 20, 0};


    float execute_output;
    signed int use_registers[3];

    bool stall_flag = false, halt_flag = false;
    

    
    //instructions to add
    signed int instruction_1[3]= {0,1,0};
    signed int instruction_2[3]= {0,1,0};
    signed int instruction_3[3]= {0,1,0};
    signed int instruction_4[3]= {0,1,0};
    signed int instruction_5[3]= {0,1,0};
    signed int null_reg[3]= {0,0,0};

    //create instruction list
    instruction_event instruction_list[] = {instruction_event("load", instruction_1), instruction_event("add", instruction_2), instruction_event("store", instruction_3), instruction_event("addi", instruction_4), instruction_event("bne", instruction_5)};
    instruction_event *instruction_from_list, *instruction, *new_instruction;
    instruction_event *stall_instruction = new instruction_event("stall", null_reg);
    instruction_event *halt_instruction = new instruction_event("halt", null_reg);
    instruction_from_list = &instruction_list[0];
    //queue for pipeline stages
    deque<instruction_event*> pipeline;
    instruction_from_list->print_instruction();
    unsigned int i = 1;
    while( i < sizeof(instruction_list) ){// fetch>decode>execute>memory>write
        cout << "clock Cycle: " << clock_cycle;
        for(int j = 0; j < pipeline.size(); j++){ //cycles through all stages
            
            //MOVE INSTRUCTIONS IN PIPELINE
            instruction = pipeline.front(); //grabs current instruction
            use_registers[0] = instruction->get_registers(0);
            use_registers[1] = instruction->get_registers(1);
            use_registers[2] = instruction->get_registers(2);
            cout << "  " << instruction->get_stage();
             
            if(instruction->get_stage()=="memory")
            {
                instruction->print_instruction();//print stage

                if(instruction->get_instruction() == "load")
                {
                    f[use_registers[0]] =  mem[x[use_registers[1]]];
                }
                else if( instruction->get_instruction() == "store")
                {
                    mem[x[use_registers[1]]] = f[use_registers[0]];
                }
                else
                {
                    f[use_registers[0]] = execute_output;
                }
                pipeline.pop_front();
            }



            else if(instruction->get_stage() == "execute")
            {
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

                instruction->next_stage();
                pipeline.push_back(instruction);
                pipeline.pop_front();
            }
            else if(instruction->get_stage() == "decode")
            {
                instruction->print_instruction();
                    //if(instruction->)
                    

            }
            else if(instruction->get_stage() == "decode")
                case "fetch"://fetch new instruction
                    if(!stall_flag & !halt_flag)
                    {
                        instruction->print_instruction(); //prints instruction
                        instruction->next_stage(); //moves it to decode
                        pipeline.push_back(instruction); //adds copy to back to bottom of queue
                        pipeline.pop_front(); //removes original at top of queue
                        
                        i++;
                        new_instruction = instruction_from_list + i; //grabs next instruction in instruction list
                        new_instruction->next_stage(); //sets new instruction to fetch stage
                        pipeline.push_back(new_instruction); //adds instruction to pipeline queue
                    }
                    if(stall_flag)
                    {
                        pipeline.push_back(instruction);
                        pipeline.pop_front();
                        //pipeline.push_front(stall);
                        pipeline.front()->print_instruction();
                        break;
                    }
                    // if(halt_flag)
                    // {
                    //     if(instruction->get_instruction() != halt)//if instruction isnt halt then flush instructions in
                    //      queue
                    //     {
                    //         while(!pipleline.empty()){
                    //             pipeline.pop_front();
                    //         }
                    //     }
                        
                        //pipeline.push_front(halt_instruction);
                        pipeline.front()->print_instruction();
                        break;
            }
        } 
        clock_cycle++;
        cout << "\n";
        if(clock_cycle > 50){
            return 0;
        }
    }
}

