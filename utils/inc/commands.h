#ifndef COMMANDS_H
#define COMMANDS_H

static const int COMMANDS_AMOUNT = 27;


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>


struct Command
{
    int number;
    const char * name[10];
};

struct Line
{
    size_t len = 0;
    char * ptr = 0;
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
    {HLT,    "HLT"},
    {PUSH,   "PUSH"},
    {PUSHR,  "PUSHR"},
    {PUSHM,  "PUSHM"},
    {PUSHRM, "PUSHRM"},
    {POP,    "POP"},
    {POPR,   "POPR"},
    {POPM,   "POPM"},
    {JMP,    "JMP"},
    {JA,     "JA"},
    {JAE,    "JAE"},
    {JB,     "JB"},
    {JBE,    "JBE"},
    {JE,     "JE"},
    {JNE,    "JNE"},
    {ADD,    "ADD"},
    {SUB,    "SUB"},
    {MUL,    "MUL"},
    {DIV,    "DIV"},
    {SQRT,   "SQRT"},
    {POW,    "POW"},
    {LN,     "LN"},
    {SIN,    "SIN"},
    {COS,    "COS"},
    {CALL,   "CALL"},
    {RET,    "RET"},
    {OUT,    "OUT"}
};

enum Registers
{
    AX = 1,
    BX = 2,
    CX = 3,
    DX = 4
};

#endif