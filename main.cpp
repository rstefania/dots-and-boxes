#include <iostream>
#include "graphics2.h"
#include <cmath>
#include <cstdlib>
using namespace std;

struct punct{
    int directie[4];
    int cate;
    int patrate[4];
};
punct M[14][14];
int dl[] = {0, 1, 0, -1};
int dc[] = {-1, 0, 1, 0};
int dlc[] = {-1, 1, 1, -1};
int dld[] = {1, 1, -1, -1};
char tasta;
int ok;

struct pointer{
    int x, y;
};
pointer p;
int puncte[] = {0, 0};
int x, y, dir;
int jucator;
int nrpatrate = 144;
char afispunct[2][10];

void tura();
void selecteaza_piesa();
void tasta_buna();
void deseneaza_cerc(int x, int y, int culoare);
void selecteaza_directia();
void deseneaza_linie();
void verif_patrate();
void atribuie_patrate();
void main_menu();
void joc();
void punctaj();
void start();
int main()
{
    int graph, mod;
    initgraph(&mod, &graph, "", 950, 650);
    start();
    main_menu();
    delay(10000);
    return 0;
}

void joc()
{
    int i, j;
    setcolor(WHITE);
    for (i = 2; i <= 11; i ++)
        M[i][1].cate = M[i][12].cate = M[1][i].cate = M[12][i].cate = 1;
    M[1][1].cate = M[1][12].cate = M[12][12].cate = M[12][1].cate = 2;
    for (i = 0; i <= 650; i += 50)
    {
        line(0, i, 650, i);
        line(i, 0, i, 650);
    }
    for (i = 1; i <= 12; i ++)
        for (j = 1; j <= 12; j ++)
        {
            deseneaza_cerc(i, j, 10);
        }
    p.x = 6;
    p.y = 6;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(BLUE);
    outtextxy(750, 200, "Jucator 1:");
    setcolor(LIGHTRED);
    outtextxy(750, 300, "Jucator 2:");
    while(1)
    {
        jucator = 1 - jucator;
        tura();
        punctaj();
        setcolor(BLUE);
        outtextxy(750, 250, afispunct[1]);
        setcolor(LIGHTRED);
        outtextxy(750, 350, afispunct[0]);
        if (nrpatrate == 0)
            break;
    }
    delay(1000);
    cleardevice();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    setcolor(WHITE);
    outtextxy(100, 100, "Sfarsit de joc");
    if (puncte[1] > puncte[0])
    {
        setcolor(BLUE);
        outtextxy(100, 200, "A castigat Jucator 1");
    }
    else
    {
        setcolor(LIGHTRED);
        outtextxy(100, 200, "A castigat Jucator 2");
    }
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(100, 550, "Apasa ENTER");
    tasta = 'a';
    while (1)
    {
        if (kbhit())
            tasta = getch();
        if (tasta == '\r')
            break;
    }
    nrpatrate = 5;
    main_menu();
}

void tura()
{
    if (nrpatrate == 0)
        return;
    ok = 0;
    deseneaza_cerc(p.x, p.y, 14);
    selecteaza_piesa();
    M[p.y][p.x].cate ++;
    selecteaza_directia();
    M[p.y + dc[dir]][p.x + dl[dir]].cate ++;
    M[p.y][p.x].directie[dir] = 1;
    switch (dir)
    {
        case 0: M[p.y + dc[dir]][p.x + dl[dir]].directie[2] = 1; break;
        case 1: M[p.y + dc[dir]][p.x + dl[dir]].directie[3] = 1; break;
        case 2: M[p.y + dc[dir]][p.x + dl[dir]].directie[0] = 1; break;
        case 3: M[p.y + dc[dir]][p.x + dl[dir]].directie[1] = 1; break;
    }
    if(jucator)
    {
        setcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
    }
    else
    {
        setcolor(LIGHTRED);
        setfillstyle(SOLID_FILL, LIGHTRED);
    }
    deseneaza_linie();
    verif_patrate();
    if (ok == 1)
        tura();
}

void selecteaza_piesa()
{
    while(1)
    {
        tasta = 'c';
        tasta_buna();
        if (tasta == '\r')
            if(M[p.y][p.x].cate != 4)
                break;
        deseneaza_cerc(p.x, p.y, 10);
        switch(tasta)
        {
            case 's': p.y ++; break;
            case 'a': p.x --; break;
            case 'd': p.x ++; break;
            case 'w': p.y --; break;
            case 'S': p.y ++; break;
            case 'A': p.x --; break;
            case 'D': p.x ++; break;
            case 'W': p.y --; break;
        }
        if (p.x < 1 || p.x > 12 || p.y < 1 || p.y > 12)
            switch(tasta)
            {
                case 's': p.y --; break;
                case 'a': p.x ++; break;
                case 'd': p.x --; break;
                case 'w': p.y ++; break;
                case 'S': p.y --; break;
                case 'A': p.x ++; break;
                case 'D': p.x --; break;
                case 'W': p.y ++; break;
            }
        deseneaza_cerc(p.x, p.y, 14);
        delay(200);
    }
}

void selecteaza_directia()
{
    while(1)
    {
        tasta = 'c';
        tasta_buna();
        if(tasta == '\r')
            if(M[p.y][p.x].directie[dir] == 0)
                break;
        deseneaza_cerc(x, y, 10);
        switch(tasta)
        {
            case 's': dir = 2; break;
            case 'a': dir = 3; break;
            case 'd': dir = 1; break;
            case 'w': dir = 0; break;
            case 'S': dir = 2; break;
            case 'A': dir = 3; break;
            case 'D': dir = 1; break;
            case 'W': dir = 0; break;
        }
        x = p.x + dl[dir];
        y = p.y + dc[dir];
        if (x < 1 || x > 12 || y < 1 || y > 12)
            switch(tasta)
            {
                case 's': dir = 0; break;
                case 'a': dir = 1; break;
                case 'd': dir = 3; break;
                case 'w': dir = 2; break;
                case 'S': dir = 0; break;
                case 'A': dir = 1; break;
                case 'D': dir = 3; break;
                case 'W': dir = 2; break;
            }
        x = p.x + dl[dir];
        y = p.y + dc[dir];
        deseneaza_cerc(x, y, 14);
        delay(200);
    }
}

void tasta_buna()
{
    while(tasta != 's' && tasta != 'w' && tasta!= 'd' && tasta != 'a' && tasta != 'S' && tasta != 'W' && tasta!= 'D' && tasta != 'A' && tasta != '\r')
        while(kbhit())
            tasta = getch();

}

void verif_patrate()
{
    int i;
    if (M[p.y][p.x].cate >= 2)
    {
        for (i = 0; i <= 3; i ++)
        {
            dir = i;
            if (M[p.y][p.x].directie[dir % 4] && M[p.y][p.x].directie[(dir + 1) % 4] && M[p.y][p.x].patrate[dir] != 1)
            {
                x = p.x + dld[dir];
                y = p.y + dlc[dir];
                if (x > 0 && x < 13 && y > 0 && y < 13)
                {
                    if (M[y][x].directie[(dir + 2) % 4] && M[y][x].directie[(dir + 3) % 4])
                    {
                        puncte[jucator] ++;
                        nrpatrate --;
                        atribuie_patrate();
                        ok = 1;
                    }
                }
            }
        }
    }
}

void atribuie_patrate()
{
    M[p.y][p.x].patrate[dir] = 1;
    if(jucator)
    {
        setcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
    }
    else
    {
        setcolor(LIGHTRED);
        setfillstyle(SOLID_FILL, LIGHTRED);
    }
    switch(dir)
    {
        case 0:
        {
            M[p.y - 1][p.x + 1].patrate[2] = 1;
            M[p.y - 1][p.x].patrate[1] = 1;
            M[p.y][p.x + 1].patrate[3] = 1;
            bar(p.x * 50, p.y * 50, x * 50, y * 50);
            setcolor(WHITE);
            line(p.x * 50, p.y * 50, p.x * 50, p.y * 50 - 50);
            line(p.x * 50, p.y * 50, p.x * 50 + 50, p.y * 50);
            line(x * 50, y * 50, x * 50 - 50, y * 50);
            line(x * 50, y * 50, x * 50, y * 50 + 50);
            deseneaza_cerc(p.x, p.y, 10);
            deseneaza_cerc(x, y, 10);
            deseneaza_cerc(p.x - 1, p.y, 10);
            deseneaza_cerc(p.x, p.y + 1, 10);
            break;
        }
        case 1:
        {
            M[p.y + 1][p.x + 1].patrate[3] = 1;
            M[p.y + 1][p.x].patrate[0] = 1;
            M[p.y][p.x + 1].patrate[2] = 1;
            bar(p.x * 50, p.y * 50, x * 50, y * 50);
            setcolor(WHITE);
            line(p.x * 50, p.y * 50, p.x * 50 + 50, p.y * 50);
            line(p.x * 50, p.y * 50, p.x * 50, p.y * 50 + 50);
            line(x * 50, y * 50, x * 50, y * 50 - 50);
            line(x * 50, y * 50, x * 50 - 50, y * 50);
            deseneaza_cerc(p.x, p.y, 10);
            deseneaza_cerc(x, y, 10);
            deseneaza_cerc(p.x + 1, p.y, 10);
            deseneaza_cerc(p.x, p.y + 1, 10);
            break;
        }
        case 2:
        {
            M[p.y + 1][p.x - 1].patrate[0] = 1;
            M[p.y + 1][p.x].patrate[3] = 1;
            M[p.y][p.x - 1].patrate[1] = 1;
            bar(p.x * 50, p.y * 50, x * 50, y * 50);
            setcolor(WHITE);
            line(p.x * 50, p.y * 50, p.x * 50 - 50, p.y * 50);
            line(p.x * 50, p.y * 50, p.x * 50, p.y * 50 + 50);
            line(x * 50, y * 50, x * 50 + 50, y * 50);
            line(x * 50, y * 50, x * 50, y * 50 - 50);
            deseneaza_cerc(p.x, p.y, 10);
            deseneaza_cerc(x, y, 10);
            deseneaza_cerc(p.x - 1, p.y, 10);
            deseneaza_cerc(p.x, p.y + 1, 10);
            break;
        }
            case 3:
        {
            M[p.y - 1][p.x - 1].patrate[1] = 1;
            M[p.y - 1][p.x].patrate[2] = 1;
            M[p.y][p.x - 1].patrate[0] = 1;
            bar(p.x * 50, p.y * 50, x * 50, y * 50);
            setcolor(WHITE);
            line(p.x * 50, p.y * 50, p.x * 50 - 50, p.y * 50);
            line(p.x * 50, p.y * 50, p.x * 50, p.y * 50 - 50);
            line(x * 50, y * 50, x * 50 + 50, y * 50);
            line(x * 50, y * 50, x * 50, y * 50 + 50);
            deseneaza_cerc(p.x, p.y, 10);
            deseneaza_cerc(x, y, 10);
            deseneaza_cerc(p.x - 1, p.y, 10);
            deseneaza_cerc(p.x, p.y - 1, 10);
            break;
        }
    }
}

void deseneaza_cerc(int x, int y, int culoare)
{
    setcolor(culoare);
    setfillstyle(SOLID_FILL, culoare);
    circle(x * 50, y * 50, 5);
    floodfill(x * 50, y * 50, culoare);
}

void deseneaza_linie()
{
    line(p.x * 50, p.y * 50, x * 50, y * 50);
    deseneaza_cerc(p.x, p.y, 10);
    deseneaza_cerc(x, y, 10);
}

void main_menu()
{
    int i, j;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    setcolor(BLUE);
    outtextxy(100, 100, "1.Start joc");
    setcolor(LIGHTBLUE);
    outtextxy(100, 150, "2.Help");
    setcolor(BLUE);
    outtextxy(100, 200, "3.Exit");
    while(1)
    {
        if(kbhit())
            tasta = getch();
        if (tasta == '1')
        {
            cleardevice();
            joc();
        }
        if (tasta == '2')
        {
            cleardevice();
            setcolor(LIGHTBLUE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(100, 100, "-Selecteaza patratelul si directia");
            outtextxy(100, 150, "cu W A S D pentru a trasa o linie");
            setcolor(BLUE);
            outtextxy(100, 200, "-Cine completeaza un patratel");
            outtextxy(100, 250, "primeste 1 punct");
            outtextxy(100, 300, "si mai are dreptul la o tura");
            setcolor(LIGHTRED);
            outtextxy(100, 350, "-Cand se termina de umplut tabla");
            outtextxy(100, 400, "castiga cine are mai multe patrate");
            while ((int)tasta != 8)
                if (kbhit())
                    tasta = getch();
            cleardevice();
            main_menu();
        }
        if (tasta == '3')
            exit(0);
    }
    delay(1000);
}
//Pune intr-un sir de caractere cifrele
void punctaj()
{
    int cp, i, lgjuc, cifra;
    cp = puncte[jucator];
    if(cp <= 9)
        lgjuc = 1;
    if (cp >= 10 && cp <= 99)
        lgjuc = 2;
    if (cp >= 100)
        lgjuc = 3;
    for (i = lgjuc - 1; i >= 0; i --)
    {
        cifra = cp % 10;
        afispunct[jucator][i] = cifra + '0';
        cp /= 10;
    }
    afispunct[jucator][lgjuc] = NULL;
}

void start()
{
    int i, j;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
    setcolor(LIGHTBLUE);
    for (i = 0; i <= 280; i ++)
    {
        cleardevice();
        outtextxy(i, 200, "DOTS & BOXES");
        if (kbhit())
        {
            cleardevice();
            outtextxy(250, 200, "DOTS & BOXES");
            break;
        }
        delay(15);
    }
    setcolor(BLUE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(275, 250, "APASA ENTER PENTRU A CONTINUA");
    while(1)
    {
        while(kbhit())
            tasta = getch();
        if (tasta == '\r')
            break;
    }
    cleardevice();
    delay(100);
}
