package game;

import java.io.IOException;
import java.util.StringTokenizer;

public class Player implements boardgame.Saveable {
    private int games;
    private int wins;
    private int losses;

    /**
     * constructor
    */
    public Player() {
        games=0;
        wins=0;
        losses=0;
    }

    private void setGames(int numGames) {
        games = numGames;
    }

    private void setWins(int numWins) {
        wins = numWins;
    }

    private void setLosses(int numLosses) {
        losses = numLosses;
    }

    /**
     * gets value of instance variable games
     * @return int that is value of games
    */
    public int getGames() {
        return games;
    }

    /**
     * gets value of instance variable wins
     * @return int that is value of wins
    */
    public int getWins() {
        return wins;
    }

    /**
     * gets value of instance variable losses
     * @return int that is value of losses
    */
    public int getLosses() {
        return losses;
    }

    /**
     * increments number of games played
    */
    public void addGames() {
        games = games + 1;
    }

    /**
     * increments number of wins
    */
    public void addWins() {
        wins = wins + 1;
    }

    /**
     * increments number of losses
    */
    public void addLosses() {
        losses = losses + 1;
    }

    /**
     * creates string to save to file
     * @return string that will be saved
    */
    @Override
    public String getStringToSave() {
        String save;

        save = getGames()+","+getWins()+","+getLosses();

        return save;
    }
    
    /**
     * loads information from file into game
     * @param fileInfo string that was read from file
    */
    @Override
    public void loadSavedString(String fileInfo) {
        StringTokenizer tokens = new StringTokenizer(fileInfo,",");

        tokens = loadGames(tokens);
        tokens = loadWins(tokens);
        tokens = loadLosses(tokens);

        if(tokens.hasMoreTokens()) {
            throw new IllegalArgumentException("Too many symbols in file.");
        }
    }

    private StringTokenizer loadGames(StringTokenizer tokens) {
        String value;
        int integerValue;

        value = tokens.nextToken().strip();

        try {
            integerValue = Integer.parseInt(value);
        } catch (NumberFormatException e) {
            throw new NumberFormatException("There is an invalid symbol in the file.");
        }

        if (integerValue>=0) {
            setGames(integerValue);
        } else {
            throw new IllegalArgumentException("There is an invalid symbol in the file.");
        }

        return tokens;
    }

    private StringTokenizer loadWins(StringTokenizer tokens) {
        String value;
        int integerValue;

        value = tokens.nextToken().strip();

        try {
            integerValue = Integer.parseInt(value);
        } catch (NumberFormatException e) {
            throw new NumberFormatException("There is an invalid symbol in the file.");
        }

        if (integerValue>=0) {
            setWins(integerValue);
        } else {
            throw new IllegalArgumentException("There is an invalid symbol in the file.");
        }

        return tokens;
    }

    private StringTokenizer loadLosses(StringTokenizer tokens) {
        String value;
        int integerValue;

        value = tokens.nextToken().strip();

        try {
            integerValue = Integer.parseInt(value);
        } catch (NumberFormatException e) {
            throw new NumberFormatException("There is an invalid symbol in the file.");
        }

        if (integerValue>=0) {
            setLosses(integerValue);
        } else {
            throw new IllegalArgumentException("There is an invalid symbol in the file.");
        }

        return tokens;
    }

}