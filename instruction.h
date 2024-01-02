#include <cstdint>
#include <string>

using namespace std;

enum class op {
    ADD,
    SUB,
    MUL,
    ADDI,
    LW,
    SW,
    BEQ,
    BNE,
    SLT,
    J,
    JAL,
    NOP
};

struct instruction
{
    op opcode_;
    string rs_, rd_, rt_, immediate_;
        
};

int reg_to_num(string s, int pos);

int reg_to_num(string s, int pos, int cnt);