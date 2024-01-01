#include "Processor.h"


Processor::Processor(){
    PC = 0;
    cycle = 0;
}

void Processor::load_program(string program){
    istringstream iss(program);
    string line;

    while(getline(iss,line)){
        inst_mem.push_back(line);
		cout << line << '\n';
    }
}

void Processor::fetch(){
    ifid.line = inst_mem[PC];
    ifid.PC = ++PC;
}

void Processor::decode(){
    istringstream iss(ifid.line);
    instruction istr;
    string opcode;
    bool hazard;

    idex.PC = ifid.PC;
    iss >> opcode;
    //R-type inst
    if(opcode == "ADD"){
        istr.opcode_ = op::ADD;
        iss >> istr.rd_ >> istr.rs_ >> istr.rt_;
        idex.A = reg[reg_to_num(istr.rs_, 1)];
        idex.B = reg[reg_to_num(istr.rt_, 1)];
        idex.Rd = reg[reg_to_num(istr.rd_, 1)];
    }
    else if(opcode == "SUB"){
        istr.opcode_ = op::SUB;
        iss >> istr.rd_ >> istr.rs_ >> istr.rt_;
        idex.A = reg[reg_to_num(istr.rs_, 1)];
        idex.B = reg[reg_to_num(istr.rt_, 1)];
        idex.Rd = reg[reg_to_num(istr.rd_, 1)];
    }
    else if(opcode == "MUL"){
        istr.opcode_ = op::MUL;
        iss >> istr.rd_ >> istr.rs_ >> istr.rt_;
        idex.A = reg[reg_to_num(istr.rs_, 1)];
        idex.B = reg[reg_to_num(istr.rt_, 1)];
        idex.Rd = reg[reg_to_num(istr.rd_, 1)];
    }
    else if(opcode == "SLT"){
        istr.opcode_ = op::SLT;
        iss >> istr.rd_ >> istr.rs_ >> istr.rt_;
        idex.A = reg[reg_to_num(istr.rs_, 1)];
        idex.B = reg[reg_to_num(istr.rt_, 1)];
        idex.Rd = reg_to_num(istr.rd_, 1);
    }
    //I-type
    else if(opcode == "ADDI"){
        istr.opcode_ = op::ADDI;
        iss >> istr.rt_ >> istr.rs_ >> istr.immediate_;
        idex.Rt = reg_to_num(istr.rt_, 1);
        idex.A = reg[reg_to_num(istr.rs_, 1)];
        idex.imm = reg_to_num(istr.immediate_, 0);
    }
    else if(opcode == "LW"){
        istr.opcode_ = op::LW;
        iss >> istr.rt_ >> istr.immediate_;
        idex.Rt = reg_to_num(istr.rt_, 1);
        idex.A = reg[ reg_to_num(istr.immediate_, istr.immediate_.find('$') + 1, istr.immediate_.find(')') - istr.immediate_.find('$') - 1) ];
        idex.imm = reg_to_num(istr.immediate_, 0, istr.immediate_.find('('));
    }
    else if(opcode == "SW"){
        istr.opcode_ = op::SW;
        iss >> istr.rt_ >> istr.immediate_;
        idex.A = reg[ reg_to_num(istr.immediate_, istr.immediate_.find('$') + 1, istr.immediate_.find(')') - istr.immediate_.find('$') - 1) ];
        idex.B = reg[reg_to_num(istr.rt_, 1)];
        idex.imm = reg_to_num(istr.immediate_, 0, istr.immediate_.find('('));
    }
    else if(opcode == "BEQ"){
        istr.opcode_ = op::BEQ;
        iss >> istr.rs_ >> istr.rt_ >> istr.immediate_;
        idex.A = reg[reg_to_num(istr.rs_, 1)];
        idex.B = reg[reg_to_num(istr.rt_, 1)];
        idex.imm = reg_to_num(istr.immediate_, 1);
    }
    else if(opcode == "BNE"){
        istr.opcode_ = op::BNE;
        iss >> istr.rs_ >> istr.rt_ >> istr.immediate_;
        idex.A = reg[reg_to_num(istr.rs_, 1)];
        idex.B = reg[reg_to_num(istr.rt_, 1)];
        idex.imm = reg_to_num(istr.immediate_, 1);
    }
    else if(opcode == "J"){
        istr.opcode_ = op::J;
        iss >> istr.immediate_;
        idex.imm = reg_to_num(istr.immediate_, 1);
    }
    else if(opcode == "JAL"){
        istr.opcode_ = op::JAL;
        iss >> istr.immediate_;
        idex.imm = reg_to_num(istr.immediate_, 1);
    }
    else{
        cout << "unknown";
        exit(1);
    }

    //todo : stall
    //idex = 0 and no PC update and no ifid update
    //https://gofo-coding.tistory.com/entry/Data-Hazard#title-11
    hazard = hazard_detect(istr);
    idex.istr = istr;
}

void Processor::execute(){
    switch (idex.istr.opcode_)
    {
    case op::ADD:
        exmem.AR = idex.A + idex.B;
        exmem.Rd = idex.Rd;
        break;
    case op::SUB:
        exmem.AR = idex.A - idex.B;
        exmem.Rd = idex.Rd;
        break;
    case op::MUL:
        exmem.AR = idex.A * idex.B;
        exmem.Rd = idex.Rd;
        break;
    case op::SLT:
        exmem.AR = idex.A < idex.B ? 1 : 0;
        exmem.Rd = idex.Rd;
        break;
    case op::ADDI:
        exmem.AR = idex.A + idex.B;
        exmem.Rd = idex.Rd;
        break;
    case op::LW:
        exmem.AR = idex.A + idex.imm;
        exmem.Rd = idex.Rt;
        break;
    case op::SW:
        exmem.AR = idex.A + idex.imm;
        exmem.B = idex.B;
        break;
    case op::BEQ:
        exmem.PC = idex.PC + idex.imm;
        exmem.Z = (idex.A == idex.B);
        break;
    case op::BNE:
        exmem.PC = idex.PC + idex.imm;
        exmem.Z = (idex.A == idex.B);
        break;
    case op::J:
        PC = idex.imm;
        break;
    case op::JAL:
        reg[31] = PC;
        PC = idex.imm;
        break;
    default:
        break;
    }
    exmem.istr = idex.istr;
}

void Processor::mem(){
    switch (exmem.istr.opcode_)
    {
    case op::ADD: case op::SUB:
    case op::MUL: case op::SLT:
        memwb.AR = exmem.AR;
        memwb.Rd = exmem.Rd;
        break;
    case op::ADDI:
        memwb.AR = exmem.AR;
        memwb.Rd = exmem.Rd;
        break;
    case op::LW:
        memwb.LR = data_mem[exmem.AR];
        memwb.Rd = exmem.Rd;
        break;
    case op::SW:
        data_mem[exmem.AR] = exmem.B;
        break;
    case op::BEQ:
        if(exmem.Z == 1)
            PC = exmem.PC;
        break;
    case op::BNE:
        if(exmem.Z != 1)
            PC = exmem.PC;
        break;
    case op::J:
        break;
    case op::JAL:
        break;
    default:
        break;
    }
    memwb.istr = exmem.istr;
}

void Processor::write_back(){
    switch (memwb.istr.opcode_)
    {
    case op::ADD: case op::SUB:
    case op::MUL: case op::SLT:
        reg[memwb.Rd] = memwb.AR;
        break;
    case op::ADDI:
        reg[memwb.Rd] = memwb.AR;
        break;
    case op::LW:
        reg[memwb.Rd] = memwb.LR;
        break;
    case op::SW:
        break;
    case op::BEQ:
        break;
    case op::BNE:
        break;
    case op::J:
        break;
    case op::JAL:
        break;
    default:
        break;
    }
}

//load-use case hazard
//I-type op rt imm
//R-type op rd rs rt
bool Processor::hazard_detect(instruction in){
    if(idex.istr.opcode_ == op::LW){
        if(idex.Rt == reg_to_num(in.rs_, 1) || idex.Rt == reg_to_num(in.rt_, 1)){
            //hazard!
            return true;
        }
    }
    return false;
}

void Processor::run(){
    write_back();
    mem();
    execute();
    decode();
    fetch();
    cycle++;
}