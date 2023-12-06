#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

//count up when enabled, count down when NOT enabled
int main(int argc, char **argv, char **env) {
    int i;          // i counts # of clock cycles to simulate
    int clk;        // clk is the module clock signal

    Verilated::commandArgs(argc,argv);
    Vcounter* top = new Vcounter;
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");

    if (vbdOpen()!=1) return(-1);
    vbdHeader("Lab 1: Counter");

    top->clk = 1;
    top->rst = 0;
    top->en = 0;

    for (i=0; i<300; i++)   {

        for (clk=0; clk<2; clk++)   {
            tfp->dump (2*i + clk);
            top->clk = !top->clk;
            top->eval ();
        }

        vbdHex(4, (int(top->count) >> 16) & 0xF);
        vbdHex(3, (int(top->count) >> 8) & 0xF);
        vbdHex(2, (int(top->count) >> 4) & 0xF);
        vbdHex(1, (int(top->count) & 0xF));
        vbdCycle(i+1);
        
        top->rst = (i < 2);
        top->en = vbdFlag();
        if (Verilated::gotFinish())     exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}





/*
// Modify the testbench so that you stop counting for 3 cycles once the counter reaches 0x9, and then resume counting. 
// You may also need to change the stimulus for rst.
int main(int argc, char **argv, char **env) {
    int i,j;          // i counts # of clock cycles to simulate
    int clk;        // clk is the module clock signal

    Verilated::commandArgs(argc,argv);
    // init top verilog instance
    Vcounter* top = new Vcounter;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");

    // initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // run simulation for many clock cycles
    for (i=0; i<300; i++)   {

        //dump variables into VCD files and toggle clock
        for (clk=0; clk<2; clk++)   {
            tfp->dump (2*i + clk);
            top->clk = !top->clk;
            top->eval ();
        }
        top->rst = (i < 2)   ||  ((i >13)&&(i<17) );
        top->en = (i > 4) ;
        if (Verilated::gotFinish())     exit(0);
    }
    tfp->close();
    exit(0);
}
*/