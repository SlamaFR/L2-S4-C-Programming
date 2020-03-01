#include <ncurses.h>
#include <assert.h>

#define N 8
#define M 16
#define CELL_SIZE 4

/* Tablette */
typedef struct s_tablet {
    int tab[N][M];
} Tablet;

/* Joueur */
typedef enum {
    PLAYER_1,
    PLAYER_2
} Player;

/* Position */
typedef struct s_position {
    Tablet tablet;
    Player player;
} Position;

/* Coup */
typedef struct s_move {
    int x, y;
} Move;

Player adversary(Player player) {
    return player == PLAYER_1 ? PLAYER_2 : PLAYER_1;
}

Tablet createTablet() {
    Tablet tablet;
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            tablet.tab[i][j] = 1;
    return tablet;
}

void eat(Tablet *tablet, int x, int y) {
    int i, j;
    assert(x < COLS);
    assert(y < LINES);
    assert(tablet != NULL);

    for (i = y; i < N; i++)
        for (j = x; j < M; j++)
            tablet->tab[i][j] = 0;
}

int isLegal(Position position, Move move) {
    assert(move.x >= 0);
    assert(move.y >= 0);
    assert(move.x < M);
    assert(move.y < N);

    return position.tablet.tab[move.y][move.x];
}

int isGameOver(Position position, Player *winner) {
    if (!position.tablet.tab[0][0]) {
        *winner = position.player;
        return 1;
    }
    return 0;
}

void play(Position *position, Move move) {
    assert(position != NULL);

    eat(&position->tablet, move.x, move.y);
    position->player = adversary(position->player);
}

void displayPosition(Position position) {
    int i, j, width, height;
    clear();

    attron(A_REVERSE);
    mvprintw((LINES - CELL_SIZE * N - N) / 2, COLS / 2 - 12, " -=*   C H O M P   *=- ");
    attroff(A_REVERSE);
    if (position.player == PLAYER_1)
        mvprintw((LINES - CELL_SIZE * N) / 2, COLS / 2 - 5, "Joueur 1");
    else
        mvprintw((LINES - CELL_SIZE * N) / 2, COLS / 2 - 5, "Joueur 2");

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            attron(COLOR_PAIR(position.tablet.tab[i][j]));
            for (height = 0; height < CELL_SIZE / 2; height++) {
                for (width = 0; width < CELL_SIZE; width++) {
                    mvprintw((LINES - (CELL_SIZE / 2 + 1) * N) / 2 + 1 + i * CELL_SIZE / 2 + height + i,
                             (COLS - (CELL_SIZE + 2) * M) / 2 + j * CELL_SIZE + width + 2 * j, " ");
                }
            }
            attroff(COLOR_PAIR(position.tablet.tab[i][j]));
        }
    }
    refresh();
}

Move readMove(Position position) {
    int c;
    MEVENT ev;
    Move move;

    do {
        c = getch();

        if (c == KEY_MOUSE && getmouse(&ev) == OK) {
            move.x = (ev.x - ((COLS - (CELL_SIZE + 2) * M) / 2)) / (CELL_SIZE + 2);
            move.y = (ev.y - ((LINES - (CELL_SIZE / 2 + 1) * N) / 2)) / (CELL_SIZE / 2 + 1);

        } else continue;
    } while (move.x >= M || move.y >= N || !isLegal(position, move) || mvinch(ev.y, ev.x) == ' ');

    return move;
}

int main(void) {
    Position position;
    Player winner;
    Move move;
    initscr();
    noecho();
    curs_set(0);
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_WHITE);
    init_pair(1, COLOR_GREEN, COLOR_GREEN);
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    position.tablet = createTablet();
    position.player = PLAYER_1;

    while (!isGameOver(position, &winner)) {
        displayPosition(position);
        move = readMove(position);
        play(&position, move);
    }

    clear();
    mvprintw(LINES / 2, COLS / 2 - 10, winner == PLAYER_1 ? "Joueur 1 l'emporte !" : "Joueur 2 l'emporte !");
    refresh();
    getch();

    endwin();
    return 0;
}
