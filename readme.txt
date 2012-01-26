BattleBoat
v.1.6

This program loads first reading an ".ascii-art" file that contains ascii art of the name of the program (BattleBoat). If this file ends with a newline or does not exist, the program will still load, but the program may print the error it received or the title screen may display improperly.

Use the arrow keys to control the cursor.
Spacebar selects a space.
Hit 'Ctrl + H', 'BACKSPACE', or 'F1' for the help screen.
Hit 'Ctrl + Q' or 'ESC' to quit.

This version of Battleship was created on a Windows XP OS and is known to work on it. I have plans to test and release a *Nix version as well as a FreeBSD version.

I also included a header file (bbWin32.h) that includes windows.h to change console text color and clear the screen.

This version now has a separate header file for all programmer defined functions that are used in the game. This header file is called "bbFunctions.h".

I have made it so that the program reads in two .map files named playerA.map and playerB.map that are located in the executable's current directory. The .map files must have the following characters to make the game read correctly (it will fail loading and report errors if it finds anything other than the following):

5   C (uppercase)
4   B (uppercase)
3   S (uppercase)
3   c (lowercase)
2   p (lowercase)
83  ,

in other words, 100 characters (not counting whitespace) with a Carrier, a Battleship, a Submarine, a Cruiser, and a Patrol Boat, and all of the blank areas of water.

MUST HAVE CORRECT CAPITALIZATION AS WELL. This is important as there are two C characters (this will change as I am an idiot for doing it that way).

Each .map file is a set of characters; 10 lines with 10 characters each, ie:

C C C C C , , , , ,
, , , , , B , , , ,
, , , , , B , , , ,
, S S S , B , , , ,
, , , , , B , , , ,
, , , , , , , , , ,
, c c c , , , , , ,
, , , , , , , , , ,
, , , , , , , p p ,
, , , , , , , , , ,

Then save the map as playerA.map or playerB.map (depending on who the map is for).


Enjoy my tiny battleship program with little functionality, but lots of possibilities.
If you have any problems, tell me about them and I might fix it.
