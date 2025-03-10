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
    else if (en==1)        count <= count + {{WIDTH-1{1'b0}}, en};
    else if (en==0)        count <= count - 1;


endmodule
