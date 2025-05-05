##  Project Structure
  This project is organized into several core classes that interact to form the main executable. The primary game elements include Entity, DraggableEntity, and StaticEntity—each representing a type of block that can move or interact with the game world. Each of these classes has its own .hpp and .cpp files, located in the include/ and src/ folders respectively. 
  
  The include/ folder contains all header (.hpp) files for the classes used in the project. The src/ folder holds the corresponding implementation (.cpp) files, as well as any game assets such as images. Make sure these images remain in this location, as paths are hardcoded relative to this directory. 
  
  A .vscode/ folder is included for users of Visual Studio Code. It contains JSON configuration files (such as tasks.json and launch.json) that define how the project is built and run in that environment. 
  
  Finally, the build/ folder is where the compiled executable and any build artifacts are placed. This folder can typically be cleaned or regenerated without affecting source code.

## Setup For Development
  The general recommended setup is an IDE with strong file and project management capabilities. I personally used VSCode throughout the entire project, but any C++-compatible IDE, such as Visual Studio or CLion, should work just as well. Windows is the preferred development environment since all file paths and build configurations are set up for Windows by default. 
  
  To build and run the project, it is required that both Box2D and SDL3 are installed and correctly configured. This includes setting up include paths, library paths, and any necessary runtime dependencies in your IDE or build system. Make sure your compiler (e.g., g++, MSVC) is compatible with C++17 or later. If you're using a different OS, additional configuration may be needed and is not officially supported.

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
  All code in the repository should follow a consistent and readable style. Use CamelCase for all variables. Global variables must be fully capitalized to distinguish them clearly. Choose variable names that are specific and descriptive, and limit their scope to the most local context possible to avoid conflicts.

  Function names should also use CamelCase, while class names should follow PascalCase (starting with a capital letter). Organize code logically by grouping related functions and classes together. Keep each file focused on a single purpose, and use folders to separate assignments or modules.

  Write concise comments that explain non-obvious logic. Include a docstring at the top of each script and for each function to describe its purpose and usage. Comments should clarify what the code is doing without restating the obvious.

  Use consistent formatting: 4 spaces for indentation, avoid tabs, and limit lines to a maximum of 82 characters. Leave a blank line between functions and two blank lines between classes to improve readability.

  Write commit messages in the present tense, summarizing what was changed and why. Keep messages clear and concise to support effective version tracking and collaboration.

## Known Limitations
  At this point this project is far from complete, but here is a short list of the biggest current issues and a even briefer how to fix them.
  - Main menu needs interactive buttons, needs to be fixed in level and event handling
  - game needs better level flow, need to improve the generalizability of level end check
  - levels need to be build more extensively, and many more levels need to be built
  - volume and settings need to be implemented, and a way to pause the game loop as well

these are just a few big picture things at the moment, but there are a couple smaller images you will surely run into if you delve into this.
