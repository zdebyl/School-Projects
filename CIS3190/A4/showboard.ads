--  CIS 3190
--  Assignment 2
--  Zoe Debyl
--  March 1st 2024

package showboard is
    --  Types in showboard
    type Board_Array is array (1..10, 1..10) of Character;

    --  Procedures in showboard
    procedure printPiece(Piece: in Character);
    procedure printBoard(N: in Integer; Spaces: in Board_Array);

end showboard;