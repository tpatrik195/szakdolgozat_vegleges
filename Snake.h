#ifndef SNAKE_H
#define SNAKE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Snake
{
    public:
        int pontszam=0;
        int snakeX, snakeY;
        int randomX, randomY;
        bool food=true;
        short kigyo_irany;
        vector<int> elozoX;
        vector<int> elozoY;

        Snake();

        void beallitas(int kezdo_pozicioX, int kezdo_pozicioY, int irany, int szin){
            snakeX=kezdo_pozicioX;
            snakeY=kezdo_pozicioY;
            szines_kigyo=false;

            if(irany==2)  {eX=snakeX-0; eY=snakeY; eeX=snakeX-40; eeY=snakeY; kigyo_irany=2;}   //jobb
            if(irany==-2) {eX=snakeX+0; eY=snakeY; eeX=snakeX+40; eeY=snakeY; kigyo_irany=-2;}   //bal
            if(irany==1)  {eX=snakeX; eY=snakeY-20; eeX=snakeX; eeY=snakeY-40; kigyo_irany=1;}   //fel
            if(irany==-1) {eX=snakeX; eY=snakeY+20; eeX=snakeX; eeY=snakeY+40; kigyo_irany=-1;}   //le

            if(szin==2) {r_fej=0.0; g_fej=1.0; b_fej=0.0; r_farok=0.0; g_farok=0.5; b_farok=0.0;}   //zold
            if(szin==3) {r_fej=0.0; g_fej=0.0; b_fej=1.0; r_farok=0.0; g_farok=0.0; b_farok=0.5;}   //kek
            if(szin==4) {r_fej=1.0; g_fej=0.0; b_fej=0.0; r_farok=0.5; g_farok=0.0; b_farok=0.0;}   //piros
            if(szin==5) {r_fej=0.6; g_fej=0.6; b_fej=0.6; r_farok=0.2; g_farok=0.2; b_farok=0.2;}   //szurke
            if(szin==6) {r_fej=1.0; g_fej=0.0; b_fej=1.0; r_farok=0.5; g_farok=0.0; b_farok=0.5;}   //lila
            if(szin==7) {r_fej=1.0; g_fej=0.6; b_fej=0.1; r_farok=0.8; g_farok=0.4; b_farok=0.1;}   //narancssarga
            if(szin==8) szines_kigyo=true;   //szines
            if(szin==9) {r_fej=0.0; g_fej=0.0; b_fej=0.0; r_farok=0.0; g_farok=0.0; b_farok=0.0;}   //atlatszo
        }

        void kigyo_kirajzolasa(){
            eeX=eX;
            eeY=eY;
            eX=snakeX;
            eY=snakeY;

            if(pontszam>0){
                elozoX.push_back(snakeX);
                elozoY.push_back(snakeY);
            }

            if(kigyo_irany==1) snakeY-=20;
            if(kigyo_irany==-1) snakeY+=20;
            if(kigyo_irany==2) snakeX+=20;
            if(kigyo_irany==-2) snakeX-=20;

            if(szines_kigyo){
                /*
                //akkor valtoztatja meg a kigyo szinet ha uj pontot szed fel
                int hanyankent_valtozik=6;
                if(pontszam%6==0) {r_fej=0.0; g_fej=1.0; b_fej=0.0; r_farok=0.0; g_farok=0.5; b_farok=0.0;}   //zold
                if(pontszam%6==1) {r_fej=0.0; g_fej=0.0; b_fej=1.0; r_farok=0.0; g_farok=0.0; b_farok=0.5;}   //kek
                if(pontszam%6==2) {r_fej=1.0; g_fej=0.0; b_fej=0.0; r_farok=0.5; g_farok=0.0; b_farok=0.0;}   //piros
                if(pontszam%6==3) {r_fej=0.6; g_fej=0.6; b_fej=0.6; r_farok=0.2; g_farok=0.2; b_farok=0.2;}   //szurke
                if(pontszam%6==4) {r_fej=1.0; g_fej=0.0; b_fej=1.0; r_farok=0.5; g_farok=0.0; b_farok=0.5;}   //lila
                if(pontszam%6==5) {r_fej=1.0; g_fej=0.6; b_fej=0.1; r_farok=0.8; g_farok=0.4; b_farok=0.1;}   //sarga
                */
                //masodpercenkent valtoztatja a kigyo szinet
                time_t masodperc;
                masodperc=time(NULL);
                masodperc=masodperc%6;
                    if(masodperc==0) {r_fej=0.0; g_fej=1.0; b_fej=0.0; r_farok=0.0; g_farok=0.5; b_farok=0.0;}   //zold
                    if(masodperc==1) {r_fej=0.0; g_fej=0.0; b_fej=1.0; r_farok=0.0; g_farok=0.0; b_farok=0.5;}   //kek
                    if(masodperc==2) {r_fej=1.0; g_fej=0.0; b_fej=0.0; r_farok=0.5; g_farok=0.0; b_farok=0.0;}   //piros
                    if(masodperc==3) {r_fej=0.6; g_fej=0.6; b_fej=0.6; r_farok=0.2; g_farok=0.2; b_farok=0.2;}   //szurke
                    if(masodperc==4) {r_fej=1.0; g_fej=0.0; b_fej=1.0; r_farok=0.5; g_farok=0.0; b_farok=0.5;}   //lila
                    if(masodperc==5) {r_fej=1.0; g_fej=0.6; b_fej=0.1; r_farok=0.8; g_farok=0.4; b_farok=0.1;}   //sarga
                }

            //fej
            glColor3f(r_fej, g_fej, b_fej);
            glPointSize(20);
            glBegin(GL_POINTS);
            glVertex2i(snakeX, snakeY);
            glEnd();

            //farok ha a pontszam 0   Ooo
            glColor3f(r_farok, g_farok, b_farok);
            glPointSize(20);
            glBegin(GL_POINTS);
            glVertex2i(eX, eY);
            glVertex2i(eeX, eeY);
            glEnd();

            //farok
            if(pontszam>0){
                for(int i=elozoX.size();i>elozoX.size()-pontszam-1-2+1;i--){
                    glColor3f(r_farok, g_farok, b_farok);   //sotet zold
                    glPointSize(20);
                    glBegin(GL_POINTS);
                    glVertex2i(elozoX[i-1], elozoY[i-1]);
                    glEnd();
                }
            }
        }

        void kaja_generalas(){
            if(food){
                srand(time(NULL));
                int kilepes;
                do{
                    kilepes=0;
                    randomX=rand()%(690-120+1)+120;
                    if(randomX%20!=0) kilepes=1;
                    for(int i=elozoX.size();i>elozoX.size()-pontszam-1;i--){
                        if(randomX==elozoX[i]) kilepes=1;
                    }
                }while(kilepes==1);
                do{
                    kilepes=0;
                    randomY=rand()%(450-120+1)+120;
                    if(randomY%20!=0) kilepes=1;
                    for(int i=elozoX.size();i>elozoX.size()-pontszam-1;i--){
                        if(randomY==elozoY[i]) kilepes=1;
                    }
                }while(kilepes==1);
            }
            glColor3f(1, 1, 0);   //sarga
            glPointSize(20);
            glBegin(GL_POINTS);
            glVertex2i(randomX, randomY);
            glEnd();

            food=false;
        }

        void iranyitas(unsigned char key, int x, int y){   //w a s d
            switch(key){
                case 'w':   //fel
                    if(kigyo_irany!=-1) kigyo_irany=1;
                    break;
                case 'a':   //bal
                    if(kigyo_irany!=2) kigyo_irany=-2;
                    break;
                case 's':   //le
                    if(kigyo_irany!=1) kigyo_irany=-1;
                    break;
                case 'd':   //jobb
                    if(kigyo_irany!=-2) kigyo_irany=2;
                    break;
            }
        }

        void jatek_vege(){
            char pontszam_char[10];
            itoa(pontszam, pontszam_char, 10);
            char szoveg[50]="Pontszám: ";
            strcat(szoveg, pontszam_char);
            MessageBox(NULL, szoveg, "Játék Vége", 0);
        }

        void jatek_vezerlo(short jatekos_szam, int &penz, bool &game_over, int kigyo2_fejX, int kigyo2_fejY, vector<int> &kigyo2_farokX, vector<int> &kigyo2_farokY, int &kigyo2_pontszam){
            if(jatekos_szam==1){
                for(int i=elozoX.size();i>elozoX.size()-pontszam-1;i--){
                    if(snakeX==elozoX[i] && snakeY==elozoY[i]) {jatek_vege(); game_over=true;}  //ne lehessen atmenni a farkan
                }

                //kigyo 1
                if(snakeY<50 || snakeX<50 || snakeY>500 || snakeX>760) {jatek_vege(); game_over=true;}   //ha nekimesz a falnak
                if(snakeX==randomX && snakeY==randomY){   //uj kaja generalas
                    glColor3f(r_fej, g_fej, b_fej);
                    glPointSize(20);
                    glBegin(GL_POINTS);
                    glVertex2i(randomX, randomY);
                    glEnd();
                    pontszam++;
                    penz+=10;
                    food=true;
                    kaja_generalas();
                }
            }

            if(jatekos_szam==2){
                //kigyo 1
                for(int i=elozoX.size();i>elozoX.size()-pontszam-1;i--){
                    if(snakeX==elozoX[i] && snakeY==elozoY[i]){   //ne lehessen atmenni a farkan
                        char pontszam_char[10];
                        itoa(kigyo2_pontszam, pontszam_char, 10);
                        char szoveg[50]="2. jatekos(kek) nyert!\nPontszám: ";
                        strcat(szoveg, pontszam_char);
                        MessageBox(NULL, szoveg, "Játék Vége", 0);

                        game_over=true;
                    }
                }
                if(snakeY<50+20 || snakeX<50+20 || snakeY>500-20 || snakeX>760-20){   //ha nekimesz a falnak
                    char pontszam_char[10];
                    itoa(kigyo2_pontszam, pontszam_char, 10);
                    char szoveg[50]="2. jatekos(kek) nyert!\nPontszám: ";
                    strcat(szoveg, pontszam_char);
                    MessageBox(NULL, szoveg, "Játék Vége", 0);

                    game_over=true;
                }

                //kigyo 2
                if(kigyo2_fejY<50+20 || kigyo2_fejX<50+20 || kigyo2_fejY>500-20 || kigyo2_fejX>760-20){   //ha nekimegy a falnak
                    char pontszam_char[10];
                    itoa(pontszam, pontszam_char, 10);
                    char szoveg[50]="1. jatekos(zold) nyert!\nPontszám: ";
                    strcat(szoveg, pontszam_char);
                    MessageBox(NULL, szoveg, "Játék Vége", 0);

                    game_over=true;
                }
                //a 20-ak azert kellenek, mert hanem a feje a falba lesz amikor meghal

                for(int i=kigyo2_farokX.size();i>kigyo2_farokX.size()-kigyo2_pontszam-1;i--){
                    if(kigyo2_fejX==kigyo2_farokX[i] && kigyo2_fejY==kigyo2_farokY[i]){   //ne lehessen atmenni a farkan
                        char pontszam_char[10];
                        itoa(pontszam, pontszam_char, 10);
                        char szoveg[50]="1. jatekos(zold) nyert!\nPontszám: ";
                        strcat(szoveg, pontszam_char);
                        MessageBox(NULL, szoveg, "Játék Vége", 0);

                        game_over=true;
                    }
                }

                //egymasba utkozes, ha mar van pontszam
                if(kigyo2_farokX.size()>0 && kigyo2_farokY.size()>0){
                    for(int i=kigyo2_farokX.size();i>kigyo2_farokX.size()-kigyo2_pontszam-1;i--){
                        if(snakeX==kigyo2_farokX[i] && snakeY==kigyo2_farokY[i]){   //ne lehessen atmenni a farkan
                            char pontszam_char[10];
                            itoa(kigyo2_pontszam, pontszam_char, 10);
                            char szoveg[50]="2. jatekos(kek) nyert!\nPontszám: ";
                            strcat(szoveg, pontszam_char);
                            MessageBox(NULL, szoveg, "Játék Vége", 0);

                            game_over=true;
                        }
                        else if(snakeX==kigyo2_fejX && snakeY==kigyo2_fejY){
                            MessageBox(NULL, "Dontetlen!", "Játék Vége", 0);
                            game_over=true;
                        }
                    }
                }
                if(elozoX.size()>0 && elozoY.size()>0){
                    for(int i=elozoX.size();i>elozoX.size()-pontszam-1;i--){
                        if(kigyo2_fejX==elozoX[i] && kigyo2_fejY==elozoY[i]){   //ne lehessen atmenni a farkan
                            char pontszam_char[10];
                            itoa(pontszam, pontszam_char, 10);
                            char szoveg[50]="1. jatekos(zold) nyert!\nPontszám: ";
                            strcat(szoveg, pontszam_char);
                            MessageBox(NULL, szoveg, "Játék Vége", 0);

                            game_over=true;
                        }
                        else if(kigyo2_fejX==snakeX && kigyo2_fejY==snakeY){
                            MessageBox(NULL, "Dontetlen!", "Játék Vége", 0);
                            game_over=true;
                        }
                    }
                }

                //kigyo 1
                if(snakeX==randomX && snakeY==randomY){   //uj kaja generalas
                    glColor3f(r_fej, g_fej, b_fej);
                    glPointSize(20);
                    glBegin(GL_POINTS);
                    glVertex2i(randomX, randomY);
                    glEnd();
                    pontszam++;
                    penz+=10;
                    food=true;
                    kaja_generalas();
                }

                //kigyo 2
                if(kigyo2_fejX==randomX && kigyo2_fejY==randomY){   //uj kaja generalas
                    glColor3f(r_fej, g_fej, b_fej);
                    glPointSize(20);
                    glBegin(GL_POINTS);
                    glVertex2i(randomX, randomY);
                    glEnd();
                    kigyo2_pontszam++;
                    food=true;
                    kaja_generalas();
                }
            }
        }

    private:
        int eX, eY, eeX, eeY;
        int eX2, eY2, eeX2, eeY2;
        float r_fej, g_fej, b_fej, r_farok, g_farok, b_farok;
        bool szines_kigyo=false;
};

#endif // SNAKE_H
