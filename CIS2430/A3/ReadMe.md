# A3

This program creates a Game Suite to allow two players to play TicTacToe and Numerical TicTacToe

## Description

This program uses a graphical user interface to create a Game Suite to allow users to play multiple games. Players have a choice of playing TicTacToe or Numerical TicTacToe and can also switch between games and return to the Game Suite when they would like. While playing, users can choose to save or load a game. While in the Game Suite, users can choose to save or load a players profile, which includes their statistics on the number of games played, games won and games lost. The format of this file is a csv file that has in a line; number of games played, number of wins, number of losses. This program also allows for a command line version of TicTacToe to be run.

## Getting Started

### Executing program

* Building and running the program for command line TicTacToe:
```
gradle build
gradle run
java -cp build/classes/java/main tictactoe.TextUI
```
* Expected output:
board representation

Its player 1's turn
Enter the row to place your token (1-3):

* Building and running the program for the Game Suite:
```
gradle build
gradle run
java -jar build/libs/A3.jar
```
* Expected output:
GUI with the title "Game Suite", message that says "Welcome to the game suite!", menu called Player Profile, button called "Play TicTacToe" and button called "Play Numerical TicTacToe

## Author Information

* Zoe Debyl
* zdebyl@uoguelph.ca

## Development History


* 1.9
    * added javadoc comments and README
    * See [commit change]() or See [release history]()
* 1.8
    * added methods for saving/loading player profiles
    * See [commit change]() or See [release history]()
* 1.7
    * moved files
    * See [commit change]() or See [release history]()
* 1.6
    * added class for player
    * See [commit change]() or See [release history]()
* 1.5
    * fixed error checking for files
    * See [commit change]() or See [release history]()
* 1.4
    * improved methods for implementing files
    * See [commit change]() or See [release history]()
* 1.3
    * add error checking
    * See [commit change]() or See [release history]()
* 1.2
    * load files that have been previously saved
    * See [commit change]() or See [release history]()
* 1.1
    * implemented file saving
    * See [commit change]() or See [release history]()
* 1.0
    * add save file for tictactoe
    * See [commit change]() or See [release history]()
* 0.9
    * added file and methods for loading/saving files
    * See [commit change]() or See [release history]()
* 0.8
    * added menu bar for saving and loading files/player profiles
    * See [commit change]() or See [release history]()
* 0.7
    * basic functioning games
    * See [commit change]() or See [release history]()
* 0.6
    * added grid for games
    * See [commit change]() or See [release history]()
* 0.5
    * setup gui
    * See [commit change]() or See [release history]()
* 0.4
    * NumTicTacToe methods complete and NumTextUI implemented for testing
    * See [commit change]() or See [release history]()
* 0.3
    * TicTacToe methods complete and TextUI complete
    * See [commit change]() or See [release history]()
* 0.2
    * tictactoe classes set up
    * See [commit change]() or See [release history]()
* 0.1
    * Initial Release
