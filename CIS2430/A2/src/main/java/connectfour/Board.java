package connectfour;

import java.util.ArrayList;

/*
Performs all methods related to the board. Sets initial board, updates board
and checks win conditions.
@author Zoe Debyl
*/
public class Board{
    private ArrayList<Integer> theBoard;

    /*
    Constructor for Board class. Creates an arraylist for board and an instance of TextUI
    */
    public Board() {
        theBoard = new ArrayList<Integer>();

        //set all values to 0 (empty space)
        for (int i=0; i<42; i++) {
            theBoard.add(0);
        }
    }

    /*get board method
    @return     array list that represents the board
    */
    public ArrayList<Integer> getBoard() {
        return theBoard;
    }

    /*set board method
    @param  position    position in arraylist to change
    @param  token       0,1,2 for which token should be in this position
    */
    public void setBoard(int position, int token) {
        theBoard.set(position, token);
    }

    /*
    Checks if column is full
    @param column   number of the column user wanted to play in
    @return         0 if column is full, 1 if column is not full
    */
    public int checkColumn(int column) {
        int columnCheck = column-1;
        int check=0;
        int current=0;
        int numZeros=0;

        //check if column is full
        while (columnCheck<42) {
            current = theBoard.get(columnCheck);

            if (current==0) {
                numZeros++;
            }
            
            columnCheck=columnCheck+7;
        }

        if (numZeros != 0) {
            check = 1;
        }
        
        return check;
    }

    /*
    Changes board to reflect players turn
    @param  column      number of column player wants to play
    @param  playerTurn  1 or 2 for which players turn it is
    */
    public void changeBoard(int column, int playerTurn) {
        int position = column+34;
        int check=0;
        int current;

        //get position of token
        while (check==0) {
            current = theBoard.get(position);

            if (current==0) {
                check = 1;
            } else {
                position=position-7;
            }
        }

        //change position to users token
        theBoard.set(position, playerTurn);
    }

    /*
    Checks win conditions
    @return     1 if there is a winner, 0 if there is no winner
    */
    public int getWinConditions() {
        int win=0;
        int rowCheck;
        int columnCheck;
        int diagonalRightCheck;
        int diagonalLeftCheck;

        rowCheck = getRowWin();
        columnCheck = getColumnWin();
        diagonalRightCheck = getRightDiagonalWin();
        diagonalLeftCheck = getLeftDiagonalWin();
        
        if (rowCheck==1 || columnCheck==1 || diagonalRightCheck==1 || diagonalLeftCheck==1) {
            win = 1;
        }

        return win;
    }

    //win in a row
    private int getRowWin() {
        int win=0;
        int numOneInRow=0;
        int numTwoInRow=0;
        int current;

        //go through array
        for (int i=0; i<42; i++) {
            //check if starting new row
            if (i!=0 && i%7==0) {
                numOneInRow=0;
                numTwoInRow=0;
            }

            current = theBoard.get(i);

            //track number of same tokens in a row
            if (current==1) {
                numOneInRow++;
                numTwoInRow=0;
            } else if (current==2) {
                numOneInRow=0;
                numTwoInRow++;
            } else {
                numOneInRow=0;
                numTwoInRow=0;
            }

            //check for four in a row
            if (numOneInRow >= 4) {
                win=1;
            } else if (numTwoInRow >= 4) {
                win=1;
            }
        }

        //return 1 if winner, else return 0
        return win;
    }


    //win in a column
    private int getColumnWin() {
        int win=0;
        int numOneInColumn=0;
        int numTwoInColumn=0;
        int current;

        //go through each column
        for (int i=0; i<7; i++) {
            numOneInColumn=0;
            numTwoInColumn=0;

            //go through each value in column
            for (int j=0; j<6; j++) {
                current = theBoard.get(i+7*j);

                //track number of same tokens in a column
                if (current==1) {
                    numOneInColumn++;
                    numTwoInColumn=0;
                } else if (current==2) {
                    numOneInColumn=0;
                    numTwoInColumn++;
                } else {
                    numOneInColumn=0;
                    numTwoInColumn=0;
                }

                //check for four in a row
                if (numOneInColumn >= 4) {
                    win=1;
                } else if (numTwoInColumn >= 4) {
                    win=1;
                }
            }
        }
        
        //return 1 if winner, else return 0
        return win;
    }

    //win in right diagonal
    private int getRightDiagonalWin() {
        int win=0;
        int numOneInDiagonal=0;
        int numTwoInDiagonal=0;
        int current;
        int temp;

        //go through right diagonals
        for (int i=0; i<15; i++) {
            numOneInDiagonal=0;
            numTwoInDiagonal=0;

            for (int j=0; j<6;j++) {
                if ((i+8*j)>=0 && (i+8*j)<=41) {
                    current = theBoard.get(i+8*j);

                    //track number of same tokens in a diagonal
                    if (current==1) {
                        numOneInDiagonal++;
                        numTwoInDiagonal=0;
                    } else if (current==2) {
                        numOneInDiagonal=0;
                        numTwoInDiagonal++;
                    } else {
                        numOneInDiagonal=0;
                        numTwoInDiagonal=0;
                    }

                    //check for four in a row
                    if (numOneInDiagonal >= 4) {
                        win=1;
                    } else if (numTwoInDiagonal >= 4) {
                        win=1;
                    }

                }

                temp=i+8*j;
                
                if ((temp+1)%7==0) {
                    j=6;
                }
            }
        }

        //return 1 if winner, else return 0
        return win;
    }

    //win in left diagonal
    private int getLeftDiagonalWin() {
        int win=0;
        int numOneInDiagonal=0;
        int numTwoInDiagonal=0;
        int current;
        int temp;

        //go through left diagonals
        for (int i=0; i<21; i++) {
            numOneInDiagonal=0;
            numTwoInDiagonal=0;

            for (int j=0; j<6;j++) {
                if ((i+6*j)>=0 && (i+6*j)<=41) {
                    current = theBoard.get(i+6*j);

                    //track number of same tokens in a diagonal
                    if (current==1) {
                        numOneInDiagonal++;
                        numTwoInDiagonal=0;
                    } else if (current==2) {
                        numOneInDiagonal=0;
                        numTwoInDiagonal++;
                    } else {
                        numOneInDiagonal=0;
                        numTwoInDiagonal=0;
                    }

                    //check for four in a row
                    if (numOneInDiagonal >= 4) {
                        win=1;
                    } else if (numTwoInDiagonal >= 4) {
                        win=1;
                    }

                }

                temp=i+6*j;

                if (temp%7==0) {
                    j=6;
                }
            }
        }

        //return 1 if winner, else return 0
        return win;
    }

    /*
    Checks if board is full
    @return     0 if board is full, 1 if board is not full
    */
    public int checkBoardFull() {
        int check=0;
        int current;
        int numZeros=0;

        //check if column is full
        for (int i=0; i<42; i++) {
            current = theBoard.get(i);

            if (current==0) {
                numZeros++;
            }            
        }

        if (numZeros != 0) {
            check = 1;
        }
            
        return check;
    }

    /*
    Override toString method
    @return     game board
    */
    @Override
    public String toString() {
        String boardString="";

        for (int i=0; i<6; i++) {
            for (int j=0; j<7; j++) {
                boardString+=theBoard.get((i*7)+j);
            }
            boardString += "\n";
        }

        return boardString;
    }
}