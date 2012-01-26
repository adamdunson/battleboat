//BattleBoat for Win32 command prompt
// This program was written on Windows XP for Windows XP
// It is neither intended or expected to work on any other platform
// It may work with Win9x, ME, and 2000. Possibly even the NT platforms.
// I haven't tested it on those platforms, nor do I intend to.
// Linux may work with some adjustments ... still working on that though.

#include <cstdio>           //standard input/output
#include <cstdlib>          //standard library
#include "./bbFunctions.h"  //Includes all custom functions used in this program
#include "./bbWin32.h"      //Includes the Win32 system specific functions
#include "./bbKeyDefs.h"    //Includes the input key definitions

int main(int argc, char **argv)
{
    // Universal variables
    char input;
    int currR = 0;
    int currC = 0;
    bool playerA = true;
    bool xyzzyCheatA = false;
    bool xyzzyCheatB = false;


/*************************************************/
/********************          *******************/
/********************   MAPS   *******************/
/********************          *******************/
/*************************************************/

/* Pieces:
    C = Carrier
    B = Battleship
    S = Submarine
    c = Cruiser
    p = Patrol boat
    . = spaces not selected yet
    / = uncovered blank space
*/

// Player A
    // This mapA is displayed on the screen, and always contains a cursor
    char mapA[10][10];
    // This mapA is the necessary part of movement, it never contains the cursor value
    char mapANoMovement[10][10];
    // This is PlayerB's pieces, used to create mapANoMovement as the game progresses
    char mapAUncovered[10][10];

//Player B
    // This mapB is displayed on the screen, and always contains a cursor
    char mapB[10][10];
    // This mapB is the necessary part of movement, it never contains the cursor value
    char mapBNoMovement[10][10];
    // This is PlayerA's pieces, used to create mapBNoMovement as the game progresses
    char mapBUncovered[10][10];

    // Initilize (load) program and variables
    initialize(mapA, mapANoMovement, mapAUncovered, mapB, mapBNoMovement, mapBUncovered);

    // MAIN PROGRAM
    for(;;)
    {
    /*************************************************/
    /********************          *******************/
    /********************  MAIN A  *******************/
    /********************          *******************/
    /*************************************************/

    while(playerA)
    {
        printf("Player A\n");
        printMap(mapA, mapBUncovered);
        getCurrPos(mapA, currR, currC);
        if(xyzzyCheatA && mapAUncovered[currR][currC] != ',')
        {
            printf(".\n");
        }
        else printf("\n");

    // input loop A
        do
        {
            input = 0;
            input = getKeybChar();
            if(input == (char) -32) input = getKeybChar();
            else if(input == (char) CONTROL_C || input == (char) ESCAPE) exit(EXIT_SUCCESS);
            else if(input == (char) CONTROL_H)
            {
                help();
                input = 0;
                break;
            }
            else if(input == (char) 0)
            {
                input = getKeybChar();
                if(input == (char) F1)
                {
                    help();
                    break;
                }
            }
            /*Cheat similar to the winmine cheat*/
            if(input == 'x')
            {
                input = getKeybChar();
                if(input == 'y')
                {
                    input = getKeybChar();
                    if(input == 'z')
                    {
                        input = getKeybChar();
                        if(input == 'z')
                        {
                            input = getKeybChar();
                            if(input == 'y')
                            {
                                if(!xyzzyCheatA) xyzzyCheatA = true;
                                else xyzzyCheatA = false;
                                break;
                            }
                        }
                    }
                }
            }
        } while(input != (char) UP_ARROW && input != (char) LEFT_ARROW && input != (char) DOWN_ARROW && input != (char) RIGHT_ARROW && input != (char) SPACEBAR);

        if(input != 0)
        {
            switch((int) input)
            {
                case UP_ARROW:
                    if(currR != 0)
                    {
                        mapA[currR][currC] = mapANoMovement[currR][currC];
                        mapA[(currR - 1)][currC] = ((int) -37);
                    }
                    break;
                case LEFT_ARROW:
                    if(currC != 0)
                    {
                        mapA[currR][currC] = mapANoMovement[currR][currC];
                        mapA[currR][(currC - 1)] = ((int) -37);
                    }
                    break;
                case DOWN_ARROW:
                    if(currR != 9)
                    {
                        mapA[currR][currC] = mapANoMovement[currR][currC];
                        mapA[(currR + 1)][currC] = ((int) -37);
                    }
                    break;
                case RIGHT_ARROW:
                    if(currC != 9)
                    {
                        mapA[currR][currC] = mapANoMovement[currR][currC];
                        mapA[currR][(currC + 1)] = ((int) -37);
                    }
                    break;
                case SPACEBAR:
                    if(mapANoMovement[currR][currC] == '.')
                    {
                        mapANoMovement[currR][currC] = mapAUncovered[currR][currC];
                        if(mapAUncovered[currR][currC] == 'C')
                        {
                            printf("HIT!\n");
                            mapAUncovered[currR][currC] = 'x';
                            if(CarrierSink(mapANoMovement))
                            {
                                printf("YOU SUNK MY CARRIER.\n");
                            }
                        }
                        else if(mapAUncovered[currR][currC] == 'B')
                        {
                            printf("HIT!\n");
                            mapAUncovered[currR][currC] = 'x';
                            if(BattleshipSink(mapANoMovement))
                            {
                                printf("YOU SUNK MY BATTLESHIP.\n");
                            }
                        }
                        else if(mapAUncovered[currR][currC] == 'S')
                        {
                            printf("HIT!\n");
                            mapAUncovered[currR][currC] = 'x';
                            if(SubmarineSink(mapANoMovement))
                            {
                                printf("YOU SUNK MY SUBMARINE.\n");
                            }
                        }
                        else if(mapAUncovered[currR][currC] == 'c')
                        {
                            printf("HIT!\n");
                            mapAUncovered[currR][currC] = 'x';
                            if(CruiserSink(mapANoMovement))
                            {
                                printf("YOU SUNK MY CRUISER.\n");
                            }
                        }
                        else if(mapAUncovered[currR][currC] == 'p')
                        {
                            printf("HIT!\n");
                            mapAUncovered[currR][currC] = 'x';
                            if(PatrolBoatSink(mapANoMovement))
                            {
                                printf("YOU SUNK MY PATROL BOAT.\n");
                            }
                        }
                        else
                        {
                            printf("MISS!\n");
                        }
                        if(checkWin(playerA, mapAUncovered))
                        {
                            printf("Press any key to quit...");
                            getKeybChar();
                            exit(EXIT_SUCCESS);
                        }
                        printf("Press any key to end your turn. . .");
                        getKeybChar();
                        clearScr();
                        printf("Player B's turn. Press any key to continue. . .");
                        getKeybChar();
                        playerA = false;
                    }
                    break;
            }
            clearScr();
        }
    }

    /*************************************************/
    /********************          *******************/
    /********************  MAIN B  *******************/
    /********************          *******************/
    /*************************************************/

    while(!playerA)
    {
        printf("Player B\n");
        printMap(mapB, mapAUncovered);
        getCurrPos(mapB, currR, currC);
        if(xyzzyCheatB && mapBUncovered[currR][currC] != ',')
        {
            printf(".\n");
        }
        else printf("\n");
//      printf("MESSAGE:\n%s", messages); // Still may use this someday

    // input loop B
        do
        {
            input = 0;
            input = getKeybChar();
            if(input == (char) -32) input = getKeybChar();
            else if(input == (char) CONTROL_C || input == (char) ESCAPE) exit(EXIT_SUCCESS);
            else if(input == (char) CONTROL_H)
            {
                help();
                break;
            }
            else if(input == (char) 0)
            {
                input = getKeybChar();
                if(input == (char) F1)
                {
                    help();
                    break;
                }
            }
            /*Cheat similar to the winmine cheat*/
            if(input == 'x')
            {
                input = getKeybChar();
                if(input == 'y')
                {
                    input = getKeybChar();
                    if(input == 'z')
                    {
                        input = getKeybChar();
                        if(input == 'z')
                        {
                            input = getKeybChar();
                            if(input == 'y')
                            {
                                if(!xyzzyCheatB) xyzzyCheatB = true;
                                else xyzzyCheatB = false;
                                break;
                            }
                        }
                    }
                }
            }
        } while(input != (char) UP_ARROW && input != (char) LEFT_ARROW && input != (char) DOWN_ARROW && input != (char) RIGHT_ARROW && input != (char) SPACEBAR);
        if(input != 0)
        {
            switch((int) input)
            {
                case UP_ARROW:
                    if(currR != 0)
                    {
                        mapB[currR][currC] = mapBNoMovement[currR][currC];
                        mapB[(currR - 1)][currC] = ((int) -37);
                    }
                    break;
                case LEFT_ARROW:
                    if(currC != 0)
                    {
                        mapB[currR][currC] = mapBNoMovement[currR][currC];
                        mapB[currR][(currC - 1)] = ((int) -37);
                    }
                    break;
                case DOWN_ARROW:
                    if(currR != 9)
                    {
                        mapB[currR][currC] = mapBNoMovement[currR][currC];
                        mapB[(currR + 1)][currC] = ((int) -37);
                    }
                    break;
                case RIGHT_ARROW:
                    if(currC != 9)
                    {
                        mapB[currR][currC] = mapBNoMovement[currR][currC];
                        mapB[currR][(currC + 1)] = ((int) -37);
                    }
                    break;
                case SPACEBAR:
                    if(mapBNoMovement[currR][currC] == '.')
                    {
                        mapBNoMovement[currR][currC] = mapBUncovered[currR][currC];
                        if(mapBUncovered[currR][currC] == 'C')
                        {
                            printf("HIT!\n");
                            mapBUncovered[currR][currC] = 'x';
                            if(CarrierSink(mapBNoMovement))
                            {
                                printf("YOU SUNK MY CARRIER.\n");
                            }
                        }
                        else if(mapBUncovered[currR][currC] == 'B')
                        {
                            printf("HIT!\n");
                            mapBUncovered[currR][currC] = 'x';
                            if(BattleshipSink(mapBNoMovement))
                            {
                                printf("YOU SUNK MY BATTLESHIP.\n");
                            }
                        }
                        else if(mapBUncovered[currR][currC] == 'S')
                        {
                            printf("HIT!\n");
                            mapBUncovered[currR][currC] = 'x';
                            if(SubmarineSink(mapBNoMovement))
                            {
                                printf("YOU SUNK MY SUBMARINE.\n");
                            }
                        }
                        else if(mapBUncovered[currR][currC] == 'c')
                        {
                            printf("HIT!\n");
                            mapBUncovered[currR][currC] = 'x';
                            if(CruiserSink(mapBNoMovement))
                            {
                                printf("YOU SUNK MY CRUISER.\n");
                            }
                        }
                        else if(mapBUncovered[currR][currC] == 'p')
                        {
                            printf("HIT!\n");
                            mapBUncovered[currR][currC] = 'x';
                            if(PatrolBoatSink(mapBNoMovement))
                            {
                                printf("YOU SUNK MY PATROL BOAT.\n");
                            }
                        }
                        else
                        {
                            printf("MISS!\n");
                        }
                        if(checkWin(playerA, mapBUncovered))
                        {
                            printf("Press any key to quit...");
                            getKeybChar();
                            exit(EXIT_SUCCESS);
                        }
                        printf("Press any key to end your turn. . .");
                        getKeybChar();
                        clearScr();
                        printf("Player A's turn. Press any key to continue. . .");
                        getKeybChar();
                        playerA = true;
                    }
                    break;
            }
            clearScr();
        }
    }
    }
    return EXIT_SUCCESS;
}
