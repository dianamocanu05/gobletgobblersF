#pragma once
#include "Tabla.h"
#include <fstream>
#include "Player.h"
#include <cstdio>
int nrJuc=1;
int PCindex=0;
Player player,computer;
Dreptunghi tabla[3][3];
int matr[3][3];
char numeComputer[10];
char numePlayer[10];
int matriceAnt[3][3];
int castigator;
char GenereazaNumeComputer(char nume[10])
{

    char caractere[] =
        "0123456789"
        "!@#$%^&*"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    int lungime = strlen(caractere) - 1;


    srand(time(0));
    for(int z=0; z < 5; z++)
    {
        char aux[2];
        aux[0]=caractere[rand() % lungime];
        aux[1]='\0';
        strcat(nume, aux);

    }

}
bool AmAlesPvC(int x, int y)
{
    Dreptunghi buton;
    InitDreptunghi(501,0,lungimeEcran,latimeEcran,buton);
    return (Contine(x,y,buton));
}

void NumePVC()
{
    cleardevice();
    settextstyle(0,0,4);
    setcolor(WHITE);
    outtextxy(50,100,"Introdu numele:");
    outtextxy(50,200,"Player 1:");
    outtextxy(50,300,"Computer: ");
    GenereazaNumeComputer(numeComputer);
    outtextxy(350,300,numeComputer);
    IntroduNume(350,200,numePlayer,nrJuc,numeComputer);

}
void Refresh()
{
    bool computerMoved=false;
    setfillstyle(SOLID_FILL,BLACK);
    settextstyle(0,0,4);
    bar(0,0,lungimeEcran,latimeEcran);
    CopiazaMatrice(matriceAnt,matr);
    if(nrJuc==1)
    {
        setcolor(4);
        outtextxy(50,50,numePlayer);
    }
    else
    {

        setcolor(1);
        outtextxy(latimeEcran-100,50,numeComputer);
    }

    int x,y,linie,coloana;
    int i;
    DeseneazaTabla(tabla);
    DeseneazaPiese(player);
    DeseneazaPiese(computer);
    if(nrJuc==1)
    {
        Click(x,y);

        for( i=0; i<6; i++)
        {

            if(Contine(x,y,player.piese[i].d))
            {
                player.piese[i].aFostSelectata=true;
                break;
            }
        }

    }
    else
    {
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(matr[i][j]==0) //verificam unde o putem punte
                {
                    if(PotPunePiesa(computer.piese[PCindex].dimensiune,i,j,matr))
                    {

                        PlaseazaPiesa(tabla,i,j,computer.piese[PCindex]);
                        computerMoved=true;
                        break;
                    }
                }

            }
            if(computerMoved)//s a produs o schimbare
            {
                break;
            }
        }
        PCindex++;


    }
    if(nrJuc==1)
    {
        Click(x,y);
        int l=DeterminaLinie(y);
        int c=DeterminaColoana(x);

        if(PotPunePiesa(player.piese[i].dimensiune,l,c,matr))
        {
            Piesa mutare;
            CopiazaPiese(mutare,player.piese[i]);
            PlaseazaPiesa(tabla,l,c,player.piese[i]);
            Dreptunghi confirma;
            Dreptunghi undo;
            DeseneazaButoane(confirma,undo);
            Click(x,y);
            if(Contine(x,y,undo))
            {
                CopiazaMatrice(matr,matriceAnt);
                CopiazaPiese(player.piese[i],mutare);
            }

            //confirma sau undo;

        }

    }


    nrJuc=(nrJuc++)%2+1;

}
void JocPvC()
{
    time_t gameStart;
    time_t timpFinal;
    gameStart=clock();
    int playerCastigator;
    nrJuc=1;
    InitTabla(tabla);
    Piesa pieseP1[6];
    Piesa pieseP2[6];
    InitPiese(pieseP1,pieseP2);
    InitPlayer(player,numePlayer,pieseP1);
    InitPlayer(computer,numeComputer,pieseP2);
    while(1)
    {
        Refresh();
        castigator=win(matr);
        if(castigator!=0)
        {

            timpFinal=clock();
            break;
        }
    }
    settextstyle(0,0,4);
    char buffer[40];
    setfillstyle(SOLID_FILL,BLACK);
    bar(0,0,lungimeEcran,latimeEcran);

    time_t timpTotal=(timpFinal-gameStart)/ CLOCKS_PER_SEC;

    if(castigator==1)
    {
        sprintf(buffer,"Jucatorul %s a castigat!!!",numePlayer);
        outtextxy(100,100,buffer);
        sprintf(buffer,"%s %d",numePlayer,timpTotal);
        ScrieInFisier(buffer);
    }
    else
    {
        sprintf(buffer,"Jucatorul %s a castigat!!!",numeComputer);
        outtextxy(100,100,buffer);
        sprintf(buffer,"%s %d",numeComputer,timpTotal);
        ScrieInFisier(buffer);
    }
    AfiseazaNEntryuri(5);


}


