#include <stdio.h>
#include <stdlib.h>
#include "minesweeper.h"
#include <string.h>

void print(int h, int w, char t[h][w])
{
    int k = 0;
    printf("   ");
    for(char i='A'; i<='Z' && k<w; i++)
    {
        printf("%c", i);
        k++;
    }
    if(k == 26)
        for(char j='a'; j<='z' && k<w; j++)
        {
            printf("%c", j);
            k++;
        }
    printf("\n");
    for(int l=0; l<h; l++)
    {
        if(l+1 < 10)
            printf(" %d ", l+1);
        else
            printf("%d ", l+1);
        for(int m=0; m<w; m++)
            printf("%c", t[l][m]);
        if(l+1 < 10)
            printf("  %d\n", l+1);
        else
            printf(" %d\n", l+1);
    }
    k = 0;
    printf("   ");
    for(char i='A'; i<='Z' && k<w; i++)
    {
        printf("%c", i);
        k++;
    }
    if(k == 26)
        for(char j='a'; j<='z' && k<w; j++)
        {
            printf("%c", j);
            k++;
        }
    printf("\n");
}
///A = coloana zero
///1 = randul zero
void create(int nr_bombs, char cols[], int rows[], int h, int w, char t[h][w])
{
    for(int i=0; i<h; i++)
        for(int j=0; j<w; j++)
            t[i][j] = '.';
    int b = 0;
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            if((int)cols[b] == 65+j && rows[b] == i+1 && cols[b] >= 'A' && cols[b] <= 'Z')
            {
                t[i][j] = 'X';
                b++;
            }
            else if((int)cols[b] == 97+j && rows[b] == i+1 && cols[b] >= 'a' && cols[b] <= 'z')
            {
                t[i][j+26] = 'X';
                b++;
            }
            if(b == nr_bombs)
                break;
        }
        if(b == nr_bombs)
            break;
    }
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            int nr1 = 0, nr2 = 0, nr3 = 0, nr4 = 0, nr5 = 0, nr6 = 0, nr7 = 0, nr8 = 0;
            if(t[i-1][j] == 'X' && i != 0)
                nr3++;
            if(t[i+1][j] == 'X' && i != h-1)
                nr4++;
            if(j != w-1)
            {
                if(t[i][j+1] == 'X')
                    nr6++;
                if(t[i-1][j+1] == 'X' && i != 0)
                    nr7++;
                if(t[i+1][j+1] == 'X' && i != h-1)
                    nr1++;
            }
            if(j != 0)
            {
                if(t[i+1][j-1] == 'X' && i != h-1)
                    nr8++;
                if(t[i-1][j-1] == 'X' && i != 0)
                    nr2++;
                if(t[i][j-1] == 'X')
                    nr5++;
            }
            int sum = nr1+nr2+nr3+nr4+nr5+nr6+nr7+nr8;
            if(sum != 0 && t[i][j] != 'X')
                t[i][j] = (char)(sum+48);
        }
    }
}

char** init_state(int h, int w)
{
    char** s = calloc(h, sizeof(char*));
    for(int i=0; i<h; i++)
        s[i] = calloc(w, sizeof(char));
    for(int k=0; k<h; k++)
        for(int j=0; j<w; j++)
            s[k][j] = '?';
    return s;
}

int discover(int i, int j, int h, int w, char t[h][w], char** s)
{
    if(i<0 || i>h || j<0 || j>w)
        return -2;
    else if(t[i][j] == 'X')
        return -1;
    else if(s[i][j] == '.')
        return 0;
    else if(t[i][j]>='1' && t[i][j] < '9')
    {
        s[i][j] = '.';
        return 1;
    }
    ///  i-1 j-1,  i-1 j,  i-1 j+1
    ///  i   j-1,  i   j,  i   j+1
    ///  i+1 j-1,  i+1 j,  i+1 j+1
    else
    {
        s[i][j] = '.';
        for(int k=-1; k<=1; k++)
        {
            for(int m=-1; m<=1; m++)
            {
                if(k == 0 && m == 0)
                    continue; ///ca sa nu mai repete apelul deja facut pe t[i][j]
                if(!(i+k>-1 && i+k<h && j+m>-1 && j+m<w))
                    continue; ///in cazul in care ne aflam in afara tablei si cu t[i+k][j+m]
                if(s[i+k][j+m] != '.') ///daca nu a fost deja descoperit
                    discover(i+k, j+m, h, w, t, s);
            }
        }
        return 2;
    }
}

comanda* Comenzi(char* str, int len, int* cat)
{
    comanda* sir = (comanda*)calloc(101, sizeof(comanda));
    int nr = 0;
    int j = 0;
    int i = 0;
    int ok = 0;
    while(i < len)
    {
        if((str[i] >= 'a' && str[i] <= 'z')||(str[i] >= 'A' && str[i] <= 'Z'))
        {
            int m = i+1;
            nr = 0;
            while(str[m] >= 48 && str[m] <= 57)
            {
                nr = nr*10 + (str[m]-48);/// '2'-'0'
                m++;
                ok = 1;
            }
            ///daca nr > 99, ar trebui continue, sa sara peste comenzile gresite
            if(ok)
            {
                sir[j].coloana = str[i];
                sir[j].randul = nr;///ex A21 -> randul = 2*10+1
                if(i>0 && str[i-1] == '!')
                    sir[j].tip = str[i-1];
                j++;
            }
            ok = 0; ///am folosit un ok pt cazul in care avem o comanda cu randul zero
        }
        i++;
    }
    *cat = j;
    return sir;
}

void print_comenzi(comanda* c, int len)
{
    if(len == 0)
    {
        printf("Nu exista comenzi!\n");
        return;
    }
    printf("Cele %d comenzi sunt:\n", len);
    for(int i=0; i<len; i++)
        printf("%c%c%d\n", c[i].tip, c[i].coloana, c[i].randul);
}

void mark(int i, int j, int h, int w, char** s)
{
    if(s[i][j] == '?')
        s[i][j] = '!';
    else if(s[i][j] == '!')
        s[i][j] = '?';
}

void player_view(int h, int w, char t[h][w], char** s)
{
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            if(s[i][j] == '.')
                s[i][j] = t[i][j];
        }
    }
}

void print2(int h, int w, char** t)
{
    int k = 0;
    printf("   ");
    for(char i='A'; i<='Z' && k<w; i++)
    {
        printf("%c", i);
        k++;
    }
    if(k == 26)
        for(char j='a'; j<='z' && k<w; j++)
        {
            printf("%c", j);
            k++;
        }
    printf("\n");
    for(int l=0; l<h; l++)
    {
        if(l+1 < 10)
            printf(" %d ", l+1);
        else
            printf("%d ", l+1);
        for(int m=0; m<w; m++)
            printf("%c", t[l][m]);
        if(l+1 < 10)
            printf("  %d\n", l+1);
        else
            printf(" %d\n", l+1);
    }
    k = 0;
    printf("   ");
    for(char i='A'; i<='Z' && k<w; i++)
    {
        printf("%c", i);
        k++;
    }
    if(k == 26)
        for(char j='a'; j<='z' && k<w; j++)
        {
            printf("%c", j);
            k++;
        }
    printf("\n");
}
