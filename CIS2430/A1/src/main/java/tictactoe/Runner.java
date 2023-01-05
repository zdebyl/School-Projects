public class Runner {

    public static void main(String[] args) {
        //declare instance of game and string to hold return value
        Game play = new Game();
        String winner;

        //get and print winner
        winner = play.getWinner();
        System.out.println(winner);
        
    }
}