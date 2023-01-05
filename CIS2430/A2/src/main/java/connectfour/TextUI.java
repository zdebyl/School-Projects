package connectfour;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.nio.file.Files;
import java.nio.file.FileSystems;
import java.nio.file.Path;

/*
Interacts with user. Outputs messages and gets user input.
@author Zoe Debyl
*/
public class TextUI{

    //gets if user wants a new or old game and returns file name
    public String getNewOldGame() {
        Scanner input = new Scanner(System.in);
        Scanner input2 = new Scanner(System.in);
        int check = 0;
        int check2 = 0;
        int newOrOld=0;
        String fileName="x";
        String tempFileName;

        //get user input and validate
        while (check==0) {
            try {
                System.out.print("Enter '1' to load an old game or '2' to start a new game: ");
                newOrOld = input.nextInt();

                if (newOrOld!=1 && newOrOld!=2) {
                    System.out.println("Invalid. Please try again.");
                } else if (newOrOld == 1) {
                    while (check2==0) {
                        System.out.print("Enter the file name: ");
                        fileName = input2.nextLine();

                        tempFileName = fileName + ".csv";
                        Path path = FileSystems.getDefault().getPath("./assets", tempFileName);

                        if (Files.notExists(path)) {
                            System.out.println("This file does not exist.");
                        } else {
                            check2=1;
                        }
                    }

                    check = 1;
                } else {
                    check = 1;
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid input.");
                input.nextLine();
            }
        }

        return fileName;
    }

    //gets if user wants to save the file and returns file name
    public String getSaveFile() {
        Scanner input = new Scanner(System.in);
        Scanner input2 = new Scanner(System.in);
        int check = 0;
        int saveOrNo;
        String fileName="x";

        //get user input and validate
        while (check==0) {
            try {
                System.out.print("Would you like to save the game? Enter '1' for yes or '2' for no: ");
                saveOrNo = input.nextInt();

                if (saveOrNo!=1 && saveOrNo!=2) {
                    System.out.println("Invalid. Please try again.");
                } else if (saveOrNo == 1) {
                    System.out.print("Enter the file name: ");
                    fileName = input2.nextLine();
                    check = 1;
                } else {
                    check = 1;
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid input.");
                input.nextLine();
            }        
        }

        return fileName;
    }

    //gets if user wants to keep playing and returns choice
    public int getContinuePlaying() {
        Scanner input = new Scanner(System.in);
        int check = 0;
        int continuePlayingOrNo=1;

        //get user input and validate
        while (check==0) {
            try {
                System.out.print("Would you like to continue playing? Enter '1' for yes or '2' for no: ");
                continuePlayingOrNo = input.nextInt();

                if (continuePlayingOrNo!=1 && continuePlayingOrNo!=2) {
                    System.out.println("Invalid. Please try again.");
                } else {
                    check = 1;
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid input.");
                input.nextLine();
            }
        }

        //return 1 if they want to keep playing and 2 if they don't
        return continuePlayingOrNo;
    }

    //gets if user wants a new game returns choice
    public int getNewGame() {
        Scanner input = new Scanner(System.in);
        int check = 0;
        int newGameOrNo=1;

        //get user input and validate
        while (check==0) {
            try {
                System.out.print("Would you like to play a new game? Enter '1' for yes or '2' for no: ");
                newGameOrNo = input.nextInt();

                if (newGameOrNo!=1 && newGameOrNo!=2) {
                    System.out.println("Invalid. Please try again.");
                } else {
                    check = 1;
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid input.");
                input.nextLine();
            }
        }

        if (newGameOrNo==1) {
            newGameOrNo=0;
        }

        //return 0 if they want a new game and 2 if they don't
        return newGameOrNo;
    }

    //prints exit message
    public void exitMessage() {
        System.out.println("Game over. Thanks for playing!");
    }

    //prints message for players turn and returns column
    public int playerTurnMessage(int playerTurn) {
        Scanner input = new Scanner(System.in);
        int check=0;
        int check2=0;
        int current=0;
        int numZeros=0;
        int column=0;

        System.out.println("Its player "+playerTurn+"'s turn");
        
        //get valid column number
        while(check2==0) {
            try {
                System.out.print("Enter the column where you would like to place your token (1-7): ");
                column = input.nextInt();

                if (column<1 || column>7) {
                    System.out.println("Invalid column. Please try again.");
                } else {
                    check2=1;
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid input.");
                input.nextLine();
            }
        }

        return column;
    }

    //Displays board
    public void displayBoard(ArrayList<Integer> board) {
        int current;
        int position=0;

        //columns
        for (int i=0; i<6; i++) {
            //rows
            for (int j=0; j<7; j++) {
                position = (i*7)+j;
                current = board.get(position);
                System.out.print(current);
            }
            System.out.println("");
        }
    }

    //prints message for winner
    public void winnerMessage(int playerTurn) {
        System.out.println("Player "+playerTurn+" wins!");
    }

    //error message
    public void errorMessage() {
        System.out.println("An error occured with this file.");
    }

    //success message
    public void successMessage() {
        System.out.println("File saved/read successfully.");
    }

    //excpetion message
    public void exceptionMessage(String message) {
        System.out.println(message);
        System.out.println("File not valid to play. Creating new board.");
    }

    public void columnFullMessage() {
        System.out.println("Column is full. Please try again");
    }

    //toString method
    @Override
    public String toString() {
        return "TextUI";
    }
}