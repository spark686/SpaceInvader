# SpaceInvader
For the second project, we decided to build to the game Space Invader, the 2-dimensional arcade game. The users can either win the game by taking all of the enemies down or lose the game by making its stamina 0. There are 3 different stages that progressively becomes harder as the user advance from one to the other. User can ascend each level by clearing out all the visible enemies. Each time the user defeat an ememy, their score increment by some number which is based on the type of enemy. The score is visible at the upper right hand corner of the screen. 

# How to play
There are three possible user inputs that controls an object: left arrow key input, right arrow key input, and space bar input. Left arrow key and right arrow key inputs move an object horizontally on x-axis. An object does not move along y-axis. The space bar input creates a bullet in front of user spaceship, which is used to defeat the enemy NPCs. Each bullet ascend only on y-axis. 

# How to run it:
1. Type "make" in the terminal
2. Type "./space" in the terminal

# How to win
The user can win by taking all of the enemies for each of the stages. The user can know the won the game because the win screen shows up. They can either click restart to replay the game or exit the screen.

# How to loss
The user loss the game by getting hit by the enemies' bullets. The user can know that they lost on the following game when the lost screen shows up. Similar to the win screen, they can either click restart to replay the game or exit the screen. 

<!-- # TrackC
# Purpose:
The purpose of checkpoint 2 Track C is to design non-player objects that does not directly depend on user inputs. Each bullet created from space bar inputs becomes NPCs that can move by itself. It moves toward the top of the screen, only ascending its y-axis location. We also created three types of enemies, each with different health and speed. These enemies move left and right making it difficult for the user to shoot them. These enemies are stored in a vector and their position are incremented every cycle.

# How to run it:
Follow the "#How to run it" from checkpoint 2 Track B. -->
