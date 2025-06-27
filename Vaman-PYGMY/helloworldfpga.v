/* Logic Function Display
June 27, 2025  
Code by G V V Sharma (adapted)
Released under GNU GPL
*/

// Declaring the module
module helloworldfpga(

input  wire W,
input  wire X,
input  wire Y,

output wire a,
output wire b,
output wire c,
output wire d,
output wire e,
output wire f,
output wire g

);

reg F;

always @(*)
begin

// Boolean Logic: F = (W & X) | (X & ~Y) | (W & ~Y)
F = (W & X) | (X & ~Y) | (W & ~Y);

// Display Decoder for F
// If F = 0 => display "0" (segments a,b,c,d,e,f ON, g OFF)
// If F = 1 => display "1" (segments b,c ON, others OFF)

if (F == 1'b0)
begin
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    e = 0;
    f = 0;
    g = 1;
end
else
begin
    a = 1;
    b = 0;
    c = 0;
    d = 1;
    e = 1;
    f = 1;
    g = 1;
end

end
endmodule
// End of module

