##  Project Structure
This project is organized into several classes that all interact and combine into the main executable. the Entity, DraggableEntity, and StaticEntity are all implementaitons of a block that can move and interact with the gameworld, and have their corresponding .hpp and .cpp files in include and source respectivly. the inlcude folder also has the rest of the .hpp class files, while the src has the corresponding .cpp file and also the images the project uses. the project has a .vscode folder where all of the json make files are stored, and finally a build folder where the final executable is deposited.

## Setup For Development
  the general recommended setup is an ide with good file management settings, i personally have used VScode for the entirety of the project but VS or any other cpp compatible ide should work. windows is the recommended use and development environment because all of the file paths are for windows.
  it is also required that you have box2d and SDL3 installed and properly pathed to to be able to run and complile the software.

## How to Contribute
  Make a pull! the worst i can say is no do whatever you want to it. make sure to test and pull the current copy again before you commit, so code is not overridden.

## Code Standards
  use CamelCase for all varibles, and all global varibles must be capitalized. use specific names, and when possible as local as possible to prevent any overlap.

## Known Limitations
  At this point this project is far from complete, but here is a short list of the biggest current issues and a even briefer how to fix them.
  - Main menu needs interactive buttons, needs to be fixed in level and event handling
  - game needs better level flow, need to improve the generalizability of level end check
  - levels need to be build more extensively, and many more levels need to be built
  - volume and settings need to be implemented, and a way to pause the game loop as well
  these are just a few big picture things at the moment, but there are a couple smaller images you will surely run into if you delve into this.
