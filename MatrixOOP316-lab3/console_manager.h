class ConsoleManager{
    public:
        static void GotoXY(int col, int row);
        static void ClearScreen();
        static void SetConsoleColor(int foreground);
        static int* GetConsoleSize();
        static void DestroySymbol(int x, int y);
        static void HideCursor();
        static void DisplayCursor();
};