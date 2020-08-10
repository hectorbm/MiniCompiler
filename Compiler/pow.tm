{Imprime x ^ y}
read x;
read y;
if y >= 0 then
    res := 1;
    if y = 0 then
        write res;
    else
        repeat
            res := res * x;
            y := y - 1;
        until y <= 0;
        write res;
    end
end