#ifndef COMMANDS_H
#define COMMANDS_H

static const int COMMANDS_AMOUNT = 27;

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

struct Line
 {
     size_t len = 0;
     char * ptr = 0;
 };

struct Command
{
    int number;
    int args_amount;
    const char * name[10];
};

enum CommandCodes 
{
    HLT      = 0,
    PUSH     = 10,
    PUSHR    = 11,  //
    PUSHM    = 12,  //
    PUSHRM   = 13,  //
    POP      = 20,
    POPR     = 21,  //
    POPM     = 22,  //
    JMP      = 30,  //
    JA       = 31,  //
    JAE      = 32,  //
    JB       = 33,  //
    JBE      = 34,  //
    JE       = 35,  //
    JNE      = 36,  //
    ADD      = 40,
    SUB      = 41,
    MUL      = 42,
    DIV      = 43,
    SQRT     = 44,
    POW      = 45,  //
    LN       = 46,  //
    SIN      = 47,
    COS      = 48,
    CALL     = 5,   //
    RET      = 6,   //
    OUT      = 7    //
};

Command Commands[COMMANDS_AMOUNT] =
{
    {HLT,       0,    "HLT"},
    {PUSH,      1,    "PUSH"},
    {PUSHR,     2,    "PUSHR"},
    {PUSHM,     2,    "PUSHM"},
    {PUSHRM,    2,    "PUSHRM"},
    {POP,       0,    "POP"},
    {POPR,      1,    "POPR"},
    {POPM,      1,    "POPM"},
    {JMP,       1,    "JMP"},
    {JA,        1,    "JA"},
    {JAE,       1,    "JAE"},
    {JB,        1,    "JB"}, 
    {JBE,       1,    "JBE"}, 
    {JE,        1,    "JE"},  
    {JNE,       1,    "JNE"}, 
    {ADD,       0,    "ADD"}, 
    {SUB,       0,    "SUB"}, 
    {MUL,       0,    "MUL"}, 
    {DIV,       0,    "DIV"}, 
    {SQRT,      0,    "SQRT"},
    {POW,       0,    "POW"}, 
    {LN,        0,    "LN"},  
    {SIN,       0,    "SIN"}, 
    {COS,       0,    "COS"}, 
    {CALL,      1,    "CALL"},
    {RET,       1,    "RET"}, 
    {OUT,       1,    "OUT"},
};

enum Registers
{
    AX = 0,
    BX = 1,
    CX = 2,
    DX = 3
};

#endif