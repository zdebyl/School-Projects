# Connect Four

This program allows two players using the same keyboard to play a game of Connect Four.

## Description

The program creates a board using tokens 0, 1 and 2; where 0 represents an empty space, and 1 and 2 represent player 1 and 2's tokens respetively. To start the game, the player can choose to load an old game from a csv file or start a new game. If loading an old game, the program will read the file, ensure it is properly formatted and check if there is already a winner or if the board is full. If it is a valid file, the game will continue with this board, at the correct player's turn. Otherwise, a new empty board will be created and the game will continue with this board. Player's alternate turns choosing the column in which they would like to place their token. As well, at each turn the player can choose if they would like to save the file. If they do, after it saves, they can choose to continue playing or to exit. If the players keep playing, the game will end once one player has four tokens in a row, either in a row, column, or diagonal, or if the board fills with no winner. Once this happens, the players can choose to exit or play a new game. If they choose to play a new game, it runs the same way, starting with asking the players if they would like to load an old game or start a new game.

## Getting Started

### Executing program

* Building and running the program:
```
gradle build
gradle run
java -cp build/classes/java/main connectfour.ConnectFour
```
* Expected output:
Enter '1' to load an old game or '2' to start a new game:

## Author Information

* Zoe Debyl
* zdebyl@uoguelph.ca

## Development History

* 0.9
    * Final changes
    * See [commit change]() or See [release history]()
* 0.8
    * Junit testing added
    * See [commit change]() or See [release history]()
* 0.7
    * Reconfigured classes and fixed bugs
    * See [commit change]() or See [release history]()
* 0.6
    * Exception handling added
    * See [commit change]() or See [release history]()
* 0.5
    * All methods finished, javadoc comments added
    * See [commit change]() or See [release history]()
* 0.4
    * Fixed bugs
    * See [commit change]() or See [release history]()
* 0.3
    * Fixed bugs
    * See [commit change]() or See [release history]()
* 0.2
    * Most methods completed
    * See [commit change]() or See [release history]()
* 0.1
    * Initial Release