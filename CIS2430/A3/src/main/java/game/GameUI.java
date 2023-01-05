package game;

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
import java.awt.FlowLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import numericaltictactoe.NumTicTacToeView;
import tictactoe.TicTacToeView;

public class GameUI extends JFrame {
    private JPanel gamePanel;
    private Player player1;
    private Player player2;

    /**
     * constructor
     * @param title title of game
    */
    public GameUI(String title) {
        super();
        gamePanel = new JPanel();
        player1 = new Player();
        player2 = new Player();

        this.setSize(500,500);
        this.setTitle(title);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setLayout(new BorderLayout());

        add(gamePanel, BorderLayout.CENTER);
        add(makeButtonsPanel(), BorderLayout.SOUTH);
        reset();

        pack();
        setVisible(true);  
    }

    private JPanel makeTitlePanel() {
        JPanel titlePanel = new JPanel();
        titlePanel.add(makeTitle());
        return titlePanel;
    }

    private JPanel makeButtonsPanel() {
        JPanel buttonsPanel = new JPanel();
        buttonsPanel.setLayout(new FlowLayout());
        buttonsPanel.add(makeTicTacToeButton());
        buttonsPanel.add(makeNumTicTacToeButton());
        return buttonsPanel;
    }

    private JLabel makeTitle() {
        JLabel title = new JLabel("Welcome to the game suite!");
        return title;
    }

    private JButton makeTicTacToeButton() {
        JButton tictactoe = new JButton("Play TicTacToe");
        tictactoe.addActionListener(e->playTicTacToe());
        return tictactoe;
    }

    private JButton makeNumTicTacToeButton() {
        JButton numtictactoe = new JButton("Play Numerical TicTacToe");
        numtictactoe.addActionListener(e->playNumTicTacToe());
        return numtictactoe;        
    }

    private JMenuBar makePlayerProfileMenu() {
        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("Player Profile");
        JMenuItem loadPlayer1Profile = new JMenuItem("Load Player 1 Profile");
        JMenuItem loadPlayer2Profile = new JMenuItem("Load Player 2 Profile");
        JMenuItem savePlayer1Profile = new JMenuItem("Save Player 1 Profile");
        JMenuItem savePlayer2Profile = new JMenuItem("Save Player 2 Profile");

        menu.add(loadPlayer1Profile);
        menu.add(loadPlayer2Profile);        
        menu.add(savePlayer1Profile);
        menu.add(savePlayer2Profile);
        menuBar.add(menu);

        loadPlayer1Profile.addActionListener(e1->doLoadPlayer1Profile());
        loadPlayer2Profile.addActionListener(e1->doLoadPlayer2Profile());
        savePlayer1Profile.addActionListener(e2->doSavePlayer1Profile());
        savePlayer2Profile.addActionListener(e2->doSavePlayer2Profile());

        return menuBar;
    }

    /**
     * starts tictactoe game
    */
    protected void playTicTacToe() {
        gamePanel.removeAll();
        gamePanel.add(new TicTacToeView(3,3,this));

        getContentPane().repaint();
        getContentPane().revalidate();
        pack();
    }

    /**
     * starts numtictactoe
    */
    protected void playNumTicTacToe() {
        gamePanel.removeAll();
        gamePanel.add(new NumTicTacToeView(3,3,this));

        getContentPane().repaint();
        getContentPane().revalidate();
        pack();
    }

    /**
     * loads player 1's profile
    */
    protected void doLoadPlayer1Profile() {
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
                SaveLoadFiles.load(player1, loadFileName, loadFilePath);
            } catch (IllegalArgumentException e) {
                JOptionPane.showMessageDialog(null,e.getMessage());
            }  
        }
    }

    /**
     * loads player 2's profile
    */
    protected void doLoadPlayer2Profile() {
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
                SaveLoadFiles.load(player2, loadFileName, loadFilePath);
            } catch (IllegalArgumentException e) {
                JOptionPane.showMessageDialog(null,e.getMessage());
            }  
        }
    }

    /**
     * saves player 1's profile
    */
    protected void doSavePlayer1Profile() {
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
                SaveLoadFiles.save(player1, saveFileName, saveFilePath);
            } catch (IllegalArgumentException e) {
                JOptionPane.showMessageDialog(null,e.getMessage());
            }
        }
    }

    /**
     * saves player 2's profile
    */
    protected void doSavePlayer2Profile() {
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
                SaveLoadFiles.save(player2, saveFileName, saveFilePath);
            } catch (IllegalArgumentException e) {
                JOptionPane.showMessageDialog(null,e.getMessage());
            }
        }
    }

    /**
     * updates players statistics
     * @param winnerCheck int that represents the state of the game
    */
    public void updatePlayers(int winnerCheck) {
        if (winnerCheck==0||winnerCheck==1||winnerCheck==2) {
            player1.addGames();
            player2.addGames();
        }

        if (winnerCheck==1) {
            player1.addWins();
            player2.addLosses();
        } else if (winnerCheck==2) {
            player2.addWins();
            player1.addLosses();
        }
    }

    /**
     * resets Game Suite
    */
    public void reset() {
        gamePanel.removeAll();

        gamePanel.add(makeTitlePanel(), BorderLayout.NORTH);

        setJMenuBar(makePlayerProfileMenu());
        
        getContentPane().repaint();
        getContentPane().revalidate();
        pack();
    }

    /**
     * main method
     * @param args
    */
    public static void main(String[] args) {
        GameUI game = new GameUI("Game Suite");
    }


}