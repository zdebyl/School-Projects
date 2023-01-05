package tictactoe;

import game.SaveLoadFiles;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JFileChooser;
import javax.swing.filechooser.FileSystemView;
import java.io.File;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import boardgame.ui.PositionAwareButton;

import game.GameUI;

public class TicTacToeView extends JPanel {
    private TicTacToe play;
    private GameUI gameSuite;
    private PositionAwareButton[][] board;
    private JLabel playerTurnLabel;

    /**
     * constructor
     * @param wide width of board
     * @param tall height of board
     * @param gameFrame frame that class is from
    */
    public TicTacToeView(int wide, int tall, GameUI gameFrame) {
        super();

        gameSuite = gameFrame;

        setLayout(new BorderLayout());

        this.play = new TicTacToe(3,3);

        gameSuite.setJMenuBar(makeSaveLoadMenu());

        add(makeTitlePanel(), BorderLayout.NORTH);
        add(makeButtonsPanel(), BorderLayout.SOUTH);
        add(playerTurnPanel(), BorderLayout.EAST);
        add(makeButtonGrid(3,3), BorderLayout.CENTER);

        startGame();
    }

    private void startGame() {
        play.setCurrentPlayer(1);
        playerTurnMessage();

        play.newGame();
        setBoard();
    }

    private JPanel makeTitlePanel() {
        JPanel titlePanel = new JPanel();
        titlePanel.add(makeTitle());
        return titlePanel;
    }

    private JPanel makeButtonsPanel() {
        JPanel buttonsPanel = new JPanel();
        buttonsPanel.add(makeGameSuiteButton());
        return buttonsPanel;
    }

    private JLabel makeTitle() {
        JLabel title = new JLabel("Welcome to TicTacToe!");
        return title;
    }

    private JButton makeGameSuiteButton() {
        JButton tictactoe = new JButton("Return to Game Suite");
        tictactoe.addActionListener(e->returnToGameSuite());
        return tictactoe;
    }

    private JPanel makeButtonGrid(int tall, int wide){
        JPanel panel = new JPanel();
        board = new PositionAwareButton[tall][wide];
        panel.setLayout(new GridLayout(wide, tall));
        
        for (int y=0; y<wide; y++) {
            for (int x=0; x<tall; x++) { 
            //Create buttons and link each button back to a coordinate on the grid
            board[y][x] = new PositionAwareButton();
            board[y][x].setAcross(x+1); //made the choice to be 1-based
            board[y][x].setDown(y+1);
            board[y][x].addActionListener(e->playTurn(e));
            panel.add(board[y][x]);
            }
        }
        return panel;
    }

    private JMenuBar makeSaveLoadMenu() {
        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("Save/Load Options");
        JMenuItem loadGame = new JMenuItem("Load Game");
        JMenuItem saveGame = new JMenuItem("Save Game");

        menu.add(loadGame);
        menu.add(saveGame);
        menuBar.add(menu);

        loadGame.addActionListener(e1->doLoadGame());
        saveGame.addActionListener(e2->doSaveGame());

        return menuBar;
    }

    /**
     * loads game
    */
    protected void doLoadGame() {
        File loadFile;
        String loadFilePath;
        String loadFileName;
        JFileChooser loadFileChoice = new JFileChooser();
        int loadUserChoice = loadFileChoice.showOpenDialog(this);

        if(loadUserChoice==JFileChooser.APPROVE_OPTION) {
            loadFile = loadFileChoice.getSelectedFile();
            loadFilePath = loadFile.getAbsolutePath();
            loadFileName = loadFile.getName();
            try {
                SaveLoadFiles.load(play, loadFileName, loadFilePath);
                setBoard();
                playerTurnMessage();
            } catch (IllegalArgumentException e) {
                JOptionPane.showMessageDialog(null,e.getMessage()+" Starting new game.");
                startGame();
            }  
        }
    }

    /**
     * saves game
    */
    protected void doSaveGame() {
        File saveFile;
        String saveFilePath;
        String saveFileName;
        JFileChooser saveFileChoice = new JFileChooser();
        int saveUserChoice = saveFileChoice.showOpenDialog(this);

        if(saveUserChoice==JFileChooser.APPROVE_OPTION) {
            saveFile = saveFileChoice.getSelectedFile();
            saveFilePath = saveFile.getAbsolutePath();
            saveFileName = saveFile.getName();
            try {
                SaveLoadFiles.save(play, saveFileName, saveFilePath);
            } catch (IllegalArgumentException e) {
                JOptionPane.showMessageDialog(null,e.getMessage());
            }
        }
    }

    private JPanel playerTurnPanel() {
        JPanel playerTurnPanel = new JPanel();
        playerTurnLabel = new JLabel();
        playerTurnPanel.add(playerTurnLabel);

        return playerTurnPanel;
    }

    private void playerTurnMessage() {
        playerTurnLabel.setText("Its player "+play.getCurrentPlayer()+"'s turn");
    }


    private void setBoard() {
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                board[i][j].setText(play.getCell(j+1,i+1));
            }
        }
    }

    /**
     * does turn and checks board to see if game is over
     * @param e button clicked
    */
    protected void playTurn(ActionEvent e) {
        if(changeButton(e)) {
            checkGame();
        }
    }

    private boolean changeButton(ActionEvent e) {
        String userInput;
        int across;
        int down;
        boolean returnValue=false;

        PositionAwareButton change = ((PositionAwareButton)(e.getSource()));

        across = change.getAcross();
        down = change.getDown();

        userInput = collectInput();

        if (!userInput.equals("")) {
            try {
                play.takeTurn(across,down,userInput);
                returnValue=true;
            } catch (IllegalArgumentException except) {
                JOptionPane.showMessageDialog(null,except.getMessage());
            }

            change.setText(play.getCell(across,down));
        }

        return returnValue;
    }

    private String collectInput() {
        String userInput="";
        String input;
        int playerTurn = play.getCurrentPlayer();

        if (playerTurn==1) {
            input = "X";
        } else {
            input = "O";
        }

        userInput = JOptionPane.showInputDialog("Enter an "+input+": ");

        if (!userInput.equals(input)) {
            JOptionPane.showMessageDialog(null,"Invalid symbol");
            userInput="";
        }

        return userInput;
    }

    private void checkGame() {
        int userChoice;

        if(play.isDone()) {
            gameSuite.updatePlayers(play.getWinner());

            JOptionPane.showMessageDialog(null,play.getGameStateMessage());
            userChoice = JOptionPane.showConfirmDialog(
                null,"Would you like to play again (or press no to return to the Game Suite)?",
                "Game Over!", JOptionPane.YES_NO_OPTION);

            if(userChoice == JOptionPane.YES_OPTION) {
                startGame();
            } else {
                returnToGameSuite();
            }
        } else {
            play.incrementCurrentPlayer();
            playerTurnMessage();
        }
    }

    /**
     * go back to game suite
    */
    protected void returnToGameSuite() {
        gameSuite.reset();
    }

}