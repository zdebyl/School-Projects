package numericaltictactoe;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;

public class NumTextUI {
    private NumTicTacToe game = new NumTicTacToe(3,3);
    private int across;
    private int down;
    private int turnVal;

    /**
     * runs game
    */
    public void play() {
        String finalMessage;

        game.setCurrentPlayer(1);

        while (!game.isDone()) {
            System.out.println(game);

            System.out.println("Its player "+game.getCurrentPlayer()+"'s turn");

            playerTurn();
            
            if (!game.isDone()) {
                game.incrementCurrentPlayer();
            }
        }

        finalMessage = game.getGameStateMessage();

        System.out.println(game);
        System.out.println(finalMessage);
    }

    private void playerTurn() {
        int check=0;

        while(check==0) {
            //get user input
            getInput();

            //update board
            try {
                game.takeTurn(across,down,turnVal);
                check=1;
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage()+" Please choose another position.");
            }
        }
    }

    private void getInput() {
        Scanner input = new Scanner(System.in);
        int check = 0;

        while (check==0) {
            try {
                System.out.print("Enter the row to place your token (1-3): ");
                across = input.nextInt();
                check=1;
            } catch (Exception e) {
                System.out.println("Invalid. Please try again");
                input.nextLine();
            }
        }

        check=0;

        while (check==0) {
            try {
            System.out.print("Enter the column to place your token (1-3): ");
                down = input.nextInt();
                check=1;
            } catch (Exception e) {
                System.out.println("Invalid. Please try again");
                input.nextLine();
            }
        }

        getTurnVal();
    }

    private void getTurnVal() {
        Scanner input = new Scanner(System.in);
        int check = 0;

        while (check==0) {
            try {
                System.out.print("Enter the number you would like to play: ");
                turnVal = input.nextInt();
                check=1;
            } catch (Exception e) {
                System.out.println("Invalid. Please try again");
                input.nextLine();
            }
        }
    }

    /**
     * main method
     * @param args
    */
    public static void main(String[] args) {
        NumTextUI tester = new NumTextUI();

        tester.play();
    }
}