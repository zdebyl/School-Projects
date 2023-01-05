package connectfour;

import java.util.ArrayList;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.io.IOException;
import java.util.StringTokenizer;

/*
Manages all aspects of the game, including player turns and when to keep playing.
Calls TextUI to output to user and get user input and calls Board to update board.
Loads and saves files.
@author Zoe Debyl
*/

public class ConnectFour{
    //instance variables
    private int playerTurn;
    private TextUI interactWithUser;
    private Board theBoard;

    public static void main(String[] args) {
        //declare instance of ConnectFour and string to hold return value
        ConnectFour play = new ConnectFour();
        play.game();
    }

    //constructor
    public ConnectFour() {
        interactWithUser = new TextUI();
    }

    //runs game
    public void game() {
        int exit=0;
        int exit2=0;
        int check=0;
        int continuePlaying=1;
        int firstTurn=0;
        String fileNameLoad;
        String fileNameSave;
        while (exit2==0) {
            exit=0;
            continuePlaying=1;
            firstTurn=0;
            theBoard = new Board();
            fileNameLoad = interactWithUser.getNewOldGame();
            if (fileNameLoad!="x") {
                playerTurn = initializeBoard(fileNameLoad);
            } else {
                playerTurn = 1;
            }
            while (exit == 0) {
                if (firstTurn == 1) {
                    setPlayerTurn();
                }
                firstTurn=1;
                interactWithUser.displayBoard(theBoard.getBoard());
                check=0;
                while (check==0) {
                    fileNameSave = interactWithUser.getSaveFile();
                    if (!fileNameSave.equals("x")) {
                        check = saveFile(fileNameSave);
                        if (check==1) {
                            continuePlaying = interactWithUser.getContinuePlaying();
                        }
                    } else {
                        check = 1;
                    }
                }
                if (continuePlaying == 1) {
                    exit = playerTurn();
                    if (exit==1) {
                        exit2 = interactWithUser.getNewGame();
                    }
                } else {
                    interactWithUser.exitMessage();
                    exit = 1;
                    exit2=1;
                }
            }
        }
    }

    //runs players turn
    private int playerTurn() {
        int exit=0;
        int column=0;
        int winner;
        int full;
        int checkColumn=0;
        String fileNameSave;
        
        while (checkColumn==0) {
            column = interactWithUser.playerTurnMessage(playerTurn);
            checkColumn = theBoard.checkColumn(column);    
            if (checkColumn==0) {
                interactWithUser.columnFullMessage();
            }
        }

        theBoard.changeBoard(column, playerTurn);
        winner = theBoard.getWinConditions();

        if (winner==1) {
            interactWithUser.displayBoard(theBoard.getBoard());
            interactWithUser.winnerMessage(playerTurn);
            fileNameSave = interactWithUser.getSaveFile();

            if (!fileNameSave.equals("x")) {
                saveFile(fileNameSave);
            }
            
            exit = 1;
        } else {
            full = theBoard.checkBoardFull();
            if (full == 0) {
                interactWithUser.displayBoard(theBoard.getBoard());
                interactWithUser.exitMessage();

                fileNameSave = interactWithUser.getSaveFile();
                if (!fileNameSave.equals("x")) {
                    saveFile(fileNameSave);
                }

                exit = 1;
            }
        }

        //returns 1 to exit, else returns 0
        return exit;
    }

    //updates who's turn it is
    private void setPlayerTurn() {
        //initial turn
        if (playerTurn == 0) {
            playerTurn = 1;
        } else if (playerTurn == 1) {
            playerTurn = 2;
        } else if (playerTurn == 2) {
            playerTurn = 1;
        }
    }

    //saves game to file
    private int saveFile(String fileName) {
        String boardString="";
        int validFile=1;
        ArrayList<Integer> tempBoard = new ArrayList<Integer>();

        tempBoard = theBoard.getBoard();

        fileName = fileName + ".csv";

        //create string to be written to file
        for (int i=0; i<6; i++) {
            for (int j=0; j<7; j++) {
                boardString+=tempBoard.get((i*7)+j);

                if (j!=6) {
                    boardString += ",";
                }
            }
            boardString += "\n";
        }

        //save file
        Path path = FileSystems.getDefault().getPath("./assets", fileName);

        try {
            Files.writeString(path,boardString);

            interactWithUser.successMessage();

        } catch (IOException e) {
            interactWithUser.errorMessage();
            validFile=0;
        }

        //return 1 if file is valid, else return 0
        return validFile;
    }

    //initializes board
    private int initializeBoard(String fileName) {
        int turn=1;
        int fileBoard=0;

        //loads file
        try {
            turn = loadFile(fileName);
            fileBoard=1;
        } catch (Exception e) {
            interactWithUser.exceptionMessage(e.getMessage());
            theBoard = new Board();
            turn=1;
        }

        //if file is valid, check if board is full or if there is a winner
        if (fileBoard == 1) {
            try {
                checkBoard();
            } catch (Exception e) {
                interactWithUser.exceptionMessage(e.getMessage());
                theBoard = new Board();
                turn=1;
            }
        }

        return turn;
    }

    //loads old game
    private int loadFile(String fileName) throws Exception {
        fileName = fileName + ".csv";
        Path path = FileSystems.getDefault().getPath("./assets", fileName);
        String lines = null;
        int player;
        int player1NumTurns=0;
        int player2NumTurns=0;

        try{
            lines = Files.readString(path);
            interactWithUser.successMessage();
        }catch(IOException e){
            interactWithUser.errorMessage();
        }

        StringTokenizer tokens = new StringTokenizer(lines,",\n");

        for (int i=0; i<42; i++) {
            player = Integer.parseInt(tokens.nextToken().strip());

            if (player==1) {
                player1NumTurns++;
            } else if (player==2) {
                player2NumTurns++;
            } else if (player!=0) {
                throw new Exception("There is an invalid symbol in the file.");
            }

            theBoard.setBoard(i,player);
        }

        if(tokens.hasMoreTokens()) {
            throw new Exception("Too many symbols in file.");
        }

        //returns players turn
        if (player1NumTurns>player2NumTurns) {
            return 2;
        } else {
            return 1; 
        }
    }

    //checks if board from file is full or if there is a winner
    private void checkBoard() throws Exception {
        int win;
        int full;

        //check for winner
        win = theBoard.getWinConditions();

        if (win==1) {
            throw new Exception("There is already a winner in this game.");
        }

        //check if board is full
        full = theBoard.checkBoardFull();

        if (full==0) {
            throw new Exception("This board is full.");
        }
    }

    //toString method
    @Override
    public String toString() {
        return "ConnectFour";
    }
}