##  Project Structure
This project is organized into several classes that all interact and combine into the main executable. the Entity, DraggableEntity, and StaticEntity are all implementaitons of a block that can move and interact with the gameworld, and have their corresponding .hpp and .cpp files in include and source respectivly. the inlcude folder also has the rest of the .hpp class files, while the src has the corresponding .cpp file and also the images the project uses. the project has a .vscode folder where all of the json make files are stored, and finally a build folder where the final executable is deposited.

## Setup For Development
  the general recommended setup is an ide with good file management settings, i personally have used VScode for the entirety of the project but VS or any other cpp compatible ide should work. windows is the recommended use and development environment because all of the file paths are for windows.
  it is also required that you have box2d and SDL3 installed and properly pathed to to be able to run and complile the software.

## How to Contribute
Getting Started
1. Fork the Main Repository:
  Fork the main repository into your GitHub account. This action creates a new repository in your account, where you'll be working from.

2. Sync Your Repository:
    If you've forked the repository earlier, it's important to keep it up to date. Follow these steps to sync your fork with the latest version:
    
    Configure the remote for your fork:
    
    git remote add upstream https://github.com/YourGitHubUsername/YourCourseRepo
    Fetch any changes from the upstream:
    
    git fetch upstream
    Checkout the local main branch of your fork:
    
    git checkout main
    Merge changes from the upstream into your main branch:
    
    git merge upstream/main
    Making Changes

3. Commit and Push:
    Commit your changes to your local repository:
    
    git commit -m "Your descriptive commit message"
    Push your changes to your online repository:
    
    git push origin main
5. Create a Pull Request:
  Submit a pull request to submit your work for review.


## Code Standards
  use CamelCase for all varibles, and all global varibles must be capitalized. use specific names, and when possible as local as possible to prevent any overlap.

## Known Limitations
  At this point this project is far from complete, but here is a short list of the biggest current issues and a even briefer how to fix them.
  - Main menu needs interactive buttons, needs to be fixed in level and event handling
  - game needs better level flow, need to improve the generalizability of level end check
  - levels need to be build more extensively, and many more levels need to be built
  - volume and settings need to be implemented, and a way to pause the game loop as well

these are just a few big picture things at the moment, but there are a couple smaller images you will surely run into if you delve into this.
