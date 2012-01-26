#include <cstdio>

// the three functions below are defined in the system specific header located in the current directory (bbWin32.h)
char getKeybChar();
void clearScr();
void setColor(unsigned short color);

//Initialize all other functions
void initialize(char (&mapA)[10][10], char (&mapANoMovement)[10][10], char (&mapAUncovered)[10][10], char (&mapB)[10][10], char (&mapBNoMovement)[10][10], char (&mapBUncovered)[10][10]);
bool checkMapOK(char (&mapUncovered)[10][10]);

void welcomeScreen();
void help();

void printMap(char (&map)[10][10], char (&mapUncovered)[10][10]);
void getCurrPos(char (&map)[10][10], int &, int &);
bool checkWin(bool &playerA, char (&mapUncovered)[10][10]);

bool CarrierSink(char (&mapNoMovement)[10][10]);
bool BattleshipSink(char (&mapNoMovement)[10][10]);
bool SubmarineSink(char (&mapNoMovement)[10][10]);
bool CruiserSink(char (&mapNoMovement)[10][10]);
bool PatrolBoatSink(char (&mapNoMovement)[10][10]);

//All functions defined below

void initialize(char (&mapA)[10][10], char (&mapANoMovement)[10][10], char (&mapAUncovered)[10][10], char (&mapB)[10][10], char (&mapBNoMovement)[10][10], char (&mapBUncovered)[10][10])
{
    printf("Loading...please wait.\n"); // In case reading the map values and initialization takes a long time

// initialize map and mapNoMovement
    for(int i=0; i<10; i++)
    {
        for(int x=0; x<10; x++)
        {
            mapA[i][x] = '.';
            mapANoMovement[i][x] = '.';
            mapB[i][x] = '.';
            mapBNoMovement[i][x] = '.';
        }
    }

// read .map files to create maps
    FILE* map;
    char mapVal;
    map = fopen("playerA.map", "r");
    if (map == NULL)
    {
        printf("Error opening file playerA.map. Please create this file in the current directory.\n");
        printf("Press any key to exit...");
        getKeybChar();
        exit(EXIT_FAILURE);
    }
    else
    {
        for(int i=0; i<10; i++)
        {
            for(int x=0; x<10; x++)
            {
                if(x<9)fscanf(map, "%c ", &mapVal);
                else fscanf(map, "%c\n", &mapVal);
                if(mapVal == ' ' || mapVal == '\n' || mapVal == '\r' || mapVal == '\t') continue;
                mapBUncovered[i][x] = mapVal;
            }
        }
        fclose(map);
        if(!checkMapOK(mapBUncovered))
        {
            printf("Error! Incorrect count when counting pieces.\nPlease check to make sure you have the needed number of pieces in playerA.map.\n");
            printf("Press any key to exit...");
            getKeybChar();
            exit(EXIT_FAILURE);
        }
    }
    map = fopen("playerB.map", "r");
    if (map == NULL)
    {
        printf("Error opening file playerB.map. Please create this file in the current directory.\n");
        printf("Press any key to exit...");
        getKeybChar();
        exit(EXIT_FAILURE);
    }
    else
    {
        for(int i=0; i<10; i++)
        {
            for(int x=0; x<10; x++)
            {
                if(x<9)fscanf(map, "%c ", &mapVal);
                else fscanf(map, "%c\n", &mapVal);
                if(mapVal == ' ' || mapVal == '\n' || mapVal == '\r' || mapVal == '\t') continue;
                mapAUncovered[i][x] = mapVal;
            }
        }
        fclose(map);
        if(!checkMapOK(mapAUncovered))
        {
            printf("Error! Incorrect count when counting pieces.\nPlease check to make sure you have the needed number of pieces in playerB.map.\n");
            printf("Press any key to exit...");
            getKeybChar();
            exit(EXIT_FAILURE);
        }
    }
    // initialize cursors
    mapA[0][0] = ((int) -37); //-37 is a block character for the cursor
    mapB[0][0] = ((int) -37);

    clearScr();
    welcomeScreen();
}

void welcomeScreen()
{
    printf("Welcome to BattleBoat!\n");
    printf("  _______       __   __   __       _______             __\n");
    printf(" |   _   .---.-|  |_|  |_|  .-----|   _   .-----.---.-|  |_\n");
    printf(" |.  1   |  _  |   _|   _|  |  -__|.  1   |  _  |  _  |   _|\n");
    printf(" |.  _   |___._|____|____|__|_____|.  _   |_____|___._|____|\n");
    printf(" |:  1    \\                       |:  1    \\\n");
    printf(" |::.. .  /                       |::.. .  /\n");
    printf(" `-------\'                        `-------\'\n");
    printf("\n\nPress any key to continue. . .");
    getKeybChar();
    clearScr();
}

void help()
{
    clearScr();
    printf(" ---------------\n");
    printf("| Help Message: |\n");
    printf(" ---------------\n\n");
    printf("Quit: Ctrl+Q or ESC\n");
    printf("Help: Ctrl+H (or Backspace) or F1\n");
    printf("Use arrow keys to move the cursor.\n");
    printf("Press spacebar to select coordinates.\n");
    printf("Press any key to continue.");
    getKeybChar();
    clearScr();
}

bool checkMapOK(char (&mapUncovered)[10][10])
{
    int counterC = 0;
    int counterB = 0;
    int counterS = 0;
    int counterc = 0;
    int counterp = 0;
    int counterComma = 0;

    for(int i=0; i<10; i++)
    {
        for(int x=0; x<10; x++)
        {
            if(mapUncovered[i][x] == 'C') counterC++;
            if(mapUncovered[i][x] == 'B') counterB++;
            if(mapUncovered[i][x] == 'S') counterS++;
            if(mapUncovered[i][x] == 'c') counterc++;
            if(mapUncovered[i][x] == 'p') counterp++;
            if(mapUncovered[i][x] == ',') counterComma++;
        }
    }
    if(counterC == 5 && counterB == 4 && counterS == 3 && counterc == 3 && counterp == 2 && counterComma == 83) return true;
    else return false;
}

void getCurrPos(char (&map)[10][10], int &currR, int &currC)
{
    for(int i=0; i<10; i++)
    {
        for(int x=0; x<10; x++)
        {
            if(map[i][x] == ((int) -37))
            {
                currR = i;
                currC = x;
                return;
            }
        }
    }
}

void printMap(char (&map)[10][10], char (&mapUncovered)[10][10])
{
    printf("\n           RADAR      \t\t           STATUS     \n\n");
    printf("    0 1 2 3 4 5 6 7 8 9 \t    0 1 2 3 4 5 6 7 8 9\n");
    printf("    _ _ _ _ _ _ _ _ _ _ \t    _ _ _ _ _ _ _ _ _ _\n");
    for(int i=0; i<10; i++)
    {
        for(int x=0; x<10; x++)
        {
            if(x == 0) printf("%d | ", i);
            if(map[i][x] != '.' && map[i][x] != ',' && map[i][x] != -37)
            {
                setColor(12);
                printf("%c ", map[i][x]);
                setColor(7);
            }
            else if(map[i][x] == ',' && map[i][x] != -37)
            {
                setColor(9);
                printf("/ ");
                setColor(7);
            }
            else if(map[i][x] == '.' || map[i][x] == -37)
            {
                printf("%c ", map[i][x]);
            }
            if(x == 9)
            {
                printf("|\t");
                for(int y=0; y<10; y++)
                {
                    if(y == 0) printf("%d | ", i);
                    if(mapUncovered[i][y] == 'x')
                    {
                        setColor(12);
                        printf("%c ", mapUncovered[i][y]);
                        setColor(7);
                    }
                    else printf("%c ", mapUncovered[i][y]);
                    if(y == 9)
                    {
                        printf("|");
                    }
                }
            }
        }
        printf("\n");
    }
    printf("  | _ _ _ _ _ _ _ _ _ _ |\t  | _ _ _ _ _ _ _ _ _ _ |");
}

bool checkWin(bool &playerA, char (&mapUncovered)[10][10])
{
    int counter = 0;
    for(int i=0; i<10; i++)
    {
        for(int x=0; x<10; x++)
        {
            if(mapUncovered[i][x] == 'x')
            {
                counter += 1;
                if(playerA && counter == 17)
                {
                    printf("\nPlayer A wins!\n");
                    return true;
                }
                else if(!playerA && counter == 17)
                {
                    printf("\nPlayer B wins!\n");
                    return true;
                }
            }
        }
    }
    return false;
}

// Check which ships have been sunk

bool CarrierSink(char (&mapNoMovement)[10][10])
{
    int counter = 0;
    for(int i=0; i<10; i++)
    {
        for(int x=0; x<10; x++)
        {
            if(mapNoMovement[i][x] == 'C')
            {
                counter += 1;
                if(counter == 5) return true;
            }
        }
    }
    return false;
}

bool BattleshipSink(char (&mapNoMovement)[10][10])
{
    int counter = 0;
    for(int i=0; i<10; i++)
    {
        for(int x=0; x<10; x++)
        {
            if(mapNoMovement[i][x] == 'B')
            {
                counter += 1;
                if(counter == 4) return true;
            }
        }
    }
    return false;
}

bool SubmarineSink(char (&mapNoMovement)[10][10])
{
    int counter = 0;
    for(int i=0; i<10; i++)
    {
        for(int x=0; x<10; x++)
        {
            if(mapNoMovement[i][x] == 'S')
            {
                counter += 1;
                if(counter == 3) return true;
            }
        }
    }
    return false;
}

bool CruiserSink(char (&mapNoMovement)[10][10])
{
    int counter = 0;
    for(int i=0; i<10; i++)
    {
        for(int x=0; x<10; x++)
        {
            if(mapNoMovement[i][x] == 'c')
            {
                counter += 1;
                if(counter == 3) return true;
            }
        }
    }
    return false;
}

bool PatrolBoatSink(char (&mapNoMovement)[10][10])
{
    int counter = 0;
    for(int i=0; i<10; i++)
    {
        for(int x=0; x<10; x++)
        {
            if(mapNoMovement[i][x] == 'p')
            {
                counter += 1;
                if(counter == 2) return true;
            }
        }
    }
    return false;
}
