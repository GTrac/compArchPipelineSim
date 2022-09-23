#ifndef ENUMS_H_
#define ENUMS_H_

typedef enum{
    none, fetch, decode, execute, memory, write
} stage_t;

typedef enum{
    load,
    add,
    store,
    addi,
    bne,
    stall
} instruction_t;

#endif