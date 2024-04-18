#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define DELAY 30000

typedef struct{int x, y, goles, tamaño;} Paleta;

int main(int argc, char *argv[]) {
    int x = 0, y = 0;
    int siguiente_x = 0, siguiente_y = 0;
    int direccion_x = 1, direccion_y = 1;
    int tamaño_pantalla_y = 50, tamaño_pantalla_x = 50;
    int i;
    bool terminar = false;
    Paleta paleta_der, paleta_izq;

    initscr();

    if (has_colors() == FALSE) {
        endwin();
        printf("Este terminal no soporta colores\n");
        exit(1);
    }

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    clear();

    refresh();
    getmaxyx(stdscr, tamaño_pantalla_y, tamaño_pantalla_x);

    WINDOW * ventana = newwin(tamaño_pantalla_y, tamaño_pantalla_x, 0, 0);
    wbkgd(ventana, COLOR_PAIR(3));
    box(ventana, '|', '-');

    mvwprintw(ventana, 1, 1, "Desarrollado por: Pablo Fernández Gallardo. GitHub: https://github.com/pabloferugr");
    mvwprintw(ventana, 4, 4, "Instrucciones:");
    mvwprintw(ventana, 5, 4, "Jugador 1:");
    mvwprintw(ventana, 6, 4, "\t- W : Arriba");
    mvwprintw(ventana, 7, 4, "\t- S : Abajo");
    mvwprintw(ventana, 8, 4, "Jugador 2:");
    mvwprintw(ventana, 9, 4, "\t- Flecha Arriba : Arriba");
    mvwprintw(ventana, 10, 4, "\t- Flecha Abajo : Abajo");
    mvwprintw(ventana, 11, 4, "¡El primero en llegar a 5 puntos gana!");
    mvwprintw(ventana, 12, 4, "Presiona cualquier tecla para empezar, E para salir.");
    wrefresh(ventana);

    getch();
    endwin();

    initscr();
    noecho();
    curs_set(false);
    nodelay(stdscr, true);
    keypad(stdscr, true);

    paleta_der.tamaño = 7;
    paleta_der.x = tamaño_pantalla_x - 2;
    paleta_der.y = tamaño_pantalla_y / 2 - paleta_der.tamaño / 2;
    paleta_der.goles = 0;

    paleta_izq.tamaño = 7;
    paleta_izq.x = 2;
    paleta_izq.y = tamaño_pantalla_y / 2 - paleta_izq.tamaño / 2;
    paleta_izq.goles = 0;

    while (!terminar) {
        clear();
        mvprintw(y, x, "o");
        for (i = 0; i < tamaño_pantalla_y; ++i) {
            mvprintw(i, tamaño_pantalla_x / 2, "|");
        }

        for (i = 0; i < paleta_der.tamaño; ++i) {
            mvprintw(paleta_der.y + i, paleta_der.x, "|");
        }

        for (i = 0; i < paleta_izq.tamaño; ++i) {
            mvprintw(paleta_izq.y + i, paleta_izq.x , "|");
        }
        mvprintw(0, tamaño_pantalla_x / 4, "%i", paleta_izq.goles);
        mvprintw(0, tamaño_pantalla_x - tamaño_pantalla_x / 4, "%i", paleta_der.goles);

        switch (getch()) {
            case 'w':
                if (paleta_izq.y > 0)
                    paleta_izq.y--;
                break;
            case 's':
                if (paleta_izq.y + paleta_izq.tamaño < tamaño_pantalla_y)
                    paleta_izq.y++;
                break;
            case KEY_UP:
                if (paleta_der.y > 0)
                    paleta_der.y--;
                break;
            case KEY_DOWN:
                if (paleta_der.y + paleta_der.tamaño < tamaño_pantalla_y)
                    paleta_der.y++;
                break;
            case 'e':
                terminar = true;
                break;
        }

        refresh();

        usleep(DELAY);

        siguiente_x = x + direccion_x;
        siguiente_y = y + direccion_y;

        if (paleta_der.x == x) {
            for (i = 0; i < paleta_der.tamaño; ++i) {
                if ((paleta_der.y + i) == y) {
                    direccion_x *= -1;
                    x += direccion_x;
                }
            }
        }

        if (paleta_izq.x == x) {
            for (i = 0; i < paleta_izq.tamaño; ++i) {
                if ((paleta_izq.y + i) == y) {
                    direccion_x *= -1;
                    x += direccion_x;
                }
            }
        }

        if (siguiente_x >= tamaño_pantalla_x) {
            paleta_izq.goles++;
            x = tamaño_pantalla_x / 4;
            y = tamaño_pantalla_y / 2;
            direccion_y *= -1;
        } else if (siguiente_x < 0) {
            paleta_der.goles++;
            x = tamaño_pantalla_x - tamaño_pantalla_x / 4;
            y = tamaño_pantalla_y / 2;
            direccion_y *= -1;

        } else {
            x += direccion_x;
        }

        if (siguiente_y >= tamaño_pantalla_y || siguiente_y < 0) {
            direccion_y *= -1;
        } else {
            y += direccion_y;
        }
        if (paleta_izq.goles == 5) {
            terminar = true;
        }
        if (paleta_der.goles == 5) {
            terminar = true;
        }

    }

    endwin();
}
