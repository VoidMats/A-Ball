
# A-Ball

1. Compilation instructions
2. Generating Doxygen
3. User instructions
4. Notes on game

## 1. Compilation instructions

Download or clone the repository into a folder of your choice.
Make sure you have a c++ compiler, supporting std=c++14.
Enter the software folder inside the repository using your terminal.

If you do not have sfml installed, type:
```console
  $ sudo apt-get install libsfml-dev
```

If you want to delete old cmake files, type:
```console
  $ \rm -r CMakeCache.txt CMakeFiles/
```
Type:
```console
    cmake .
```
Type:
```console
    make
```
To start the game
Type:
```console
    ./sfml
```

## 2. Generating Doxygen

Enter the software folder inside the repository using your terminal.

Type:
```console
  $ doxygen Doxyfile
```

Resulting files found in the html and latex folders.

## 3. User instructions

A-Ball: A game where you control a paddle in space. Your goal is to destroy all the evil spacebricks by bouncing the ball around the battlefield. But be careful, you cannot allow the ball fall down into the abyss or you will lose a life. Sometimes when a brick is destroyed a mystical powerup will fall. Pick it up to gain special powers for a limited amount of time. However, not all powers are beneficial...

## Keyboard controls

Menu navigation:

Up: Up-arrow
Down: Down-arrow
Select: Enter
Exit: Esc

Gameplay:

Up: Up-arrow
Down: Down-arrow
Left: Left-arrow
Right: Right-arrow
Shoot ball: Space
Exit: Esc


## 4. Notes on game

Brick size:
Width: 40
Height: 20

Number of bricks in one row: 16
Number of rows in the game: 16

Window size:
Width: 640
Height: 800

Moving objects list:
Ball class
Player class
Power_up class
Shot class

Static objects list:
Box class

Brick objects list:
Brick class
