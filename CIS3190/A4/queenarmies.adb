with showboard; use showboard;
with ada.text_io; use ada.text_io;
with ada.integer_text_io; use ada.integer_text_io;

procedure queenarmies is
    type Positions_Occupied is array (1..4, 1..2) of Integer;
    
    numRows, numQueens: Integer;
    spaceValue: showboard.Board_Array;
    spacesUsed: Positions_Occupied;
    solutionExists: Boolean;

    --  Get user input
    procedure userInput(n: out Integer; m: out Integer) is
        valid: Boolean;
    begin
        valid := False;

        while not valid loop
            --  Get values for n and m
            put("Enter the number of rows for an nxn board (less than or equal to 10): ");
            get(n);
            put("Enter the number of queens (less than are equal to 4): ");
            get(m);

            --  Check if input is valid
            if n>10 or m>4 then
                put_line("Number too large. Please try again.");
                valid := False;
            elsif n<1 or m<1 then
                put_line("Number must be positive. Please try again.");
                valid := False;
            elsif (2*m) > n**2 then
                put_line("Number invalid. Please try again.");
                valid := False;
            else
                valid := True;
            end if;
        end loop;
        
    end userInput;

    --  Initialize spaces of board to empty
     procedure initializeSpaces(spaces: in out Board_Array; n: in Integer) is
    begin
        --  Set board spaces to alternating x and o
        for i in 1..n loop
            for j in 1..n loop
                if ((i+j) rem 2) = 0 then
                    spaces(i,j) := 'x';
                else
                    spaces(i,j) := 'o';
                end if;
            end loop;
        end loop;

    end initializeSpaces;

    --  Initialize indices of spaces used to 0
    procedure initializeEmptySpaces(positions: in out Positions_Occupied) is
    begin
        --  Set indices of positions occupied to 0
        for i in 1..4 loop
            for j in 1..2 loop
                positions(i,j) := 0;
            end loop;
        end loop;

    end initializeEmptySpaces;
   
    --  Set black queens to spaces for first solution
    procedure setBlackSpacesFirst(spaces: in out Board_Array; positions: in out Positions_Occupied; m: in Integer; n: in Integer) is
        numPiecesUsed: Integer;
    begin
        --  Initialize counter
        numPiecesUsed := 0;

        --  Exceptions
        if n = 5 and m = 3 then
            positions(1,1) := 3;
            positions(1,2) := 1;
            positions(2,1) := 3;
            positions(2,2) := 3;
            positions(3,1) := 4;
            positions(3,2) := 1;
            spaces(3,1) := 'B';
            spaces(3,3) := 'B';
            spaces(4,1) := 'B';
        elsif n = 5 and m = 4 then
            positions(1,1) := 1;
            positions(1,2) := 1;
            positions(2,1) := 1;
            positions(2,2) := 5;
            positions(3,1) := 5;
            positions(3,2) := 1;
            positions(4,1) := 5;
            positions(4,2) := 5;
            spaces(1,1) := 'B';
            spaces(1,5) := 'B';
            spaces(5,1) := 'B';
            spaces(5,5) := 'B';
        else
            --  Set spaces
            for i in 1..2 loop
                for j in 1..2 loop
                    if numPiecesUsed < m then
                        spaces(i, j) := 'B';
                        positions(numPiecesUsed+1,1) := i;
                        positions(numPiecesUsed+1,2) := j;
                    end if;

                    numPiecesUsed := numPiecesUsed + 1;
                end loop;
            end loop;
        end if;

    end setBlackSpacesFirst;

    --  Set black queens to spaces for second solution
    procedure setBlackSpacesSecond(spaces: in out Board_Array; positions: in out Positions_Occupied; m: in Integer; n: in Integer) is
        numPiecesUsed: Integer;
    begin
        --  Initialize counter
        numPiecesUsed := 0;

        --  Exceptions
        if n = 5 and m = 3 then
            positions(1,1) := 1;
            positions(1,2) := 1;
            positions(2,1) := 1;
            positions(2,2) := 5;
            positions(3,1) := 4;
            positions(3,2) := 4;
            spaces(1,1) := 'B';
            spaces(1,5) := 'B';
            spaces(4,4) := 'B';
        elsif n = 5 and m = 4 then
            positions(1,1) := 1;
            positions(1,2) := 3;
            positions(2,1) := 1;
            positions(2,2) := 5;
            positions(3,1) := 5;
            positions(3,2) := 3;
            positions(4,1) := 5;
            positions(4,2) := 5;
            spaces(1,3) := 'B';
            spaces(1,5) := 'B';
            spaces(5,3) := 'B';
            spaces(5,5) := 'B';
        else
            --  Set spaces
            for i in reverse n-1..n loop
                for j in reverse n-1..n loop
                    if numPiecesUsed < m then
                        spaces(i, j) := 'B';
                        positions(numPiecesUsed+1,1) := i;
                        positions(numPiecesUsed+1,2) := j;
                    end if;

                    numPiecesUsed := numPiecesUsed + 1;
                end loop;
            end loop;
        end if;

    end setBlackSpacesSecond;

    --  Check if placement of queens is valid
    function checkValidSpace(attackPositions: in Positions_Occupied; m: in Integer; currentX: in Integer; currentY: in Integer) return Boolean is
        attackX, attackY: Integer;
    begin
        --  Go through each attack queen
        for i in 1..m loop
            attackX := attackPositions(i,1);
            attackY := attackPositions(i,2);

            --  Check if rows are the same
            if attackX = currentX then
                return False;
            end if;

            --  Check if columns are the same
            if attackY = currentY then
                return False;
            end if;

            --  Check if diagonals are the same
            if abs(attackX-currentX) = abs(attackY-currentY) then
                return False;
            end if;
        end loop;

        return True;

    end checkValidSpace;

    --  Set white queens to spaces and check if there is a solution
    procedure setWhiteSpaces(spaces: in out Board_Array; attackPositions: in Positions_Occupied; m: in Integer; n: in Integer; solution: out Boolean) is
        numPiecesUsed: Integer;
    begin
        --  Initialize counter
        numPiecesUsed := 0;

        --  Set spaces
        for i in 1..n loop
            for j in 1..n loop
                if numPiecesUsed < m then
                    if spaces(i,j) /= 'B' then
                        if checkValidSpace(attackPositions, m, i, j) then
                            spaces(i,j) := 'W';
                            numPiecesUsed := numPiecesUsed + 1;
                        end if;
                    end if;
                end if;
            end loop;
        end loop;

        --  Check if all queens were placed
        if numPiecesUsed < m then
            solution := False;
        else
            solution := True;
        end if;

    end setWhiteSpaces;

begin
    --  Get user input
    userInput(numRows, numQueens);

    --  SOLUTION 1
    --  Initialize
    initializeSpaces(spaceValue, numRows);
    initializeEmptySpaces(spacesUsed);

    --  Set black queens to their spaces
    setBlackSpacesFirst(spaceValue, spacesUsed, numQueens, numRows);

    --  Set white queens to their spaces
    setWhiteSpaces(spaceValue, spacesUsed, numQueens, numRows, solutionExists);

    --  Output solution or that it doesn't exist
    if solutionExists then
        put_line("Solution 1:");
        showboard.printBoard(numRows, spaceValue);

        --  SOLUTION 2
        new_line;
        put_line("Solution 2:");

        --  Initialize
        initializeSpaces(spaceValue, numRows);
        initializeEmptySpaces(spacesUsed);

        --  Set black queens to their spaces
        setBlackSpacesSecond(spaceValue, spacesUsed, numQueens, numRows);

        --  Set white queens to their spaces
        setWhiteSpaces(spaceValue, spacesUsed, numQueens, numRows, solutionExists);

        --  Print board
        showboard.printBoard(numRows, spaceValue);
    else
        put("No solution exists.");
    end if;

end queenarmies;