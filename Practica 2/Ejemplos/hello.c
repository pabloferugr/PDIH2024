// gcc hello.c -o hello -lncurses

#include <ncurses.h>
#include <stdio.h>
int main() {
initscr();
printw("Hello World!");
refresh();
getch();
endwin();
return 0;
}

