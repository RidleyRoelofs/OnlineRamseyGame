Welcome to the Online Ramsey Game on K_6!

The rules are simple. 
Two players: Builder and Painter. Both will agree on the size of red path and blue cycle at the start of the game. Then play will commence on the Builder's turn. The Builder will select an edge to build, and then the Painter will choose to paint the edge either red or blue. Keep in mind that by painting a red path or blue cycle with the specified size, will result in a win for the Builder. The players will tie if all edges have been built/painted without painting the red path or blue cycle.

Enjoy!

Building and Installing the Online Ramsey Game
==============================================

This section provides instructions for building and installing the Online Ramsey Game software using CMake.

Step 1: Clone the Repository
----------------------------
Open a terminal and clone the GitHub repository containing the project software:
git clone https://github.com/uvic-seng475-2023-05/cpp_project-onlineramseygame.git

Step 2: Navigate to Top Directory
----------------------------
cd OnlineRamseyGame

Step 3: Configure the Build
----------------------------
Specify the $INSTALL_DIR
cmake -H. -Btmp_cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR

Step 4: Build and Install Software
----------------------------
Build and install the software out of source using:
cmake --build tmp_cmake --clean-first --target install

Step 5: Run the Demo Script
----------------------------
Run the following script located in the install directory:
$INSTALL_DIR/bin/demo
