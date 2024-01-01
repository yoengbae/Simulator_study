#include <vector>
#include <string>
#include <iostream>
#include "Processor.h"

using namespace std;

int main(){

    //assume
    //register : $n
    //no label
    string factorial = 
    "LW $9, 0\n"
    "LW $11, 4\n"
    "BEQ $8, $0, 6\n"
    "MUL $9, $9, $8\n"
    "ADDI $8, $8, -1\n"
    "J 2\n"
    "SW $11 0($10)\n";

    Processor p = Processor();
    p.load_program(factorial);
	getchar();

}