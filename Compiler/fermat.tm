{Fermat last theorem, returns valid n for a^n + b^n = c^n}
read a;
read b;
read c;
read nMax;
if nMax > 0 then
    n := 0;
    repeat
        resA := 1;
        if n > 0 then
            nAux := n;
            repeat
                resA := resA * a;
                nAux := nAux - 1;
            until nAux <= 0;
        end

        resB := 1;
        if n > 0 then
            nAux := n;
            repeat
                resB := resB * b;
                nAux := nAux - 1;
            until nAux <= 0;
        end

        resC := 1;
        if n > 0 then
            nAux := n;
            repeat
                resC := resC * c;
                nAux := nAux - 1;
            until nAux <= 0;
        end

        sumabPow := resA + resB;

        if sumabPow = resC then
            write n;
        end
        n := n + 1;

    until nMax = n;
end