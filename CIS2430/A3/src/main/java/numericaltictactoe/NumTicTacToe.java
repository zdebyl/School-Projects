package numericaltictactoe;

import java.io.IOException;
import java.util.StringTokenizer;

public class NumTicTacToe extends boardgame.BoardGame implements boardgame.Saveable {

    private NumTicTacToeGrid board;

    /**
     * constructor
     * @param wide width of board
     * @param tall height of board
    */
    public NumTicTacToe(int wide, int tall) {
        super(wide,tall);
        board = new NumTicTacToeGrid(wide,tall);
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

        if (!valueAtPosition.equals(" ")) {
            throw new IllegalArgumentException("Position full.");
        }

        //check if number is valid
        if(!checkNum(Integer.parseInt(input))) {
            throw new IllegalArgumentException("Player entered value is invalid.");
        }

        //check if number has already been played
        if (checkNumPlayed(Integer.parseInt(input))) {
            throw new IllegalArgumentException("This number has already been played.");
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

        if (!valueAtPosition.equals(" ")) {
            throw new IllegalArgumentException("Position full.");
        }

        //check if number is valid
        if(!checkNum(input)) {
            throw new IllegalArgumentException("Player entered value is invalid.");
        }

        //check if number has already been played
        if (checkNumPlayed(input)) {
            throw new IllegalArgumentException("This number has already been played.");
        }

        //update the board
        setValue(across,down,String.valueOf(input));
        setValue(across,down,String.valueOf(input));
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

        //check for winner
        if (checkWinConditions()==1||checkWinConditions()==2) {
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
        int winner;

        //check for winner
        winner = checkWinConditions();

        if (winner==1||winner==2) {
            return winner;
        } else {
            //check for tie
            if (checkBoardFull()) {
                return 0;
            }
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
            return "Player 1 (odds) wins!";
        } else if (winner==2) {
            return "Player 2 (evens) wins!";
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

    private boolean checkNum(int num) {
        int player = getCurrentPlayer();

        if (player==1) {
            if (num==1||num==3||num==5||num==7||num==9) {
                return true;
            }
        } else {
            if (num==0||num==2||num==4||num==6||num==8) {
                return true;
            }
        }

        return false;
    }

    private boolean checkNumPlayed(int playerNum) {
        String valueAtPosition;
        int numAtPosition;

        for (int i=1; i<=3; i++) {
            for (int j=1; j<=3; j++) {
                valueAtPosition = getCell(i,j);

                if (!valueAtPosition.equals(" ")) {
                    numAtPosition = Integer.parseInt(valueAtPosition);

                    if (numAtPosition==playerNum) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    private boolean checkBoardFull() {
        String valueAtPosition;
        int numPlays=0;

        for (int i=1; i<=3; i++) {
            for (int j=1; j<=3; j++) {
                valueAtPosition = getCell(i,j);

                if (!valueAtPosition.equals(" ")) {
                    numPlays++;
                }
            }
        }

        if (numPlays==9) {
            return true;
        }
        
        return false;
    }

    private int checkWinConditions() {
        if (checkRows()||checkColumns()||checkLeftDiagonal()||checkRightDiagonal()) {
            return getCurrentPlayer();
        }
        
        return -1;
    }

    private boolean checkRows() {
        int sum=0;
        int numAtPosition;
        int numPlayed=0;
        String valueAtPosition;

        for (int i=1; i<=3; i++) {
            for (int j=1; j<=3; j++) {
                valueAtPosition = getCell(j,i);

                if (!valueAtPosition.equals(" ")) {
                    numAtPosition = Integer.parseInt(valueAtPosition);
                    sum = sum + numAtPosition;
                    numPlayed++;
                }
            }

            if (sum==15&&numPlayed==3) {
                return true;
            } else {
                numPlayed=0;
                sum=0;
            }
        }

        return false;
    }

    private boolean checkColumns() {
        int sum=0;
        int numAtPosition;
        int numPlayed=0;
        String valueAtPosition;

        for (int i=1; i<=3; i++) {
            for (int j=1; j<=3; j++) {
                valueAtPosition = getCell(i,j);

                if (!valueAtPosition.equals(" ")) {
                    numAtPosition = Integer.parseInt(valueAtPosition);
                    sum = sum + numAtPosition;
                    numPlayed++;
                }
            }

            if (sum==15&&numPlayed==3) {
                return true;
            } else {
                numPlayed=0;
                sum=0;
            }
        }
        
        return false;
    }

    private boolean checkLeftDiagonal() {
        int sum=0;
        int numAtPosition;
        int numPlayed=0;
        String valueAtPosition;

        for (int i=1; i<=3; i++) {
            valueAtPosition = getCell(4-i,i);

            if (!valueAtPosition.equals(" ")) {
                numAtPosition = Integer.parseInt(valueAtPosition);
                sum = sum + numAtPosition;
                numPlayed++;
            }
        }

        if (sum==15&&numPlayed==3) {
            return true;
        } else {
            numPlayed=0;
            sum=0;
        }

        return false;
    }

    private boolean checkRightDiagonal() {
        int sum=0;
        int numAtPosition;
        int numPlayed=0;
        String valueAtPosition;

        for (int i=1; i<=3; i++) {
            valueAtPosition = getCell(i,i);

            if (!valueAtPosition.equals(" ")) {
                numAtPosition = Integer.parseInt(valueAtPosition);
                sum = sum + numAtPosition;
                numPlayed++;
            }
        }

        if (sum==15&&numPlayed==3) {
            return true;
        } else {
            numPlayed=0;
            sum=0;
        }

        return false;
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
            recentPlayer="E";
        } else {
            recentPlayer="O";
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

        if (playerTurn.equals("O")) {
            setCurrentPlayer(2);
        } else if (playerTurn.equals("E")) {
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
                if (position.equals("0")||position.equals("1")||position.equals("2")||position.equals("3")
                    ||position.equals("4")||position.equals("5")||position.equals("6")||position.equals("7")
                    ||position.equals("8")||position.equals("9")||position.equals(" ")) {
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