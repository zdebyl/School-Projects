import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;

public class Game {
    //instance variables
    private Character playerTurn;
    private int numTurn;
    private Board theBoard;
    private ArrayList<Integer> positionsTaken;
    private ArrayList<Integer> positionsX;
    private ArrayList<Integer> positionsO;

    //constructor, sets turn originally
    public Game() {
        setTurn();
    }

    //sets initial values
    public void setTurn() {
        playerTurn = 'X';
        numTurn = 0;
        positionsTaken = new ArrayList<Integer>();
        positionsX = new ArrayList<Integer>();
        positionsO = new ArrayList<Integer>();
    }

    //runs game and returns winner
    public String getWinner() {
        boolean winnerOrNot=false;
        int position=-1;
        theBoard = new Board();
        String message;

        //keep playing until theres a winner
        while (!winnerOrNot && numTurn!=9) {
            //call getBoard
            theBoard.getBoard(numTurn, position, playerTurn);

            //check if theres a winner
            winnerOrNot = checkWinner();

            //if someone won, return the winner
            if (winnerOrNot) {
                message = "Winner = " + playerTurn;
                return message;
            }

            //if its not the first turn, change turn to next player
            if (numTurn==0) {
                numTurn++;
            } else {
                changeTurn();
                numTurn++;
            }

            //call userTurn
            position = userTurn();
        }

        message = "It's a tie!";
        return message;
    }

    //output and input for users turn and ensures valid number is input
    private int userTurn() {
        int position=-1;
        int valid=0;
        Scanner input = new Scanner(System.in);

        //get and validate user input
        while (valid<2) {
            valid=0;

            System.out.println("Its player "+playerTurn+"'s turn");
            System.out.print("Enter Position between 0 and 8:\n");
            position = input.nextInt();

            //check if its between 0-8
            if (position>=0 && position<=8) {
                valid++;
            } else {
                System.out.println("Error - Out of Bounds");
            }

            //check if the spot has already been taken
            if (positionsTaken.contains(position)) {
                System.out.println("This spot is already taken!");
            } else {
                valid++;
            }
        }

        //add position to list of taken positions
        positionsTaken.add(position);

        if (playerTurn == 'X') {
            positionsX.add(position);
        } else {
            positionsO.add(position);
        }
        
        //return users turn choice
        return position;
    }

    //changes to the next players turn
    private void changeTurn() {
        //change turn
        if (playerTurn == 'X') {
            playerTurn = 'O';
        } else {
            playerTurn = 'X';
        }
    }

    //checks if someone has won
    private boolean checkWinner() {
        //make win conditions
        ArrayList<Integer> win1 = new ArrayList<Integer>();
        win1.addAll(Arrays.asList(0,1,2));
        ArrayList<Integer> win2 = new ArrayList<Integer>();
        win2.addAll(Arrays.asList(0,3,6));
        ArrayList<Integer> win3 = new ArrayList<Integer>();
        win3.addAll(Arrays.asList(0,4,8));        
        ArrayList<Integer> win4 = new ArrayList<Integer>();
        win4.addAll(Arrays.asList(3,4,5));
        ArrayList<Integer> win5 = new ArrayList<Integer>();
        win5.addAll(Arrays.asList(1,4,7));
        ArrayList<Integer> win6 = new ArrayList<Integer>();
        win6.addAll(Arrays.asList(2,4,6));
        ArrayList<Integer> win7 = new ArrayList<Integer>();
        win7.addAll(Arrays.asList(6,7,8));
        ArrayList<Integer> win8 = new ArrayList<Integer>();
        win8.addAll(Arrays.asList(2,5,8));

        //check win conditions
        if (playerTurn == 'X') {
            if (positionsX.containsAll(win1) || positionsX.containsAll(win2) || positionsX.containsAll(win3)) {
                return true;
            } else if (positionsX.containsAll(win4) || positionsX.containsAll(win5)){
                return true;
            } else if (positionsX.containsAll(win6) || positionsX.containsAll(win7)) {
                return true;
            } else if (positionsX.containsAll(win8)) {
                return true;
            }
        } else {
            if (positionsO.containsAll(win1) || positionsO.containsAll(win2) || positionsO.containsAll(win3)) {
                return true;
            } else if (positionsO.containsAll(win4) || positionsO.containsAll(win5)){
                return true;
            } else if (positionsO.containsAll(win6) || positionsO.containsAll(win7)) {
                return true;
            } else if (positionsO.containsAll(win8)) {
                return true;
            }
        }

        return false;
    }
}