fiboO := 0;
fiboI := 1;
read x;
if x = 0 then
    write fiboO;
end
if x = 1 then
    write fiboI;
end
if x >= 2 then
    x := x - 2;
    repeat
        fiboII := fiboO + fiboI;
        fiboO := fiboI;
        fiboI := fiboII;
        x:= x - 1;
    until x < 0;
    write fiboII;
end
