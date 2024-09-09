with ada.text_io; use ada.text_io;

package body showboard is
    --  Print Unicode chess pieces
    procedure printPiece(piece: in Character) is
    begin
        --  Convert ascii to unicode chess pieces
        if piece = 'x' then
            put("■");
        elsif piece = 'o' then
            put(" ");
        elsif piece = 'B' then
            put("♛");
        elsif piece = 'W' then
            put("♕");
        end if;

    end printPiece;

    --  Print board
    procedure printBoard(n: in Integer; spaces: in Board_Array) is
    begin
        for i in 1..n loop
            --  Print lines
            for j in 1..n loop
                put("⎯⎯⎯⎯");
            end loop;
            put("⎯");

            New_Line;

            --  Print values
            for j in 1..n loop
                put("| ");
                printPiece(spaces(i,j));
                put(" ");
            end loop;
            put("|");

            New_Line;
        end loop;

        --  Print last line
        for j in 1..n loop
            put("⎯⎯⎯⎯");
        end loop;
        put("⎯");

    end printBoard;
    
end showboard;