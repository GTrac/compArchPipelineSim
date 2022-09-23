#include <queue>
#include <iostream>
#include <chrono>
#include <ctime> 
#include <vector>
#include <string>
#include <list>
#include "enums.h"
#include "instructionEvent.h"

using namespace std;

void create_instruction_set(queue<instruction_event> queue);

int main(){
    long int clock_cycle = 0;
    float f[32];
    float x[32];
    float hold;
    
    //instructions to add
    signed char instruction_1[3]= {0,1,0};
    signed char instruction_2[3]= {0,1,0};
    signed char instruction_3[3]= {0,1,0};
    signed char instruction_4[3]= {0,1,0};
    signed char instruction_5[3]= {0,1,0};

    //create instruction list
    instruction_event instruction_list[] = {instruction_event(load, instruction_1), instruction_event(add, instruction_2), instruction_event(store, instruction_3), instruction_event(addi, instruction_4), instruction_event(bne, instruction_5)};
    //queue for pipeline stages
    queue<instruction_event> pipeline;
    unsigned int i = 0;
    while( i < sizeof(instruction_list) ){// fetch>decode>execute>memory>write
        for(int j = 0; j < pipeline.size(); j++){
            switch(pipeline.front().get_stage()){
                case write:

                case memory:

                case execute:

                case decode:

                case fetch:
            }
            
        }
        pipeline.push(instruction_list[i]); //FETCH
        clock_cycle++;
    }
}
//x1 = 20
//x2 = 0

// void create_instruction_set(queue<instruction_event> queue)
// {
//     //load 0,1,0
//     signed char instruction_1[3]= {0,1,0};
//     queue.emplace(load, instruction_1);
//     //add 4,0,2
//     signed char instruction_2[3]= {0,1,0};
//     queue.emplace(load, instruction_2);
//     //store 4 1
//     signed char instruction_3[3]= {0,1,0};
//     queue.emplace(load, instruction_3);
//     //addi 1,1,-1
//     signed char instruction_4[3]= {0,1,0};
//     queue.emplace(load, instruction_4);
// }