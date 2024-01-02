#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "instruction.h"

using namespace std;

struct IF_ID{
    int PC;
    string line;
};

struct ID_EX{
    int PC;
    int A, B;
    int imm;
    int Rd, Rt;
    instruction istr;
};

struct EX_MEM{
    int PC;
    int AR;
    int Z;
    int B;
    int Rd;
    instruction istr;
};

struct MEM_WB{
    int AR;
    int Rd;
    int LR;
    instruction istr;
};


class Processor {
    public:
        Processor(string re, string me);
        void Init_data_mem_state(string re);
        void Init_regs_state(string me);

        void load_program(string program);

        void fetch();
        void decode();
        void execute();
        void mem();
        void write_back();

        bool hazard_detect(instruction in);
        void run();
        

    private:
        //GP Registers
        //r0 : zero
        //r31 : destination
        int reg[31];

        //Special-Purpose Registers
        int PC;
        //int HI;
        //int LO;

        //pipeline registers
        IF_ID ifid;
        ID_EX idex;
        EX_MEM exmem;
        MEM_WB memwb;

        vector<string> inst_mem;
        int data_mem[1024];
        int cycle;
};