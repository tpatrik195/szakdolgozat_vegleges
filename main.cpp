#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Map.h"
#include "Snake.h"
#include "tools.h"
#include "Gomb.h"

#define ABLAK_HOSSZUSAG 820
#define ABLAK_SZELLESSEG 610

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

#define BLACK 0
#define WHITE 1
#define GREEN 2
#define BLUE 3
#define RED 4
#define GRAY 5
#define PURPLE 6
#define ORANGE 7
#define colorful 8
#define transparent 9

#define FPS 13

using namespace std;

Gomb belepes_ful_gomb;
Gomb jelszo_megjelenitese_b;
Gomb belepes_gomb;
Gomb regisztracio_ful_gomb;
Gomb jelszo_megjelenitese_r;
Gomb regisztracio_gomb;

Gomb egyjatekos_gomb;
Gomb ketjatekos_gomb;
Gomb online_gomb;
Gomb online_szoba_letrehozasa;
Gomb online_kod_beirasa;
Gomb online_letrehozas;
Gomb online_belepes;
Gomb bolt_gomb;
Gomb ranglista_gomb;
Gomb sugo_gomb;
Gomb sugo_vissza_gomb;
Gomb kijelentkezes_gomb;

Gomb megvasarol_zold;
Gomb megvasarol_kek;
Gomb megvasarol_piros;
Gomb megvasarol_szurke;
Gomb megvasarol_lila;
Gomb megvasarol_sarga;
Gomb megvasarol_szines;
Gomb megvasarol_atlatszo;

int penz=0;
short szint=0;
string eleresi_ut="";

short cursor_x=0;
short cursor_y=0;

bool bejelentkezes_ablak=true;
bool menu_ablak=false;
bool egyjatekos_ablak=false;
bool ketjatekos_ablak=false;
bool belepes_ful=true;
bool regisztracio_ful=false;
bool sikeres_belepes=false;
bool sikeres_regisztralas=false;
bool sugo_ablak=false;
bool sugo_felirat=false;
bool kijelentkezes_felirat=false;
bool bolt_ablak=false;
bool ranglista_ablak=false;
bool online_ablak=false;
bool online_szoba_ful=true;
bool online_kod_ful=false;
bool generaljon=false;
bool game_over=false;

//kigyo szinei
short kezdoszin=2;
bool zold, kek, piros, szurke, lila, sarga, szines, atlatszo;

vector<char> felhasznalo_nev;
vector<char> jelszo;
vector<char> jelszo_ujra;

bool felhasznalo_nev_beirasa=false;
bool jelszo_beirasa=false;
bool reg_felhasznalo_nev_beirasa=false;
bool reg_jelszo_beirasa=false;
bool reg_jelszo_ujra_beirasa=false;
bool jelszo_megjelenitese=false;
bool jelszo_megjelenitese_b_felirat=false;
bool jelszo_megjelenitese_r_felirat=false;
bool csillag_felirat=false;

short szoveg_hossza_b_f_nev=0, szoveg_hossza_b_j=0, szoveg_hossza_r_f_nev=0, szoveg_hossza_r_j=0, szoveg_hossza_r_j_u=0;
//b - bejelentkezesnel
//r - regisztracional

int kigyo_jelenlegi_szine=GREEN;
Map palya(30, 30, 1);
Snake kigyo, kigyo2;

void init(){
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, ABLAK_HOSSZUSAG, ABLAK_SZELLESSEG, 0);
}

void resize(int w,int h){
    glutReshapeWindow(ABLAK_HOSSZUSAG, ABLAK_SZELLESSEG);
}

char irany_jatekos1, irany_jatekos2;
void betu_jatekos_1(unsigned char key, int x, int y) {irany_jatekos1=key;}   //w a s d
void betu_jatekos_2(int key, int, int){   //fel le jobb bal
    switch(key){
        case GLUT_KEY_UP:   {irany_jatekos2='w'; break;}
        case GLUT_KEY_DOWN: {irany_jatekos2='s'; break;}
        case GLUT_KEY_RIGHT:{irany_jatekos2='d'; break;}
        case GLUT_KEY_LEFT: {irany_jatekos2='a'; break;}
    }
}

void display_menu();

void iras(unsigned char key, int x, int y){
    //belepesnel az iras
    if(belepes_ful && !regisztracio_ful){
        if(felhasznalo_nev_beirasa && !jelszo_beirasa){   //felhasznalonev
            szovegmezobe_iras(key, felhasznalo_nev, 180, szoveg_hossza_b_f_nev);
        }
        if(!felhasznalo_nev_beirasa && jelszo_beirasa){   //jelszo
            szovegmezobe_iras(key, jelszo, 218, szoveg_hossza_b_j);
        }
    }

    //regisztracional az iras
    if(regisztracio_ful && !belepes_ful){
        if(reg_felhasznalo_nev_beirasa && !reg_jelszo_beirasa && !reg_jelszo_ujra_beirasa){
            szovegmezobe_iras(key, felhasznalo_nev, 180, szoveg_hossza_r_f_nev);
        }
        if(!reg_felhasznalo_nev_beirasa && reg_jelszo_beirasa && !reg_jelszo_ujra_beirasa){
            szovegmezobe_iras(key, jelszo, 218, szoveg_hossza_r_j);
        }
        if(!reg_felhasznalo_nev_beirasa && !reg_jelszo_beirasa && reg_jelszo_ujra_beirasa){
            szovegmezobe_iras(key, jelszo_ujra, 225, szoveg_hossza_r_j_u);
        }
    }

    glutPostRedisplay();
}

void mouse_routine(int x, int y){
    //jelszo megjelenitese bejelentkezes
    if(x>=jelszo_megjelenitese_b.pozicioX1 && x<=jelszo_megjelenitese_b.pozicioX2 &&
       y>=jelszo_megjelenitese_b.pozicioY1 && y<=jelszo_megjelenitese_b.pozicioY2){
        jelszo_megjelenitese_b_felirat=true;
        cursor_x=x;
        cursor_y=y;
        glutPostRedisplay();
    }
    else{
        jelszo_megjelenitese_b_felirat=false;
        glutPostRedisplay();
    }

    //jelszo megjelenitese regisztracional
    if(x>=jelszo_megjelenitese_r.pozicioX1 && x<=jelszo_megjelenitese_r.pozicioX2 &&
       y>=jelszo_megjelenitese_r.pozicioY1 && y<=jelszo_megjelenitese_r.pozicioY2){
        jelszo_megjelenitese_r_felirat=true;
        cursor_x=x;
        cursor_y=y;
        glutPostRedisplay();
    }
    else{
        jelszo_megjelenitese_r_felirat=false;
        glutPostRedisplay();
    }

    //sugo felirat
    if(x>=sugo_gomb.pozicioX1 && x<=sugo_gomb.pozicioX2 &&
       y>=sugo_gomb.pozicioY1 && y<=sugo_gomb.pozicioY2){
        sugo_felirat=true;
        cursor_x=x;
        cursor_y=y;
        glutPostRedisplay();
    }
    else{
        sugo_felirat=false;
        glutPostRedisplay();
    }

    //kijelentkezes felirat
    if(x>=kijelentkezes_gomb.pozicioX1 && x<=kijelentkezes_gomb.pozicioX2 &&
       y>=kijelentkezes_gomb.pozicioY1 && y<=kijelentkezes_gomb.pozicioY2){
        kijelentkezes_felirat=true;
        cursor_x=x;
        cursor_y=y;
        glutPostRedisplay();
    }
    else{
        kijelentkezes_felirat=false;
        glutPostRedisplay();
    }

    //csillag felirat
    if(x>=136 && x<=155 && y>=34 && y<=52){
        csillag_felirat=true;
        cursor_x=x;
        cursor_y=y;
        glutPostRedisplay();
    }
    else{
        csillag_felirat=false;
        glutPostRedisplay();
    }
}

void display_egyjatekos_mod(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    palya.palya_kirajzolasa();
    glutKeyboardFunc(betu_jatekos_1);
    kigyo.iranyitas(irany_jatekos1, 0, 0);
    kigyo.kigyo_kirajzolasa();
    kigyo.kaja_generalas();
    kigyo.jatek_vezerlo(1, penz, game_over, kigyo2.snakeX, kigyo2.snakeY, kigyo2.elozoX, kigyo2.elozoY, kigyo2.pontszam);
    szam_kiirasa_az_ablakra(kigyo.pontszam, "Pontszam: ", GLUT_BITMAP_TIMES_ROMAN_24, 345, 580);

    glutSwapBuffers();

    if(game_over==true){
        string datum=datum_lekerdezese();
        string sor, f="", path="";
        vector<string> tartalom;
        for(int i=0;i<felhasznalo_nev.size();i++) f+=felhasznalo_nev[i];
        //path="C:\\Users\\PATRIK\\Documents\\atestat\\"+f+".pontszamok";
        path=eleresi_ut+"\\"+f+".pontszamok";
        ifstream fin(path.c_str());
        while(!fin.eof()){
            getline(fin, sor);
            tartalom.push_back(sor);
        }
        fin.close();

        string regi_rekord="";
        int rekord;
        for(int i=0;i<tartalom[0].size();i++){
            if(isdigit(tartalom[0][i])){
                while(isdigit(tartalom[0][i])){
                    regi_rekord+=tartalom[0][i];
                    i++;
                }
                break;
            }
        }
        rekord=string_to_int(regi_rekord);

        ofstream fout(path.c_str());
        if(kigyo.pontszam>rekord) fout<<"Rekord: "<<kigyo.pontszam<<" pont ["<<datum<<"]"<<endl;
        else fout<<tartalom[0]<<endl;   //a rekordot irja bele legfelulre
        fout<<"["<<datum<<"] --------------> pontszam: "<<kigyo.pontszam<<endl;
        for(int i=1;i<tartalom.size();i++){
            if(i!=tartalom.size()-1) fout<<tartalom[i]<<endl;
            else fout<<tartalom[i];
        }
        fout.close();

        //a amikor vege a jateknak, akkor beleirja hogy + mennyi penzt szereztel
        felhasznalo_adatainak_felulirasa(felhasznalo_nev, jelszo, szint, penz, kigyo_jelenlegi_szine, zold, kek, piros, szurke, lila, sarga, szines, atlatszo, eleresi_ut);

        kigyo.pontszam=0;
        kigyo.elozoX.clear();
        kigyo.elozoY.clear();
        kigyo.beallitas(420, 280, RIGHT, kigyo_jelenlegi_szine);

        egyjatekos_ablak=false;
        glutDisplayFunc(display_menu);
    }
}

void display_ketjatekos_mod(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    palya.palya_kirajzolasa();

    kigyo.kaja_generalas();
    kigyo.jatek_vezerlo(2, penz, game_over, kigyo2.snakeX, kigyo2.snakeY, kigyo2.elozoX, kigyo2.elozoY, kigyo2.pontszam);

    glutKeyboardFunc(betu_jatekos_1);
    kigyo.iranyitas(irany_jatekos1, 0, 0);
    kigyo.kigyo_kirajzolasa();

    glutSpecialFunc(betu_jatekos_2);
    kigyo2.iranyitas(irany_jatekos2, 0, 0);
    kigyo2.kigyo_kirajzolasa();

    //jatekos 1
    //az ablak aljan kiirja a pontszamot es hogy melyik kigyohoz tartozik(kirajzolja a kigyot)
    egy_kigyo_kirajzolasa(GREEN, 205, 555);
    szam_kiirasa_az_ablakra(kigyo.pontszam, "Pontszam: ", GLUT_BITMAP_TIMES_ROMAN_24, 170, 590);
    //jatekos 2
    //az ablak aljan kiirja a pontszamot es hogy melyik kigyohoz tartozik(kirajzolja a kigyot)
    egy_kigyo_kirajzolasa(BLUE, 575, 555);
    szam_kiirasa_az_ablakra(kigyo2.pontszam, "Pontszam: ", GLUT_BITMAP_TIMES_ROMAN_24, 540, 590);

    glutSwapBuffers();

    if(game_over==true){
        kigyo.pontszam=0;
        kigyo.elozoX.clear();
        kigyo.elozoY.clear();
        kigyo.beallitas(440, 260, RIGHT, kigyo_jelenlegi_szine);

        kigyo2.pontszam=0;
        kigyo2.elozoX.clear();
        kigyo2.elozoY.clear();
        kigyo2.beallitas(400, 300, LEFT, kigyo_jelenlegi_szine);

        ketjatekos_ablak=false;
        glutDisplayFunc(display_menu);
    }
}

void timer(int extra){
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timer, 0);
}

void display_menu(){
    game_over=false;

    glutKeyboardFunc(iras);
    glutPassiveMotionFunc(mouse_routine);
    //glutMouseFunc(kattintas);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //gombok
    egyjatekos_gomb.beallitas("1 Jatekos mod", GLUT_BITMAP_HELVETICA_18, true, true, ORANGE, BLACK, 34, 546, 150, 30, 16, 11);
    ketjatekos_gomb.beallitas("2 Jatekos mod", GLUT_BITMAP_HELVETICA_18, true, true, ORANGE, BLACK, 234, 546, 150, 30, 16, 11);
    online_gomb.beallitas("Online", GLUT_BITMAP_HELVETICA_18, true, true, ORANGE, BLACK, 434, 546, 150, 30, 46, 11);
    bolt_gomb.beallitas("Bolt", GLUT_BITMAP_HELVETICA_18, true, true, ORANGE, BLACK, 634, 546, 150, 30, 58, 11);
    ranglista_gomb.beallitas("Elozo pontszamok", GLUT_BITMAP_HELVETICA_18, true, true, WHITE, BLACK, 585, 34, 200, 30, 25, 11);
    sugo_gomb.beallitas("...", GLUT_BITMAP_HELVETICA_18, true, true, WHITE, BLACK, 754, 84, 30, 30, 8, 9);
    kijelentkezes_gomb.beallitas("->", GLUT_BITMAP_HELVETICA_18, true, true, WHITE, BLACK, 754, 134, 30, 30, 6, 10);

    //szint kiirasa
    fajl_tartalmanak_szetszedese(felhasznalo_nev, jelszo, sikeres_belepes, szint, penz, kezdoszin, zold, kek, piros, szurke, lila, sarga, szines, atlatszo, eleresi_ut);
    kiiras("S z i n t : ", GLUT_BITMAP_HELVETICA_18, 34, 52);
    //nagyobbik csilag/korvonal
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2i(145, 55);
    glVertex2i(127, 70);
    glVertex2i(134, 49);
    glVertex2i(115, 35);
    glVertex2i(138, 35);
    glVertex2i(145, 15);
    glVertex2i(152, 35);
    glVertex2i(175, 35);
    glVertex2i(156, 49);
    glVertex2i(163, 70);
    glVertex2i(145, 55);
    glEnd();
    //kisebbik csillag
    glColor3f(0.0, 0.0, 0.5);
    glBegin(GL_POLYGON);
    glVertex2i(145, 52);
    glVertex2i(130, 67);
    glVertex2i(137, 47);
    glVertex2i(121, 37);
    glVertex2i(140, 37);
    glVertex2i(145, 19);
    glVertex2i(150, 37);
    glVertex2i(170, 37);
    glVertex2i(153, 48);
    glVertex2i(159, 64);
    glVertex2i(145, 52);
    glEnd();
    //szam beleirasa a csillagba
    szam_kiirasa_az_ablakra(szint, "", GLUT_BITMAP_HELVETICA_18, 140, 50);

    //nev kiirasa
    char nev[30];   //30 a mx karakter, ha csak 'i' betuket ir be akkor is belefer a 30-ba
    string str_nev="";
    //egyszer at kell masolni stringbe, mert hanem karaktereket fuz meg hozza
    for(int i=0;i<felhasznalo_nev.size();i++){
        str_nev+=felhasznalo_nev[i];
    }
    for(int i=0;i<30;i++){
        nev[i]=str_nev[i];
    }
    kiiras(nev, GLUT_BITMAP_9_BY_15, 34, 82);

    //penz kiirasa
    szam_kiirasa_az_ablakra(penz, "$", GLUT_BITMAP_9_BY_15, 34, 100);

    //kep, felirat
    // S
    glBegin(GL_LINE_STRIP);
    glVertex2i(213, 90);
    glVertex2i(237, 103);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(200, 110);
    glVertex2i(220, 90);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(241, 130);
    glVertex2i(199, 108);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(238, 129);
    glVertex2i(215, 141);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(216, 140);
    glVertex2i(205, 132);
    glEnd();
    // N
    glBegin(GL_LINE_STRIP);
    glVertex2i(244, 143);
    glVertex2i(248, 102);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(244, 97);
    glVertex2i(275, 138);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(272, 141);
    glVertex2i(281, 90);
    glEnd();
    // A
    glBegin(GL_LINE_STRIP);
    glVertex2i(281, 140);
    glVertex2i(290, 90);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(290, 90);
    glVertex2i(310, 142);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(284, 130);
    glVertex2i(308, 132);
    glEnd();
    // K
    glBegin(GL_LINE_STRIP);
    glVertex2i(317, 143);
    glVertex2i(316, 92);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(317, 122);
    glVertex2i(341, 138);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(316, 122);
    glVertex2i(339, 109);
    glEnd();
    // E
    glBegin(GL_LINE_STRIP);
    glVertex2i(350, 140);
    glVertex2i(347, 92);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(350, 140);
    glVertex2i(375, 143);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(349, 115);
    glVertex2i(371, 115);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(347, 92);
    glVertex2i(374, 90);
    glEnd();
    // G
    glBegin(GL_LINE_STRIP);
    glVertex2i(481, 105);
    glVertex2i(458, 92);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(435, 116);
    glVertex2i(460, 90);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(434, 114);
    glVertex2i(462, 142);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(460, 140);
    glVertex2i(479, 124);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(480, 125);
    glVertex2i(462, 120);
    glEnd();
    // A
    glBegin(GL_LINE_STRIP);
    glVertex2i(490, 140);
    glVertex2i(499, 90);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(499, 90);
    glVertex2i(519, 142);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(494, 130);
    glVertex2i(516, 132);
    glEnd();
    // M
    glBegin(GL_LINE_STRIP);
    glVertex2i(527, 144);
    glVertex2i(528, 90);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(525, 92);
    glVertex2i(546, 120);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(541, 118);
    glVertex2i(567, 91);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(564, 91);
    glVertex2i(569, 143);
    glEnd();
    // E
    glBegin(GL_LINE_STRIP);
    glVertex2i(580, 140);
    glVertex2i(577, 92);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(580, 140);
    glVertex2i(605, 143);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(579, 115);
    glVertex2i(601, 115);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(577, 92);
    glVertex2i(605, 90);
    glEnd();
    //palya
    hatterszin_ballitasa(110, 170, 600, 340, 0.0, 0.0, 0.0);
    hatterszin_ballitasa(110, 170, 600, 20, 0.9, 0.9, 0.9);
    hatterszin_ballitasa(690, 170, 20, 340, 0.9, 0.9, 0.9);
    hatterszin_ballitasa(110, 490, 600, 20, 0.9, 0.9, 0.9);
    hatterszin_ballitasa(110, 170, 20, 340, 0.9, 0.9, 0.9);
    //zold kigyo
    hatterszin_ballitasa(290, 230, 20, 20, 0.0, 1.0, 0.0);
    hatterszin_ballitasa(210, 230, 80, 20, 0.0, 0.5, 0.0);
    //piros kigyo
    hatterszin_ballitasa(610, 250, 20, 60, 0.5, 0.0, 0.0);
    hatterszin_ballitasa(530, 310, 100, 20, 0.5, 0.0, 0.0);
    hatterszin_ballitasa(510, 310, 20, 20, 1.0, 0.0, 0.0);
    //lila kigyo
    hatterszin_ballitasa(170, 370, 20, 20, 0.5, 0.0, 0.5);
    hatterszin_ballitasa(170, 390, 60, 20, 0.5, 0.0, 0.5);
    hatterszin_ballitasa(230, 390, 20, 20, 1.0, 0.0, 1.0);
    //kek kigyo
    hatterszin_ballitasa(490, 430, 60, 20, 0.0, 0.0, 0.5);
    hatterszin_ballitasa(470, 430, 20, 20, 0.0, 0.0, 1.0);
    //kaja
    hatterszin_ballitasa(410, 350, 20, 20, 1.0, 1.0, 0.0);



    //ranglista
    if(ranglista_ablak){
        hatterszin_ballitasa(125, 115, 570, 397, 0.4, 0.4, 0.4);
        negyzet_keret_kirajzolasa(125, 115, 570, 397);

        kiiras("E L O Z O    P O N T S Z A M O K", GLUT_BITMAP_HELVETICA_18, 270, 160);

        string f="";
        for(int i=0;i<felhasznalo_nev.size();i++) f+=felhasznalo_nev[i];
        string path=eleresi_ut+"\\"+f+".pontszamok";
        int i=0;
        char tartalom[50];   //50 karakter, belefer 999 pontszam max
        ifstream fin(path.c_str());
        while(i<13){
            fin.getline(tartalom, 50);
            if(i==0)kiiras(tartalom, GLUT_BITMAP_9_BY_15, 255, 445);
            else kiiras(tartalom, GLUT_BITMAP_9_BY_15, 193, 185+(i*20));
            i++;
        }
        fin.close();

        sugo_vissza_gomb.beallitas("Vissza", GLUT_BITMAP_HELVETICA_18, true, true, WHITE, BLACK, 340, 460, 150, 30, 47, 11);
    }

    //sugo ablak
    if(sugo_ablak){   //keret
        hatterszin_ballitasa(125, 115, 570, 397, 0.4, 0.4, 0.4);
        negyzet_keret_kirajzolasa(125, 115, 570, 397);

        kiiras("S U G O", GLUT_BITMAP_HELVETICA_18, 377, 145);
        kiiras("Egyjatekos mod: -> Iranyitas: w a s d", GLUT_BITMAP_9_BY_15, 145, 165);
        kiiras("                -> Gyujtsd ossze a sarga negyzeteket(=10$).", GLUT_BITMAP_9_BY_15, 145, 185);
        kiiras("                -> Ha a falnak vagy a farkaba utkozik a ki-", GLUT_BITMAP_9_BY_15, 145, 205);
        kiiras("                   gyo, akkor vege a jateknak.", GLUT_BITMAP_9_BY_15, 145, 225);
        kiiras("Ketjatekos mod: -> Iranyitas: w a s d / up down left right", GLUT_BITMAP_9_BY_15, 145, 245);
        kiiras("                -> Egyszerre tud jatszani ket ember egy", GLUT_BITMAP_9_BY_15, 145, 265);
        kiiras("                   szamitogepen.", GLUT_BITMAP_9_BY_15, 145, 285);
        kiiras("                -> Aki hamarabb felszedi a sarga negyzetet,", GLUT_BITMAP_9_BY_15, 145, 305);
        kiiras("                   aze a pont.", GLUT_BITMAP_9_BY_15, 145, 325);
        kiiras("                -> Az elozo szabalyok ervenyesek + ha neki-", GLUT_BITMAP_9_BY_15, 145, 345);
        kiiras("                   mesz a masik jatekosnak es a pontszam", GLUT_BITMAP_9_BY_15, 145, 365);
        kiiras("                   nagyobb mint nulla, akkor is vege a jat-", GLUT_BITMAP_9_BY_15, 145, 385);
        kiiras("                   eknak es vesztessz.", GLUT_BITMAP_9_BY_15, 145, 405);
        kiiras("A boltban skineket tudsz vasarolni a kigyonak.", GLUT_BITMAP_9_BY_15, 145, 425);
        kiiras("Ha jobbklikkel kattintassz, akkor gyorsitja a kigyot.", GLUT_BITMAP_9_BY_15, 145, 445);

        sugo_vissza_gomb.beallitas("Vissza", GLUT_BITMAP_HELVETICA_18, true, true, WHITE, BLACK, 340, 460, 150, 30, 47, 11);
    }

    //bolt ablak
    if(bolt_ablak){   //keret
        hatterszin_ballitasa(125, 115, 570, 397, 0.4, 0.4, 0.4);
        negyzet_keret_kirajzolasa(125, 115, 570, 397);

        kiiras("B O L T", GLUT_BITMAP_HELVETICA_18, 380, 145);

        fajl_tartalmanak_szetszedese(felhasznalo_nev, jelszo, sikeres_belepes, szint, penz, kigyo_jelenlegi_szine, zold, kek, piros, szurke, lila, sarga, szines, atlatszo, eleresi_ut);

        //vasarlas
        //ha mar meg van akkor a gombon a "Kivalaszt" felirat jelenjen meg ne a "1000 $"
        egy_kigyo_kirajzolasa(GREEN, 190, 190);
        if(kigyo_jelenlegi_szine==GREEN){
            hatterszin_ballitasa(157, 160, 104, 60, 0.35, 0.35, 0.35);
            negyzet_keret_kirajzolasa(157, 160, 104, 60);
            egy_kigyo_kirajzolasa(GREEN, 190, 190);
        }
        if(zold) megvasarol_zold.beallitas("Kivalaszt", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 159, 230, 100, 20, 10, 7);
        else megvasarol_zold.beallitas("1000 $", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 159, 230, 100, 20, 24, 7);

        egy_kigyo_kirajzolasa(BLUE, 324, 190);
        if(kigyo_jelenlegi_szine==BLUE){
            hatterszin_ballitasa(291, 160, 104, 60, 0.35, 0.35, 0.35);
            negyzet_keret_kirajzolasa(291, 160, 104, 60);
            egy_kigyo_kirajzolasa(BLUE, 324, 190);
        }
        if(kek) megvasarol_kek.beallitas("Kivalaszt", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 293, 230, 100, 20, 10, 7);
        else megvasarol_kek.beallitas("1000 $", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 293, 230, 100, 20, 24, 7);

        egy_kigyo_kirajzolasa(RED, 458, 190);
        if(kigyo_jelenlegi_szine==RED){
            hatterszin_ballitasa(425, 160, 104, 60, 0.35, 0.35, 0.35);
            negyzet_keret_kirajzolasa(425, 160, 104, 60);
            egy_kigyo_kirajzolasa(RED, 458, 190);
        }
        if(piros) megvasarol_piros.beallitas("Kivalaszt", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 427, 230, 100, 20, 10, 7);
        else megvasarol_piros.beallitas("1000 $", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 427, 230, 100, 20, 24, 7);

        egy_kigyo_kirajzolasa(GRAY, 592, 190);
        if(kigyo_jelenlegi_szine==GRAY){
            hatterszin_ballitasa(559, 160, 104, 60, 0.35, 0.35, 0.35);
            negyzet_keret_kirajzolasa(559, 160, 104, 60);
            egy_kigyo_kirajzolasa(GRAY, 592, 190);
        }
        if(szurke) megvasarol_szurke.beallitas("Kivalaszt", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 561, 230, 100, 20, 10, 7);
        else megvasarol_szurke.beallitas("1000 $", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 561, 230, 100, 20, 24, 7);

        egy_kigyo_kirajzolasa(PURPLE, 190, 360);
        if(kigyo_jelenlegi_szine==PURPLE){
            hatterszin_ballitasa(157, 330, 104, 60, 0.35, 0.35, 0.35);
            negyzet_keret_kirajzolasa(157, 330, 104, 60);
            egy_kigyo_kirajzolasa(PURPLE, 190, 360);
        }
        if(lila) megvasarol_lila.beallitas("Kivalaszt", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 159, 400, 100, 20, 10, 7);
        else megvasarol_lila.beallitas("1000 $", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 159, 400, 100, 20, 24, 7);

        egy_kigyo_kirajzolasa(ORANGE, 324, 360);
        if(kigyo_jelenlegi_szine==ORANGE){
            hatterszin_ballitasa(291, 330, 104, 60, 0.35, 0.35, 0.35);
            negyzet_keret_kirajzolasa(291, 330, 104, 60);
            egy_kigyo_kirajzolasa(ORANGE, 324, 360);
        }
        if(sarga) megvasarol_sarga.beallitas("Kivalaszt", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 293, 400, 100, 20, 10, 7);
        else megvasarol_sarga.beallitas("1000 $", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 293, 400, 100, 20, 24, 7);

        //minden masodperc utan valtozzon meg a szine
        time_t masodperc;
        masodperc=time(NULL);
        masodperc=masodperc%6;
        if(masodperc==0) egy_kigyo_kirajzolasa(GREEN, 458, 360);   //zold
        if(masodperc==1) egy_kigyo_kirajzolasa(BLUE, 458, 360);    //kek
        if(masodperc==2) egy_kigyo_kirajzolasa(RED, 458, 360);     //piros
        if(masodperc==3) egy_kigyo_kirajzolasa(GRAY, 458, 360);    //szurke
        if(masodperc==4) egy_kigyo_kirajzolasa(PURPLE, 458, 360);  //lila
        if(masodperc==5) egy_kigyo_kirajzolasa(ORANGE, 458, 360);  //sarga
        if(kigyo_jelenlegi_szine==colorful){
            hatterszin_ballitasa(425, 330, 104, 60, 0.35, 0.35, 0.35);
            negyzet_keret_kirajzolasa(425, 330, 104, 60);
            //minden masodperc utan valtozzon meg a szine
            if(masodperc==0) egy_kigyo_kirajzolasa(GREEN, 458, 360);   //zold
            if(masodperc==1) egy_kigyo_kirajzolasa(BLUE, 458, 360);    //kek
            if(masodperc==2) egy_kigyo_kirajzolasa(RED, 458, 360);     //piros
            if(masodperc==3) egy_kigyo_kirajzolasa(GRAY, 458, 360);    //szurke
            if(masodperc==4) egy_kigyo_kirajzolasa(PURPLE, 458, 360);  //lila
            if(masodperc==5) egy_kigyo_kirajzolasa(ORANGE, 458, 360);  //sarga
        }
        if(szines) megvasarol_szines.beallitas("Kivalaszt", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 427, 400, 100, 20, 10, 7);
        else megvasarol_szines.beallitas("10000 $", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 427, 400, 100, 20, 21, 7);

        negyzet_keret_kirajzolasa(582, 350, 20, 20);
        negyzet_keret_kirajzolasa(602, 350, 40, 20);
        if(kigyo_jelenlegi_szine==transparent){
            hatterszin_ballitasa(559, 330, 104, 60, 0.35, 0.35, 0.35);
            negyzet_keret_kirajzolasa(559, 330, 104, 60);
            negyzet_keret_kirajzolasa(582, 350, 20, 20);
            negyzet_keret_kirajzolasa(602, 350, 40, 20);
        }
        if(atlatszo) megvasarol_atlatszo.beallitas("Kivalaszt", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 561, 400, 100, 20, 10, 7);
        else megvasarol_atlatszo.beallitas("10000 $", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 561, 400, 100, 20, 21, 7);


        sugo_vissza_gomb.beallitas("Vissza", GLUT_BITMAP_HELVETICA_18, true, true, WHITE, BLACK, 340, 460, 150, 30, 47, 11);
    }

    //online ablak
    if(online_ablak){
        hatterszin_ballitasa(125, 115, 570, 397, 0.4, 0.4, 0.4);
        negyzet_keret_kirajzolasa(125, 115, 570, 397);

        kiiras("O N L I N E", GLUT_BITMAP_HELVETICA_18, 362, 160);

        if(online_szoba_ful && !online_kod_ful){
            //hatter
            glColor3f(0.35, 0.35, 0.35);
            glBegin(GL_POLYGON);
            glVertex2i(440, 250);
            glVertex2i(630, 250);
            glVertex2i(630, 440);
            glVertex2i(190, 440);
            glVertex2i(190, 200);
            glVertex2i(380, 200);
            glVertex2i(440, 249);
            glEnd();

            //keret
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINE_STRIP);
            glVertex2i(190, 200);
            glVertex2i(380, 200);
            glVertex2i(440, 250);
            glVertex2i(630, 250);
            glVertex2i(630, 440);
            glVertex2i(190, 440);
            glVertex2i(190, 199);
            glEnd();

            kiiras("A generalt kod :  _ _ _ _ _ _", GLUT_BITMAP_HELVETICA_18, 300, 280);

            kiiras("1. jatekos: nev, csatlakozva/nincs csatlakozva", GLUT_BITMAP_9_BY_15, 200, 320);
            kiiras("2. jatekos: nev, csatlakozva/nincs csatlakozva", GLUT_BITMAP_9_BY_15, 200, 340);
            kiiras("3. jatekos: nev, csatlakozva/nincs csatlakozva", GLUT_BITMAP_9_BY_15, 200, 360);
            kiiras("4. jatekos: nev, csatlakozva/nincs csatlakozva", GLUT_BITMAP_9_BY_15, 200, 380);

            online_letrehozas.beallitas("Letrehozas", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 505, 400, 110, 25, 10, 9);
        }
        if(!online_szoba_ful && online_kod_ful){
            //hatter
            glColor3f(0.35, 0.35, 0.35);
            glBegin(GL_POLYGON);
            glVertex2i(380, 250);
            glVertex2i(440, 200);
            glVertex2i(630, 200);
            glVertex2i(630, 440);
            glVertex2i(190, 440);
            glVertex2i(190, 250);
            glVertex2i(380, 249);
            glEnd();

            //keret
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINE_STRIP);
            glVertex2i(190, 250);
            glVertex2i(380, 250);
            glVertex2i(440, 200);
            glVertex2i(630, 200);
            glVertex2i(630, 440);
            glVertex2i(190, 440);
            glVertex2i(190, 249);
            glEnd();

            kiiras("KOD", GLUT_BITMAP_HELVETICA_18, 340, 340);
            hatterszin_ballitasa(390, 319, 80, 30, 0.4, 0.4, 0.4);
            negyzet_keret_kirajzolasa(390, 319, 80, 30);

            online_belepes.beallitas("Csatlakozas", GLUT_BITMAP_9_BY_15, true, true, ORANGE, BLACK, 505, 400, 110, 25, 7, 9);
        }

        online_szoba_letrehozasa.beallitas("Szoba letrehozasa", GLUT_BITMAP_HELVETICA_18, true, true, ORANGE, BLACK, 200, 210, 170, 30, 8, 11);
        online_kod_beirasa.beallitas("Kod beirasa", GLUT_BITMAP_HELVETICA_18, true, true, ORANGE, BLACK, 450, 210, 170, 30, 38, 11);

        sugo_vissza_gomb.beallitas("Vissza", GLUT_BITMAP_HELVETICA_18, true, true, WHITE, BLACK, 340, 460, 150, 30, 47, 11);
    }

    //csillag felirat
    if(csillag_felirat){
        glColor3f(0.5, 0.5, 0.5);
        glBegin(GL_QUADS);
        glVertex2i(cursor_x-130, cursor_y+16);
        glVertex2i(cursor_x, cursor_y+16);
        glVertex2i(cursor_x, cursor_y+62);
        glVertex2i(cursor_x-130, cursor_y+62);
        glVertex2i(cursor_x-130, cursor_y+16);
        glEnd();
        kiiras("Egy palya teljesitese", GLUT_BITMAP_HELVETICA_12, cursor_x-126, cursor_y+30);
        kiiras("utan lepsz szintet.", GLUT_BITMAP_HELVETICA_12, cursor_x-126, cursor_y+44);
        kiiras("H A M A R O S A N !", GLUT_BITMAP_HELVETICA_12, cursor_x-126, cursor_y+58);
    }

    //sugo felirat
    if(sugo_felirat){
        glColor3f(0.5, 0.5, 0.5);
        glBegin(GL_QUADS);
        glVertex2i(cursor_x-37, cursor_y+16);
        glVertex2i(cursor_x, cursor_y+16);
        glVertex2i(cursor_x, cursor_y+36);
        glVertex2i(cursor_x-37, cursor_y+36);
        glVertex2i(cursor_x-37, cursor_y+16);
        glEnd();
        kiiras("Sugo", GLUT_BITMAP_HELVETICA_12, cursor_x-33, cursor_y+30);
    }

    //kijelentkezes felirat
    if(kijelentkezes_felirat){
        glColor3f(0.5, 0.5, 0.5);
        glBegin(GL_QUADS);
        glVertex2i(cursor_x-83, cursor_y+16);
        glVertex2i(cursor_x, cursor_y+16);
        glVertex2i(cursor_x, cursor_y+36);
        glVertex2i(cursor_x-83, cursor_y+36);
        glVertex2i(cursor_x-83, cursor_y+5);
        glEnd();
        kiiras("Kijelentkezes", GLUT_BITMAP_HELVETICA_12, cursor_x-78, cursor_y+30);
    }

    glutSwapBuffers();
}

void display_belepes(){
    glutPassiveMotionFunc(mouse_routine);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //bejelentkezes
    if(belepes_ful && !regisztracio_ful){
        //hatterszin
        hatterszin_ballitasa(240, 160, 170, 50, 0.4, 0.4, 0.4);
        hatterszin_ballitasa(240, 210, 340, 190, 0.4, 0.4, 0.4);

        //keret
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_STRIP);
        glVertex2i(240, 160);
        glVertex2i(410, 160);
        glVertex2i(410, 210);
        glVertex2i(580, 210);
        glVertex2i(580, 400);
        glVertex2i(240, 400);
        glVertex2i(240, 159);
        glEnd();

        kiiras("Felhasznalo nev", GLUT_BITMAP_HELVETICA_18, 250, 270);
        hatterszin_ballitasa(390, 250, 180, 30, 0.35, 0.35, 0.35);
        negyzet_keret_kirajzolasa(390, 250, 180, 30);
        kiiras("Jelszo", GLUT_BITMAP_HELVETICA_18, 250, 310);
        hatterszin_ballitasa(312, 290, 218, 30, 0.35, 0.35, 0.35);
        negyzet_keret_kirajzolasa(312, 290, 218, 30);

        int befele_f_nev=395;
        for(int i=0;i<felhasznalo_nev.size();i++){
            ostringstream oss;
            oss<<(i+1)<<felhasznalo_nev[i];
            glRasterPos2i(befele_f_nev, 270);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, felhasznalo_nev[i]);
            befele_f_nev+=karakter_hossza(felhasznalo_nev[i]);
        }

        if(jelszo_megjelenitese){
            int befele_j=317;
            for(int i=0;i<jelszo.size();i++){
                ostringstream oss;
                oss<<(i+1)<<jelszo[i];
                glRasterPos2i(befele_j, 310);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, jelszo[i]);
                befele_j+=karakter_hossza(jelszo[i]);
            }
        }
        else{
            int befele_j=317;
            for(int i=0;i<jelszo.size();i++){
                glRasterPos2i(befele_j, 315);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '*');
                befele_j+=10;
            }
        }

        jelszo_megjelenitese_b.beallitas("", GLUT_BITMAP_HELVETICA_18, true, true, ORANGE, BLACK, 541, 292, 25, 25, 0, 0);
        belepes_gomb.beallitas("Belepes", GLUT_BITMAP_HELVETICA_18, true, true, WHITE, BLACK, 335, 350, 150, 30, 42, 11);

        //jelszo megjelenitese felirat
        if(jelszo_megjelenitese_b_felirat){
            glColor3f(0.5, 0.5, 0.5);
            glBegin(GL_QUADS);
            glVertex2i(cursor_x-125, cursor_y+16);
            glVertex2i(cursor_x, cursor_y+16);
            glVertex2i(cursor_x, cursor_y+36);
            glVertex2i(cursor_x-125, cursor_y+36);
            glVertex2i(cursor_x-125, cursor_y+16);
            glEnd();
            kiiras("Jelszo megjelenitese", GLUT_BITMAP_HELVETICA_12, cursor_x-120, cursor_y+30);
        }
    }

    //regisztracio
    if(!belepes_ful && regisztracio_ful){
        //hatterszin
        hatterszin_ballitasa(410, 160, 170, 50, 0.4, 0.4, 0.4);
        hatterszin_ballitasa(240, 210, 340, 190, 0.4, 0.4, 0.4);

        //keret
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_STRIP);
        glVertex2i(410, 160);
        glVertex2i(580, 160);
        glVertex2i(580, 400);
        glVertex2i(240, 400);
        glVertex2i(240, 210);
        glVertex2i(410, 210);
        glVertex2i(410, 159);
        glEnd();

        kiiras("Felhasznalo nev", GLUT_BITMAP_HELVETICA_18, 250, 250);
        hatterszin_ballitasa(390, 230, 180, 30, 0.35, 0.35, 0.35);
        negyzet_keret_kirajzolasa(390, 230, 180, 30);
        kiiras("Jelszo", GLUT_BITMAP_HELVETICA_18, 250, 290);
        hatterszin_ballitasa(312, 270, 218, 30, 0.35, 0.35, 0.35);
        negyzet_keret_kirajzolasa(312, 270, 218, 30);
        kiiras("Jelszo ujra", GLUT_BITMAP_HELVETICA_18, 250, 330);
        hatterszin_ballitasa(345, 310, 225, 30, 0.35, 0.35, 0.35);
        negyzet_keret_kirajzolasa(345, 310, 225, 30);

        int befele_f_nev=395;
        for(int i=0;i<felhasznalo_nev.size();i++){
            ostringstream oss;
            oss<<(i+1)<<felhasznalo_nev[i];
            glRasterPos2i(befele_f_nev, 250);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, felhasznalo_nev[i]);
            befele_f_nev+=karakter_hossza(felhasznalo_nev[i]);
        }

        if(jelszo_megjelenitese){
            int befele_j=317;
            for(int i=0;i<jelszo.size();i++){
                ostringstream oss;
                oss<<(i+1)<<jelszo[i];
                glRasterPos2i(befele_j, 290);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, jelszo[i]);
                befele_j+=karakter_hossza(jelszo[i]);
            }
            int befele_j_u=350;
            for(int i=0;i<jelszo_ujra.size();i++){
                ostringstream oss;
                oss<<(i+1)<<jelszo_ujra[i];
                glRasterPos2i(befele_j_u, 330);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, jelszo_ujra[i]);
                befele_j_u+=karakter_hossza(jelszo_ujra[i]);
            }
        }
        else{
            int befele_j=317;
            for(int i=0;i<jelszo.size();i++){
                glRasterPos2i(befele_j, 295);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '*');
                befele_j+=10;
            }
            int befele_j_u=350;
            for(int i=0;i<jelszo_ujra.size();i++){
                glRasterPos2i(befele_j_u, 335);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '*');
                befele_j_u+=10;
            }
        }

        jelszo_megjelenitese_r.beallitas("", GLUT_BITMAP_HELVETICA_18, true, true, ORANGE, BLACK, 542, 272, 25, 25, 0, 0);
        regisztracio_gomb.beallitas("Regisztracio", GLUT_BITMAP_HELVETICA_18, true, true, WHITE, BLACK, 335, 350, 150, 30, 25, 11);

        //jelszo megjelenitese felirat
        if(jelszo_megjelenitese_r_felirat){
            glColor3f(0.5, 0.5, 0.5);
            glBegin(GL_QUADS);
            glVertex2i(cursor_x-125, cursor_y+16);
            glVertex2i(cursor_x, cursor_y+16);
            glVertex2i(cursor_x, cursor_y+36);
            glVertex2i(cursor_x-125, cursor_y+36);
            glVertex2i(cursor_x-125, cursor_y+16);
            glEnd();
            kiiras("Jelszo megjelenitese", GLUT_BITMAP_HELVETICA_12, cursor_x-120, cursor_y+30);
        }
    }

    belepes_ful_gomb.beallitas("Bejelentkezes", GLUT_BITMAP_HELVETICA_18, true, true, WHITE, BLACK, 250, 170, 150, 30, 21, 11);
    regisztracio_ful_gomb.beallitas("Regisztracio", GLUT_BITMAP_HELVETICA_18, true, true, WHITE, BLACK, 420, 170, 150, 30, 25, 11);

    glutSwapBuffers();
}

void kattintas(int button, int state, int x, int y){
    //belepes ful
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
       x>=belepes_ful_gomb.pozicioX1 && x<=belepes_ful_gomb.pozicioX2 &&
       y>=belepes_ful_gomb.pozicioY1 && y<=belepes_ful_gomb.pozicioY2 &&
       bejelentkezes_ablak && !menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak){
        belepes_ful=true;
        regisztracio_ful=false;
        felhasznalo_nev_beirasa=false;
        jelszo_beirasa=false;
        jelszo_megjelenitese=false;
        felhasznalo_nev.clear();
        jelszo.clear();
        jelszo_ujra.clear();
        szoveg_hossza_b_f_nev=0;
        szoveg_hossza_b_j=0;
        szoveg_hossza_r_f_nev=0;
        szoveg_hossza_r_j=0;
        szoveg_hossza_r_j_u=0;
    }
    //felhasznalonev beirasa
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
       x>=390 && x<=570 && y>=250 && y<=280 &&
       bejelentkezes_ablak && !menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak){
        felhasznalo_nev_beirasa=true;
        jelszo_beirasa=false;
    }
    //jelszo beirasa
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
       x>=312 && x<=530 && y>=290 && y<=320 &&
       bejelentkezes_ablak && !menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak){
        felhasznalo_nev_beirasa=false;
        jelszo_beirasa=true;
    }
    //jelszo megjelenitese
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
       x>=jelszo_megjelenitese_b.pozicioX1 && x<=jelszo_megjelenitese_b.pozicioX2 &&
       y>=jelszo_megjelenitese_b.pozicioY1 && y<=jelszo_megjelenitese_b.pozicioY2 &&
       bejelentkezes_ablak && !menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak){
        if(belepes_ful) jelszo_megjelenitese=!jelszo_megjelenitese;
    }
    //belepes
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=belepes_gomb.pozicioX1 && x<=belepes_gomb.pozicioX2 &&
        y>=belepes_gomb.pozicioY1 && y<=belepes_gomb.pozicioY2 &&
        bejelentkezes_ablak && !menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak){

        //ellenorzi hogy a beirt felhasznalonevhez a megadott jelszo helyes-e
        fajl_tartalmanak_szetszedese(felhasznalo_nev, jelszo, sikeres_belepes, szint, penz, kezdoszin, zold, kek, piros, szurke, lila, sarga, szines, atlatszo, eleresi_ut);

        if(belepes_ful && !regisztracio_ful){
            if(felhasznalo_nev.size()==0 && jelszo.size()>0) MessageBox(NULL, "Nem adtal meg felhasznalonevet.", "Hiba", 0);
            else if(jelszo.size()==0 && felhasznalo_nev.size()>0) MessageBox(NULL, "Nem adtal meg jelszot.", "Hiba", 0);
            else if(felhasznalo_nev.size()==0 && jelszo.size()==0) MessageBox(NULL, "Nem toltotted ki a mezoket.", "Hiba", 0);
            else if(sikeres_belepes){
                menu_ablak=true;
                bejelentkezes_ablak=false;
                glutDisplayFunc(display_menu);
            }
            else{
                MessageBox(NULL, "Helytelen jelszo vagy felhasznalonev.", "Hiba", 0);
                felhasznalo_nev.clear();
                jelszo.clear();
            }
        }
        felhasznalo_nev_beirasa=false;
        jelszo_beirasa=false;
        szoveg_hossza_b_f_nev=0;
        szoveg_hossza_b_j=0;
        szoveg_hossza_r_f_nev=0;
        szoveg_hossza_r_j=0;
        szoveg_hossza_r_j_u=0;
    }

    //regisztracio ful
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=regisztracio_ful_gomb.pozicioX1 && x<=regisztracio_ful_gomb.pozicioX2 &&
        y>=regisztracio_ful_gomb.pozicioY1 && y<=regisztracio_ful_gomb.pozicioY2 &&
        bejelentkezes_ablak && !menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak){
        belepes_ful=false;
        regisztracio_ful=true;
        felhasznalo_nev_beirasa=false;
        jelszo_beirasa=false;
        jelszo_megjelenitese=false;
        felhasznalo_nev.clear();
        jelszo.clear();
        jelszo_ujra.clear();
        szoveg_hossza_b_f_nev=0;
        szoveg_hossza_b_j=0;
        szoveg_hossza_r_f_nev=0;
        szoveg_hossza_r_j=0;
        szoveg_hossza_r_j_u=0;
    }
    //felhasznalonev beirasa
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=390 && x<=570 && y>=230 && y<=260 &&
        bejelentkezes_ablak && !menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak){
        reg_felhasznalo_nev_beirasa=true;
        reg_jelszo_beirasa=false;
        reg_jelszo_ujra_beirasa=false;
    }
    //jelszo beirasa
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=312 && x<=530 && y>=270 && y<=300 &&
        bejelentkezes_ablak && !menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak){
        reg_felhasznalo_nev_beirasa=false;
        reg_jelszo_beirasa=true;
        reg_jelszo_ujra_beirasa=false;
    }
    //jelszo ujra beirasa
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=345 && x<=570 && y>=310 && y<=340 &&
        bejelentkezes_ablak && !menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak){
        reg_felhasznalo_nev_beirasa=false;
        reg_jelszo_beirasa=false;
        reg_jelszo_ujra_beirasa=true;
    }
    //jelszo megjelenitese
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
       x>=jelszo_megjelenitese_r.pozicioX1 && x<=jelszo_megjelenitese_r.pozicioX2 &&
       y>=jelszo_megjelenitese_r.pozicioY1 && y<=jelszo_megjelenitese_r.pozicioY2 &&
       bejelentkezes_ablak && !menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak){
        if(regisztracio_ful) jelszo_megjelenitese=!jelszo_megjelenitese;
    }

    //regisztracio
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=regisztracio_gomb.pozicioX1 && x<=regisztracio_gomb.pozicioX2 &&
        y>=regisztracio_gomb.pozicioY1 && y<=regisztracio_gomb.pozicioY2 &&
        bejelentkezes_ablak && !menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak){
        if(!belepes_ful && regisztracio_ful){
            bool a_ket_jelszo_talal=false;
            if(jelszo.size()==jelszo_ujra.size()){   //ellenorzi hogy a ket jelszo egyezik-e
                int ellenorzo=0;
                for(int i=0;i<jelszo.size();i++){
                    if(jelszo[i]==jelszo_ujra[i]) ellenorzo++;
                }
                if(ellenorzo==jelszo.size()) a_ket_jelszo_talal=true;
            }
            //ellenorzi, hogy van-e ilyen nevu felhasznalo
            if(felhasznalo_nev.size()>0 && jelszo.size()> 0 && jelszo_ujra.size()>0 && a_ket_jelszo_talal &&
               !regisztralasnal_ellenorzi_hogy_vane_mar_ilyen_nevu_felhasznalo(felhasznalo_nev, eleresi_ut)) sikeres_regisztralas=true;

            if(sikeres_regisztralas){
                MessageBox(NULL, "Sikeres regisztracio!", "Ertesites", 0);

                regisztralt_mentese_fajlba(felhasznalo_nev, jelszo, eleresi_ut);

                felhasznalo_nev.clear();
                jelszo.clear();
                jelszo_ujra.clear();
                belepes_ful=true;
                regisztracio_ful=false;
            }
            else{
                if(felhasznalo_nev.size()==0 && jelszo.size()>0 && jelszo_ujra.size()>0) MessageBox(NULL, "Nem adtal meg felhasznalonevet!", "Hiba", 0);
                if(felhasznalo_nev.size()>0 && jelszo.size()==0 && jelszo_ujra.size()>0) MessageBox(NULL, "Nem adtal meg jelszot!", "Hiba", 0);
                if(felhasznalo_nev.size()>0 && jelszo.size()>0 && jelszo_ujra.size()==0) MessageBox(NULL, "Nem adtad meg ujra a jelszot!", "Hiba", 0);
                if(!a_ket_jelszo_talal) MessageBox(NULL, "A ket jelszo nem egyezik!", "Hiba", 0);
                if(regisztralasnal_ellenorzi_hogy_vane_mar_ilyen_nevu_felhasznalo(felhasznalo_nev, eleresi_ut)) MessageBox(NULL, "Mar van ilyen nevu felhasznalo!", "Hiba", 0);
                felhasznalo_nev.clear();
                jelszo.clear();
                jelszo_ujra.clear();
            }
        }
        reg_felhasznalo_nev_beirasa=false;
        reg_jelszo_beirasa=false;
        reg_jelszo_ujra_beirasa=false;
        szoveg_hossza_b_f_nev=0;
        szoveg_hossza_b_j=0;
        szoveg_hossza_r_f_nev=0;
        szoveg_hossza_r_j=0;
        szoveg_hossza_r_j_u=0;
    }

    //egyjatekos mod
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
       x>=egyjatekos_gomb.pozicioX1 && x<=egyjatekos_gomb.pozicioX2 &&
       y>=egyjatekos_gomb.pozicioY1 && y<=egyjatekos_gomb.pozicioY2 &&
       menu_ablak && !bejelentkezes_ablak &&
       !ranglista_ablak && !sugo_ablak && !bolt_ablak && !online_ablak && !ketjatekos_ablak && !egyjatekos_ablak){
        egyjatekos_ablak=true;
        kigyo.beallitas(420, 280, RIGHT, kigyo_jelenlegi_szine);
        glutPassiveMotionFunc(!mouse_routine);
        glutDisplayFunc(display_egyjatekos_mod);
        //glutKeyboardFunc(iranyitas_egyjatekos_mod);
        //glutSpecialFunc(iranyitas_ketjatekos_mod);

        //azet nem itt kell a time fuggveny hanem a mainbe mert
        //ha itt van akkor minen kor utan gyorsul fel a kigyo
        //glutTimerFunc(0, timer, 0);
    }

    //ketjatekos mod
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
       x>=ketjatekos_gomb.pozicioX1 && x<=ketjatekos_gomb.pozicioX2 &&
       y>=ketjatekos_gomb.pozicioY1 && y<=ketjatekos_gomb.pozicioY2 &&
       menu_ablak && !bejelentkezes_ablak &&
       !ranglista_ablak && !sugo_ablak && !bolt_ablak && !online_ablak && !egyjatekos_ablak && !ketjatekos_ablak){
        ketjatekos_ablak=true;
        kigyo.beallitas(440, 260, RIGHT, GREEN);
        kigyo2.beallitas(400, 300, LEFT, BLUE);
        glutPassiveMotionFunc(!mouse_routine);
        glutDisplayFunc(display_ketjatekos_mod);
        //glutKeyboardFunc(iranyitas_egyjatekos_mod);
        //glutSpecialFunc(iranyitas_ketjatekos_mod);

        //azet nem itt kell a time fuggveny hanem a mainbe mert
        //ha itt van akkor minen kor utan gyorsul fel a kigyo
        //glutTimerFunc(0, timer, 0);
    }

    //online
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=online_gomb.pozicioX1 && x<=online_gomb.pozicioX2 &&
        y>=online_gomb.pozicioY1 && y<=online_gomb.pozicioY2 &&
        menu_ablak && !bejelentkezes_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        !ranglista_ablak && !sugo_ablak && !bolt_ablak){
        online_ablak=true;

    }
    //szoba letrehozasa ful
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=online_szoba_letrehozasa.pozicioX1 && x<=online_szoba_letrehozasa.pozicioX2 &&
        y>=online_szoba_letrehozasa.pozicioY1 && y<=online_szoba_letrehozasa.pozicioY2 &&
        menu_ablak && !bejelentkezes_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        online_ablak && !ranglista_ablak && !sugo_ablak && !bolt_ablak){
        online_szoba_ful=true;
        online_kod_ful=false;
    }
    //letrehozas gomb
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=online_letrehozas.pozicioX1 && x<=online_letrehozas.pozicioX2 &&
        y>=online_letrehozas.pozicioY1 && y<=online_letrehozas.pozicioY2 &&
        menu_ablak && !bejelentkezes_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        !bolt_ablak && !sugo_ablak && !ranglista_ablak && online_ablak &&
        online_szoba_ful && !online_kod_ful){
        MessageBox(NULL, "H A M A R O S A N !", "Ertesites", 0);
    }
    //kod beirasa ful
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=online_kod_beirasa.pozicioX1 && x<=online_kod_beirasa.pozicioX2 &&
        y>=online_kod_beirasa.pozicioY1 && y<=online_kod_beirasa.pozicioY2 &&
        menu_ablak && !bejelentkezes_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        online_ablak && !ranglista_ablak && !sugo_ablak && !bolt_ablak){
        online_szoba_ful=false;
        online_kod_ful=true;
    }
    //csatlakozas gomb
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=online_belepes.pozicioX1 && x<=online_belepes.pozicioX2 &&
        y>=online_belepes.pozicioY1 && y<=online_belepes.pozicioY2 &&
        menu_ablak && !bejelentkezes_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        !bolt_ablak && !sugo_ablak && !ranglista_ablak && online_ablak&&
        !online_szoba_ful && online_kod_ful){
        MessageBox(NULL, "H A M A R O S A N !", "Ertesites", 0);
    }

    //bolt
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=bolt_gomb.pozicioX1 && x<=bolt_gomb.pozicioX2 &&
        y>=bolt_gomb.pozicioY1 && y<=bolt_gomb.pozicioY2 &&
        !bejelentkezes_ablak && menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        !ranglista_ablak && !sugo_ablak && !online_ablak){
        bolt_ablak=true;
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=megvasarol_zold.pozicioX1 && x<=megvasarol_zold.pozicioX2 &&
        y>=megvasarol_zold.pozicioY1 && y<=megvasarol_zold.pozicioY2 &&
        !bejelentkezes_ablak && menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        bolt_ablak && !ranglista_ablak && !sugo_ablak && !online_ablak){
        if(!zold && penz>=1000){   //ha nincs meg akkor megvasarolja
            zold=true;
            penz-=1000;
        }
        if(!zold && penz<1000) MessageBox(NULL, "Nincs eleg penzed!", "Hiba", 0);
        if(zold) kigyo_jelenlegi_szine=GREEN;
        felhasznalo_adatainak_felulirasa(felhasznalo_nev, jelszo, szint, penz, kigyo_jelenlegi_szine, zold, kek, piros, szurke, lila, sarga, szines, atlatszo, eleresi_ut);
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=megvasarol_kek.pozicioX1 && x<=megvasarol_kek.pozicioX2 &&
        y>=megvasarol_kek.pozicioY1 && y<=megvasarol_kek.pozicioY2 &&
        !bejelentkezes_ablak && menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        bolt_ablak && !ranglista_ablak && !sugo_ablak && !online_ablak){
        if(!kek && penz>=1000){   //ha nincs meg akkor megvasarolja
            kek=true;
            penz-=1000;
        }
        if(!kek && penz<1000) MessageBox(NULL, "Nincs eleg penzed!", "Hiba", 0);
        if(kek) kigyo_jelenlegi_szine=BLUE;
        felhasznalo_adatainak_felulirasa(felhasznalo_nev, jelszo, szint, penz, kigyo_jelenlegi_szine, zold, kek, piros, szurke, lila, sarga, szines, atlatszo, eleresi_ut);
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=megvasarol_piros.pozicioX1 && x<=megvasarol_piros.pozicioX2 &&
        y>=megvasarol_piros.pozicioY1 && y<=megvasarol_piros.pozicioY2 &&
        !bejelentkezes_ablak && menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        bolt_ablak && !ranglista_ablak && !sugo_ablak && !online_ablak){
        if(!piros && penz>=1000){   //ha nincs meg akkor megvasarolja
            piros=true;
            penz-=1000;
        }
        if(!piros && penz<1000) MessageBox(NULL, "Nincs eleg penzed!", "Hiba", 0);
        if(piros) kigyo_jelenlegi_szine=RED;
        felhasznalo_adatainak_felulirasa(felhasznalo_nev, jelszo, szint, penz, kigyo_jelenlegi_szine, zold, kek, piros, szurke, lila, sarga, szines, atlatszo, eleresi_ut);
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=megvasarol_szurke.pozicioX1 && x<=megvasarol_szurke.pozicioX2 &&
        y>=megvasarol_szurke.pozicioY1 && y<=megvasarol_szurke.pozicioY2 &&
        !bejelentkezes_ablak && menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        bolt_ablak && !ranglista_ablak && !sugo_ablak && !online_ablak){
        if(!szurke && penz>=1000){   //ha nincs meg akkor megvasarolja
            szurke=true;
            penz-=1000;
        }
        if(!szurke && penz<1000) MessageBox(NULL, "Nincs eleg penzed!", "Hiba", 0);
        if(szurke) kigyo_jelenlegi_szine=GRAY;
        felhasznalo_adatainak_felulirasa(felhasznalo_nev, jelszo, szint, penz, kigyo_jelenlegi_szine, zold, kek, piros, szurke, lila, sarga, szines, atlatszo, eleresi_ut);
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=megvasarol_lila.pozicioX1 && x<=megvasarol_lila.pozicioX2 &&
        y>=megvasarol_lila.pozicioY1 && y<=megvasarol_lila.pozicioY2 &&
        !bejelentkezes_ablak && menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        bolt_ablak && !ranglista_ablak && !sugo_ablak && !online_ablak){
        if(!lila && penz>=1000){   //ha nincs meg akkor megvasarolja
            lila=true;
            penz-=1000;
        }
        if(!lila && penz<1000) MessageBox(NULL, "Nincs eleg penzed!", "Hiba", 0);
        if(lila) kigyo_jelenlegi_szine=PURPLE;
        felhasznalo_adatainak_felulirasa(felhasznalo_nev, jelszo, szint, penz, kigyo_jelenlegi_szine, zold, kek, piros, szurke, lila, sarga, szines, atlatszo, eleresi_ut);
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=megvasarol_sarga.pozicioX1 && x<=megvasarol_sarga.pozicioX2 &&
        y>=megvasarol_sarga.pozicioY1 && y<=megvasarol_sarga.pozicioY2 &&
        !bejelentkezes_ablak && menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        bolt_ablak && !ranglista_ablak && !sugo_ablak && !online_ablak){
        if(!sarga && penz>=1000){   //ha nincs meg akkor megvasarolja
            sarga=true;
            penz-=1000;
        }
        if(!sarga && penz<1000) MessageBox(NULL, "Nincs eleg penzed!", "Hiba", 0);
        if(sarga) kigyo_jelenlegi_szine=ORANGE;
        felhasznalo_adatainak_felulirasa(felhasznalo_nev, jelszo, szint, penz, kigyo_jelenlegi_szine, zold, kek, piros, szurke, lila, sarga, szines, atlatszo, eleresi_ut);
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=megvasarol_szines.pozicioX1 && x<=megvasarol_szines.pozicioX2 &&
        y>=megvasarol_szines.pozicioY1 && y<=megvasarol_szines.pozicioY2 &&
        !bejelentkezes_ablak && menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        bolt_ablak && !ranglista_ablak && !sugo_ablak && !online_ablak){
        if(!szines && penz>=10000){   //ha nincs meg akkor megvasarolja
            szines=true;
            penz-=10000;
        }
        if(!szines && penz<10000) MessageBox(NULL, "Nincs eleg penzed!", "Hiba", 0);
        if(szines) kigyo_jelenlegi_szine=colorful;
        felhasznalo_adatainak_felulirasa(felhasznalo_nev, jelszo, szint, penz, kigyo_jelenlegi_szine, zold, kek, piros, szurke, lila, sarga, szines, atlatszo, eleresi_ut);
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=megvasarol_atlatszo.pozicioX1 && x<=megvasarol_atlatszo.pozicioX2 &&
        y>=megvasarol_atlatszo.pozicioY1 && y<=megvasarol_atlatszo.pozicioY2 &&
        !bejelentkezes_ablak && menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        bolt_ablak && !ranglista_ablak && !sugo_ablak && !online_ablak){
        if(!atlatszo && penz>=10000){   //ha nincs meg akkor megvasarolja
            atlatszo=true;
            penz-=10000;
        }
        if(!atlatszo && penz<10000) MessageBox(NULL, "Nincs eleg penzed!", "Hiba", 0);
        if(atlatszo) kigyo_jelenlegi_szine=transparent;
        felhasznalo_adatainak_felulirasa(felhasznalo_nev, jelszo, szint, penz, kigyo_jelenlegi_szine, zold, kek, piros, szurke, lila, sarga, szines, atlatszo, eleresi_ut);
    }

    //ranglista
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=ranglista_gomb.pozicioX1 && x<=ranglista_gomb.pozicioX2 &&
        y>=ranglista_gomb.pozicioY1 && y<=ranglista_gomb.pozicioY2 &&
        !bejelentkezes_ablak && menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        !sugo_ablak && !bolt_ablak && !online_ablak){
        ranglista_ablak=true;
    }

    //sugo
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=sugo_gomb.pozicioX1 && x<=sugo_gomb.pozicioX2 &&
        y>=sugo_gomb.pozicioY1 && y<=sugo_gomb.pozicioY2 &&
        !bejelentkezes_ablak && menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        !ranglista_ablak && !bolt_ablak && !online_ablak){
        sugo_ablak=true;
    }

    //sugo, bolt , online es ranglista bezaras
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=sugo_vissza_gomb.pozicioX1 && x<=sugo_vissza_gomb.pozicioX2 &&
        y>=sugo_vissza_gomb.pozicioY1 && y<=sugo_vissza_gomb.pozicioY2 &&
        !bejelentkezes_ablak && menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak){
        sugo_ablak=false;
        bolt_ablak=false;
        ranglista_ablak=false;
        online_ablak=false;
        online_szoba_ful=true;
        online_kod_ful=false;
    }

    //kijelentkezes
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
        x>=kijelentkezes_gomb.pozicioX1 && x<=kijelentkezes_gomb.pozicioX2 &&
        y>=kijelentkezes_gomb.pozicioY1 && y<=kijelentkezes_gomb.pozicioY2 &&
        !bejelentkezes_ablak && menu_ablak && !egyjatekos_ablak && !ketjatekos_ablak &&
        !ranglista_ablak && !sugo_ablak && !bolt_ablak && !online_ablak){
        felhasznalo_nev.clear();
        jelszo.clear();
        jelszo_megjelenitese=false;
        sikeres_belepes=false;
        szoveg_hossza_b_f_nev=0;
        szoveg_hossza_b_j=0;
        szoveg_hossza_r_f_nev=0;
        szoveg_hossza_r_j=0;
        szoveg_hossza_r_j_u=0;
        kigyo_jelenlegi_szine=kezdoszin;
        bejelentkezes_ablak=true;
        menu_ablak=false;
        egyjatekos_ablak=false;
        ketjatekos_ablak=false;
        glutDisplayFunc(display_belepes);
    }
}

int main(int argc, char* argv[])
{
    //eleresi ut bekerese
    cout<<"Ird be az alkalmazas eleresi utjat(helyesen add meg)!"<<endl;
    cout<<"Egy pelda: C:\\Users\\..\\projekt mappa neve(pl.: ATESTAT)"<<endl;
    do{
        cin>>eleresi_ut;
        if(eleresi_ut.size()==0) cout<<"Nem adtal meg eleresi utat!"<<endl;
    }while(eleresi_ut.size()==0);

    //zarja be a consolet
    HWND handleWindow;
    AllocConsole();
    handleWindow=FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(handleWindow, 0);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(ABLAK_HOSSZUSAG, ABLAK_SZELLESSEG);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-810)/2, (glutGet(GLUT_SCREEN_HEIGHT)-650)/2);
    glutCreateWindow("Snake Game");
    init();
    glutDisplayFunc(display_belepes);
    glutKeyboardFunc(iras);
    glutMouseFunc(kattintas);
    glutTimerFunc(0, timer, 0);
    glutReshapeFunc(resize);
    glutMainLoop();

    return 0;
}
