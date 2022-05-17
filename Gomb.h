#ifndef GOMB_H
#define GOMB_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Gomb
{
    public:
        float pozicioX1, pozicioY1, pozicioX2, pozicioY2;

        Gomb();

        void beallitas(char szoveg[], void *betutipus, bool hatter, bool keret, int hatterszin, int betuszin,
                       float pozicioX, float pozicioY, float meretX, float meretY, float szovegPozicioX, float szovegPozicioY){

            pozicioX1=pozicioX;
            pozicioY1=pozicioY;
            pozicioX2=pozicioX1+meretX;
            pozicioY2=pozicioY1+meretY;

            if(hatterszin==0 || betuszin==0) {h_r=0.0; h_g=0.0; h_b=0.0; b_r=0.0; b_g=0.0; b_b=0.0;}   //fekete
            if(hatterszin==1 || betuszin==1) {h_r=1.0; h_g=1.0; h_b=1.0; b_r=1.0; b_g=1.0; b_b=1.0;}   //feher
            if(hatterszin==2 || betuszin==2) {h_r=1.0; h_g=0.0; h_b=0.0; b_r=1.0; b_g=0.0; b_b=0.0;}   //piros
            if(hatterszin==3 || betuszin==3) {h_r=1.0; h_g=0.7; h_b=0.0; b_r=1.0; b_g=0.6; b_b=0.1;}   //narancssarga

            if(keret){
                glColor3f(1, 0.7, 0);
                glBegin(GL_QUADS);
                glVertex2i(pozicioX-3, pozicioY-3);
                glVertex2i(pozicioX+meretX+3, pozicioY-3);
                glVertex2i(pozicioX+meretX+3, pozicioY+meretY+3);
                glVertex2i(pozicioX-3, pozicioY+meretY+3);
                glEnd();
            }

            if(hatter){
                glColor3f(1, 0.9, 0);
                glBegin(GL_QUADS);
                glVertex2i(pozicioX, pozicioY);
                glVertex2i(pozicioX+meretX, pozicioY);
                glVertex2i(pozicioX+meretX, pozicioY+meretY);
                glVertex2i(pozicioX, pozicioY+meretY);
                glEnd();
            }

            //glColor3f(b_r, b_g, b_b);
            glColor3f(0, 0, 0);
            char buf[100]={0};
            sprintf(buf, szoveg);
            renderBitmap(pozicioX+szovegPozicioX, pozicioY+(szovegPozicioY*2), betutipus, buf);
        }
    private:
        float h_r, h_g, h_b, b_r, b_g, b_b;

        void renderBitmap(float x, float y, void *font, char *string){
            char *c;
            glRasterPos2f(x, y);
            for(c=string;*c!='\0';c++){
                glutBitmapCharacter(font, *c);
            }
        }
};

#endif // GOMB_H
