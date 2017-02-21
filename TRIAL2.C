#include<conio.h>
#include<stdio.h>
#include "assembly.h"
#include "figures.h"
#include "mouse.h"
#include "tools.h"
#include "bmp.h"
#define v800x600x256     0x103

#define STARTWIDTH 129
#define STARTHEIGHT 112
#define MAXWIDTH 800
#define MAXHEIGHT 600
#define SELECTED 15
#define SELECTEDCOLOR1 -2
#define SELECTEDCOLOR2 -126
#define FONDO 62

#define BLACK 0
#define GREY  -92
#define BROWN 1
#define RED 79
#define ORANGE 103
#define YELLOW -5
#define GREEN 113
#define SKYBLUE -24
#define BLUE -46
#define PURPLE -43
#define DARKRED 68
#define LIGHTBROWN 102
#define PINK -17
#define ORANGE2 55
#define RED2 15
#define SKYBLUE2 9
#define SKYBLUE3 -20
#define STRONGPINK -121
#define PURPLE2 66
#define GREEN2 16
#define BLUE2 -112
#define PATTERN1 1
#define PATTERN2 2

#define CLOSE 0
#define CIRCLE 1
#define FILLCIRCLE 2
#define RECTANGLE 3
#define FILLRECTANGLE 4
#define POLYGON 5
#define FILLPOLYGON 6
#define LINE 7
#define LETTER 8

#define PENCIL 9
#define SPRAY 10
#define BUCKET 11
#define GETCOLOR 12
#define ERRASER 13
#define SELECT 14
#define PASTE 15

#define NORMAL 1
#define MEDIUM 3
#define LARGE 5



void changeColor(int opColor, int *opColor1[], int *opColor2[], int color, int *color1, int *color2, int x1, int y1, int x2, int y2){
  int x,y,b;
  if(opColor ==1){
    getMouse(&x, &y, &b);
    hideMouse(x,y);
    rectangle((int)opColor1[0],(int)opColor1[1],(int)opColor1[2],(int)opColor1[3], FONDO,3);
    *color1 = color;
    opColor1[0]=x1;
    opColor1[1]=y1;
    opColor1[2]=x2;
    opColor1[3]=y2;
    rectangle((int)opColor1[0],(int)opColor1[1],(int)opColor1[2],(int)opColor1[3], SELECTEDCOLOR1,3);
    showMouse(x,y);
  }else{
    getMouse(&x, &y, &b);
    hideMouse(x,y);
    rectangle((int)opColor2[0],(int)opColor2[1],(int)opColor2[2],(int)opColor2[3], FONDO,3);
    *color2 = color;
    opColor2[0]=x1;
    opColor2[1]=y1;
    opColor2[2]=x2;
    opColor2[3]=y2;
    rectangle((int)opColor2[0],(int)opColor2[1],(int)opColor2[2],(int)opColor2[3], SELECTEDCOLOR2,3);
    showMouse(x,y);
  }
}

void changeOption(int *opSelected[], int *opcion, int op, int x1, int y1, int x2, int y2){
  int x,y,b;
  getMouse(&x, &y, &b);
  hideMouse(x,y);
  rectangle((int)opSelected[0],(int)opSelected[1],(int)opSelected[2],(int)opSelected[3], FONDO,3);
  *opcion = op;
  opSelected[0]=x1;
  opSelected[1]=y1;
  opSelected[2]=x2;
  opSelected[3]=y2;
  rectangle((int)opSelected[0],(int)opSelected[1],(int)opSelected[2],(int)opSelected[3], SELECTED,3);
  showMouse(x,y);
}
void main(void){
  int i,j, color, x,y ,x0,y0, tempx,tempy , b,cont, xc,yc, opcion;
  int opColor = 1;
  int color1 = BLACK;
  int color2 = BLACK;
  int opSelected[4] = {10,280,40,310};
  int opColor1[4] = {300,5,342,45};
  int opColor2[4] = {5,310,45,342};
  int thickSelected[4] = {13,322,112,333};
  int writeSelected[4] = {117,3,157,45};
  int thick =NORMAL;
  int selected = 0;
  int selectedCoordinates[4] ={0,0,0,0};
  int opWrite;
  int opPattern = 0;
  int WHITE = -1;
  int a[20][2];
  char ch;
  FILE *f;
  BITMAP bmp;

  if( !setVideoSVGA(v800x600x256, 800, 600)){
      printf("\r\nError inicializacion de SVGA.\r\n");
      return;
  }
  openBMP(0, 0, "fondo.bmp", &bmp);
  rectangle(opColor1[0],opColor1[1],opColor1[2],opColor1[3], SELECTEDCOLOR1,3);
  rectangle(thickSelected[0],thickSelected[1],thickSelected[2],thickSelected[3], SELECTED,3);
  rectangle(2,140,90,165,SELECTED,3);
  setMouse();
  setBoundariesMouse(790, 590);
  getMouse(&x, &y, &b);
  do {
    refreshMouse(&x, &y, &b, &tempx, &tempy);
    //COLOR1
    if(y>=145 && y<=163 && x>=6 && x<=90 && b == 1){
      if(opColor == 2){
        hideMouse(x,y);
        rectangle(2,170,90,195,FONDO,3);
        rectangle(2,140,90,165,SELECTED,3);
        opColor = 1;
        showMouse(x,y);
      }
    }
    //COLOR2
    if(y>=175 && y<=193 && x>=6 && x<=90 && b == 1){
      if(opColor == 1){
        hideMouse(x,y);
        rectangle(2,140,90,165,FONDO,3);
        rectangle(2,170,90,195,SELECTED,3);
        opColor = 2;
        showMouse(x,y);
      }
    }
    //BLACK
    if(y>=9 && y<=45 && x>=306 && x<=342 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, BLACK,&color1,&color2, 300,5,342,45);
    }
    //GREY
    if(y>=9 && y<=45 && x>=350 && x<=385 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, GREY,&color1,&color2, 345,5,385,45);
    }
    //BROWN
    if(y>=9 && y<=45 && x>=393 && x<=426 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, BROWN,&color1,&color2, 390,5,426,45);
    }
    //RED
    if(y>=9 && y<=45 && x>=438 && x<=471 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, RED,&color1,&color2, 435,5,471,45);
    }
    //ORANGE
    if(y>=9 && y<=45 && x>=479 && x<=514 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, ORANGE,&color1,&color2, 475,5,514,45);
    }
    //YELLOW
    if(y>=9 && y<=45 && x>=523 && x<=556 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, YELLOW,&color1,&color2, 519,5,556,45);
    }
    //GREEN
    if(y>=9 && y<=45 && x>=566 && x<=601 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, GREEN,&color1,&color2, 562,5,601,45);
    }
    //SKYBLUE
    if(y>=9 && y<=45 && x>=613 && x<=646 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, SKYBLUE,&color1,&color2, 610,5,646,45);
    }
    //BLUE
    if(y>=9 && y<=45 && x>=655 && x<=688 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, BLUE,&color1,&color2, 652,5,688,45);
    }
    //PURPLE
    if(y>=9 && y<=45 && x>=697 && x<=732 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, PURPLE,&color1,&color2, 695,5,732,45);
    }
    //DARKRED
    if(y>=9 && y<=45 && x>=742 && x<=775 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, DARKRED,&color1,&color2, 740,5,775,45);
    }
    //WHITE
    if(y>=51 && y<=86 && x>=306 && x<=342 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, WHITE,&color1,&color2, 303,47,342,86);
    }
     //LIGHTBROWN
    if(y>=51 && y<=86 && x>=352 && x<=388 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, LIGHTBROWN,&color1,&color2, 350,47,388,86);
    }
     //PINK
    if(y>=51 && y<=86 && x>=392 && x<=428 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, PINK,&color1,&color2, 390,47,428,86);
    }
     //ORANGE
    if(y>=51 && y<=86 && x>=439 && x<=473 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, ORANGE,&color1,&color2, 435,47,473,86);
    }
     //RED2
    if(y>=51 && y<=86 && x>=481 && x<=516 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, RED2,&color1,&color2,478,47,516,86);
    }
     //SKYBLUE2
    if(y>=51 && y<=86 && x>=523 && x<=557 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, SKYBLUE2,&color1,&color2, 520,47,557,86);
    }
     //SKYBLUE3
    if(y>=51 && y<=86 && x>=566 && x<=602 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, SKYBLUE3,&color1,&color2, 563,47,602,86);
    }
     //STRONGPINK
    if(y>=51 && y<=86 && x>=612 && x<=647 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, STRONGPINK,&color1,&color2, 610,47,647,86);
    }
     //PURPLE2
    if(y>=51 && y<=86 && x>=657 && x<=691 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, PURPLE2,&color1,&color2, 655,47,691,86);
    }
     //GREEN2
    if(y>=51 && y<=86 && x>=698 && x<=735 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, GREEN2,&color1,&color2, 695,47,735,86);
    }
     //BLUE2
    if(y>=51 && y<=86 && x>=743 && x<=776 && b == 1){
      changeColor(opColor, &opColor1, &opColor2, BLUE2,&color1,&color2, 740,47,776,86);
    }
    //PATTERN1
    if(y>=31 && y<=81 && x>=180 && x<=230 && b == 1){
      changeColor(2, &opColor1, &opColor2, PATTERN1,&color1,&opPattern, 177,28,232,83);
    }
    //PATTERN2
    if(y>=31 && y<=81 && x>=241 && x<=291 && b == 1){
      changeColor(2, &opColor1, &opColor2, PATTERN2,&color1,&opPattern, 238,28,292,83);
    }


    //CLOSE
    if(y>=0 && y<=18 && x>=782 && x<=800 && b == 1){
      opcion = CLOSE;
    }
    //CIRCLE
    if(y>=209 && y<=230 && x>=8 && x<=30 && b == 1){
      if(selected){
        undo();
	selected = 0;
      }
      changeOption(&opSelected, &opcion, CIRCLE, 5,205,31,231);
    }
    //FILLCIRCLE
    if(y>=241 && y<=261 && x>=10 && x<=32 && b == 1){
      changeOption(&opSelected, &opcion, FILLCIRCLE, 5,235,32,265);
    }
    //RECTANGLE
    if(y>=210 && y<=232 && x>=55 && x<=76 && b == 1){
      changeOption(&opSelected, &opcion, RECTANGLE, 50,205,78,235);
    }
    //FILLRECTANGLE
    if(y>=238 && y<=262 && x>=55 && x<=79 && b == 1){
      changeOption(&opSelected, &opcion, FILLRECTANGLE, 50,235,80,262);
    }
    //POLYGON
    if(y>=208 && y<=235 && x>=99 && x<=120 && b == 1){
      changeOption(&opSelected, &opcion, POLYGON, 96,205,122,238);
    }
    //FILLPOLYGON
    if(y>=240 && y<=264 && x>=97 && x<=122 && b == 1){
      changeOption(&opSelected, &opcion, FILLPOLYGON, 94,237,122,267);
    }
    //LINE
    if(y>=285 && y<=310 && x>=14 && x<=39 && b == 1){
      changeOption(&opSelected, &opcion, LINE, 11,282,42,313);
    }
    //LETTER
    if(y>=279 && y<=314 && x>=73 && x<=99 && b == 1){
      changeOption(&opSelected, &opcion, LETTER, 70,276,102,317);
    }

    //NORMAL
    if(y>=322 && y<=333 && x>=15 && x<=108 && b == 1){
      changeOption(&thickSelected, &thick, NORMAL, 13,322,112,333);
    }
     //MEDIUM
    if(y>=337 && y<=340 && x>=15 && x<=109 && b == 1){
      changeOption(&thickSelected, &thick, MEDIUM, 13,333,112,342);
    }
     //LARGE
    if(y>=347 && y<=352 && x>=14 && x<=110 && b == 1){
      changeOption(&thickSelected, &thick, LARGE, 13,342,112,354);
    }

     //PENCIL
    if(y>=5 && y<=43 && x>=119 && x<=155 && b == 1){
      changeOption(&opSelected, &opcion, PENCIL, 117,3,157,45);
    }
    //BUCKET
    if(y>=52 && y<=92 && x>=88 && x<=108 && b == 1){
      changeOption(&opSelected, &opcion, BUCKET, 86,50,110,94);
    }
    //SPRAY
    if(y>=6 && y<=45 && x>=86 && x<=107 && b == 1){
      changeOption(&opSelected, &opcion, SPRAY, 84,4,109,47);
    }
    //GETCOLOR
    if(y>=52 && y<=92 && x>=121 && x<=152 && b == 1){
      changeOption(&opSelected, &opcion, GETCOLOR, 119,50,154,94);
    }
    //ERRASER
    if(y>=464 && y<=518 && x>=31 && x<=80 && b == 1){
      changeOption(&opSelected, &opcion, ERRASER, 28,461,83,521);
    };
    //SELECT
    if(y>=534 && y<=575 && x>=22 && x<=106 && b == 1){
      changeOption(&opSelected, &opcion, SELECT, 18,530,108,577);
    }

    //UNDO
    if(y>=414 && y<=449 && x>=63 && x<=101 && b == 1){
      undo();
    }
    //COPY
    if(y>=366 && y<=406 && x>=18 && x<=50 && b == 1){
      if(selected){
        copy(selectedCoordinates[0],selectedCoordinates[1],selectedCoordinates[2],selectedCoordinates[3]);
        undo();
      }
    }
    //paste
    if(y>=365 && y<=408 && x>=68 && x<=98 && b == 1){
      changeOption(&opSelected, &opcion, PASTE, 65,365,99,408);
    }
     //CUT
    if(y>=417 && y<=448 && x>=19 && x<=49 && b == 1){
      if(selected){
        copy(selectedCoordinates[0],selectedCoordinates[1],selectedCoordinates[2],selectedCoordinates[3]);
        fillRectangle(selectedCoordinates[0],selectedCoordinates[1],selectedCoordinates[2],selectedCoordinates[3],-1,-1,1,0);
      }
    }

    //OPEN
    if(y>=44 && y<=67 && x>=36 && x<=60 && b == 1){
      openBMP(STARTWIDTH, STARTHEIGHT, "save.bmp", &bmp);
    }
    //SAVE
    if(y>=4 && y<=34 && x>=3 && x<=33 && b == 1){
      saveImage(STARTWIDTH,STARTHEIGHT, MAXWIDTH - STARTWIDTH,MAXHEIGHT - STARTHEIGHT,"save.bmp");
    }

    //NEW
    if(y>=72 && y<=106 && x>=7 && x<=38 && b == 1){
      fillRectangle(STARTWIDTH,STARTHEIGHT+1,MAXWIDTH,MAXHEIGHT,-1,-1,1,0);
    }
    if( x> STARTWIDTH && y >STARTHEIGHT && b == 1)
      switch(opcion){
        case CIRCLE:
          x0 = x;
          y0 = y;
          getMouse(&x, &y, &b);
          while(b == 1){
              refreshMouse(&x, &y, &b, &tempx, &tempy);
          }
          hideMouse(x, y);
          if((x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT) && x!=x0 && y!=y0){
            saveUndo();
            ellipse(x0+((x-x0)>>1), y0+((y-y0)>>1),abs(x-x0)>>1, abs(y-y0)>>1,color1,thick);
          }
          showMouse(x, y);
        break;
        case FILLCIRCLE:
          x0 = x;
          y0 = y;
          getMouse(&x, &y, &b);
          while(b == 1){
              refreshMouse(&x, &y, &b, &tempx, &tempy);
          }
          hideMouse(x, y);
          if((x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT) && x!=x0 && y!=y0){
            saveUndo();
            fillEllipse(x0+((x-x0)>>1), y0+((y-y0)>>1),abs(x-x0)>>1, abs(y-y0)>>1,color1,color2,thick,opPattern);
          }
          showMouse(x, y);
        break;
        case RECTANGLE:
          x0 = x;
          y0 = y;
          getMouse(&x, &y, &b);
          while(b == 1){
              refreshMouse(&x, &y, &b, &tempx, &tempy);
          }
          hideMouse(x, y);
          if((x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT) && x!=x0 && y!=y0){
            saveUndo();
            rectangle(x0, y0,x0+(x-x0), y0+(y-y0),color1,thick);
          }
          showMouse(x, y);
        break;
        case FILLRECTANGLE:
          x0 = x;
          y0 = y;
          getMouse(&x, &y, &b);
          while(b == 1){
              refreshMouse(&x, &y, &b, &tempx, &tempy);
          }
          hideMouse(x, y);
          if((x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT) && x!=x0 && y!=y0){
            saveUndo();
            fillRectangle(x0, y0,x0+(x-x0), y0+(y-y0),color1,color2,thick,opPattern);
          }
          showMouse(x, y);
        break;
        case POLYGON:
          x0 = x; 
          y0 = y;
          i = x; 
          j = y;
          hideMouse(x, y);
          saveUndo();
          showMouse(x, y);
          while(b!=2){
              refreshMouse(&x, &y, &b, &tempx, &tempy);
              while(b!=1 && b!=2){
                  refreshMouse(&x, &y, &b, &tempx, &tempy);
              }
              if(b==1){
                  if(b==1 && (x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT)){
                      hideMouse(x, y);
                      //delay(300);
                      line(x0, y0, x, y, color1, thick,0);
                      showMouse(x, y);
                  }
              }else{
                  if(b==2 && (x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT)){
                      hideMouse(x, y);
                      //delay(300);
                      line(i, j, x0, y0, color1, thick,0);
                      showMouse(x, y);
                  }
              }
              x0 = x;
              y0 = y;
          }
        break;
        case FILLPOLYGON:
          x0 = x; 
          y0 = y;
          i = x; 
          j = y;
          hideMouse(x, y);
          saveUndo();
          showMouse(x, y);
          a[0][0] = i; 
          a[0][1] = j;
          cont = 1;
          while(b!=2){
              refreshMouse(&x, &y, &b, &tempx, &tempy);
              while(b!=1 && b!=2){
                  refreshMouse(&x, &y, &b, &tempx, &tempy);
              }
              if(b==1){
                  if(b==1 && (x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT)){
                      hideMouse(x, y);
                      a[cont][0] = x; 
                      a[cont][1] = y;
                      delay(300);
                      line(x0, y0, x, y, color1, thick,0);
                      showMouse(x, y);
                      cont++;
                  }
              }else{
                  if(b==2 && (x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT)){
                      hideMouse(x, y);
                      line(i, j, x0, y0, color1, thick,0);
                      a[cont][0] = i; 
                      a[cont][1] = j;
                      delay(300);
                      showMouse(x, y);
                      cont++;
                  }
              }
              x0 = x;
              y0 = y;
          }
          scanLine(a,cont,color1,color2,thick,opPattern);
        break;
        case LINE:
          x0 = x;
          y0 = y;
          getMouse(&x, &y, &b);
          while(b == 1){
              refreshMouse(&x, &y, &b, &tempx, &tempy);
          }
          hideMouse(x, y);
          if((x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT) && x!=x0 && y!=y0){
            saveUndo();
            line(x0, y0,x0+(x-x0), y0+(y-y0),color1,thick,0);
          }
          showMouse(x, y);
        break;
        case LETTER:
        break;
        case PENCIL:
          hideMouse(x, y);
          x0 = x;
          y0 = y;
          getMouse(&x, &y, &b);
          saveUndo();
          while(b==1 && ((x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT))){
              line(x0, y0, x, y, color1, thick,0);
              x0 = x; 
              y0 = y;
              getMouse(&x, &y, &b);
          }
          showMouse(x, y);
        break;
        case SPRAY:
          hideMouse(x, y);
          saveUndo();
          while(b==1 && ((x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT))){
              spray( x, y, color1,thick);
              getMouse(&x, &y, &b);
          }
          //hideMouse(x,y);
          //showMouse(x, y);
        break;
        case BUCKET:
          while(b ==1){
            refreshMouse(&x, &y, &b, &tempx, &tempy);
          }
          hideMouse(x,y);
          saveUndo();
          floodFill(x,y,getPixel(x,y),color1,opPattern);
          getMouse(&x,&y,&b);
          showMouse(x,y);
        break;
        case GETCOLOR:
          hideMouse(x,y);
          while(b ==1){
            getMouse(&x, &y, &b);
            //refreshMouse(&x, &y, &b, &tempx, &tempy);
          }
          WHITE = getPixel(x,y);
          fillRectangle(308,55,338,82,WHITE,WHITE,1,0);
          changeColor(opColor, &opColor1, &opColor2, WHITE,&color1,&color2, 303,47,342,86);
        break;
        case ERRASER:
          hideMouse(x, y);
          x0 = x;
          y0 = y;
          getMouse(&x, &y, &b);
          saveUndo();
          while(b==1 && ((x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT))){
              fillRectangle(x0, y0, x, y, -1,-1, thick,0);
              x0 = x; 
              y0 = y;
              getMouse(&x, &y, &b);
          }
        break;
        case SELECT:
          x0 = x;
          y0 = y;
          getMouse(&x, &y, &b);
          while(b == 1){
              refreshMouse(&x, &y, &b, &tempx, &tempy);
          }
          hideMouse(x, y);
          if((x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT) && x!=x0 && y!=y0){
            saveUndo();
            rectangle(x0, y0,x, y,80,1);
      	    selected = 1;
      	    selectedCoordinates[0]=x0;
      	    selectedCoordinates[1]=y0;
      	    selectedCoordinates[2]=x;
      	    selectedCoordinates[3]=y;
          }
          showMouse(x, y);
        break;
        case PASTE:
          getMouse(&x, &y, &b);
          while(b == 1){
              refreshMouse(&x, &y, &b, &tempx, &tempy);
          }
          hideMouse(x, y);
          if((x > STARTWIDTH && x < MAXWIDTH) && (y > STARTHEIGHT && y < MAXHEIGHT)){
            saveUndo();
            paste(x,y);
          }
          showMouse(x, y);
        break;
      }
    /*if(opcion ==RECTANGLE && b == 1){
      x0 = x;
      y0 = y;
      getMouse(&x, &y, &b);
      while(b == 1){
          refreshMouse(&x, &y, &b, &tempx, &tempy);
      }
      hideMouse(x, y);
      printf("%i", getPixel(x,y));
      showMouse(x, y);
    }*/
    
  }while (!((x > 776 && x < 800) && (y > 0 && y < 24) && b == 1));
  getchar(); /* write the last w just incase it was really cool */
  unSetVideoSVGA();
  printf("%d",ch);
  getch();
                        /* and you want know what value w had */
}
