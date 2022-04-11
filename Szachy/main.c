#include <stdio.h>
#include <stdlib.h>
#define K 0
#define H 1
#define W 2
#define G 3
#define S 4
#define P 5
#define k_k 6
#define h_k 7
#define w_k 8
#define g_k 9
#define s_k 10
#define p_k 11
#define PUSTE 12
#define WYGRANA 100000
#define PRZEGRANA -100000


int MAX_KIER[] = {8, 8, 4, 4, 8, 3, 8, 8, 4, 4, 8, 3, 0};
int MAX_ODL[] = {2, 8, 8, 8, 2, 2, 2, 8, 8, 8, 2, 2, 0};

int WX[12][8] = {
    {0, 1, 1, 1, 0, -1, -1, -1},
    {0, 1, 1, 1, 0, -1, -1, -1},
    {0, 1, 0, -1},
    {1, 1, -1, -1},
    {1, 2, 2, 1, -1, -2, -2, -1},
    {-1, -1, -1},
    {0, 1, 1, 1, 0, -1, -1, -1},
    {0, 1, 1, 1, 0, -1, -1, -1},
    {0, 1, 0, -1},
    {1, 1, -1, -1},
    {1, 2, 2, 1, -1, -2, -2, -1},
    {1, 1, 1}};

int WY[12][8] = {
    {-1, -1, 0, 1, 1, 1, 0, -1},
    {-1, -1, 0, 1, 1, 1, 0, -1},
    {-1, 0, 1, 0},
    {-1, 1, 1, -1},
    {-2, -1, 1, 2, 2, 1, -1, -2},
    {-1, 0, 1},
    {-1, -1, 0, 1, 1, 1, 0, -1},
    {-1, -1, 0, 1, 1, 1, 0, -1},
    {-1, 0, 1, 0},
    {-1, 1, 1, -1},
    {-2, -1, 1, 2, 2, 1, -1, -2},
    {-1, 0, 1}};





   int heuryst[13][8][8]={
                // król
            {
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
            },
            // hetman
            {
                    {-176, -178, -178, -179, -179, -178, -178, -176},
                    {-178, -180, -180, -180, -180, -180, -180, -178},
                    {-178, -180, -181, -181, -181, -181, -180, -178},
                    {-179, -180, -181, -181, -181, -181, -180, -179},
                    {-180, -180, -181, -181, -181, -181, -180, -179},
                    {-178, -181, -181, -181, -181, -181, -180, -178},
                    {-178, -180, -181, -180, -180, -180, -180, -178},
                    {-176, -178, -178, -179, -179, -178, -178, -176},
            },
            // wie¿a
            {       {-100, -100, -100, -100, -100, -100, -100, -100},
                    {-101, -102, -102, -102, -102, -102, -102, -101},
                    {-99, -100, -100, -100, -100, -100, -100, -99},
                    {-99, -100, -100, -100, -100, -100, -100, -99},
                    {-99, -100, -100, -100, -100, -100, -100, -99},
                    {-99, -100, -100, -100, -100, -100, -100, -99},
                    {-99, -100, -100, -100, -100, -100, -100, -99},
                    {-100, -100, 100, -101, -101, -100, -100, -100},
            },
            // goniec
            {
                    {-56, -58, -58, -58, -58, -58, -58, -56},
                    {-58, -60, -60, -60, -60, -60, -60, -58},
                    {-58, -60, -61, -62, -62, -61, -60, -58},
                    {-58, -61, -61, -62, -62, -61, -61, -58},
                    {-58, -60, -62, -62, -62, -62, -60, -58},
                    {-58, -62, -62, -62, -62, -62, -62, -58},
                    {-58, -61, -60, -60, -60, -60, -61, -58},
                    {-56, -58, -58, -58, -58, -58, -58, -56},
            },
            // skoczek
            {
                    {-50, -52, -54, -54, -54, -54, -52, -50},
                    {-52, -56, -60, -60, -60, -60, -56, -52},
                    {-54, -60, -62, -63, -63, -62, -60, -54},
                    {-54, -61, -63, -64, -64, -63, -61, -54},
                    {-54, -60, -63, -64, -64, -63, -60, -54},
                    {-54, -61, -62, -63, -63, -62, -61, -54},
                    {-52, -56, -60, -61, -61, -60, -56, -52},
                    {-50, -52, -54, -54, -54, -54, -52, -50},
            },
            // pionek
            {
                    {-20, -20, -20, -20, -20, -20, -20, -20},
                    {-30, -30, -30, -30, -30, -30, -30, -30},
                    {-22, -22, -24, -26, -26, -24, -22, -22},
                    {-21, -21, -22, -25, -25, -22, -21, -21},
                    {-20, -20, -20, -24, -24, -20, -20, -20},
                    {-21, -19, -18, -20, -20, -18, -19, -21},
                    {-21, -22, -22, -16, -16, -22, -22, -21},
                    {-20, -20, -20, -20, -20, -20, -20, -20},
            },
            // król komputera
            {
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA}
            },
            // hetman komputera
            {
                    {176, 178, 178, 179, 179, 178, 178, 176},
                    {178, 180, 180, 180, 180, 180, 180, 178},
                    {178, 180, 181, 181, 181, 181, 180, 178},
                    {179, 180, 181, 181, 181, 181, 180, 179},
                    {180, 180, 181, 181, 181, 181, 180, 179},
                    {178, 181, 181, 181, 181, 181, 180, 178},
                    {178, 180, 181, 180, 180, 180, 180, 178},
                    {176, 178, 178, 179, 179, 178, 178, 176},
            },
            // wie¿a komputera
            {       {100, 100, 100, 101, 101, 100, 100, 100},
                    {99, 100, 100, 100, 100, 100, 100, 99},
                    {99, 100, 100, 100, 100, 100, 100, 99},
                    {99, 100, 100, 100, 100, 100, 100, 99},
                    {99, 100, 100, 100, 100, 100, 100, 99},
                    {99, 100, 100, 100, 100, 100, 100, 99},
                    {101, 102, 102, 102, 102, 102, 102, 101},
                    {100, 100, 100, 100, 100, 100, 100, 100},
            },
            // goniec komputera
            {
                    {56, 58, 58, 58, 58, 58, 58, 56},
                    {58, 61, 60, 60, 60, 60, 61, 58},
                    {58, 62, 62, 62, 62, 62, 62, 58},
                    {58, 60, 62, 62, 62, 62, 60, 58},
                    {58, 61, 61, 62, 62, 61, 61, 58},
                    {58, 60, 61, 62, 62, 61, 60, 58},
                    {58, 60, 60, 60, 60, 60, 60, 58},
                    {56, 58, 58, 58, 58, 58, 58, 56},
            },
            // skoczek komputera
            {
                    {50, 52, 54, 54, 54, 54, 52, 50},
                    {52, 56, 60, 60, 60, 60, 56, 52},
                    {54, 60, 62, 63, 63, 62, 60, 54},
                    {54, 61, 63, 64, 64, 63, 61, 54},
                    {54, 60, 63, 64, 64, 63, 60, 54},
                    {54, 61, 62, 63, 63, 62, 61, 54},
                    {52, 56, 60, 61, 61, 60, 56, 52},
                    {50, 52, 54, 54, 54, 54, 52, 50},
            },
            // pionek komputera
            {
                {20, 20, 20, 20, 20, 20, 20, 20},
                {21, 22, 22, 16, 16, 22, 22, 21},
                {26, 26, 26, 25, 24, 26, 26, 25},
                {20, 20, 20, 24, 24, 20, 20, 20},
                {21, 21, 22, 25, 25, 22, 21, 21},
                {22, 22, 24, 26, 26, 24, 22, 22},
                {30, 30, 30, 30, 30, 30, 30, 22},
                {20, 20, 20, 20, 20, 20, 20, 20}
            },
            // puste
            {
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
            }

    };




void wypisz(int plansza[8][8]){
    printf("   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");
    printf("---+---+---+---+---+---+---+---+---+\n");
    for (int i = 0; i < 8; i++)
    {
        printf(" %d |", i);
        for (int k = 0; k < 8; k++)
        {
            int f = plansza[i][k];
            printf(" %s |", figura(f));
        }
        printf("\n---+---+---+---+---+---+---+---+---+\n");
        printf("\n");
    }
}

int figura(int i){
if (i ==K)
        return "K";
    if (i == H)
        return "H";
    if (i == W)
        return "W";
    if (i == G)
        return "G";
    if (i== S)
        return "S";
    if (i == P)
        return "P";

    if (i == k_k)
        return "k";
    if (i == h_k)
        return "h";
    if (i == w_k)
        return "w";
    if (i == g_k)
        return "g";
    if (i == s_k)
        return "s";
    if (i == p_k)
        return "p";
    return " ";
}



int ocena(int plansza[8][8])
{
int i,j,w=0,t=0,p=0;
  for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
           {
             if(plansza[i][j]==k_k) t++;
             if(plansza[i][j]==K) p++;
           w +=heuryst[plansza[i][j]][i][j];}

    if(t==0)
    return PRZEGRANA;
    if(p==0)
    return WYGRANA;
    return w;
}



int druch(int plansza[8][8], int tryb, int *x, int *y, int *k, int *o)
{
 int px_pom,py_pom,k_pom,o_pom,px,py,dx,dy,kierunek,odleglosc;
       int wynik,wmax,wmin,ruch_fig,bita_fig;
    wynik=ocena(plansza);

if (tryb == 0 || 2*wynik > WYGRANA || 2*wynik < PRZEGRANA)
        return wynik;

    if (tryb % 2 == 0)
    {
        for (px = 0, wmax = 100 * PRZEGRANA; px < 8; px++)
         for (py = 0; py < 8; py++)

            if (plansza[px][py] >= 6 && plansza[px][py] <12)
              for (kierunek = 0; kierunek < MAX_KIER[plansza[px][py]]; kierunek++)
                 for (odleglosc = 1; odleglosc < MAX_ODL[plansza[px][py]]; odleglosc++)
                        {
                            dx = (odleglosc - 1) * WX[plansza[px][py]][kierunek];
                            dy = (odleglosc - 1) * WY[plansza[px][py]][kierunek];
                            if (odleglosc >= 2 && plansza[px + dx][py + dy] !=PUSTE)
                                break;
                            dx = odleglosc * WX[plansza[px][py]][kierunek];
                            dy = odleglosc * WY[plansza[px][py]][kierunek];

                            if (px + dx >= 0 && px + dx < 8 && py + dy >= 0 && py + dy < 8)

                                if (plansza[px + dx][py + dy] == PUSTE || plansza[px + dx][py + dy] <= 5)

                                    if (plansza[px][py] != 11 || (plansza[px + dx][py + dy] == PUSTE && dy == 0) || (plansza[px + dx][py + dy] !=PUSTE && dy != 0))
                                    {
                                        ruch_fig = plansza[px][py];
                                        bita_fig = plansza[px + dx][py + dy];
                                        plansza[px + dx][py + dy] = plansza[px][py];
                                        plansza[px][py] =PUSTE;
                                        if (plansza[px + dx][py + dy] == 11 && py + dy == 7)
                                            plansza[px + dx][py + dy] = h_k;
                                        wynik = druch(plansza, tryb - 1, &px_pom, &py_pom, &k_pom, &o_pom);

                                        plansza[px][py] = ruch_fig;
                                        plansza[px + dx][py + dy] = bita_fig;

                                        if (wynik >= wmax)
                                        {
                                            wmax = wynik;
                                            *x = px;
                                            *y = py;
                                            *k = kierunek;
                                            *o = odleglosc;
                                        }
                                    }
                        }
        return wmax;
    }
    else
    {
        for (px = 0, wmin = 100 * WYGRANA; px < 8; px++)
            for (py = 0; py < 8; py++)

                if (plansza[px][py] <= 5)
                    for (kierunek = 0; kierunek < MAX_KIER[plansza[px][py]]; kierunek++)
                        for (odleglosc = 1; odleglosc < MAX_ODL[plansza[px][py]]; odleglosc++)
                        {
                            dx = (odleglosc - 1) * WX[plansza[px][py]][kierunek];
                            dy = (odleglosc - 1) * WY[plansza[px][py]][kierunek];

                            if (odleglosc >= 2 && plansza[px + dx][py + dy] !=PUSTE)
                                break;
                            dx = odleglosc * WX[plansza[px][py]][kierunek];
                            dy = odleglosc * WY[plansza[px][py]][kierunek];

                            if (px + dx >= 0 && px + dx < 8 && py + dy >= 0 && py + dy < 8)
                                if (plansza[px + dx][py + dy] >= 6)

                                    if (plansza[px][py] != 5 || (plansza[px + dx][py + dy] ==PUSTE && dx == 0) || (plansza[px + dx][py + dy] !=PUSTE && dx != 0))
                                    {
                                        ruch_fig = plansza[px][py];
                                        bita_fig = plansza[px + dx][py + dy];
                                        plansza[px + dx][py + dy] = plansza[px][py];
                                        plansza[px][py] = PUSTE;

                                        if (plansza[px + dx][py + dy] == 5 && py + dy == 0)
                                            plansza[px + dx][py + dy] = 1;
                                        wynik = druch(plansza, tryb - 1, &px_pom, &py_pom, &k_pom, &o_pom);

                                        plansza[px][py] = ruch_fig;
                                        plansza[px + dx][py + dy] = bita_fig;
                                        if (wynik <= wmin)
                                        {
                                            wmin = wynik;
                                            *x = px;
                                            *y = py;
                                            *k = kierunek;
                                            *o = odleglosc;
                                        }
                                    }
                                }
                             return wmin;
                       }
                     }


int main()
{

int r = 0,w;

int plansza[8][8] = {
    {w_k,s_k,g_k,h_k,k_k,g_k,s_k,w_k},
    {p_k,p_k,p_k,p_k,p_k,p_k,p_k,p_k},
    {PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE},
    {PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE},
    {PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE},
    {PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE,PUSTE},
    {P,P,P,P,P,P,P,P},
    {W,S,G,H,K,G,S,W}};

    wypisz(plansza);

    while (1)
    {
        int x,y,k,o,xp,yp,xt,yt;

        printf("TWOJ RUCH Z...DO:\n");
        scanf("%d%d%d%d",&xp,&yp,&xt,&yt);
        plansza[xt][yt]=plansza[xp][yp];
        plansza[xp][yp]=PUSTE;
        wypisz(plansza);
        w=ocena(plansza);
        if(w==WYGRANA||w==PRZEGRANA) break;
        r=druch(plansza, 4, &x, &y, &k, &o);
        printf("%d %d %d %d\n",x,y,k,o);
        plansza[x +o*WX[plansza[x][y]][k]][y + o*WY[plansza[x][y]][k]] = plansza[x][y];
        plansza[x][y] = PUSTE;
        wypisz(plansza);
        w=ocena(plansza);
        if(w==WYGRANA||w==PRZEGRANA) break;
    }
     if(w==WYGRANA) printf("SZACH MAT PRZEGRALES"); return 0;
     if(w==PRZEGRANA) printf("SZACH MAT WYGRALES"); return 0;

         return 0;
    }

