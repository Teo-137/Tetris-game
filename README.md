# Tetris-game
The Tetris project is a computer implementation of the classic Tetris game. The player manipulates falling 
blocks of various shapes in such a way that they form complete horizontal lines. When a line is completely 
filled with blocks, it is removed, and the player earns points. The game ends when the blocks reach the top 
edge of the board.

Intruction
The program starts by asking the player to enter their nickname. Then, a menu is displayed with the following options: Play, Settings, High Scores, and Exit.
In the Settings menu, the player can choose the difficulty level, which determines the speed at which the blocks fall: Easy, Medium Hard, Endless – the speed gradually increases over time.
The High Scores table displays the top 10 best scores, sorted and shown with the date they were achieved and the nickname of the player.
During gameplay, the user can use the following keys: A – move the block left,  D – move the block right, S – move the block down, W – rotate the block, Q – quit the game (requires confirmation)
Points are awarded based on the number of lines cleared at once, and are calculated using the factorial function: Clearing 1 line – 1 point, Clearing 2 lines – 2 points, Clearing 3 lines – 6 points, Clearing 4 lines – 24 points

Compilation
To compile the project, simply use the standard procedure:
g++ main.cpp tetris.cpp block.cpp board.cpp -o main 
The program uses the <conio.h> library for the functions getch() and kbhit(), which are not available on Linux systems.
