public class Board {
    //instance variables
    private StringBuilder line1;
    private StringBuilder line2;
    private StringBuilder line3;
    private StringBuilder line4;
    private StringBuilder line5;

    //constructor
    public Board() {
        setBoard();
    }

    //creates board
    public void setBoard() {
        //initialize each line
        line1 = new StringBuilder("0|1|2");
        line2 = new StringBuilder("-+-+-");
        line3 = new StringBuilder("3|4|5");
        line4 = new StringBuilder("-+-+-");
        line5 = new StringBuilder("6|7|8");
    }

    //does everything for board and returns true/false for winner
    public void getBoard(int numTurn, int position, Character playerTurn) {
        //check board, change board and check winner
        if (numTurn != 0) {
            changeBoard(position, playerTurn);
        }

        //display board
        displayBoard();
    }

    //updates board after users turn
    private void changeBoard(int position, Character playerTurn) {
        //check position of where player wants to go
        if (position==0) {
            line1.replace(line1.indexOf("0"), line1.indexOf("0")+1, playerTurn.toString());
        } else if (position==1) {
            line1.replace(line1.indexOf("1"), line1.indexOf("1")+1, playerTurn.toString());
        } else if (position==2) {
            line1.replace(line1.indexOf("2"), line1.indexOf("2")+1, playerTurn.toString());
        } else if (position==3) {
            line3.replace(line3.indexOf("3"), line3.indexOf("3")+1, playerTurn.toString());
        } else if (position==4) {
            line3.replace(line3.indexOf("4"), line3.indexOf("4")+1, playerTurn.toString());
        } else if (position==5) {
            line3.replace(line3.indexOf("5"), line3.indexOf("5")+1, playerTurn.toString());
        } else if (position==6) {
            line5.replace(line5.indexOf("6"), line5.indexOf("6")+1, playerTurn.toString());
        } else if (position==7) {
            line5.replace(line5.indexOf("7"), line5.indexOf("7")+1, playerTurn.toString());
        } else if (position==8) {
            line5.replace(line5.indexOf("8"), line5.indexOf("8")+1, playerTurn.toString());
        }
    }

    //display board
    private void displayBoard() {
        //print each line
        System.out.println(line1.toString());
        System.out.println(line2.toString());
        System.out.println(line3.toString());
        System.out.println(line4.toString());
        System.out.println(line5.toString());
    }
}