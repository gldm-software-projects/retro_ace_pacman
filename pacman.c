/*
 *      PACMAN for Jupiter Ace
 *
 *      coded by Gian Luca De Michelis
 *
 */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <input.h>
//#include <games.h>
#include <sys/ioctl.h>
#include <sound.h>

/* Key definitions, change these to define your keys! */
#define K_UP 'Q'
#define K_DOWN 'A'
#define K_LEFT 'O'
#define K_RIGHT 'P'


// caratteri che rappresentano i muri
#define h_all  141
#define v_all  142
#define a_s_h  143
#define a_s_l  144
#define a_d_h  145
#define a_d_l  146
#define p_upp  147
#define p_dwn  148
#define p_sxx  149
#define p_dxx  150
#define t_upp  151
#define t_dwn  152
#define t_dxx  153
#define t_sxx  154
// caratteri che rappresentano pacman
#define pacmanSx      129
#define pacmanDx  	  128
#define pacmanSu      130
#define pacmanGiu     131
#define pacmanPieno   132
#define pacmanMezzo   133
#define pacmanPezzo   134
// caratteri che rappresentano i fantasmi
#define fantasmaSx     136
#define fantasmaDx     137
#define fantasmaMorto  135
#define fantasmaFugaSx 155 
#define fantasmaFugaDx 156
// edibles
#define pallino       139
#define powerUp       138
#define frutto        140
// altri caratteri
#define SPC           32
// definizione posizioni
#define STARTING_X    11
#define STARTING_Y    15

// costanti
#define itemsCount     178  /* numero dei pallini */
#define sogliaFantasma 15
#define sogliaPowerUp  40
#define sogliaFrutto   50
#define sogliaFlash    10

static const unsigned char wallsgraph[483] = {
  a_d_l,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,t_upp,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,a_s_l,
  v_all,0,0,0,0,0,0,0,0,0,0,v_all,0,0,0,0,0,0,0,0,0,0,v_all,
  v_all,138,p_dxx,h_all,p_sxx,0,p_dxx,h_all,h_all,p_sxx,0,p_upp,0,p_dxx,h_all,h_all,p_sxx,0,p_dxx,h_all,p_sxx,138,v_all,
  v_all,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,v_all,
  v_all,0,p_dxx,h_all,p_sxx,0,p_dwn,0,p_dxx,h_all,h_all,t_upp,h_all,h_all,p_sxx,0,p_dwn,0,p_dxx,h_all,p_sxx,0,v_all,
  v_all,0,0,0,0,0,v_all,0,0,0,0,v_all,0,0,0,0,v_all,0,0,0,0,0,v_all,
  a_d_h,h_all,h_all,h_all,a_s_l,0,t_sxx,h_all,h_all,p_sxx,SPC,p_upp,SPC,p_dxx,h_all,h_all,t_dxx,0,a_d_l,h_all,h_all,h_all,a_s_h,
  SPC,SPC,SPC,SPC,v_all,0,v_all,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,v_all,0,v_all,SPC,SPC,SPC,SPC,
  h_all,h_all,h_all,h_all,a_s_h,0,p_upp,SPC,a_d_l,h_all,h_all,SPC,h_all,h_all,a_s_l,SPC,p_upp,0,a_d_h,h_all,h_all,h_all,h_all,
  SPC,SPC,SPC,SPC,SPC,0,SPC,SPC,v_all,137,137,SPC,136,136,v_all,SPC,SPC,0,SPC,SPC,SPC,SPC,SPC,
  h_all,h_all,h_all,h_all,a_s_l,0,p_dwn,SPC,a_d_h,h_all,h_all,h_all,h_all,h_all,a_s_h,SPC,p_dwn,0,a_d_l,h_all,h_all,h_all,h_all,
  SPC,SPC,SPC,SPC,v_all,0,v_all,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,SPC,v_all,0,v_all,SPC,SPC,SPC,SPC,
  a_d_l,h_all,h_all,h_all,a_s_h,0,p_upp,SPC,p_dxx,h_all,h_all,t_upp,h_all,h_all,p_sxx,SPC,p_upp,0,a_d_h,h_all,h_all,h_all,a_s_l,
  v_all,0,0,0,0,0,0,0,0,0,0,v_all,0,0,0,0,0,0,0,0,0,0,v_all,
  v_all,0,p_dxx,h_all,a_s_l,0,p_dxx,h_all,h_all,p_sxx,0,p_upp,0,p_dxx,h_all,h_all,p_sxx,0,a_d_l,h_all,p_sxx,0,v_all,
  v_all,138,0,0,v_all,0,0,0,0,0,0,128,0,0,0,0,0,0,v_all,0,0,138,v_all,
  t_sxx,h_all,p_sxx,0,p_upp,0,p_dwn,0,p_dxx,h_all,h_all,t_upp,h_all,h_all,p_sxx,0,p_dwn,0,p_upp,0,p_dxx,h_all,t_dxx,
  v_all,0,0,0,0,0,v_all,0,0,0,0,v_all,0,0,0,0,v_all,0,0,0,0,0,v_all,
  v_all,0,p_dxx,h_all,h_all,h_all,t_dwn,h_all,h_all,p_sxx,0,p_upp,0,p_dxx,h_all,h_all,t_dwn,h_all,h_all,h_all,p_sxx,0,v_all,
  v_all,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,v_all,
  a_d_h,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,h_all,a_s_h};

//21righe * 23 colonne = 483 puntini
static const unsigned char walls[483] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,
    1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,
    1,1,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,1,1,
    1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,
    1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,
    2,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,3,
    1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,
    1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,
    1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,0,1,
    1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
    1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,
    1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,
    1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
 
//22 righe * 23 colonne
static const unsigned char datapoints[483] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,
    0,2,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,2,0,
    0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
    0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,
    0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,
    0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,
    0,1,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,
    0,2,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,2,0,
    0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,
    0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,
    0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,
    0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

static unsigned char items[483];

//VARIABILI
static unsigned char korj, keyprem; //gestione joystick e tastiera
static unsigned char stageNo;
static unsigned char ghostInStage; //valori da 0 a 4
static unsigned char BlinkyShowing, InkyShowing, PinkyShowing, ClydeShowing;//1 se visibile, 0 se nascosto.
static unsigned char BlinkyRunHome, InkyRunHome, PinkyRunHome, ClydeRunHome; //1 se morto e gli occhietti stanno tornando a casa.
static unsigned char BlinkyScared, InkyScared, PinkyScared, ClydeScared;//1 se spaventato, 0 se normale
static unsigned char waiting; //tempo di pausa ad ogni loop (da 16 a 4) in centesimi di secondo
static unsigned char counterFantasma; //contatore per l'apparizione dei fantasmi
static unsigned char counterPowerUp;
static unsigned char counterFrutto;
static unsigned char lives; //numero vite
static unsigned char itemsRemaining; //pallini ancora da mangiare
//	DIM t1,t2 	as ULONG
static unsigned char pacmanChar; //usato per disegnare il pacman
static unsigned char ghostChar;  //usato per disegnare tutti i fantasmi
static char fVertMov, fHorizMov;
static char pmVertMov,pmHorizMov;
static char pmVertIn,pmHorizIn;
static unsigned char ghostIsScared;
static unsigned int score, maxscore;
static unsigned char bounce;
static unsigned char tmpVal;
static unsigned char pmr,pmc,pmr2,pmc2; //posizione pacman (prima e dopo)
static unsigned char f1r,f1c,f1r2,f1c2; //posizione fantasma uno (prima e dopo)
static unsigned char f2r,f2c,f2r2,f2c2; //posizione fantasma due (prima e dopo)
static unsigned char f3r,f3c,f3r2,f3c2; //posizione fantasma tre (prima e dopo)
static unsigned char f4r,f4c,f4r2,f4c2; //posizione fantasma quattro (prima e dopo)
static unsigned char still; //1 se il pacman è fermo contro un muro, 0 se si sta muovendo
static unsigned char cur,cuc,cur2,cuc2; //utili come variabili temporanee di posizione del fantasma elaborato
static unsigned char tmpCounter,displayPU;

static unsigned char udgs[] = {
0b00111100, 0b01111110, 0b11111000, 0b11110000, 0b11110000, 0b11111000, 0b01111110, 0b00111100,// pacman dx
0b00111100, 0b01111110, 0b00011111, 0b00001111, 0b00001111, 0b00011111, 0b01111110,	0b00111100,// pacman sx
0b00000000,	0b01000010, 0b11000011, 0b11100111, 0b11111111, 0b11111111, 0b01111110, 0b00111100,// pacman su
0b00111100, 0b01111110, 0b11111111, 0b11111111, 0b11100111, 0b11000011,	0b01000010, 0b00000000,// pacman giu
0b00111100,	0b01111110,	0b11111111,	0b11111111,	0b11111111,	0b11111111,	0b01111110,	0b00111100,// pacman pieno
0b00000000,	0b00000000,	0b00000000,	0b00000000,	0b11111111,	0b11111111,	0b01111110,	0b00111100,// pacman mezzo
0b00000000,	0b00000000,	0b00000000,	0b00000000, 0b00011000,	0b00111100,	0b01111110,	0b00111100,// pacman pezzo
0b00000000,	0b00000000,	0b00101000,	0b00101000,	0b00000000,	0b00000000,	0b00000000,	0b00000000,// fantasma occhi
0b00111100,	0b01111110,	0b01010110,	0b01010110,	0b01111110,	0b01111110,	0b01111110,	0b00101010,// fantasma sinistra
0b00111100,	0b01111110,	0b01101010, 0b01101010,	0b01111110,	0b01111110,	0b01111110,	0b01010100,// fantasma destra
0b00000000,	0b00000000,	0b00011000,	0b00111100,	0b00111100,	0b00011000,	0b00000000,	0b00000000,// powerUp
0b00000000,	0b00000000,	0b00000000,	0b00011000,	0b00011000,	0b00000000,	0b00000000,	0b00000000,// pallino da mangiare
0b01000110, 0b00101111,	0b00010110, 0b00010000,	0b00111100, 0b01111110, 0b01111110, 0b00111100,//  frutto
0b00000000, 0b00000000, 0b00000000,	0b11111111,	0b11111111, 0b00000000, 0b00000000, 0b00000000,// h_all
0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000,// v_all
0b00011000, 0b00011000, 0b00111000, 0b11110000,	0b11100000, 0b00000000, 0b00000000, 0b00000000,// a_s_h
0b00000000, 0b00000000, 0b00000000, 0b11100000, 0b11110000, 0b00111000, 0b00011000, 0b00011000,// a_s_l
0b00011000, 0b00011000, 0b00011100, 0b00001111,	0b00000111, 0b00000000, 0b00000000, 0b00000000,// a_d_h
0b00000000, 0b00000000, 0b00000000, 0b00000111, 0b00001111, 0b00011100, 0b00011000, 0b00011000,// a_d_l
0b00011000, 0b00011000, 0b00000000,	0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,// p_upp
0b00000000, 0b00000000, 0b00000000,	0b00000000, 0b00000000, 0b00000000, 0b00011000, 0b00011000,// p_dwn
0b00000000, 0b00000000, 0b00000000,	0b11000000, 0b11000000, 0b00000000,	0b00000000, 0b00000000,// p_s11
0b00000000, 0b00000000, 0b00000000,	0b00000011, 0b00000011, 0b00000000,	0b00000000, 0b00000000,// p_d11
0b00000000, 0b00000000, 0b00000000,	0b11111111,	0b11111111, 0b00111100, 0b00011000, 0b00011000,// t_upp  050
0b00011000, 0b00011000, 0b00111100,	0b11111111,	0b11111111, 0b00000000, 0b00000000, 0b00000000,// t_dwn  052
0b00011000, 0b00011000, 0b00111000, 0b11111000, 0b11111000, 0b00111000, 0b00011000, 0b00011000,// t_d11  053
0b00011000, 0b00011000, 0b00011100, 0b00011111, 0b00011111, 0b00011100, 0b00011000, 0b00011000,// t_s11  054
0b00111100, 0b01000010, 0b10101001, 0b10101001, 0b10000001, 0b10000001, 0b10000001, 0b01010101,// scaredGostSx
0b00111100, 0b01000010, 0b10010101, 0b10010101, 0b10000001, 0b10000001, 0b10000001, 0b10101010 // scaredGostDx
};

/********************* funzioni ***********************************************/
//lettura dell'input da tastiera
static void readInputKey();
//lettura dell'input da joystick
static void readInputJoy() ;
//la seguente procedura verifica se pacman impatta con un fantasma in tutti i possibili casi
static void checkCatch();
//questa funzione calcola lo spostamento proposto di un fantasma verso casa
static void ghostRunHome();
//questa funzione calcola lo spostamento proposto di un fantasma che scappa dal pacman
static void ghostRunAway();
//questa funzione calcola lo spostamento proposto di un fantasma che insegue pacman
static void ghostFocus();
//questa funzione calcola lo spostamento reale del fantasma tenendo conto dei muri
static void calculateGhostMovement(unsigned char row, unsigned char col);

static void manageGhost();
static void catched();
static void eraseGhost(unsigned char row, unsigned char col);
static void splashScreen();
static void drawRemainingLives();
static void pacManStartPos();
static void pacManDies();
static void blinkReady();
static void blinkStageCleared();
static void blinkGameOver();
static void playEatGhost();
static void printCharacterAt(unsigned char car, unsigned char x, unsigned char y);
static void newgame();
static void newstage();
static void drawloop();
static void drawboard();
//fine dichiarazione funzioni

int main()
{
  void *param = &udgs;
  console_ioctl(IOCTL_GENCON_SET_UDGS, &param);
  
  in_GetKeyReset();
  maxscore = 0;
  korj     = 0;
  while (1){
    // splashScreen();
    keyprem  = 'K';
	while ((keyprem=='J') || (keyprem=='K')){
		if (keyprem=='J')        korj     = 1;
		else if (keyprem=='K')   korj     = 0;
		splashScreen();
	}

    newgame();
  }
  return 0;
}

static void splashScreen()
{
  clrscr();
  gotoxy(0,0);
  printf("GLDM GAMES presents:");//PRINT AT 0,0; ink 5;"GLDM GAMEZ presenta"
  printCharacterAt(pacmanDx,3,3);
  printCharacterAt(pacmanDx,5,3);
  printCharacterAt(pacmanDx,7,3);
  gotoxy(11,3);
  printf("PAC-MAN");
  printCharacterAt(pacmanSx,22,3);
  printCharacterAt(pacmanSx,24,3);
  printCharacterAt(pacmanSx,26,3);
  
  gotoxy(6,6);
  printf("HIGH SCORE: %d",maxscore);
  gotoxy(3,18);
  printf("press K or J to select input"); 
  
  gotoxy(7,10);
  if (korj==1){ //JOYSTICK SELECTED
	  printf("HOW TO PLAY:");
	  gotoxy(9,12);
	  printf("Move the joystick,");
	  gotoxy(9,13);
	  printf("run for your life!");
	  gotoxy(3,16);	  
	  printf("Selected input: JOYSTICK");  
      gotoxy(5,19);
	  printf("press FIRE to start.");
	  unsigned char y =0;
	  while (y==0) {
		unsigned char r = inp(0x01);
		if (r==32) {
			y=1;
			keyprem='X';
		}
		else {
			keyprem = toupper(getk());
			if (keyprem=='K') y=1;
		}
	  }
  }
  else { //KEYBOARD SELECTED  
	  printf("HOW TO PLAY:");
	  gotoxy(9,11);
	  printf("P = right");
	  gotoxy(9,12);
	  printf("O = left");
	  gotoxy(9,13);
	  printf("Q = up");
	  gotoxy(9,14);
	  printf("A = down");
	  gotoxy(3,16);
	  printf("Selected input: KEYBOARD");  //
	  gotoxy(3,19);
	  printf("press any other key to start."); 
	  in_WaitForNoKey();
	  in_WaitForKey();
      keyprem=toupper(getk());
	  in_WaitForNoKey(); 
  } 
}

static void newgame()
{
  clrscr();
  gotoxy(0,0);
  stageNo = 1;
  score = 0;
  lives = 2;
  waiting = 16; //velocità del gioco alla partenza della partita
  while (lives>0){
    newstage();
    drawloop();
    if (lives==0) {
      blinkGameOver();
    }
    else {
      blinkStageCleared();
      if(lives<4) lives++;
    }
    if (waiting>4) waiting=waiting-1;
    stageNo++;
    csleep(100);
  }
  if (score>maxscore) maxscore=score;
}

static void readInputKey()
{
  switch (toupper(getk())) { 
    case K_DOWN:
      pmHorizIn = 0;
      pmVertIn  = 1;
      break;
    case K_UP:
      pmHorizIn = 0;
      pmVertIn  = -1;
      break;
    case K_RIGHT:
      pmHorizIn = 1;
      pmVertIn  = 0;
      break;
    case K_LEFT:
      pmHorizIn = -1;
      pmVertIn  = 0;
      break;
  }
}


//lettura dell'input da JOYSTICK
static void readInputJoy() {
	unsigned char r = inp(0x01);
	switch (r){
		case 1: //UP
			pmHorizIn = 0;
			pmVertIn  = -1;
			break;
		case 2: //DOWN
			pmHorizIn = 0;
			pmVertIn  = 1;
			break;
		case 4: //RIGHT
			pmHorizIn = 1;
			pmVertIn  = 0;
			break;
		case 8: //LEFT
			pmHorizIn = -1;
			pmVertIn  = 0;
			break;
		default:
			pmHorizIn = 0;
			pmVertIn  = 0;
			break;
	}
}

static void newstage()
{
  drawboard();
  
  counterFantasma = sogliaFantasma;
  ghostInStage  = 0;
  
  InkyShowing   = 0;
  PinkyShowing  = 0;
  BlinkyShowing = 0;
  ClydeShowing  = 0;
  				 
  InkyRunHome   = 0;
  PinkyRunHome  = 0;
  BlinkyRunHome = 0;
  ClydeRunHome  = 0;
  
  InkyScared   = 0;
  PinkyScared  = 0;
  BlinkyScared = 0;
  ClydeScared  = 0;
  
  f1c = 0;
  f2c = 0;
  f3c = 0;
  f4c = 0;
  f1r = 0;
  f2r = 0;
  f3r = 0;
  f4r = 0;	
	
  //pacman
  pacManStartPos();
  drawRemainingLives();
  
  //carico i punti nell'array items
  for (unsigned int i = 0; i < 483; i++) {	
    items[i]=datapoints[i];
  }
 
  //setup numero di pallini da mangiare
  itemsRemaining = itemsCount;

  counterFrutto   = 0;
  counterPowerUp  = 0;
  tmpCounter 	    = 0;
  
  blinkReady();
}

static void drawboard()
{
  unsigned char x, y;
  unsigned int posn;
  
  for (y = 0; y != 21; y++) {
    for (x = 0; x != 23; x++) {
      gotoxy(x, y+1);
      posn=x+y*23;
      if (wallsgraph[posn]>0) {
        putch(wallsgraph[posn]);
      }
      else {
        putch(pallino);
      }
    }
  }

  gotoxy(24,2);
  printf("STAGE %d",stageNo);
  gotoxy(24,14);
  cputs("INKY");
  gotoxy(24,15);
  cputs("PINKY");
  gotoxy(24,16);
  cputs("BLINKY");
  gotoxy(24,17);
  cputs("CLYDE");
  /////////////////// fantasmi assenti
  printCharacterAt(SPC,31,14);
  printCharacterAt(SPC,31,15);
  printCharacterAt(SPC,31,16);
  printCharacterAt(SPC,31,17);
  ///////////////////score
  gotoxy(2,0);
  cputs("SCORE:    ");
}

static void pacManStartPos() 
{
  printCharacterAt(pacmanDx,STARTING_X,STARTING_Y+1);
  pmr        = STARTING_Y;
  pmr2       = STARTING_Y;
  pmc        = STARTING_X;
  pmc2       = STARTING_X;
  pmHorizMov = 1;
  pmVertMov  = 0;
  pmHorizIn  = 0;
  pmVertIn   = 0;
  pacmanChar = pacmanDx;
}

static void blinkReady() 
{
  gotoxy(9,12);
  cputs("READY!");

  bit_beep(195,466);//115000/246.94); //B3  = 246.94 Hz 
  csleep(1);
  bit_beep(195,233);//115000/493.88); //B4  = 493.88 Hz 
  csleep(1);
  bit_beep(195,311);//115000/369.99); //F#4 = 369.99 Hz 
  csleep(1);
  bit_beep(195,370);//115000/311.13); //D#4 = 311.13 Hz 
  csleep(1);
  bit_beep(98,233);//115000/493.88); //B4  = 493.88 Hz 
  csleep(1);
  bit_beep(293,311);//115000/369.99); //F#4 = 369.99 Hz 
  csleep(1);
  bit_beep(390,370);//115000/311.13); //D#4 = 311.13 Hz   
  csleep(3);
  
  gotoxy(9,12);
  cputs("      ");

  bit_beep(195,439);//115000/261.63); // C4 = 261.63 Hz 
  csleep(1);
  bit_beep(195,220);//115000/523.25); // C5 = 523.25 Hz 
  csleep(1);
  bit_beep(195,293);//115000/392.00); // G4 = 392.00 Hz 
  csleep(1);
  bit_beep(195,349);//115000/329.63); // E4 = 329.63 Hz 
  csleep(1);
  bit_beep(98,220);//115000/523.25);  // C5 = 523.25 Hz
  csleep(1);
  bit_beep(293,293);//115000/392.00); 
  csleep(1);
  bit_beep(390,349);//115000/329.63); 
  csleep(3);
  gotoxy(9,12);
  cputs("READY!");

  bit_beep(195,466);//115000/246.94); //B3  = 246.94 Hz 
  csleep(1);
  bit_beep(195,233);//115000/493.88); //B4  = 493.88 Hz 
  csleep(1);
  bit_beep(195,311);//115000/369.99); //F#4 = 369.99 Hz 
  csleep(1);
  bit_beep(195,370);//115000/311.13); //D#4 = 311.13 Hz 
  csleep(1);
  bit_beep(98,233);//115000/493.88);  //B4  = 493.88 Hz 
  csleep(1);
  bit_beep(293,311);//115000/369.99); //F#4 = 369.99 Hz 
  csleep(1);
  bit_beep(390,370);//115000/311.13); //D#4 = 311.13 Hz 
  csleep(3);
  gotoxy(9,12);
  cputs("      ");

  bit_beep(98,370);//115000/311.13);  //311.13 Hz
  csleep(1);
  bit_beep(98,349);//115000/329.63);  //329.63 Hz
  csleep(1);
  bit_beep(195,329);//115000/349.23); // F4 = 349.23 Hz 
  csleep(3);  
  
  bit_beep(98,329);//115000/349.23); // 349.99 Hz
  csleep(1);
  bit_beep(98,311);//115000/369.99); // 369.99 Hz
  csleep(1);
  bit_beep(195,293);//115000/392.00); // 392.00 Hz
  csleep(3);     
  
  bit_beep(98,293);//115000/392.00); // 392.00 Hz
  csleep(1);
  bit_beep(98,277);//115000/415.30); // G#4 = 415.30 Hz
  csleep(1);
  bit_beep(195,261);//115000/440.00); // A4 = 440 Hz
  csleep(1);      
  bit_beep(390,233);//115000/493.88); // 493.88 Hz
  // inizio piccola attesa
  csleep(3);
  // fine piccola attesa
}

static void blinkGameOver(){
  for (unsigned char i=0; i<3; i++){
    gotoxy(8,12);
    cputs("GAME OVER");
    csleep(25);
    gotoxy(8,12);
    cputs("         ");
    csleep(25);
  }
}

static void blinkStageCleared(){
  for (unsigned char i=0; i<3; i++){
    gotoxy(8,12);
    cputs(" CLEARED!");
    csleep(25);
    gotoxy(8,12);
    cputs("         ");
    csleep(25);
  }
}

static void drawloop()
{
  while((itemsRemaining>0)&&(lives>0))  {
    if (korj==1) {
		readInputJoy();}
	else {
		readInputKey();
	}

    //ricalcolo posizione pacman
    //if((pmHorizIn==0) && (pmVertIn==0)){
      // continuo come prima, ovvero non cambio direzione sulla base dell'input
    //}
    if((pmHorizIn!=0) || (pmVertIn!=0)) {
      // provo a modificare la traiettoria
      // verifico se l'input punta a posizioni valide
      if (walls[pmc + pmHorizIn+23*(pmr + pmVertIn)] == 0) {
        // c'e' posto, aggiorno gli spostamenti
        pmVertMov  = pmVertIn;
        pmHorizMov = pmHorizIn;
      }
      //else {
      //  // ci sarebbe un muro: lascio gli spostamenti attuali
      //}
    }
      
    // verifico cosa ci sarebbe nella posizione di arrivo
    tmpVal = walls[(pmr + pmVertMov)*23+pmc + pmHorizMov];  
    if (tmpVal==0) { // c'e' posto, aggiorno la posizione
      pmr   = pmr + pmVertMov;
      pmc   = pmc + pmHorizMov;
      still = 0;
    }
    else if (tmpVal==2) { // passaggio a sx
      pmc        = 22;
      still      = 0;
      bounce     = 0;
      pmHorizMov = -1;
    }
    else if (tmpVal==3) { // passaggio a dx
      pmc        = 2;
      still      = 0;
      bounce     = 0;
      pmHorizMov = 1;
    }
    else if (tmpVal==1) { // ci sarebbe un muro: lascio le posizioni attuali.
      still=1;
    }

    // calcolo la direzione del pacman
    if ((bounce==1) && (still==0)){
      if (pmVertMov == 1) {
        pacmanChar = pacmanGiu;
      } 
      else if (pmVertMov == -1){ 
        pacmanChar = pacmanSu;
      } 
      else if (pmHorizMov == -1){ 
        pacmanChar = pacmanSx;
      } 
      else if (pmHorizMov == 1){
        pacmanChar = pacmanDx;
      }
    }	
    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    //cancello posizione precedente giocatore (se mi sto muovendo)
    if (still==0) { 
      //PRINT AT pmr2,pmc2;" "
      //gotoxy(pmc2,pmr2+1);
      //putch(SPC);
      printCharacterAt(SPC,pmc2,pmr2+1);
      unsigned int arraypos=pmr*23+pmc;
      // verifico se ho mangiato un punto 
      if (items[arraypos] == 1) {
        score = score +10;    
        bit_fx(0); // eat pill
        items[arraypos]=0;
        itemsRemaining = itemsRemaining-1;
      }
      else if (items[arraypos]==9) {
        score = score + 200;
        bit_fx2(5); // eat ghost or fruit
        items[arraypos] = 0;
        counterFrutto = 0;
        //itemsRemaining = itemsRemaining-1
      }
      else if (items[arraypos]==2) {
        // mangiato un power-up
        if ((InkyShowing==1)&&(InkyRunHome==0))     { 
          InkyScared=1;
          printCharacterAt(fantasmaFugaSx,31,14);
          }
        if ((PinkyShowing==1)&&(PinkyRunHome==0))   { 
          PinkyScared=1;
          printCharacterAt(fantasmaFugaSx,31,15);        
          }
        if ((BlinkyShowing==1)&&(BlinkyRunHome==0)) { 
          BlinkyScared=1;
          printCharacterAt(fantasmaFugaSx,31,16);         
          }
        if ((ClydeShowing==1)&&(ClydeRunHome==0))   { 
          ClydeScared=1;
          printCharacterAt(fantasmaFugaSx,31,17);  
        }
        counterPowerUp = sogliaPowerUp;//inizia il conto alla rovescia
        score = score + 50;			
        //gotoxy(10,0);
        //cprintf("%d",score);
        bit_fx4(2); // eat power-up 
        items[arraypos] = 0;
        itemsRemaining = itemsRemaining-1;
      }
    }
    //else {
    //  // sono fermo
    //}

    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    //disegno pacman
    if (bounce==1) {
      printCharacterAt(pacmanChar,pmc,pmr+1);
      bounce=0;
    }
    else {  
      printCharacterAt(pacmanPieno,pmc,pmr+1);
      bounce=1;
    }
    //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    //verifico impatto coi fantasmi
    checkCatch();

    //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    //'disegno inky
    if(InkyShowing==1) {
      //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
      if ((f1r==9) && ((f1c<3)||(f1c>19))) {
        // gestione tunnel
        fVertMov  = f1r-f1r2;
        fHorizMov = f1c-f1c2;				
      }		
      if (InkyRunHome==1) {				
        fVertMov  = f1r-f1r2;
        fHorizMov = f1c-f1c2;
        cuc = f1c; 
        cur = f1r; 
        ghostRunHome();
      }
      else if (InkyScared==1) {
        if ((tmpCounter % 4)==0) {
            cuc = f1c; 
            cur = f1r; 
            ghostRunAway();
         } 
         else {
          fVertMov  = f1r-f1r2;
          fHorizMov = f1c-f1c2;
        }
      } 
      else {
       if ((rand()%50)>2) {
        // parto dallo spostamento ereditato dalla traiettoria precedente 
        fVertMov  = f1r-f1r2;
        fHorizMov = f1c-f1c2;
       }
       else {
         cuc = f1c; 
         cur = f1r; 
         ghostFocus();
        }
      }
      // registro posizione precedente 
      f1c2 = f1c;
      f1r2 = f1r;
      //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''			
      cuc  = f1c;
      cuc2 = f1c2;		
      cur  = f1r;
      cur2 = f1r2;
      ghostIsScared = InkyScared;
      manageGhost();
      f1c  = cuc;
      f1c2 = cuc2;			
      f1r  = cur;
      f1r2 = cur2;
      //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
      // cancello posizione precedente
      eraseGhost(f1r2,f1c2);
      //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
      // scrivo posizione corrente
      if (InkyRunHome==1) {
        if ((f1c==11)&&(f1r==7)) {
          // sono a casa
          InkyShowing=0;
          InkyRunHome=0;
          ghostInStage = ghostInStage-1;
          counterFantasma = sogliaFantasma;
          printCharacterAt(fantasmaSx,12,10); 
          printCharacterAt(SPC,31,14);
        }
        else {
          printCharacterAt(fantasmaMorto,f1c,f1r+1);
        }
      }
      else {
        // funziona sia per fantasma normale che per fantasma che fugge
        printCharacterAt(ghostChar,f1c,f1r+1);
      }
    }
    //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    //'disegno pinky
    if (PinkyShowing==1) {
      if ((f2r==9) && ((f2c<3)||(f2c>19))) {
        // gestione tunnel  //
        fVertMov  = f2r-f2r2; 
        fHorizMov = f2c-f2c2;	
      }		  
      if (PinkyRunHome==1) {				  	
        fVertMov  = f2r-f2r2;  
        fHorizMov = f2c-f2c2;  
        cuc = f2c;   
        cur = f2r;   
        ghostRunHome();  
      }  
      else if (PinkyScared==1) {  			
        if ((tmpCounter % 4)==0) {			
            cuc = f2c;   		
            cur = f2r;   		
            ghostRunAway();  
        }   
        else { 
          fVertMov  = f2r-f2r2; 
          fHorizMov = f2c-f2c2; 
        } 
      } 
      else { 
       if ((rand()%50)>5) {  
        // parto dallo spostamento ereditato dalla traiettoria precedente 
        fVertMov  = f2r-f2r2; 			
        fHorizMov = f2c-f2c2; 			
       } 				
       else { 	
         cuc = f2c; 
         cur = f2r;   
         ghostFocus();
        }		
      }  		
      // registro posizione precedente  
      f2c2 = f2c;  
      f2r2 = f2r;  
      //''''''''''''''''''''''''''''''''
      cuc  = f2c;  
      cuc2 = f2c2;	
      cur  = f2r;  
      cur2 = f2r2; 
      ghostIsScared = PinkyScared;  
      manageGhost();
      f2c  = cuc;  
      f2c2 = cuc2;	
      f2r  = cur;  
      f2r2 = cur2;  
      //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' 
      // cancello posizione precedente
      eraseGhost(f2r2,f2c2);  	
      //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' 
      // scrivo posizione corrente  
      if (PinkyRunHome==1) { 	
        if ((f2c==11)&&(f2r==7)) {  
          // sono a casa  			
          PinkyShowing=0; 				
          PinkyRunHome=0; 				
          ghostInStage = ghostInStage-1;  	
          counterFantasma = sogliaFantasma;  
          printCharacterAt(fantasmaDx,10,10); 
          printCharacterAt(SPC,31,15);  	
        }  
        else {  
          printCharacterAt(fantasmaMorto,f2c,f2r+1);  
        }  
      }  
      else { 
        // funziona sia per fantasma normale che per fantasma che fugge 
        printCharacterAt(ghostChar,f2c,f2r+1);  
      }  

    }
    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    //'disegno blinky
    if (BlinkyShowing==1) {
        
      if ((f3r==9) && ((f3c<3)||(f3c>19))) { 
        // gestione tunnel //	
        fVertMov  = f3r-f3r2; 
        fHorizMov = f3c-f3c2;	
      }		 			
      if (BlinkyRunHome==1) {	
        fVertMov  = f3r-f3r2; 
        fHorizMov = f3c-f3c2; 				
        cuc = f3c;  
        cur = f3r;  
        ghostRunHome(); 
      } 
      else if (BlinkyScared==1) { 
        if ((tmpCounter % 4)==0) {
            cuc = f3c;  		
            cur = f3r;  		
            ghostRunAway(); 	
         }      
         else { 
          fVertMov  = f3r-f3r2; 
          fHorizMov = f3c-f3c2; 
        }
      }  
      else {
       if ((rand()%50)>15) { 
        // parto dallo spostamento ereditato dalla traiettoria precedente  	
        fVertMov  = f3r-f3r2; 
        fHorizMov = f3c-f3c2; 
       } 
       else {
         cuc = f3c;  
         cur = f3r;  
         ghostFocus(); 
        } 
      }   
      // registro posizione precedente 
      f3c2 = f3c; 
      f3r2 = f3r; 
      //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
      cuc  = f3c; 
      cuc2 = f3c2;
      cur  = f3r; 			
      cur2 = f3r2;
      ghostIsScared = BlinkyScared;
      manageGhost();
      f3c  = cuc; 
      f3c2 = cuc2;
      f3r  = cur; 
      f3r2 = cur2;
      //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' 
      // cancello posizione precedente 
      eraseGhost(f3r2,f3c2); 
      //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' 
      // scrivo posizione corrente
      if (BlinkyRunHome==1) { 
        if ((f3c==11)&&(f3r==7)) {
          // sono a casa 
          BlinkyShowing=0;
          BlinkyRunHome=0;
          ghostInStage = ghostInStage-1; 	
          counterFantasma = sogliaFantasma; 
          printCharacterAt(fantasmaSx,13,10); 
          printCharacterAt(SPC,31,16); 		
        } 	
        else {
          printCharacterAt(fantasmaMorto,f3c,f3r+1); 
        } //
      } //	
      else {
        // funziona sia per fantasma normale che per fantasma che fugge 
        printCharacterAt(ghostChar,f3c,f3r+1); //			else
      } 
    }
    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    //'disegno clyde
    if (ClydeShowing==1) {
      if ((f4r==9) && ((f4c<3)||(f4c>19))) {
        // gestione tunnel//	
        fVertMov  = f4r-f4r2;
        fHorizMov = f4c-f4c2;
      }		
      if (ClydeRunHome==1) {	
        fVertMov  = f4r-f4r2;
        fHorizMov = f4c-f4c2;
        cuc = f4c; 
        cur = f4r; 
        ghostRunHome();
      }
      else if (ClydeScared==1) {
        if ((tmpCounter % 4)==0) {
            cuc = f4c;					
            cur = f4r;					
            ghostRunAway();
         } 
         else {
          fVertMov  = f4r-f4r2;
          fHorizMov = f4c-f4c2;
        }
      }  
      else {
       if ((rand()%50)>10) {	
        // parto dallo spostamento ereditato dalla traiettoria precedente //
        fVertMov  = f4r-f4r2;
        fHorizMov = f4c-f4c2;
       } 
       else {
         cuc = f4c; 			
         cur = f4r; 			
         ghostFocus();		
        }
      }  
      // registro posizione precedente //	
      f4c2 = f4c;
      f4r2 = f4r;
      //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''//	 
      cuc  = f4c;	
      cuc2 = f4c2;	
      cur  = f4r;			
      cur2 = f4r2;
      ghostIsScared = ClydeScared;
      manageGhost();
      f4c  = cuc;	
      f4c2 = cuc2;	
      f4r  = cur;	
      f4r2 = cur2;
      //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''//	
      // cancello posizione precedente
      eraseGhost(f4r2,f4c2);
      //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''//	
      // scrivo posizione corrente
      if (ClydeRunHome==1) {		
        if ((f4c==11)&&(f4r==7)) {
          // sono a casa 
          ClydeShowing=0;
          ClydeRunHome=0;
          ghostInStage = ghostInStage-1;     
          counterFantasma = sogliaFantasma; 
          printCharacterAt(fantasmaDx,9,10);
          printCharacterAt(SPC,31,17);		
        }
        else {
          printCharacterAt(fantasmaMorto,f4c,f4r+1);
        }
      }
      else {
        // funziona sia per fantasma normale che per fantasma che fugge
        printCharacterAt(ghostChar,f4c,f4r+1);
      }
    }
    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    //'verifico impatto coi fantasmi
    checkCatch();

    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    pmr2 = pmr;
    pmc2 = pmc;

    //secondo giro di lettura input
    if (korj==1) {
		readInputJoy();}
	else {
		readInputKey();
	}
    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    //aggiungo i fantasmi se devo
    if ((counterFantasma==0)&&(ghostInStage<4)) {
      if (InkyShowing==0){
        // appare INKY, il fantasma uno, colore verde
        InkyShowing = 1;
        ghostInStage = ghostInStage+1;
        counterFantasma = sogliaFantasma;
        printCharacterAt(SPC,12,10); //cancello la posizione in-house di inky
        printCharacterAt(fantasmaSx,31,14);
        f1c  = 11;//STARTING_X;
        f1r  = 7;//was9
        f1c2 = 10;//STARTING_X-1;//was12
        f1r2 = 7;//was10	
      }
      else if (PinkyShowing==0) {
        // appare PINKY, il fantasma due, colore magenta
        PinkyShowing = 1;//   PinkyShowing = 1;
        ghostInStage = ghostInStage+1;//   ghostInStage = ghostInStage+1;
        counterFantasma = sogliaFantasma;//   counterFantasma=sogliaFantasma;
        printCharacterAt(SPC,10,10); //cancello la posizione in-house di Pinky
        printCharacterAt(fantasmaSx,31,15);//   printCharacterAt(fantasmaSx,31,15);//PRINT AT 15,31;ink 3;chr$ fantasmaSx
        f2c  = 11;//STARTING_X;//   f2c  = 12;
        f2r  = 7;//was9//   f2r  = 8;
        f2c2 = 12;//STARTING_X-1;//was12//   f2c2 = 11;
        f2r2 = 7;//was10	//   f2r2 = 8;
      }
      else if (BlinkyShowing==0){
        // appare BLINKY, il fantasma tre, colore rosso
        BlinkyShowing = 1;//  BlinkyShowing = 1;
        ghostInStage = ghostInStage+1;//  ghostInStage = ghostInStage+1;
        counterFantasma = sogliaFantasma;//  counterFantasma=sogliaFantasma;
        printCharacterAt(SPC,13,10); //cancello la posizione in-house di Blinky
        printCharacterAt(fantasmaSx,31,16);//  printCharacterAt(fantasmaSx,31,16);//PRINT AT 16,31;ink 2;chr$ fantasmaSx
        f3c  = 11;//STARTING_X;//  f3c  = 12;
        f3r  = 7;//was9//  f3r  = 9;
        f3c2 = 10;//STARTING_X-1;//was12//  f3c2 = 12;
        f3r2 = 7;//was10	//  f3r2 = 10;
      }
      else if(ClydeShowing==0){
        // appare CLYDE, il fantasma quattro, colore cyan
        ClydeShowing = 1;//   ClydeShowing = 1;
        ghostInStage = ghostInStage+1;//   ghostInStage = ghostInStage+1;
        counterFantasma = sogliaFantasma;//   counterFantasma=sogliaFantasma;
        printCharacterAt(SPC,9,10); //cancello la posizione in-house di Clyde
        printCharacterAt(fantasmaSx,31,17);//   printCharacterAt(fantasmaSx,31,17);//PRINT AT 17,31;ink 5;chr$ fantasmaSx
        f4c  = 11;//STARTING_X;//   f4c  = 12;
        f4r  = 7;//was9//   f4r  = 9;
        f4c2 = 12;//STARTING_X-1;//was12//   f4c2 = 12;
        f4r2 = 7;//was10	//   f4r2 = 10;
      }
    }

    //piccola attesa
    csleep(waiting-ghostInStage);//-ghostInStage);

    if (counterFrutto>0) { 
      if (counterFrutto==1) { 
        printCharacterAt(SPC,11,12);
        items[11*23+11]=0;
      }
      counterFrutto=counterFrutto-1;
    } 

    if (counterFantasma>0) counterFantasma=counterFantasma-1;

    if (counterPowerUp > 0) { 
      counterPowerUp = counterPowerUp-1;
      //displayPU = counterPowerUp/4;
      if ((tmpCounter % 4) == 0) {
        if (counterPowerUp>=4) {
          gotoxy(24,8);//PRINT AT 8,24;ink 7; 
          cputs("POWER-UP");
          //print at 9,25;ink 7;bright 1;"- ";displayPU;" -"
          //beep 0.03,11
        }
        else {
          gotoxy(24,8);//PRINT AT 8,24;ink 7; 
          cputs("        ");
          // PRINT AT 8,24;ink 7; "        "
          // print at 9,25;ink 7;"     "
         }
      }
    }
    else {
      if (InkyScared == 1){
        InkyScared = 0;
        printCharacterAt(fantasmaSx,31,14); 
        //print at 14,31;ink 4;chr$ fantasmaSx
      }
      if (PinkyScared == 1){
        PinkyScared  = 0;
        printCharacterAt(fantasmaSx,31,15); 
        // print at 15,31;ink 3;chr$ fantasmaSx
      }
      if (BlinkyScared == 1){
        BlinkyScared = 0;
        printCharacterAt(fantasmaSx,31,16); 
        // print at 16,31;ink 2;chr$ fantasmaSx
      }
      if (ClydeScared == 1){
        ClydeScared  = 0;
         printCharacterAt(fantasmaSx,31,17); 
        // print at 17,31;ink 5;chr$ fantasmaSx
      }
    }

      tmpCounter=tmpCounter+1;
      // vediamo se disegnare un frutto
      if (tmpCounter>5) {
        if ((tmpCounter % 75)==0) {
          if (counterFrutto==0) { 
            counterFrutto=sogliaFrutto;
            printCharacterAt(frutto,11,12);
            items[11*23+11]=9;
          }
        }
      }

    gotoxy(8,0);
    printf(" %d  ",score);
    //gotoxy(9,0);
    //printf("%d X=%d Y=%d X=%d Y=%d",score,f1c,f1r,f1c2,f1r2);

  }
}

static void checkCatch(){
  if((InkyShowing==1)&&(InkyRunHome==0)&&(f1r==pmr)&&(f1c==pmc)){
    if (InkyScared==1){   // ho preso Inky
      score = score + 100;
      InkyScared = 0;
      bit_fx2(5); // eat ghost or fruit
      InkyRunHome=1;
      printCharacterAt(fantasmaMorto,31,14);
    } 
    else {
      // inky mi ha preso
      catched();
    }
  }
  else if ((PinkyShowing==1)&&(PinkyRunHome==0)&&(f2r==pmr)&&(f2c==pmc)){
    if (PinkyScared==1) { // ho preso Pinky
      score = score + 100;
      PinkyScared = 0;
      bit_fx2(5); // eat ghost or fruit
      PinkyRunHome=1;
      printCharacterAt(fantasmaMorto,31,15);
    } 
    else {
      // Pinky mi ha preso
      catched();
    }
  }
  else if ((BlinkyShowing==1)&&(BlinkyRunHome==0)&&(f3r==pmr)&&(f3c==pmc)){
    if (BlinkyScared==1) {  // ho preso Blinky
      score = score + 100;
      BlinkyScared = 0;
      bit_fx2(5); // eat ghost or fruit
      BlinkyRunHome=1;
      printCharacterAt(fantasmaMorto,31,16);
    } 
    else {
      // Blinky mi ha preso
      catched();
    }
  }
  else if ((ClydeShowing==1)&&(ClydeRunHome==0)&&(f4r==pmr)&&(f4c==pmc)){
    if (ClydeScared==1){  // ho preso Clyde
      score = score + 100;
      ClydeScared = 0;
      bit_fx2(5); // eat ghost or fruit
      ClydeRunHome=1;
      printCharacterAt(fantasmaMorto,31,17);
    } 
    else {
      // Clyde mi ha preso
      catched();
    }
  }
}

static void catched(){
  // animazione pacman muore
  pacManDies();
  // verificare che non ci sia un fantasma nella posizione di partenza o nelle caselle adiacenti
  if (((f1c==STARTING_X)||(f1c==STARTING_X+1)||(f1c==STARTING_X+2)) && (f1r==STARTING_Y)){
    f1c  = STARTING_X-1;
    f1c2 = STARTING_X;
    ghostChar = fantasmaSx;
    //if (InkyScared==1) ghostChar = fantasmaFugaSx;
    //else ghostChar = fantasmaSx;
  }

  if (((f2c==STARTING_X)||(f2c==STARTING_X+1)||(f2c==STARTING_X+2)) && (f2r==STARTING_Y)) {
    f2c  = STARTING_X-1;
    f2c2 = STARTING_X;
    ghostChar = fantasmaSx;
    //if (PinkyScared==1) ghostChar = fantasmaFugaSx;
    //else ghostChar = fantasmaSx;
  }

  if (((f3c==STARTING_X)||(f3c==STARTING_X+1)||(f3c==STARTING_X+2)) && (f3r==STARTING_Y)){
    f3c  = STARTING_X-1;
    f3c2 = STARTING_X;
    ghostChar = fantasmaSx;
  //if (BlinkyScared==1) ghostChar = fantasmaFugaSx;
  //else ghostChar = fantasmaSx;
  }

  if (((f4c==STARTING_X)||(f4c==12)||(f4c==13)) && (f4r==STARTING_Y)){
    f4c  = STARTING_X-1;
    f4c2 = STARTING_X;
    ghostChar = fantasmaSx;
    //if (ClydeScared==1) ghostChar = fantasmaFugaSx;
    //else ghostChar = fantasmaSx;
  }

  //ridisegnare tutti i fantasmi
  if (InkyRunHome==1) { printCharacterAt(fantasmaMorto,f1c,f1r+1); }
  else if ((InkyScared==1)||(InkyShowing==1)) { printCharacterAt(ghostChar,f1c,f1r+1); }

  if (PinkyRunHome==1) { printCharacterAt(fantasmaMorto,f2c,f2r+1); }
  else if ((PinkyScared==1)||(PinkyShowing==1)) { printCharacterAt(ghostChar,f2c,f2r+1); }
  
  if (BlinkyRunHome==1) { printCharacterAt(fantasmaMorto,f3c,f3r+1); }
  else if ((BlinkyScared==1)||(BlinkyShowing==1)) { printCharacterAt(ghostChar,f3c,f3r+1); }
  
  if (ClydeRunHome==1) { printCharacterAt(fantasmaMorto,f4c,f4r+1); }
  else if ((ClydeScared==1)||(ClydeShowing==1)) { printCharacterAt(ghostChar,f4c,f4r+1); }

  if (lives==0){
    //non dovrei mai essere qui
  }
  else {
    lives=lives-1;
    drawRemainingLives();
    if (lives>0){
      pacManStartPos();
      blinkReady();
    }
  } 
}

static void ghostRunAway(){
  //quattro casi:
	if (pmc<=cuc) { // pacman a sinistra
		if (pmr<=cur) { // caso 1: pacman in alto a sinistra
			if ((cuc-pmc)>(cur-pmr)) { // pacman è più vicino verticalmente
				fVertMov  = 1;
				fHorizMov = 0;
			} 
      else { // pacman è più vicino orizzontalmente
				fVertMov  = 0;
				fHorizMov = 1;
			}
		} 
    else { // caso 2: pacman in basso a sinistra
			if ((cuc-pmc)>(pmr-cur)) { // pacman è più vicino verticalmente
				fVertMov  = -1;
				fHorizMov = 0;
			} 
      else { // pacman è più vicino orizzontalmente
				fVertMov  = 0;
				fHorizMov = 1;
			}
		}
	} 
  else { // pacman a destra
		if (pmr<=cur) {	// caso 3: pacman in alto a destra
			if ((pmc-cuc)>(cur-pmr)) { // pacman è più vicino verticalmente
				fVertMov  = 1;
				fHorizMov = 0;
			} 
      else { // pacman è più vicino orizzontalmente
				fVertMov  = 0;
				fHorizMov = -1;
			}
		} 
    else { // caso 4: pacman in basso a destra
			if ((pmc-cuc)>(pmr-cur)) { // pacman è più vicino verticalmente
				fVertMov  = -1;
				fHorizMov = 0;
			} 
      else { // pacman è più vicino orizzontalmente
				fVertMov  = 0;
				fHorizMov = -1;
			}
		}
	}
}

static void ghostRunHome() {
	if ((cur>4)&&(cur<10)&&(cuc>=7)&&(cuc<=15)) { //siamo nel quadrato magico
    //printCharacterAt(fantasmaDx,31,0);
		if (cuc>11) { // siamo a destra dell//obiettivo
      //printCharacterAt(fantasmaDx,30,0);
			if ( walls[cur*23+cuc-1]==0 ) {// a sinistra c'è posto
				fHorizMov = -1;
				fVertMov  = 0;
      } 
      else { //a sinistra c'è muro
        if (cur>=7) { //siamo  sotto l'obiettivo: saliamo
          fHorizMov = 0;
          fVertMov  = -1;
        } 
        else { //siamo sopra l'obiettivo: scendiamo
          fHorizMov = 0;
          fVertMov  = 1;
        }
      }
    } 
    else { // siamo a sinistra dell'obiettivo
      //printCharacterAt(SPC,30,0);
			if ( walls[cur*23+cuc+1]==0) { //a destra c'è posto
				fHorizMov = 1;
				fVertMov  = 0;
      } 
      else { //a destra c'è muro
				if (cur>=7) { // siamo sotto l'obiettivo: saliamo
					fHorizMov = 0;
					fVertMov  = -1;
        } 
        else { // siamo sopra l//obiettivo: scendiamo
					fHorizMov = 0;
					fVertMov  = 1;
        }
      }    
    }
  } 
  else { // NON siamo nel quadrato magico
    //printCharacterAt(SPC,31,0);
		if (cur==9)  { //zona centrale
			if (cuc<8) {
				fHorizMov = 1;
				fVertMov  = 0;
			} 
      else if (cuc>16) {
				fHorizMov = -1;
				fVertMov  = 0;
      } 
      else { //entro nel quadrato magico!
				fHorizMov = 0;
				fVertMov  = -1;
      } 
		} 
    else  if (cur<9) { //zona superiore (esterna al quadrato magico): basta scendere
			if ( walls[(cur+1)*23+cuc]==0 ) {
				fHorizMov = 0;
				fVertMov  = 1;
      }  
    } 
    else { //zona inferiore, devo andare su
			if (walls[(cur-1)*23+cuc]==0) {
				fHorizMov = 0;
				fVertMov  = -1;
        //} else {
        //	if ( cuc<12 ) {
        //		//cerco di andare alla colonna 6
        //		if ( cuc<6 ) {
        // } else { //cerco di andare alla colonna 18
        // }
      }
    }
  }
}

static void ghostFocus(){
  //quattro casi:
  if (pmc<=cuc) { // pacman a sinistra
    if (pmr<=cur) { // caso 1: pacman in alto a sinistra
      if ((cuc-pmc)>(cur-pmr)) { // pacman è più lontano orizzontalmente che verticalmente
        fVertMov  = 0;
        fHorizMov = -1;
      }
      else { // pacman è più lontano verticalmente che orizzontalmente
        fVertMov  = -1;
        fHorizMov = 0;
      }
    }
    else { // caso 2: pacman in basso a sinistra
      if ((cuc-pmc)>(pmr-cur)) { // pacman è più lontano orizzontalmente che verticalmente
        fVertMov  = 0;
        fHorizMov = -1;
      }
      else { // pacman è più lontano verticalmente che orizzontalmente
        fVertMov  = 1;
        fHorizMov = 0;
      }
    }
  }
  else { // pacman a destra
    if (pmr<=cur) { // caso 3: pacman in alto a destra
      if ((pmc-cuc)>(cur-pmr)) { // pacman è più lontano orizzontalmente che verticalmente
        fVertMov  = 0;
        fHorizMov = 1;
      }
      else { // pacman è più lontano verticalmente che orizzontalmente
        fVertMov  = -1;
        fHorizMov = 0;
      }
    }
    else { // caso 4: pacman in basso a destra
      if ((pmc-cuc)>(pmr-cur)) {
        //pacman è più lontano orizzontalmente che verticalmente
        fVertMov  = 0;
        fHorizMov = 1;
      }else{
        //pacman è più lontano verticalmente che orizzontalmente
        fVertMov  = 1;
        fHorizMov = 0;
      }
    }
  }
}

// questa funzione definisce la posizione reale e la grafica
// del fantasma, valorizzando ghostChar
static void manageGhost()
{
  //calcolo la nuova posizione corrente
	tmpVal = walls[(cur + fVertMov)*23 +(cuc + fHorizMov)];
	if (tmpVal == 2) {
		//passaggio a sx
		cuc    = 21;
		cuc2   = 22;
		if ((ghostIsScared==1)&&((counterPowerUp>10)||(bounce==1)))	ghostChar=fantasmaFugaSx;	
    else ghostChar=fantasmaSx;
		//visto che traslo la posizione di partenza, devo cancellare il fantasma residuo
		printCharacterAt(SPC,1,10);//PRINT AT 10,2;" "
	} 
  else if (tmpVal == 3) { //passaggio a dx
		cuc    = 1;
		cuc2   = 0;
		if ((ghostIsScared==1)&&((counterPowerUp>10)||(bounce==1)))	ghostChar=fantasmaFugaDx;	
    else ghostChar=fantasmaDx;
		//visto che traslo la posizione di partenza, devo cancellare il fantasma residuo
		printCharacterAt(SPC,21,10);//PRINT AT 10,22;" "
	}
  else {//in tutti gli altri casi, 
		calculateGhostMovement(cur,cuc);
		//aggiornamento posizione corrente (cur=current row, cuc=current column)
    //verifico la non sovrapposizione dei fantasmi
    static unsigned char tempcur,tempcuc;
    tempcur= cur+fVertMov;
    tempcuc= cuc+fHorizMov;
    if (((tempcur!=f1r)||(tempcuc!=f1c))&&((tempcur!=f2r)||(tempcuc!=f2c))&&((tempcur!=f3r)||(tempcuc!=f3c))&&((tempcur!=f4r)||(tempcuc!=f4c))) {
      //proseguo normale
      cur = cur+fVertMov;
      cuc = cuc+fHorizMov;
    }
		//scelgo la figura del fantasma
		if (fHorizMov>0) {
      if ((ghostIsScared==1)&&((counterPowerUp>sogliaFlash)||(bounce==1)))	ghostChar=fantasmaFugaDx;	
      else ghostChar=fantasmaDx;	
		}
    else if (fHorizMov<0) {
			if ((ghostIsScared==1)&&((counterPowerUp>sogliaFlash)||(bounce==1)))	ghostChar=fantasmaFugaSx;	
      else ghostChar=fantasmaSx;	
		}
    else {
			if (fVertMov>0) { // se scende è rivolto a destra 
				if ((ghostIsScared==1)&&((counterPowerUp>sogliaFlash)||(bounce==1)))	ghostChar=fantasmaFugaDx;	
        else ghostChar=fantasmaDx;
      }
      else { // se sale è rivolto a sinistra
        if ((ghostIsScared==1)&&((counterPowerUp>sogliaFlash)||(bounce==1)))	ghostChar=fantasmaFugaSx;	
        else ghostChar=fantasmaSx;
      }
		}	
	} 
}
  
static void eraseGhost(unsigned char row, unsigned char col)
{ 
  //if ((row*23+col)<483) {// ' questo controllo serve ad evitare l'array overflow
    if (items[row*23+col]==1) {
      printCharacterAt(pallino,col,row+1); //PRINT AT row,col;ink 6;chr$ pallino
    }
    else if (items[row*23+col]==2 ){
      printCharacterAt(powerUp,col,row+1); //PRINT AT row,col;ink 2;bright 1; chr$ powerUp
    }
    else if (items[row*23+col]==9) {
      printCharacterAt(frutto,col,row+1); //PRINT AT row,col;ink 2;bright 0; chr$ frutto
    }
    else {
      printCharacterAt(SPC,col,row+1); //PRINT AT row,col;" "
    }
  //}
}

//questa funzione calcola lo spostamento reale del fantasma tenendo conto dei muri
static void calculateGhostMovement(unsigned char row, unsigned char col)
{
  if(walls[(row + fVertMov)*23+ col + fHorizMov]==1) {	
    // ci sarebbe un muro: devo girare o tornare indietro..
    if (fVertMov==0){ // mi muovendo orizzontalmente, proviamo verticalmente
      if ((rand()%50)>25) { // provo prima giu poi su poi indietro
        if (walls[(row+1)*23+col]==0) {// va bene lo spostamento giu	
          fVertMov   = 1;			
          fHorizMov  = 0;		
        } 
        else if (walls[(row-1)*23+col]==0) { // va bene lo spostamento su	
          fVertMov   = -1;			
          fHorizMov  = 0;	
        }
        else {  // torno indietro
          fVertMov  = 0;
          fHorizMov = -fHorizMov;
        }	
      } 
      else {  // provo prima su poi giu poi indietro
        if (walls[(row-1)*23+col]==0) {  // va bene lo spostamento su	
        	fVertMov   = -1;			
        	fHorizMov  = 0;				
        }
        else if (walls[(row+1)*23+col]==0) { // va bene lo spostamento giu	
          fVertMov   = 1;		
          fHorizMov  = 0;
        }
        else { // torno indietro
          fVertMov  = 0;
          fHorizMov = -fHorizMov;
        }	
      }
    }
    else { // spostamento verticale, proviamo orizzontalmente
      if ((rand()%50)>25) {     // provo prima destra poi sinistra poi indietro
        if (walls[row*23+col+1]==0) {  // va bene lo spostamento a destra
          fHorizMov  = 1;
          fVertMov   = 0;
        }
        else if (walls[row*23+col-1]==0) { // va bene lo spostamento a sinistra
          fHorizMov  = -1;
          fVertMov   = 0;
        }
        else { // torno indietro
          fHorizMov = 0;
          fVertMov  = -fVertMov;
        }
      } 
      else { // provo prima sinistra poi destra poi indietro
        if (walls[row*23+col-1]==0) { // va bene lo spostamento a sinistra
          fHorizMov  = -1;
          fVertMov   = 0;
        }
        else if (walls[row*23+col+1]==0) {  // va bene lo spostamento a destra
          fHorizMov  = 1;
          fVertMov   = 0;
        }
        else {	// torno indietro
          fHorizMov = 0;
          fVertMov  = -fVertMov;
        }
      }
    }			
  }  
}

static void pacManDies()
{  
  bit_beep(195,311);//115000/369.99); 
  printCharacterAt(pacmanPieno,pmc,pmr+1);
  //csleep(20);
	bit_beep(195,349);//115000/329.63);
  printCharacterAt(pacmanSu,pmc,pmr+1);
  //csleep(20);
	bit_beep(195,370);//115000/311.13);	
	printCharacterAt(pacmanMezzo,pmc,pmr+1);
	//csleep(20);  
	bit_beep(195,392);//115000/293.66);
	printCharacterAt(pacmanPezzo,pmc,pmr+1);
	//csleep(20);   
  bit_beep(195,439);//115000/261.63);
	printCharacterAt(SPC,pmc,pmr+1);
  csleep(2); 
  bit_beep(260,466);//115000/246.94);
  csleep(50);    
}

static void  drawRemainingLives()
{
  gotoxy(16,0);
  cputs("          ");
	for (unsigned char i=0; i<lives; i++){
		printCharacterAt(pacmanSx,22-(i*2),0);//PRINT AT 0, 24-(i*2);ink 6; bright 1;chr$ pacmanSx
	}
}

static void printCharacterAt(unsigned char car, unsigned char x, unsigned char y){
  gotoxy(x,y);
  putch(car);
}