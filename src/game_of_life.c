#include <ncurses.h>
#include <stdio.h>
#define TRUE 1
#include <locale.h>

void field_stroy(int colony[25][80]);
void sozd_col(int colony[25][80]);
void file(int rf[25][80]);
int zhiza(int colony[25][80], int i, int j);

int main() {
    int colony[25][80] = {0};
    file(colony);
    initscr();
    if (freopen("/dev/tty", "r", stdin) != NULL) {
        printw("Speed\n");
        refresh();
        int speed;
        scanw("%d", &speed);
        do {
            timeout(speed);
            field_stroy(colony);
            sozd_col(colony);
            if (getch() == 'q') {
                break;
            }
        } while (TRUE);
    }
    endwin();
    return 0;
}

void field_stroy(int colony[25][80]) {
    clear();
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            if (colony[i][j] == 0) {
                printw("-");
            } else {
                printw("*");
            }
        }
        printw("\n");
    }
    printw("\n");
    refresh();
}

void file(int rf[25][80]) {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            scanf("%1d", &rf[i][j]);
        }
    }
}

int zhiza(int colony[25][80], int i, int j) {
    int isk_i, isk_j, sum = 0;
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            isk_i = (i + y + 25) % 25;
            isk_j = (j + x + 80) % 80;
            if (colony[isk_i][isk_j] == 1 && ((y != 0) || (x != 0))) {
                sum += colony[isk_i][isk_j];
            }
        }
    }
    return sum;
}

void sozd_col(int colony[25][80]) {
    int gg_coloniy[25][80];
    int counter;
    for (int i = 0; i <= 24; i++) {
        for (int j = 0; j <= 79; j++) {
            counter = zhiza(colony, i, j);
            if (((colony[i][j]) == 1) && ((counter > 3) || (counter < 2))) {
                gg_coloniy[i][j] = 0;
            } else if ((colony[i][j] == 0) && (counter == 3)) {
                gg_coloniy[i][j] = 1;
            } else {
                gg_coloniy[i][j] = colony[i][j];
            }
        }
    }
    for (int i = 0; i <= 24; i++) {
        for (int j = 0; j <= 79; j++) {
            colony[i][j] = gg_coloniy[i][j];
        }
    }
}
