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
    JAL
};

struct instruction
{
    op opcode_;
    string rs_, rd_, rt_, immediate_;
        
};

uint32_t reg_to_num(string s, int pos){
    string ss = s.substr(pos);
    return stoi(ss);
}

uint32_t reg_to_num(string s, int pos, int cnt){
    string ss = s.substr(pos, cnt);
    return stoi(ss);
}