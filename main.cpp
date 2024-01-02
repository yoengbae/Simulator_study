#include "Processor.h"

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 3) {
        cout << "Usage: " << "<reg filename> <mem filename>\n";
        return 1;
    }
    //assume
    //register : $n
    //no label
    string factorial = 
    "LW $9, 0\n"
    "LW $11, 4\n"
    "BEQ $8, $0, 3\n"//goto SW
    "MUL $9, $9, $8\n"
    "ADDI $8, $8, -1\n"
    "J 2\n"//goto BEQ
    "SW $11 0($10)\n";

    Processor p = Processor(argv[1], argv[2]);
    p.load_program(factorial);
    p.run();
	getchar();

}