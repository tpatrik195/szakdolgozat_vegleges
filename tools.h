#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <vector>
#include <sstream>
#include <ctime>

using namespace std;

int string_to_int(string str){
    int szam;
    stringstream(str)>>szam;
    return szam;
}

void int_to_string(string &ev_string, string &honap_string, string &nap_string, string &ora_string, string &perc_string,
                   int ev, int honap, int nap, int ora, int perc){

    stringstream es;
    es<<ev;
    ev_string=es.str();

    stringstream hs;
    hs<<honap;
    honap_string=hs.str();
    if(honap_string.size()==1) honap_string="0"+honap_string;

    stringstream ns;
    ns<<nap;
    nap_string=ns.str();
    if(nap_string.size()==1) nap_string="0"+nap_string;

    stringstream os;
    os<<ora;
    ora_string=os.str();
    if(ora_string.size()==1) ora_string="0"+ora_string;

    stringstream ps;
    ps<<perc;
    perc_string=ps.str();
    if(perc_string.size()==1) perc_string="0"+perc_string;
}

string datum_lekerdezese(){
    time_t currentTime;
    time(&currentTime);
    struct tm*myTime=localtime(&currentTime);

    int ev=0, honap=0, nap=0, ora=0, perc=0;
    ev=myTime->tm_year+1900;
    honap=myTime->tm_mon+1;
    nap=myTime->tm_mday;
    ora=myTime->tm_hour;
    perc=myTime->tm_min;

    string datum, ev_string, honap_string, nap_string, ora_string, perc_string;
    int_to_string(ev_string, honap_string, nap_string, ora_string, perc_string, ev, honap, nap, ora, perc);

    datum=ev_string+"."+honap_string+"."+nap_string+". "+ora_string+":"+perc_string;
    return datum;
}

void regisztralt_mentese_fajlba(vector<char> felhasznalo_nev, vector<char> jelszo, string eleresi_ut){
    string f="", j="";   //f-felhasznalonev / j-jelszo

    //a karakterlancokbol stringet csinal, hogy tudja beleirni a fajlba
    for(int i=0;i<felhasznalo_nev.size();i++) f+=felhasznalo_nev[i];
    for(int i=0;i<jelszo.size();i++) j+=jelszo[i];

    //beolvassa az eddigi adatokat
    string path=eleresi_ut+"\\felhasznalok.adatok";
    ifstream fin(path.c_str());
    string sor;
    vector<string> tartalom;
    while(!fin.eof()){
        getline(fin, sor);
        tartalom.push_back(sor);
    }
    fin.close();

    //a beolvasottakat beleirja
    ofstream fout(path.c_str());
    for(int i=0;i<tartalom.size();i++){
        fout<<tartalom[i]<<endl;
    }

    //beleirja az uj felhasznalo adatait
    //felhasznalonev  jelszo  szint  penz  kezdoszin  megvasarolt szinek
    fout<<f<<" "<<j<<" "<<"1"<<" "<<"100"<<" "<<"2"<<" "<<"1"<<" "<<"0"<<" "<<"0"<<" "<<"0"<<" "<<"0"<<" "<<"0"<<" "<<"0"<<" "<<"0";

    fout.close();

    //letrehozza a fajlt amibe menti majd a pontszamait
    string fajl_nev=eleresi_ut+"\\"+f+".pontszamok";
    string datum=datum_lekerdezese();
    ofstream uj_fajl(fajl_nev.c_str());
    uj_fajl<<"Rekord: 0 pont ["<<datum<<"]"<<endl;
    uj_fajl.close();
}

bool regisztralasnal_ellenorzi_hogy_vane_mar_ilyen_nevu_felhasznalo(vector<char> felhasznalo_nev, string eleresi_ut){
    bool ertek=false;

    string f="";
    for(int i=0;i<felhasznalo_nev.size();i++) f+=felhasznalo_nev[i];

    string sor, nev="";
    string a, b, c, d, e, g, h, i, j, k, l, m;   //seged/ideiglenes valtozok
    string path=eleresi_ut+"\\felhasznalok.adatok";
    ifstream fin(path.c_str());
    while(!fin.eof()){
        fin>>nev>>a>>b>>c>>d>>e>>g>>h>>i>>j>>k>>l>>m;
        if(f==nev){ertek=true; break;}
    }
    fin.close();

    return ertek;
}

void fajl_tartalmanak_szetszedese(vector<char> felhasznalo_nev, vector<char> jelszo, bool &sikeres_belepes, short &szint,
                                  int &penz, short kezdoszin, bool &szin1, bool &szin2, bool &szin3, bool &szin4,
                                  bool &szin5, bool &szin6, bool &szin7, bool &szin8, string eleresi_ut){

    string f="", j="";   //f-felhasznalonev / j-jelszo
    for(int i=0;i<felhasznalo_nev.size();i++) f+=felhasznalo_nev[i];
    for(int i=0;i<jelszo.size();i++) j+=jelszo[i];

    string path=eleresi_ut+"\\felhasznalok.adatok";
    ifstream fin(path.c_str());

    string f_nev="", jsz="";
    short sz=0, kszin=0;
    int p=0;
    bool sz1=0, sz2=0, sz3=0, sz4=0, sz5=0, sz6=0, sz7=0, sz8=0;

    while(!fin.eof()){
        fin>>f_nev>>jsz>>sz>>p>>kszin>>sz1>>sz2>>sz3>>sz4>>sz5>>sz6>>sz7>>sz8;
        if(f==f_nev && j==jsz){
            sikeres_belepes=true;
            szint=sz;
            penz=p;
            kezdoszin=kszin;
            szin1=sz1;
            szin2=sz2;
            szin3=sz3;
            szin4=sz4;
            szin5=sz5;
            szin6=sz6;
            szin7=sz7;
            szin8=sz8;
        }
    }

    fin.close();
}

void felhasznalo_adatainak_felulirasa(vector<char> felhasznalo_nev, vector<char> jelszo, short szint, int penz,
                                      short kezdoszin, bool zold, bool kek, bool piros, bool szurke, bool lila,
                                      bool sarga, bool szines, bool atlatszo, string eleresi_ut){

    string f="", j="";   //f-felhasznalonev / j-jelszo
    for(int i=0;i<felhasznalo_nev.size();i++) f+=felhasznalo_nev[i];
    for(int i=0;i<jelszo.size();i++) j+=jelszo[i];

    string path=eleresi_ut+"\\felhasznalok.adatok";
    ifstream fin(path.c_str());
    string sor;
    vector<string> tartalom;
    while(!fin.eof()){
        getline(fin, sor);
        tartalom.push_back(sor);
    }
    fin.close();

    string b_f_nev="";
    int pozicio=0;
    for(int i=0;i<tartalom.size();i++){
        int j=0;
        while(!isspace(tartalom[i][j])){
            b_f_nev+=tartalom[i][j];
            j++;
        }
        if(f==b_f_nev){
            pozicio=i;
            break;
        }
        b_f_nev="";
    }

    tartalom.erase(tartalom.begin()+pozicio);

    ofstream fout(path.c_str());
    for(int i=0;i<tartalom.size();i++){
        fout<<tartalom[i]<<endl;
    }
    fout<<f<<" "<<j<<" "<<szint<<" "<<penz<<" "<<kezdoszin<<" "<<zold<<" "<<kek<<" "<<piros<<" "<<szurke<<" "<<lila<<" "<<sarga<<" "<<szines<<" "<<atlatszo;
    fout.close();
}

void renderBitmap(float x, float y, void *font, char *string){
    char *c;
    glRasterPos2f(x, y);
    for(c=string;*c!='\0';c++){
        glutBitmapCharacter(font, *c);
    }
}

void kiiras(char szoveg[], void *betutipus, int x, int y){
    glColor3f(1.0, 1.0, 1.0);
    char buf[100]={0};

    sprintf(buf, szoveg);
    renderBitmap(x, y, betutipus, buf);
}

void szam_kiirasa_az_ablakra(int szam, char szoveg[], void *betutipus, int x, int y){
    glColor3f(1, 1, 1);
    char buf[100]={0};
    char sz[50];
    strcpy(sz, szoveg);
    char szam_char[10];
    itoa(szam, szam_char, 10);
    strcat(sz, szam_char);
    sprintf(buf, sz);
    renderBitmap(x, y, betutipus, buf);
}

void negyzet_keret_kirajzolasa(int kezdoPozicioX, int kezdoPozicioY, int hosszusag, int szellesseg){
    glColor3f(1.0, 1.0, 1.0);   //feher
    glBegin(GL_LINE_STRIP);
    glVertex2i(kezdoPozicioX, kezdoPozicioY);
    glVertex2i(kezdoPozicioX+hosszusag, kezdoPozicioY);
    glVertex2i(kezdoPozicioX+hosszusag, kezdoPozicioY+szellesseg);
    glVertex2i(kezdoPozicioX, kezdoPozicioY+szellesseg);
    glVertex2i(kezdoPozicioX, kezdoPozicioY-1);
    glFlush();
    glEnd();
}

void egy_kigyo_kirajzolasa(int szin, int pozicioX, int pozicioY){
    float r_fej, g_fej, b_fej, r_farok, g_farok, b_farok;
    if(szin==2) {r_fej=0.0; g_fej=1.0; b_fej=0.0; r_farok=0.0; g_farok=0.5; b_farok=0.0;}   //zold
    if(szin==3) {r_fej=0.0; g_fej=0.0; b_fej=1.0; r_farok=0.0; g_farok=0.0; b_farok=0.5;}   //kek
    if(szin==4) {r_fej=1.0; g_fej=0.0; b_fej=0.0; r_farok=0.5; g_farok=0.0; b_farok=0.0;}   //piros
    if(szin==5) {r_fej=0.6; g_fej=0.6; b_fej=0.6; r_farok=0.2; g_farok=0.2; b_farok=0.2;}   //szurke
    if(szin==6) {r_fej=1.0; g_fej=0.0; b_fej=1.0; r_farok=0.5; g_farok=0.0; b_farok=0.5;}   //lila
    if(szin==7) {r_fej=1.0; g_fej=0.6; b_fej=0.1; r_farok=0.8; g_farok=0.4; b_farok=0.1;}   //narancssarga

    glPointSize(20);
    glBegin(GL_POINTS);
    glColor3f(r_fej, g_fej, b_fej);   //fej
    glVertex2i(pozicioX, pozicioY);
    glColor3f(r_farok, g_farok, b_farok);   //farok
    glVertex2i(pozicioX+20, pozicioY);
    glVertex2i(pozicioX+40, pozicioY);
    glFlush();
    glEnd();
}

void hatterszin_ballitasa(int kezdoPozicioX, int kezdoPozicioY, int hosszusag, int szellesseg, float r, float g, float b){
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2i(kezdoPozicioX, kezdoPozicioY);
    glVertex2i(kezdoPozicioX+hosszusag, kezdoPozicioY);
    glVertex2i(kezdoPozicioX+hosszusag, kezdoPozicioY+szellesseg);
    glVertex2i(kezdoPozicioX, kezdoPozicioY+szellesseg);
    glVertex2i(kezdoPozicioX, kezdoPozicioY);
    glEnd();
}

int karakter_hossza(char betu){
    int hossz;

    switch(betu){
        case 'A': hossz=14; break;
        case 'B': hossz=13; break;
        case 'C': hossz=14; break;
        case 'D': hossz=13; break;
        case 'E': hossz=12; break;
        case 'F': hossz=12; break;
        case 'G': hossz=15; break;
        case 'H': hossz=14; break;
        case 'I': hossz=8;  break;
        case 'J': hossz=11; break;
        case 'K': hossz=14; break;
        case 'L': hossz=10; break;
        case 'M': hossz=17; break;
        case 'N': hossz=14; break;
        case 'O': hossz=15; break;
        case 'P': hossz=12; break;
        case 'Q': hossz=16; break;
        case 'R': hossz=14; break;
        case 'S': hossz=14; break;
        case 'T': hossz=14; break;
        case 'U': hossz=14; break;
        case 'V': hossz=15; break;
        case 'W': hossz=19; break;
        case 'X': hossz=14; break;
        case 'Y': hossz=15; break;
        case 'Z': hossz=13; break;

        case 'a': hossz=10; break;
        case 'b': hossz=12; break;
        case 'c': hossz=10; break;
        case 'd': hossz=12; break;
        case 'e': hossz=12; break;
        case 'f': hossz=9;  break;
        case 'g': hossz=12; break;
        case 'h': hossz=11; break;
        case 'i': hossz=6;  break;
        case 'j': hossz=6;  break;
        case 'k': hossz=11; break;
        case 'l': hossz=6;  break;
        case 'm': hossz=15; break;
        case 'n': hossz=11; break;
        case 'o': hossz=12; break;
        case 'p': hossz=12; break;
        case 'q': hossz=12; break;
        case 'r': hossz=9;  break;
        case 's': hossz=10; break;
        case 't': hossz=9;  break;
        case 'u': hossz=11; break;
        case 'v': hossz=11; break;
        case 'w': hossz=15; break;
        case 'x': hossz=11; break;
        case 'y': hossz=11; break;
        case 'z': hossz=10; break;

        case '0': hossz=11; break;
        case '1': hossz=10; break;
        case '2': hossz=12; break;
        case '3': hossz=11; break;
        case '4': hossz=12; break;
        case '5': hossz=11; break;
        case '6': hossz=11; break;
        case '7': hossz=11; break;
        case '8': hossz=11; break;
        case '9': hossz=11; break;

        default:  hossz=0;  break;
    }

    return hossz;
}

void szovegmezobe_iras(char key, vector<char> &feltoltes, short mezo_hossza, short &szoveg_hossza){
    if(szoveg_hossza<mezo_hossza-15){
        szoveg_hossza+=karakter_hossza(key);
        if(key!=8 && key!=13 && (isalpha(key) || isdigit(key))){
            feltoltes.push_back(key);
        }
    }
    if(key==8 && feltoltes.size()>0){
        feltoltes.pop_back();
        szoveg_hossza-=karakter_hossza(feltoltes[feltoltes.size()]);
    }
}

#endif // TOOLS_H_INCLUDED
