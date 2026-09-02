	 /***************************************************************/
	 /*                                                             */
	 /*    This program was made by IAMN1, 10G clas                 */
	 /*    Esli eta programma rabotaet,to ee napisal IAMN1          */
	 /*    Elsli net, to ne znay kto ee napisal                      */
	 /* --------------------------------------------------------    */
	 /*   In this programm 1420 lines,>80 comments, include 16 non- */
	 /* -standart functions. The latest version on the programm 6.0 */
	 /*  Date 18/05/2017 | 21:39 hours.                             */
	 /*							        */
	 /***************************************************************/

#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
/*------------------------ Definition of global variables ------------------*/
union REGS regs;
int balance;                       //Balance mode1 and mode2
int Random1,Random2,Random3; 	    //Function random
int mode1,mode2;                   //Game mode
int punkt;                         //Punkt Menu
/*------------------------ variables for change color-----------------------*/
int colorR = 4, colorG = 2, colorB = 1, colorC = 3, colorM = 5;
int colorLG = 10, colorLB = 9, colorW =15;
//colorR-Red, colorG-Green, colorB-Blue, colorC-Cyan, colorM-Magenta
//colorLG-LghtGreen, colorLB-LightBlue colorW-White

/*------------------------ Definition of the funtions ----------------------*/
void Button(int x1,int y1, int x2, int y2, int color, const char *text);
void Shadow_Button(int x1,int y1, int x2, int y2);
void Begin_1(void);
void Begin_2(void);
void Graphics_Fon(void);
void Graphics_Submenu(void);
void Countdown_C4(void);
void Head_Machine_On(void);
void Game_Mode_1(void);
void Game_Mode_2(void);
void Loading(void);
int Button_Click(int x, int y, int w, int h);
int Mouse_Regs(void);
int Button_Aiming(int x,int y,int w,int h);

/*-------------------------- Function Main ---------------------------------*/

int main(void) {
		 /* Definition of local variables (for main function) */
 char menu,submenu;   //Menu selection and submenu selecton
 int subpunkt;	      //Punkt submenu

		 /* Initializing graphics mode */
 int gdriver=DETECT, gmode;
 initgraph(&gdriver, &gmode,"c:\\turboc3\\bgi");

 randomize();

 //Process  function loading
 Loading();

 cleardevice();

 //Process function begin_1
 Begin_1();
 delay(2000);
 cleardevice();

 //Process function begin_2
 Begin_2();
 delay(2000);

 do{
    round:
    punkt=1;
    cleardevice();
    Graphics_Fon();

    //Menu
    setcolor(WHITE);
    outtextxy(265,140,"Select game mode: ");
    Shadow_Button(285,175,405,195);
    Button(270,168,390,188,colorLB,"Gues 1 of 3");
    Shadow_Button(285,220,395,240);
    Button(275,210,385,230,LIGHTGRAY,"Gues 2 of 3");
    Shadow_Button(285,260,395,280);
    Button(275,250,385,270,LIGHTGRAY,"   Exit");

    while(!kbhit()){

       Mouse_Regs();

       //Punkt3
       if(Button_Aiming(275,250,385,270)){
	 goto punkt3;
       }
       //Punkt2
       if(Button_Aiming(275,210,385,230)){
	 goto punkt2;
       }

       //Punkt1
       if(Button_Click(270,168,390,188)){
	   Game_Mode_1();
	   goto round;
       }
    }


    again:
    menu=getch();
    if(menu==0) menu=getch();

    switch(menu){
       case 80: cleardevice();
	     if(punkt==1){
		punkt2:
		punkt=2;
		cleardevice();

		Graphics_Fon();

	     //Menu
		setcolor(WHITE);
		outtextxy(265,140,"Select game mode: ");
		Shadow_Button(285,180,395,200);
		Button(275,170,385,190,LIGHTGRAY,"Gues 1 of 3");
		Shadow_Button(285,215,405,235);
		Button(270,208,390,228,colorLB,"Gues 2 of 3");
		Shadow_Button(285,260,395,280);
		Button(275,250,385,270,LIGHTGRAY,"   Exit");

		while(!kbhit()){

		   Mouse_Regs();

		   //Punkt3
		   if(Button_Aiming(275,250,385,270)){
		      goto punkt3;
		   }
		   //punkt1
		   if(Button_Aiming(275,170,385,190)){
		      goto round;
		   }

		   //Punkt2
		   if(Button_Click(270,208,390,228)){
		      Game_Mode_2();
		      goto punkt2;
		   }
		}

		goto again;
	     }
	     else if(punkt==2){
		punkt3:
		cleardevice();
		punkt=3;

		Graphics_Fon();

	     //Menu
		setcolor(WHITE);
		outtextxy(265,140,"Select game mode: ");
		Shadow_Button(285,180,395,200);
		Button(275,170,385,190,LIGHTGRAY,"Gues 1 of 3");
		Shadow_Button(285,220,395,240);
		Button(275,210,385,230,LIGHTGRAY,"Gues 2 of 3");
		Shadow_Button(285,255,405,275);
		Button(270,248,390,268,colorLB,"   Exit");

		while(!kbhit()){

		   Mouse_Regs();

		   //Punkt2
		   if(Button_Aiming(275,210,385,230)){
		      goto punkt2;
		   }
		   //Punkt1
		   if(Button_Aiming(275,170,385,190)){
		      goto round;
		   }

		   //Punkt3
		   if(Button_Click(270,248,390,268)){
		      goto round2;
		   }
		}

		goto again;
	     }
	     else{
		goto round;
	     }
	     break;

       case 72: cleardevice();
	     if(punkt==2){
		goto round;
	     }
	     else if(punkt==3){
		punkt=2;

		Graphics_Fon();

	     //Menu
		setcolor(WHITE);
		outtextxy(265,140,"Select game mode: ");
		Shadow_Button(285,180,395,200);
		Button(275,170,385,190,LIGHTGRAY,"Gues 1 of 3");
		Shadow_Button(285,215,405,235);
		Button(270,208,390,228,colorLB,"Gues 2 of 3");
		Shadow_Button(285,260,395,280);
		Button(275,250,385,270,LIGHTGRAY,"   Exit");

		while(!kbhit()){

		   Mouse_Regs();

		   //Punkt3
		   if(Button_Aiming(275,250,385,270)){
		      goto punkt3;
		   }
		   //Punkt1
		   if(Button_Aiming(275,170,385,190)){
		      goto round;
		   }

		   //Punkt2
		   if(Button_Click(270,208,390,228)){
		      Game_Mode_2();
		      goto punkt2;
		   }
		}

		goto again;
	     }
	     else{
		punkt=3;

		Graphics_Fon();

	     //Menu
		setcolor(WHITE);
		outtextxy(265,140,"Select game mode: ");
		Shadow_Button(285,180,395,200);
		Button(275,170,385,190,LIGHTGRAY,"Gues 1 of 3");
		Shadow_Button(285,220,395,240);
		Button(275,210,385,230,LIGHTGRAY,"Gues 2 of 3");
		Shadow_Button(285,255,405,275);
		Button(270,248,390,268,colorLB,"   Exit");

		while(!kbhit()){

		   Mouse_Regs();

		   //Punkt2
		   if(Button_Aiming(275,210,385,230)){
		      goto punkt2;
		   }
		   //Punkt1
		   if(Button_Aiming(275,170,385,190)){
		      goto round;
		   }

		   //Punkt3
		   if(Button_Click(270,248,390,268)){
		      goto round2;
		   }
		}

		goto again;
	     }
	     break;

       case 13:
	     if(punkt==1) {
		Game_Mode_1();//Process function Game_Mode_1
	     }
	     else if(punkt==2){
		Game_Mode_2();//Process function Game_Mode_2
		goto punkt2;
	     }
	     else  if(punkt==3){

/*----------------- Exit game mode and Menu number 2 (Submenu)-------------*/
		   round2:
		   cleardevice();
		   subpunkt=2;

		   Graphics_Fon();
		   Graphics_Submenu();

		//Submenu
		   setcolor(WHITE);
		   outtextxy(220,180,"Do you wish to exit the game?");
		   Shadow_Button(210,240,310,260);
		   Button(200,230,300,250,LIGHTGRAY,"   Yes");
		   Shadow_Button(350,234,460,254);
		   Button(335,227,445,247,colorLB,"    No");

		   while(!kbhit()){

		      Mouse_Regs();

		      //subpunkt1
		      if(Button_Aiming(200,230,300,250)){
			 goto subpunkt1;
		      }

		      //subpunkt2
		      if(Button_Click(335,227,445,247)){
			 goto punkt3;
		      }
		   }

		   again2:

		   submenu=getch();
		   if(submenu==0) submenu=getch();

		   switch(submenu){
		      case 77: cleardevice();
			       if(subpunkt==2){
				  subpunkt1:
				  subpunkt=1;

				  Graphics_Fon();
				  Graphics_Submenu();

			       //Submenu
				  setcolor(WHITE);
				  outtextxy(220,180,"Do you wish to exit the game?");
				  Shadow_Button(210,234,320,254);
				  Button(195,227,305,247,colorLB,"    Yes");
				  Shadow_Button(350,240,450,260);
				  Button(340,230,440,250,LIGHTGRAY,"    No");

				  while(!kbhit()){

				     Mouse_Regs();

				     //subpunkt2
				     if(Button_Aiming(340,230,440,250)){
					goto round2;
				     }

				     //subpunkt1
				     if(Button_Click(195,227,305,247)){
					exit(0);
				     }
				  }

				  goto again2;
			       }
			       else{
				  goto round2;
			       }
			       break;

		      case 75: cleardevice();
			       if(subpunkt==1){
				  goto round2;

			       }
			       else{
				  subpunkt=1;

				  Graphics_Fon();
				  Graphics_Submenu();

			       //Submenu
				  setcolor(WHITE);
				  outtextxy(220,180,"Do you wish to exit the game?");
				  Shadow_Button(210,234,320,254);
				  Button(195,227,305,247,colorLB,"    Yes");
				  Shadow_Button(350,240,450,260);
				  Button(340,230,440,250,LIGHTGRAY,"    No");

				  while(!kbhit()){

				     Mouse_Regs();

				     //subpunkt2
				     if(Button_Aiming(340,230,440,250)){
					goto round2;
				     }

				     //subpunkt1
				     if(Button_Click(195,227,305,247)){
					exit(0);
				     }
				  }

				  goto again2;
			       }
			       break;

		      case 13: cleardevice();
			       if(subpunkt==2) {
				  goto punkt3;
			       }
			       break;
		      default: goto again2;
		   }
	     }
	     break;
       default: goto again;
    }
 }while(subpunkt!=1);
 closegraph();
 return 0;
}

/*------------------------------- Functions ----------------------------------*/
void Begin_1(void){

   //Cyan
   setcolor(11);
   setfillstyle(SOLID_FILL,colorC);
   bar3d(480,20,510,60,10,1);  // B
   floodfill(485,19,11);
   floodfill(515,50,11);
   bar3d(120,410,150,450,10,1); // T
   floodfill(125,409,11);
   floodfill(155,440,11);
   bar3d(300,80,330,120,10,1);  // G
   floodfill(305,79,11);
   floodfill(335,110,11);

   //Red
   setcolor(12);
   setfillstyle(SOLID_FILL,colorR);
   bar3d(570,300,600,330,10,1); // O
   floodfill(575,299,12);
   floodfill(605,320,12);
   bar3d(180,300,210,330,10,1); // N
   floodfill(185,299,12);
   floodfill(215,320,12);
   bar3d(595,120,625,150,10,1); // M
   floodfill(600,119,12);
   floodfill(630,140,12);
   bar3d(300,390,330,420,10,1); // A
   floodfill(305,389,12);
   floodfill(335,410,12);
   bar3d(120,180,150,210,10,1); // H
   floodfill(125,179,12);
   floodfill(155,200,12);

   //Green
   setcolor(colorLG);
   setfillstyle(SOLID_FILL,colorG);
   bar3d(330,240,360,270,10,1); // E
   floodfill(335,239,10);
   floodfill(365,260,10);
   bar3d(480,180,510,210,10,1); // E
   floodfill(485,179,10);
   floodfill(515,200,10);
   bar3d(420,360,450,390,10,1); // E
   floodfill(425,359,10);
   floodfill(455,380,10);

   // Vuvod texta#1
   setcolor(colorW);
   settextstyle(0,0,2);
   outtextxy(130,425,"T");
   outtextxy(605,130,"m");
   outtextxy(310,400,"a");
   outtextxy(490,35,"B");
   outtextxy(580,310,"o");
   outtextxy(190,310,"n");
   outtextxy(310,95,"G");
   outtextxy(340,250,"e");
   outtextxy(490,190,"e");
   outtextxy(130,190,"e");
   outtextxy(430,370,"h");
   settextstyle(0,0,1);
}

void Begin_2(void){

   //Cyan
   setcolor(11);
   setfillstyle(SOLID_FILL,colorC);
   bar3d(60,200,90,240,10,1);  // B
   floodfill(65,199,11);
   floodfill(95,230,11);
   bar3d(340,200,370,240,10,1);  // G
   floodfill(345,199,11);
   floodfill(375,230,11);
   bar3d(230,140,260,180,10,1); // T
   floodfill(235,139,11);
   floodfill(265,170,11);

   //Red
   setcolor(12);
   setfillstyle(SOLID_FILL,colorR);
   bar3d(120,210,150,240,10,1); // O
   floodfill(125,209,12);
   floodfill(155,230,12);
   bar3d(180,210,210,240,10,1); // N
   floodfill(185,209,12);
   floodfill(215,230,12);
   bar3d(310,150,340,180,10,1); // H
   floodfill(315,149,12);
   floodfill(345,170,12);
   bar3d(400,210,430,240,10,1); // A
   floodfill(405,209,12);
   floodfill(435,230,12);
   bar3d(460,210,490,240,10,1); // M
   floodfill(465,209,12);
   floodfill(495,230,12);

   //Green
   setcolor(colorLG);
   setfillstyle(SOLID_FILL,colorG);
   bar3d(520,210,550,240,10,1); // E3
   floodfill(525,209,10);
   floodfill(555,230,10);
   bar3d(240,210,270,240,10,1); // E2
   floodfill(245,209,10);
   floodfill(275,220,10);
   bar3d(390,150,420,180,10,1); // E1
   floodfill(395,149,10);
   floodfill(425,170,10);

   // Vuvod texta#2
   setcolor(colorW);
   settextstyle(0,0,2);
   outtextxy(240,160,"T");
   outtextxy(470,220,"m");
   outtextxy(410,220,"a");
   outtextxy(70,220,"B");
   outtextxy(130,220,"o");
   outtextxy(190,220,"n");
   outtextxy(350,220,"G");
   outtextxy(250,220,"e");
   outtextxy(530,220,"e");
   outtextxy(400,160,"e");
   outtextxy(320,160,"h");
   settextstyle(0,0,1);
}

void Button(int x1,int y1, int x2, int y2, int color, const char *text){
   setfillstyle(SOLID_FILL,color);
   bar3d(x1,y1,x2,y2,0,1);
   outtextxy(x1+12,y1+7,text);
}

void Shadow_Button(int x1,int y1, int x2, int y2){
   setfillstyle(SOLID_FILL,BLACK);
   bar(x1,y1,x2,y2);
}

void Graphics_Fon(void) {

   randomize();
   setcolor(colorLG);
   setfillstyle(SOLID_FILL,colorG);
   //Square_right_up
   bar3d(60,30,120,90,10,1);
   floodfill(65,29,colorLG);
   floodfill(125,80,colorLG);

   //Square_riht_down
   bar3d(60,390,120,450,10,1);
   floodfill(65,389,colorLG);
   floodfill(125,440,colorLG);

   //Square_left_down
   bar3d(540,390,600,450,10,1);
   floodfill(545,389,colorLG);
   floodfill(605,440,colorLG);

   //Square_left_up
   bar3d(540,30,600,90,10,1);
   floodfill(545,29,colorLG);
   floodfill(605,80,colorLG);

   setcolor(colorLB);
   setfillstyle(SOLID_FILL,colorB);
   //Square_left_midle_down
   bar3d(180,390,240,450,10,1);
   floodfill(185,389,colorLB);
   floodfill(245,440,colorLB);

   //Square_right_midle_down
   bar3d(420,390,480,450,10,1);
   floodfill(425,389,colorLB);
   floodfill(485,440,colorLB);

   //Square_left_midle_up
   bar3d(420,30,480,90,10,1);
   floodfill(425,29,colorLB);
   floodfill(485,80,colorLB);

   //Square_left_midle_up
   bar3d(180,30,240,90,10,1);
   floodfill(185,29,colorLB);
   floodfill(245,80,colorLB);

   setcolor(colorM);
   setfillstyle(SOLID_FILL,colorM);

   //Triangle_right_up
   line(120,180,60,210);
   line(60,210,60,150);
   line(60,150,120,180);
   floodfill(90,180,colorM);

   //Triangle_right_down
   line(120,300,60,270);
   line(60,270,60,330);
   line(60,330,120,300);
   floodfill(90,300,colorM);

   //Triangle_midle_down
   line(330,450,300,390);
   line(300,390,360,390);
   line(360,390,330,450);
   floodfill(330,420,colorM);

   //Triangle_left_down
   line(540,300,600,270);
   line(600,270,600,330);
   line(600,330,540,300);
   floodfill(570,300,colorM);

   //Triangle_left_up
   line(540,180,600,150);
   line(600,150,600,210);
   line(600,210,540,180);
   floodfill(570,180,colorM);

   //Triangle_left_midle_up
   line(330,30,360,90);
   line(360,90,300,90);
   line(300,90,330,30);
   floodfill(330,60,colorM);

   //Square_for_menu
   setcolor(colorW);
   setfillstyle(SOLID_FILL,DARKGRAY);
   bar3d(210,100,450,320,0,1);

}

void Graphics_Submenu(void) {

   setcolor(colorW);
   setfillstyle(SOLID_FILL,DARKGRAY);
   bar3d(163,120,495,300,0,1);
}
void Countdown_C4(void){
   int counter=0;

   do{
      cleardevice();
      setfillstyle(SOLID_FILL,BROWN);
      bar(120,80,540,380);
      setcolor(BLACK);
      line(120,180,540,180);
      line(120,290,540,290);
      setcolor(colorR);
      line(530,140,510,140);
      line(530,240,510,240);
      line(530,340,510,340);
      line(510,140,510,370);
      line(510,370,435,370);
      line(435,370,435,360);
      setfillstyle(SOLID_FILL,DARKGRAY);
      bar(530,130,540,160);
      bar(530,230,540,260);
      bar(530,330,540,360);
      bar(420,350,450,360);
      bar(185,110,205,120);
      bar(195,350,225,360);
      setcolor(colorG);
      line(195,110,195,95);
      line(195,95,150,95);
      line(150,95,150,370);
      line(150,370,210,370);
      line(210,370,210,360);
      setfillstyle(SOLID_FILL,colorG);
      bar(180,120,480,350);
      setcolor(colorLG);
      setfillstyle(SOLID_FILL,BLACK);
      bar(190,130,470,180);
      setfillstyle(SOLID_FILL,colorW);
      bar(190,230,470,340);
      setcolor(BLACK);
      line(290,230,290,340);
      line(360,230,360,340);
      line(190,265,470,265);
      line(190,305,470,305);
      settextstyle(0,0,3);
      outtextxy(230,235,"1");
      outtextxy(315,235,"2");
      outtextxy(405,235,"3");
      outtextxy(230,275,"4");
      outtextxy(315,275,"5");
      outtextxy(405,275,"6");
      outtextxy(230,315,"7");
      outtextxy(315,315,"8");
      outtextxy(405,315,"9");
      settextstyle(0,0,6);
      setcolor(colorR);
      if(counter==0) outtextxy(430,135,"3");
      delay(550);
      if(counter==1) outtextxy(430,135,"2");
      delay(600);
      if(counter==2) outtextxy(430,135,"1");
      delay(600);
      settextstyle(0,0,1);
      setcolor(colorW);
      counter++;
   }while(counter!=3);
   if(counter==3) counter=0;
   cleardevice();
   setbkcolor(YELLOW);
   settextstyle(0,0,999);
   setcolor(colorR);
   outtextxy(250,240,"BOOM");
   delay(800);
   setbkcolor(colorR);
   setcolor(YELLOW);
   outtextxy(250,240,"BOOM");
   delay(800);
   settextstyle(0,0,1);
   setbkcolor(BLACK);
}

void Head_Machine_On(void){
   //Head_Machine_On
   cleardevice();
   setcolor(WHITE);
   outtextxy(120,70,"TRY YOUR LUCK AGAIN!");
   setcolor(WHITE);
   setfillstyle(SOLID_FILL,DARKGRAY);
   bar(120,80,540,410); //Head_Our_Machine
   setfillstyle(SOLID_FILL,LIGHTBLUE);
   bar3d(180,110,240,170,0,1); //Left eye
   bar3d(420,110,480,170,0,1); //Right eye
   bar3d(300,200,360,260,0,1); //Nose
   setfillstyle(SOLID_FILL,BLACK);
   setcolor(BLACK);
   fillellipse(210,140,20,25); //Left pupi
   fillellipse(450,140,20,25); //Right pupi
   setcolor(WHITE);
   setfillstyle(SOLID_FILL,LIGHTGRAY);
   bar3d(180,110,240,120,0,1); //Right eyelid
   bar3d(420,110,480,120,0,1); //Left eyelid

   settextstyle(0,0,2);
   bar3d(180,420,300,440,0,1);
   outtextxy(210,425,"RETRY");
   bar3d(360,420,480,440,0,1);
   outtextxy(390,425,"EXIT");
   settextstyle(0,0,2);
}

/*--------------------------- Game mode number 1 -----------------------------*/

void Game_Mode_1(void){

   int counter_gmode1=0,counter_win_mode1=0,counter_loss_mode1=0;
   clrscr();
   cleardevice();

   printf("\t\t\t     Enter your balance: ");
   scanf("%d",&balance);

   while(balance<=0){
      printf("\t\t     Error, balance can not be less than 1\n");
      printf("\t\t\t     Enter your balance: ");
      scanf("%d",&balance);
   }

   while(!Button_Click(360,420,480,440) && balance>0){
      again_mod_1:
      clrscr();
      cleardevice();
      printf("\t\t\tPlease, enter the number from 1 to 6: ");
      scanf("%d",&mode1);
      while((mode1<1) || (mode1>6)){
	 clrscr();
	 cleardevice();
	 printf("\t\t\tError, wrong input!\n");
	 printf("\t\t\tPlease, enter the number from 1 to 6: ");
	 scanf("%d",&mode1);
      }

      /*The countdown is taking place*/
      Countdown_C4();

      /* the head of our gaming machine, the state is on */
      Head_Machine_On(); //Process function Head_Machine_On

      settextstyle(0,0,2);
      switch(Random1=random(6)+1){
	 case 1: outtextxy(205,135,"1"); break;
	 case 2: outtextxy(205,135,"2"); break;
	 case 3: outtextxy(205,135,"3"); break;
	 case 4: outtextxy(205,135,"4"); break;
	 case 5: outtextxy(205,135,"5"); break;
	 case 6: outtextxy(205,135,"6"); break;
      }
      switch(Random2=random(6)+1){
	 case 1: outtextxy(445,135,"1"); break;
	 case 2: outtextxy(445,135,"2"); break;
	 case 3: outtextxy(445,135,"3"); break;
	 case 4: outtextxy(445,135,"4"); break;
	 case 5: outtextxy(445,135,"5"); break;
	 case 6: outtextxy(445,135,"6"); break;
      }
      switch(Random3=random(6)+1){
	 case 1: outtextxy(325,220,"1"); break;
	 case 2: outtextxy(325,220,"2"); break;
	 case 3: outtextxy(325,220,"3"); break;
	 case 4: outtextxy(325,220,"4"); break;
	 case 5: outtextxy(325,220,"5"); break;
	 case 6: outtextxy(325,220,"6"); break;
      }
      settextstyle(0,0,1);
      if(mode1==Random1 || mode1==Random2 || mode1==Random3){
	 printf("\t\t\t        Your number is: %d",mode1);

	 /* Change the mouth of our machine when we won */
	 setfillstyle(SOLID_FILL,colorG);
	 bar(200,290,460,380);

	 //Teeth
	 setfillstyle(SOLID_FILL,colorW);
	 bar(200,290,270,315); //Tooth_up_left
	 bar(200,355,270,380); //Tooth_down_left
	 bar(270,290,330,315); //Tooth_up_middle_left
	 bar(270,355,330,380); //Tootch_down_middle_left
	 bar(330,290,390,315); //Tootch_up_middle_right
	 bar(330,355,390,380); //Tootch_down_middle_right
	 bar(390,290,460,315); //Tootch_up_right
	 bar(390,355,460,380); //Tootch_down_right
	 setcolor(BLACK);
	 line(270,290,270,315); //Line_up_left
	 line(270,355,270,380); //Line_down_left
	 line(330,290,330,315); //Line_up_middle_left
	 line(330,355,330,380); //Line_down_middle_left
	 line(390,290,390,315); //Line_up_middle_right
	 line(390,355,390,380); //Line_down_middle_right
	 setcolor(WHITE);
	 outtextxy(290,325,"You won! :)");
	 outtextxy(230,335,"You quessed the number(s)!");

	 balance+=150;
	 counter_win_mode1++;

	 printf("\rBalance-score: %d",balance);
	 counter_gmode1++;

	 while(!Button_Click(180,420,300,440) || !Button_Click(360,420,480,440)){

	    Mouse_Regs();

	    if(Button_Aiming(180,420,300,440)){
	       setfillstyle(SOLID_FILL,LIGHTBLUE);
	       bar3d(180,420,300,440,0,1);
	       outtextxy(210,425,"RETRY");
	    }
	    if(Button_Aiming(360,420,480,440)){
	       setfillstyle(SOLID_FILL,LIGHTBLUE);
	       bar3d(360,420,480,440,0,1);
	       outtextxy(390,425,"EXIT");
	    }
	    if(!Button_Aiming(180,420,300,440)){
	       setfillstyle(SOLID_FILL,LIGHTGRAY);
	       bar3d(180,420,300,440,0,1);
	       outtextxy(210,425,"RETRY");
	    }
	    if(!Button_Aiming(360,420,480,440)){
	       setfillstyle(SOLID_FILL,LIGHTGRAY);
	       bar3d(360,420,480,440,0,1);
	       outtextxy(390,425,"EXIT");
	    }
	    //If button retry
	    if(Button_Click(180,420,300,440)){
	       goto again_mod_1;
	    }
	    //If button exit
	    if(Button_Click(360,420,480,440)){
	       break;
	    }
	 }
      }
      else{
	 printf("\t\t\t       Your number is: %d",mode1);

	 /* Change the mouth of our machine when we lose */
	 setfillstyle(SOLID_FILL,colorR);
	 bar(200,290,460,380);

	 //Teech
	 setfillstyle(SOLID_FILL,colorW);
	 bar(200,290,270,315); //Tooth_up_left
	 bar(200,355,270,380); //Tooth_down_left
	 bar(270,290,330,315); //Tooth_up_middle_left
	 bar(270,355,330,380); //Tootch_down_middle_left
	 bar(330,290,390,315); //Tootch_up_middle_right
	 bar(330,355,390,380); //Tootch_down_middle_right
	 bar(390,290,460,315); //Tootch_up_right
	 bar(390,355,460,380); //Tootch_down_right
	 setcolor(BLACK);
	 line(270,290,270,315); //Line_up_left
	 line(270,355,270,380); //Line_down_left
	 line(330,290,330,315); //Line_up_middle_left
	 line(330,355,330,380); //Line_down_middle_left
	 line(390,290,390,315); //Line_up_middle_right
	 line(390,355,390,380); //Line_down_middle_right
	 setcolor(colorW);
	 outtextxy(290,325,"You lose :(");
	 outtextxy(215,335,"You didn't quess the number(s)!");

	 balance-=30;
	 counter_loss_mode1++;

	 printf("\rBalance-score: %d",balance);
	 counter_gmode1++;

	 while(!Button_Click(180,420,300,440) || !Button_Click(360,420,480,440)){

	    Mouse_Regs();

	    if(Button_Aiming(180,420,300,440)){
	       setfillstyle(SOLID_FILL,LIGHTBLUE);
	       bar3d(180,420,300,440,0,1);
	       outtextxy(210,425,"RETRY");
	    }
	    if(Button_Aiming(360,420,480,440)){
	       setfillstyle(SOLID_FILL,LIGHTBLUE);
	       bar3d(360,420,480,440,0,1);
	       outtextxy(390,425,"EXIT");
	    }
	    if(!Button_Aiming(180,420,300,440)){
	       setfillstyle(SOLID_FILL,LIGHTGRAY);
	       bar3d(180,420,300,440,0,1);
	       outtextxy(210,425,"RETRY");
	    }
	    if(!Button_Aiming(360,420,480,440)){
	       setfillstyle(SOLID_FILL,LIGHTGRAY);
	       bar3d(360,420,480,440,0,1);
	       outtextxy(390,425,"EXIT");
	    }
	    //If button retry
	    if(Button_Click(180,420,300,440) && balance<=0) {
	       clrscr();
	       cleardevice();
	       printf("\n\n\n\n\n\n\n\n\t      Error,The balance amount can not be let than zero!");
	       delay(2000);
	       goto info_mode_1;
	    }
	    if(Button_Click(180,420,300,440) && balance!=0){
	       goto again_mod_1;
	    }
	    //If button exit
	    if(Button_Click(360,420,480,440)){
	       break;
	    }
	 }
      }
   }
      info_mode_1:
      clrscr();
      cleardevice();
      printf("\n\n\n\n\n\n\n\n\t\t\t       You played %d times\n\n\n",counter_gmode1);
      printf("\t\t\t       Balance-score: %d\n\n\n",balance);
      printf("\t\t\t        Numver of wins %d\n\n\n",counter_win_mode1);
      printf("\t\t\t       Number of losses %d\n\n\n",counter_loss_mode1);
      printf("\t\t\t            Goodbye!\n\n\n");

      setfillstyle(SOLID_FILL,LIGHTGRAY);
      settextstyle(0,0,2);
      outtextxy(60,60,"Information about the game played");
      bar3d(250,340,390,360,0,1);
      outtextxy(260,343,"continue");

      while(!Button_Click(250,340,390,360)){
	 Mouse_Regs();

	 if(Button_Aiming(240,340,390,360)){
	    setfillstyle(SOLID_FILL,LIGHTBLUE);
	    bar3d(250,340,390,360,0,1);
	    outtextxy(260,343,"continue");
	 }
	 else{
	    setfillstyle(SOLID_FILL,LIGHTGRAY);
	    bar3d(250,340,390,360,0,1);
	    outtextxy(260,343,"continue");
	 }
	 if(Button_Click(240,340,390,360)){
	    break;
	 }
      }
      settextstyle(0,0,1);
}

/*--------------------------- Game mode number 2 ---------------------------*/

void Game_Mode_2(void){

   int counter_gmode2=0,counter_win_mode2=0,counter_loss_mode2=0;
   clrscr();
   cleardevice();

   printf("\t\t\t     Enter your balance: ");
   scanf("%d",&balance);

   while(balance<=0){
      printf("\t\t     Error, balance can not be less than 1\n");
      printf("\t\t\t     Enter your balance: ");
      scanf("%d",&balance);
   }

   while(!Button_Click(360,420,480,440) && balance>0){
      again_mod_2:
      clrscr();
      cleardevice();
      printf("\t\t\tPlease, enter the number #1 from 1 to 6: ");
      scanf("%d",&mode1);
      printf("\t\t\tPlease, enter the number #2 from 1 to 6: ");
      scanf("%d",&mode2);

      while((mode1<1) || (mode1>6) || (mode2<1) || (mode2>6)){
	 clrscr();
	 cleardevice();
	 printf("\t\t\tError, wrong input!\n");
	 printf("\t\t\tPlease, enter the number #1 from 1 to 6: ");
	 scanf("%d",&mode1);
	 printf("\t\t\tPlease, enter the number #2 from 1 to 6: ");
	 scanf("%d",&mode2);
      }

      /*The countdown is taking place*/
      Countdown_C4();

      /* the head of our gaming machine, the state is on */
      Head_Machine_On(); //Process function Head_Machine_On

      settextstyle(0,0,2);
      switch(Random1=random(6)+1){
	 case 1: outtextxy(205,145,"1"); break;
	 case 2: outtextxy(205,145,"2"); break;
	 case 3: outtextxy(205,145,"3"); break;
	 case 4: outtextxy(205,145,"4"); break;
	 case 5: outtextxy(205,145,"5"); break;
	 case 6: outtextxy(205,145,"6"); break;
      }
      switch(Random2=random(6)+1){
	 case 1: outtextxy(445,145,"1"); break;
	 case 2: outtextxy(445,145,"2"); break;
	 case 3: outtextxy(445,145,"3"); break;
	 case 4: outtextxy(445,145,"4"); break;
	 case 5: outtextxy(445,145,"5"); break;
	 case 6: outtextxy(445,145,"6"); break;
      }
      switch(Random3=random(6)+1){
	 case 1: outtextxy(325,230,"1"); break;
	 case 2: outtextxy(325,230,"2"); break;
	 case 3: outtextxy(325,230,"3"); break;
	 case 4: outtextxy(325,230,"4"); break;
	 case 5: outtextxy(325,230,"5"); break;
	 case 6: outtextxy(325,230,"6"); break;
      }

      settextstyle(0,0,1);
      if(mode1==Random1 || mode1==Random2 || mode1==Random3 ||
	 mode2==Random1 || mode2==Random2 || mode2==Random3){

	 printf("\t\t\t     Your number is: %d, %d",mode1,mode2);

	 /* Change the moutn of our machine  when we won */
	 setfillstyle(SOLID_FILL,colorG);
	 bar(200,290,460,380);

	 //Teeth
	 setfillstyle(SOLID_FILL,colorW);
	 bar(200,290,270,315); //Tooth_up_left
	 bar(200,355,270,380); //Tooth_down_left
	 bar(270,290,330,315); //Tooth_up_middle_left
	 bar(270,355,330,380); //Tootch_down_middle_left
	 bar(330,290,390,315); //Tootch_up_middle_right
	 bar(330,355,390,380); //Tootch_down_middle_right
	 bar(390,290,460,315); //Tootch_up_right
	 bar(390,355,460,380); //Tootch_down_right
	 setcolor(BLACK);
	 line(270,290,270,315); //Line_up_left
	 line(270,355,270,380); //Line_down_left
	 line(330,290,330,315); //Line_up_middle_left
	 line(330,355,330,380); //Line_down_middle_left
	 line(390,290,390,315); //Line_up_middle_right
	 line(390,355,390,380); //Line_down_middle_right
	 setcolor(WHITE);
	 outtextxy(290,325,"You won! :)");
	 outtextxy(230,335,"You quessed the number(s)!");

	 balance+=150;
	 counter_win_mode2++;

	 printf("\rBalance-score: %d",balance);
	 counter_gmode2++;

	 while(!Button_Click(180,420,300,440) || !Button_Click(360,420,480,440)){

	    Mouse_Regs();

	    if(Button_Aiming(180,420,300,440)){
	       setfillstyle(SOLID_FILL,LIGHTBLUE);
	       bar3d(180,420,300,440,0,1);
	       outtextxy(210,425,"RETRY");
	    }
	    if(Button_Aiming(360,420,480,440)){
	       setfillstyle(SOLID_FILL,LIGHTBLUE);
	       bar3d(360,420,480,440,0,1);
	       outtextxy(390,425,"EXIT");
	    }
	    if(!Button_Aiming(180,420,300,440)){
	       setfillstyle(SOLID_FILL,LIGHTGRAY);
	       bar3d(180,420,300,440,0,1);
	       outtextxy(210,425,"RETRY");
	    }
	    if(!Button_Aiming(360,420,480,440)){
	       setfillstyle(SOLID_FILL,LIGHTGRAY);
	       bar3d(360,420,480,440,0,1);
	       outtextxy(390,425,"EXIT");
	    }
	    //If button retry
	    if(Button_Click(180,420,300,440)){
	       goto again_mod_2;
	    }
	    //If button exit
	    if(Button_Click(360,420,480,440)){
	       break;
	    }
	 }
      }
      else{
	 printf("\t\t\t     Your number is: %d, %d",mode1,mode2);

	 /* Change the moutn of our machine when we lose */
	 setfillstyle(SOLID_FILL,colorR);
	 bar(200,290,460,380);

	 //Teech
	 setfillstyle(SOLID_FILL,colorW);
	 bar(200,290,270,315); //Tooth_up_left
	 bar(200,355,270,380); //Tooth_down_left
	 bar(270,290,330,315); //Tooth_up_middle_left
	 bar(270,355,330,380); //Tootch_down_middle_left
	 bar(330,290,390,315); //Tootch_up_middle_right
	 bar(330,355,390,380); //Tootch_down_middle_right
	 bar(390,290,460,315); //Tootch_up_right
	 bar(390,355,460,380); //Tootch_down_right
	 setcolor(BLACK);
	 line(270,290,270,315); //Line_up_left
	 line(270,355,270,380); //Line_down_left
	 line(330,290,330,315); //Line_up_middle_left
	 line(330,355,330,380); //Line_down_middle_left
	 line(390,290,390,315); //Line_up_middle_right
	 line(390,355,390,380); //Line_down_middle_right
	 setcolor(colorW);
	 outtextxy(290,325,"You lose :(");
	 outtextxy(215,335,"You didn't quess the number(s)!");

	 balance-=30;
	 counter_loss_mode2++;

	 printf("\rBalance-score: %d",balance);
	 counter_gmode2++;

	 while(!Button_Click(180,420,300,440) || !Button_Click(360,420,480,440)){

	    Mouse_Regs();

	    if(Button_Aiming(180,420,300,440)){
	       setfillstyle(SOLID_FILL,LIGHTBLUE);
	       bar3d(180,420,300,440,0,1);
	       outtextxy(210,425,"RETRY");
	    }
	    if(Button_Aiming(360,420,480,440)){
	       setfillstyle(SOLID_FILL,LIGHTBLUE);
	       bar3d(360,420,480,440,0,1);
	       outtextxy(390,425,"EXIT");
	    }
	    if(!Button_Aiming(180,420,300,440)){
	       setfillstyle(SOLID_FILL,LIGHTGRAY);
	       bar3d(180,420,300,440,0,1);
	       outtextxy(210,425,"RETRY");
	    }
	    if(!Button_Aiming(360,420,480,440)){
	       setfillstyle(SOLID_FILL,LIGHTGRAY);
	       bar3d(360,420,480,440,0,1);
	       outtextxy(390,425,"EXIT");
	    }
	    //If button retry
	    if(Button_Click(180,420,300,440) && balance<=0) {
	       clrscr();
	       cleardevice();
	       printf("\n\n\n\n\n\n\n\n\t       Error,The balance amount can not be let than zero!");
	       delay(2000);
	       goto info_mode_2;
	    }
	    if(Button_Click(180,420,300,440) && balance!=0){
	       goto again_mod_2;
	    }
	    //If button exit
	    if(Button_Click(360,420,480,440)){
	       break;
	    }
	 }
      }
   }
   info_mode_2:
   clrscr();
   cleardevice();
   printf("\n\n\n\n\n\n\n\n\t\t\t       You played %d times\n\n\n",counter_gmode2);
   printf("\t\t\t       Balance-score: %d\n\n\n",balance);
   printf("\t\t\t        Numver of wins %d\n\n\n",counter_win_mode2);
   printf("\t\t\t       Number of losses %d\n\n\n",counter_loss_mode2);
   printf("\t\t\t            Goodbye!\n\n\n");

   setfillstyle(SOLID_FILL,LIGHTGRAY);
   settextstyle(0,0,2);
   outtextxy(60,60,"Information about the game played");
   bar3d(250,340,390,360,0,1);
   outtextxy(260,343,"continue");

   while(!Button_Click(250,340,390,360)){

      Mouse_Regs();

      if(Button_Aiming(240,340,390,360)){
	 setfillstyle(SOLID_FILL,LIGHTBLUE);
	 bar3d(250,340,390,360,0,1);
	 outtextxy(260,343,"continue");
      }
      else{
	 setfillstyle(SOLID_FILL,LIGHTGRAY);
	 bar3d(250,340,390,360,0,1);
	 outtextxy(260,343,"continue");
      }
      if(Button_Click(240,340,390,360)){
	 break;
      }
   }
   settextstyle(0,0,1);
}

void Loading(void){
    int i,j,x1,x2,y1,y2,x3,x4,x5,x6;
    int count=0;
    int xl1=230;
    int xl2=405;

    do{
       x1=-30;x2=-10;
       x3=-60;x4=-40;
       x5=-90;x6=-70;

       for(i=1;i<50;i++){
	  xl1+=10;xl2-=10;
	  x1+=i;x2+=i;
	  x3+=i;x4+=i;
	  x5+=i;x6+=i;
	  delay(30);
	  cleardevice();
	  rectangle(0,403,640,408);
	  rectangle(0,433,640,437);
	  setcolor(colorW);
	  setfillstyle(SOLID_FILL,colorG);
	  bar3d(x1,410,x2,430,0,1);
	  bar3d(x3,410,x4,430,0,1);
	  bar3d(x5,410,x6,430,0,1);

	  //logo
	  circle(320,240,100);
	  line(xl1,190,321,341);
	  line(xl2,190,321,341);
	  line(xl1,190,321,231);
	  line(xl2,190,321,231);


	  line(xl1,290,321,141);
	  line(xl2,290,321,141);
	  line(xl1,290,321,251);
	  line(xl2,290,321,251);

	  settextstyle(1,0,3);
	  if(i<10){
	     outtextxy(270,360,"LOADING");
	  }
	  else if(i<20){
	     outtextxy(270,360,"LOADING.");
	  }
	  else if(i<30){
	     outtextxy(270,360,"LOADING..");
	  }
	  else outtextxy(270,360,"LOADING...");

	  if(xl1>=405 || xl2<=230){
	   xl1=230; xl2=405;
	  }
       }
       settextstyle(0,0,1);
       count++;
    }while(count!=3);
}

int Mouse_Regs(void){
   regs.x.ax=1;
   int86(0x33,&regs,&regs);
   regs.x.ax=3;
   int86(0x33,&regs,&regs);

   delay(30);
   regs.x.ax=2;
   int86(0x33,&regs,&regs);
}

int Button_Click(int x,int y, int w, int h){
   int mx,my;

   mx=regs.x.cx;
   my=regs.x.dx;
   if(mx>x && mx<w && my>y && my<h && regs.x.bx==1) return 1;
   return 0;
}

int Button_Aiming(int x,int y,int w,int h){
   int mx,my;

   mx=regs.x.cx;
   my=regs.x.dx;
   if(mx>x && mx<w && my>y && my<h) return 1;
   return 0;

}
