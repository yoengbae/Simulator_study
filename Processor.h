#include <cstdint>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "instruction.h"

using namespace std;

struct IF_ID{
    uint32_t PC;
    string line;
};

struct ID_EX{
    uint32_t PC;
    uint32_t A, B;
    uint32_t imm;
    uint32_t Rd, Rt;
    instruction istr;
};

struct EX_MEM{
    uint32_t PC;
    uint32_t AR;
    uint32_t Z;
    uint32_t B;
    uint32_t Rd;
    instruction istr;
};

struct MEM_WB{
    uint32_t AR;
    uint32_t Rd;
    uint32_t LR;
    instruction istr;
};


class Processor {
    public:
        Processor();
        void Init_data_mem_state();
        void Init_regs_state();

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
        uint32_t reg[31];

        //Special-Purpose Registers
        uint32_t PC;
        //uint32_t HI;
        //uint32_t LO;

        //pipeline registers
        IF_ID ifid;
        ID_EX idex;
        EX_MEM exmem;
        MEM_WB memwb;

        vector<string> inst_mem;
        uint32_t data_mem[1024];
        uint32_t cycle;
};