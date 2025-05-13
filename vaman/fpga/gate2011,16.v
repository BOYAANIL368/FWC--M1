module pos_expression (
    input wire a,
    input wire b,
    input wire c,
    output wire f
);

    wire not_c;
    wire term1, term2;
    assign not_c = ~c;

    assign term1 = b | not_c;
    assign term2 = a | not_c;

    assign f = term1 & term2;

endmodule
