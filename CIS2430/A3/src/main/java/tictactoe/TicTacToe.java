package tictactoe;

import java.io.IOException;
import java.util.StringTokenizer;

public class TicTacToe extends boardgame.BoardGame implements boardgame.Saveable {

    private TicTacToeGrid board;

    /**
     * constructor
     * @param wide width of board
     * @param tall height of board
    */
    public TicTacToe(int wide, int tall) {
        super(wide,tall);
        board = new TicTacToeGrid(wide,tall);
    }

    /**
     * does a turn for game with string input
     * @param across number of spots across on board
     * @param down number of spots down on board
     * @return boolean that is true if no errors were found
    */
    @Override
    public boolean takeTurn(int across, int down, String input) {
        String valueAtPosition;

        //check that position is valid
        if (across<1||across>3||down<1||down>3) {
            throw new IllegalArgumentException("Invalid position.");
        }

        //check if position is taken or not
        valueAtPosition = getCell(across,down);

        if (valueAtPosition.equals("X")||valueAtPosition.equals("O")) {
            throw new IllegalArgumentException("Position full.");
        }

        //update the board
        setValue(across,down,input);

        return true;
    }

    /**
     * does a turn for game with integer input
     * @param across number of spots across on board
     * @param down number of spots down on board
     * @return boolean that is true if no errors were found
    */
    @Override
    public boolean takeTurn(int across, int down, int input) {
        String valueAtPosition;

        //check that position is valid
        if (across<1||across>3||down<1||down>3) {
            throw new IllegalArgumentException("Invalid position.");
        }

        //check if position is taken or not
        valueAtPosition = getCell(across,down);

        if (valueAtPosition.equals("X")||valueAtPosition.equals("O")) {
            throw new IllegalArgumentException("Position full.");
        }

        //if valid, update the board
        if (input==1) {
            setValue(across,down,"X");
        } else {
            setValue(across,down,"O");
        }

        return true;
    }

    /**
     * checks if the game is done
     * @return boolean that true if game is done, false if game is not done
    */
    @Override
    public boolean isDone() {
        int numPlays=0;
        String valueAtPosition;
        String winner;

        //check for winner
        winner = checkWinConditions();

        if (winner.equals("X")||winner.equals("O")) {
            return true;
        }

        //check if board is full
        if (checkBoardFull()) {
            return true;
        }

        //not done
        return false;
    }

    /**
     * gets state of the board
     * @return int that is 1 if player 1 won, 2 if player 2 won, 0 if tie, -1 if no winner
    */
    @Override
    public int getWinner() {
        String winner;

        //check for winner
        winner = checkWinConditions();

        if (winner.equals("X")) {
            return 1;
        } else if (winner.equals("O")) {
            return 2;
        }

        //check for tie
        if (checkBoardFull()) {
            return 0;
        }

        //no winner
        return -1;
    }

    /**
     * creates message based on game state
     * @return string with message to represent win/tie/no win
    */
    @Override
    public String getGameStateMessage() {
        int winner;

        winner = getWinner();

        if (winner==0) {
            return "It's a tie!";
        } else if (winner==1) {
            return "Player 1 (X) wins!";
        } else if (winner==2) {
            return "Player 2 (O) wins!";
        } else {
            return "No winner!";
        }
    }

    /**
     * represents the class with a string representation of the board
     * @return string representation of board
    */
    @Override
    public String toString(){
        String boardToPrint = "";

        for (int i=1; i<=3; i++) {
            for (int j=1; j<=3; j++) {
                boardToPrint = boardToPrint + getCell(j,i);

                if (j!=3) {
                    boardToPrint = boardToPrint + "|";
                }
            }
            boardToPrint = boardToPrint + "\n";

            if (i!=3) {
                boardToPrint = boardToPrint + "-+-+-\n";
            }
        }

        return boardToPrint;
    }

    private boolean checkBoardFull() {
        String valueAtPosition;
        int numPlays=0;

        for (int i=1; i<=3; i++) {
            for (int j=1; j<=3; j++) {
                valueAtPosition = getCell(i,j);

                if (valueAtPosition.equals("X")||valueAtPosition.equals("O")) {
                    numPlays++;
                }
            }
        }

        if (numPlays==9) {
            return true;
        }
        
        return false;
    }

    private String checkWinConditions() {
        String rowWin;
        String columnWin;
        String leftDiagonalWin;
        String rightDiagonalWin;

        rowWin = checkRows();
        columnWin = checkColumns();
        leftDiagonalWin = checkLeftDiagonal();
        rightDiagonalWin = checkRightDiagonal();

        if (rowWin.equals("X")||columnWin.equals("X")||leftDiagonalWin.equals("X")||rightDiagonalWin.equals("X")) {
            return "X";
        }else if(rowWin.equals("O")||columnWin.equals("O")||leftDiagonalWin.equals("O")||rightDiagonalWin.equals("O")) {
            return "O";
        } else {
            return "";
        }
    }

    private String checkRows() {
        int numX=0;
        int numO=0;
        String valueAtPosition;

        for (int i=1; i<=3; i++) {
            for (int j=1; j<=3; j++) {
                valueAtPosition = getCell(j,i);
                if (valueAtPosition.equals("X")) {
                    numX++;
                    numO=0;
                } else if (valueAtPosition.equals("O")) {
                    numO++;
                    numX=0;
                } else {
                    numX=0;
                    numO=0;
                }
            }
            if (numX==3) {
                return "X";
            } else if (numO==3) {
                return "O";
            } else {
                numX=0;
                numO=0;
            }
        }
        return "";
    }

    private String checkColumns() {
        int numX=0;
        int numO=0;
        String valueAtPosition;

        for (int i=1; i<=3; i++) {
            for (int j=1; j<=3; j++) {
                valueAtPosition = getCell(i,j);
                if (valueAtPosition.equals("X")) {
                    numX++;
                    numO=0;
                } else if (valueAtPosition.equals("O")) {
                    numO++;
                    numX=0;
                } else {
                    numX=0;
                    numO=0;
                }
            }
            if (numX==3) {
                return "X";
            } else if (numO==3) {
                return "O";
            } else {
                numX=0;
                numO=0;
            }
        }
        return "";
    }

    private String checkLeftDiagonal() {
        int numX=0;
        int numO=0;
        String valueAtPosition;

        for (int i=1; i<=3; i++) {
            valueAtPosition = getCell(4-i,i);

            if (valueAtPosition.equals("X")) {
                numX++;
                numO=0;
            } else if (valueAtPosition.equals("O")) {
                numO++;
                numX=0;
            } else {
                numX=0;
                numO=0;
            }
        }
        if (numX==3) {
            return "X";
        } else if (numO==3) {
            return "O";
        } else {
            numX=0;
            numO=0;
        }
        return "";
    }

    private String checkRightDiagonal() {
        int numX=0;
        int numO=0;
        String valueAtPosition;

        for (int i=1; i<=3; i++) {
            valueAtPosition = getCell(i,i);

            if (valueAtPosition.equals("X")) {
                numX++;
                numO=0;
            } else if (valueAtPosition.equals("O")) {
                numO++;
                numX=0;
            } else {
                numX=0;
                numO=0;
            }
        }
        if (numX==3) {
            return "X";
        } else if (numO==3) {
            return "O";
        } else {
            numX=0;
            numO=0;
        }
        return "";
    }

    /**
     * creates string to save to file
     * @return string that will be saved
    */
    @Override
    public String getStringToSave() {
        int player = getCurrentPlayer();
        String recentPlayer;
        String save;

        if (player==1) {
            recentPlayer="O";
        } else {
            recentPlayer="X";
        }

        save = recentPlayer+"\n";

        for (int i=1; i<=3; i++) {
            for (int j=1; j<=3; j++) {
                save+=getCell(j,i);

                if (j!=3) {
                    save += ",";
                }
            }
            save += "\n";
        }

        return save;
    }

    /**
     * loads information from file into game
     * @param fileInfo string that was read from file
    */
    @Override
    public void loadSavedString(String fileInfo) {
        StringTokenizer tokens;
        String playerTurn;

        fileInfo = addSpaces(fileInfo);

        tokens = new StringTokenizer(fileInfo,",\n");
        playerTurn = tokens.nextToken().strip();

        if (playerTurn.equals("X")) {
            setCurrentPlayer(2);
        } else if (playerTurn.equals("O")) {
            setCurrentPlayer(1);
        } else {
            throw new IllegalArgumentException("File is invalid.");
        }

        try {
            tokens = parseFile(tokens);
        } catch (IllegalArgumentException e) {
            throw e;
        }
        
        if(tokens.hasMoreTokens()) {
            throw new IllegalArgumentException("Too many symbols in file.");
        }
    }

    private String addSpaces(String fileInfo) {
        String character;
        int firstNewLine=0;
        String newFileInfo="";
        String[] parseFile=fileInfo.split("");

        for (int i=0; i<fileInfo.length(); i++) {
            character = parseFile[i];
            newFileInfo = newFileInfo + character;

            if (character.equals("\n")) {
                firstNewLine++;
            }

            if (firstNewLine>0&&i!=fileInfo.length()-1) {
                if (character.equals(",")||character.equals("\n")) {
                    character = parseFile[i+1];
                }

                if (character.equals(",")||character.equals("\n")) {
                    newFileInfo = newFileInfo + " ";
                }
            } else if (i==fileInfo.length()-1&&character.equals(",")) {
                newFileInfo = newFileInfo + " ";
            }
        }

        return newFileInfo;
    }

    private StringTokenizer parseFile(StringTokenizer tokens) {
        String position;

        for (int i=1; i<=3; i++) {
            for (int j=1; j<=3; j++) {
                if (tokens.hasMoreTokens()) {
                    position = tokens.nextToken().strip();
                } else {
                    position = " ";
                }
                if (position.equals("X")||position.equals("O")||position.equals(" ")) {
                    setValue(j, i, position);
                } else if (position.equals("")) {
                    setValue(j, i, " ");
                } else {
                    throw new IllegalArgumentException("There is an invalid symbol in the file.");
                }
            }
        }

        return tokens;
    }
}