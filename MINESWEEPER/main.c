#include <stdio.h>
#include <stdlib.h>
#include "minesweeper.h"
#include <string.h>

int main()
{
    /// 1:
    char t1[3][3] = {
        {'.', '2', 'X'},
        {'.', '2', 'X'},
        {'.', '1', '1'},
    };
    print(3, 3, t1);

    /// 2:
    /*char t[100][53];
    for(int i=0; i<100; i++)
        for(int j=0; j<53; j++)
            t[i][j] = '.';
    print(99, 52, t);*/

    /*printf("\n");
    char t[28][50];
    char cols[10] = {'A', 'A', 'E', 'E', 'E', 'b', 'c', 'g', 'B', 'X'};
    int rows[10] = {1, 2, 2, 4, 5, 6, 6, 7, 14, 15}; //randurile (si coloanele) trebuie date crescator ca sa functioneze
    create(10, cols, rows, 28, 50, t);
    print(28, 50, t);*/

    ///saptamana 9
    printf("\n");
    char t[3][6];
    char cols[] = {'B', 'D'};
    int rows[] = {1, 3};
    create(2, cols, rows, 3, 6, t);
    print(3, 6, t);

    printf("\n");
    char** stare;
    stare = init_state(3, 6);
    printf("%d\n", discover(1, 5, 3, 6, t, stare));
    for(int i=0;i<3; i++)
    {
        printf("   ");
        for(int j=0; j<6; j++)
            printf("%c", stare[i][j]);
        printf("\n");
    }
    printf("\n");

    ///saptamana 11
    //b)
    char* str = (char*)calloc(1001, sizeof(char));
    int cat = 0;
    printf("Dati str: ");
    scanf("%[^\n]s", str);
    int len = strlen(str);
    comanda* s = Comenzi(str, len, &cat);
    print_comenzi(s, cat);

    //c)
    printf("\n");
    discover(1, 5, 3, 6, t, stare);
    mark(2, 3, 3, 6, stare); //nu se va marca, deoarece deja are punct
    mark(0, 1, 3, 6, stare);
    for(int i=0;i<3; i++)
    {
        printf("   ");
        for(int j=0; j<6; j++)
            printf("%c", stare[i][j]);
        printf("\n");
    }

    //d)
    printf("\n");
    player_view(3, 6, t, stare);
    print2(3, 6, stare);
    return 0;
}
