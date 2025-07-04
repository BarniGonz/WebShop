# Space Shooter Game

A complete C++ space shooter game built with SFML (Simple and Fast Multimedia Library).

## Features

- **Player Control**: Move with WASD or arrow keys, shoot with SPACE
- **Enemy AI**: Enemies spawn automatically and shoot back
- **Collision Detection**: Bullets destroy enemies, enemy bullets/ships destroy player
- **Scoring System**: Earn points by destroying enemies
- **Game States**: Menu, gameplay, and game over screens
- **Smooth Gameplay**: 60 FPS with proper delta time handling

## Game Controls

- **Movement**: WASD or Arrow Keys
- **Shoot**: SPACE (while playing)
- **Start Game**: SPACE (from menu)
- **Restart**: R (from game over screen)
- **Quit**: ESC

## Requirements

- C++17 compiler (GCC, Clang, or MSVC)
- CMake 3.16 or higher
- SFML 2.5 or higher

## Building the Game

### On Ubuntu/Debian:
```bash
# Install dependencies
sudo apt update
sudo apt install build-essential cmake libsfml-dev

# Build the game
mkdir build
cd build
cmake ..
make

# Run the game
./space_shooter
```

### On macOS:
```bash
# Install dependencies (with Homebrew)
brew install cmake sfml

# Build the game
mkdir build
cd build
cmake ..
make

# Run the game
./space_shooter
```

### On Windows:
```bash
# Install SFML and ensure it's in your PATH
# Or use vcpkg: vcpkg install sfml

# Build with Visual Studio
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release

# Run the game
./Release/space_shooter.exe
```

## Project Structure

```
├── CMakeLists.txt          # Build configuration
├── README.md               # This file
├── include/                # Header files
│   ├── Game.h             # Main game class
│   ├── Player.h           # Player spaceship
│   ├── Enemy.h            # Enemy spaceships
│   └── Bullet.h           # Projectiles
├── src/                   # Source files
│   ├── main.cpp           # Entry point
│   ├── Game.cpp           # Game implementation
│   ├── Player.cpp         # Player implementation
│   ├── Enemy.cpp          # Enemy implementation
│   └── Bullet.cpp         # Bullet implementation
└── assets/                # Game assets (optional)
    └── arial.ttf          # Font file (optional)
```

## Game Design

### Classes

1. **Game**: Main game loop, handles events, updates, and rendering
2. **Player**: Green spaceship controlled by the player
3. **Enemy**: Red spaceships that move down and shoot
4. **Bullet**: Yellow (player) and magenta (enemy) projectiles

### Gameplay Mechanics

- Player starts at the bottom center of the screen
- Enemies spawn every 2 seconds at random X positions
- Enemies move downward and occasionally shoot
- Player bullets move upward, enemy bullets move downward
- Collision detection destroys objects and updates score
- Game ends when player is hit by enemy or enemy bullet

## Troubleshooting

### SFML Not Found
```bash
# On Ubuntu/Debian
sudo apt install libsfml-dev

# On macOS
brew install sfml

# On Windows
# Download SFML from https://www.sfml-dev.org/download.php
# Or use vcpkg: vcpkg install sfml
```

### Font Loading Warning
The game will display a warning if `assets/arial.ttf` is not found, but will still run with the default SFML font.

### Build Errors
Make sure you have:
- C++17 compatible compiler
- CMake 3.16+
- SFML 2.5+ properly installed and accessible

## License

This project is open source and available under the MIT License.