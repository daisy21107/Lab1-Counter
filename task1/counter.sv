module counter #(
    parameter WIDTH = 8
)(
    //interface signals
    input logic                 clk,        // clock
    input logic                 rst,        // reset
    input logic                 en,         // counter enable
    output logic [WIDTH-1:0]    count       // count output
);

always_ff @ (posedge clk, posedge rst)
    if (rst)    count <= {WIDTH{1'b0}};
    else        count <= count + {{WIDTH-1{1'b0}}, en};

endmodule

//The current counter has a synchronous reset. 
//To implement asynchronous reset, you can change line 11 of counter.sv to detect change in rst signal.

