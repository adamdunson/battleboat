// All WIN32 Functions are defined in this document

#include <windows.h>
#include <conio.h>
#define WIN32_LEAN_AND_MEAN
/* Standard error macro for reporting API errors from Microsoft 
   Don't actually need this, but might as well use it just in case.
*/ 
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void clearScr()
{
    COORD coordScreen = { 0, 0 };    // here's where we'll home the cursor
    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; // to get buffer info
    DWORD dwConSize;                 // number of character cells in the current buffer
    
    // get the number of character cells in the current buffer
    bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
    PERR(bSuccess, "GetConsoleScreenBufferInfo");
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    
    // fill the entire screen with blanks
    bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
    dwConSize, coordScreen, &cCharsWritten);
    PERR(bSuccess, "FillConsoleOutputCharacter");
    
    // get the current text attribute
    bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
    PERR(bSuccess, "ConsoleScreenBufferInfo");
    
    // now set the buffer's attributes accordingly
    bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
    dwConSize, coordScreen, &cCharsWritten );
    PERR(bSuccess, "FillConsoleOutputAttribute");
    
    // put the cursor at (0, 0)
    bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
    PERR(bSuccess, "SetConsoleCursorPosition");
    return;
}

void setColor(unsigned short color)
{
     SetConsoleTextAttribute(hConsole, color);
}

char getKeybChar()
{
    return getch(); //Defined in conio.h, waits and returns a single char from input
}
