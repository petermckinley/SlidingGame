# User Manual – SlidingGame

## Installation / Setup Guide

1. **Install a C++ Compiler**
   Ensure your system has one of the following installed and configured in the system PATH:

   * GCC (Linux)
   * Clang (macOS)
   * MSVC (Windows via Visual Studio)

2. **Install SDL3**

   * Download SDL3 development libraries suitable for your OS.
   * Set up the include/library paths in your build system (e.g., `CMakeLists.txt` or IDE project settings).

3. **Install Box2D**

   * Download or clone the Box2D source code or binaries.
   * Ensure headers and libraries are available to your build system.
   * Note: **Box2D must be placed in a specific folder as expected by the project.** Update include paths or project files accordingly.

4. **Ensure Correct Folder Setup**

   * This project contains hardcoded file paths. Make sure that required folders and resources are located correctly relative to the executable.
   * Important folders include:

     * `assets/` (for game assets like images or fonts)
     * `config/` (for any settings or parameters)
     * `levels/` (if the game supports level data files)

5. **Build the Project**
   From the root of the project:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

   Alternatively, use an IDE like Visual Studio or CLion if preferred.

6. **Run the Game**
   After building:

   ```bash
   ./SlidingGame
   ```

---

## Basic Usage

* Launch the game executable.
* Use keyboard inputs to move sliding blocks.
* Goal: Rearrange blocks into a specific target configuration (win condition).
* Controls may vary depending on implementation (e.g., arrow keys or WASD).

---

## Controls

- Arrow keys or WASD: Move the player
- Mouse (click and drag): Move draggable blocks
- R: Reset the current level (if implemented)
- Esc: Quit the game


## Screenshots

![Image](https://github.com/user-attachments/assets/d0cba9d6-5705-4d6d-b03a-2bfb0d0924e3)
![Image](https://github.com/user-attachments/assets/5851f471-7fb3-4bea-8aa1-80e3ef639035)

---

##  Features

* Classic sliding puzzle game mechanics.
* Collision and boundary detection.
* Optional support for customizable block layouts or level files.
* Win condition handling.

---

##  FAQ

**Q: Game doesn’t start**
A: Make sure SDL3 and Box2D are installed and correctly configured. Ensure all hardcoded folders and files are present.

**Q: How do I reset the puzzle?**
A: Restart the application or press the reset key (if implemented yet).

**Q: Can I add new puzzles?**
A: Yes, either by modifying configuration files or by hardcoding new layouts directly into the `src/` code. Level system is currently in development.
