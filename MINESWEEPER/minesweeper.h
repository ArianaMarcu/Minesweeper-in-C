#ifndef MINESWEEPER_H_INCLUDED
#define MINESWEEPER_H_INCLUDED

typedef struct comanda{
    char tip; ///. sau !
    char coloana; ///litera mare sau mica
    int randul; ///numar de la 0 la 99 inclusiv
}comanda;

void print(int h, int w, char t[h][w]);
void create(int nr_bombs, char cols[], int rows[], int h, int w, char t[h][w]);
char** init_state(int h, int w);
int discover(int i, int j, int h, int w, char t[h][w], char** s);
comanda* Comenzi(char* str, int len, int *cat);
void print_comenzi(comanda* c, int len);
void mark(int i, int j, int h, int w, char** s);
void player_view(int h, int w, char t[h][w], char** s);
void print2(int h, int w, char** t);
#endif // MINESWEEPER_H_INCLUDED
