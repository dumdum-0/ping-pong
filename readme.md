# PONG PONG

A simple game of pong but single player and increased difficulty.

Built entirely in C++ using [Raylib](https://www.raylib.com/)

## Features
- The velocity of the ball increases after each collision
- The score updates on each collision
- Clean implementation of paddle and ball using classes
- Playable with WASD and Arrow Keys

## Controls
| Action | Key |
| :--- | :--- |
|Move Up | 'W' or 'Up Arrow' |
|Move Down | 'S' or 'Down Arrow|

## Code Architecture 

- State Update - The position of paddle and ball is updated at each frame .
- Collision Check - The built in function 'CheckCollisionCircleRec' check each frame for collision of the paddle and ball .

## Prerequisites
To compile and run this project , you will need. 
- A C++ compiler
- [Raylib](https://github.com/raysan5/raylib)

## Build 

**Windows (MinGW) :**

```
g++ main.cpp -O2 -lraylib -lopengl32 -lgdi32 -lwinmm -o pong.exe
```
**Linux:**

```
g++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o pong
```

**macOS**

```
clang++ main.cpp -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -lraylib -o pong
```


