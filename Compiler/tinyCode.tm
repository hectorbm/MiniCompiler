read x;
if x>0 then
    fact:=1;
    repeat
        fact:=fact*x;
        x:=x-1;
    until x=0;
    write fact;
else
    write 0-1;
end