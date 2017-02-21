#define I   15  //Color de la forma del cursor.
#define X   17  //Color interno del cursor.

/* Variables */
static unsigned char pointer[12*16] =
{
  I,I,0,0,0,0,0,0,0,0,0,0,
  I,I,I,0,0,0,0,0,0,0,0,0,
  I,X,I,I,0,0,0,0,0,0,0,0,
  I,X,X,I,I,0,0,0,0,0,0,0,
  I,X,X,X,I,I,0,0,0,0,0,0,
  I,X,X,X,X,I,I,0,0,0,0,0,
  I,X,X,X,X,X,I,I,0,0,0,0,
  I,X,X,X,X,X,X,I,I,0,0,0,
  I,X,X,X,X,X,X,X,I,I,0,0,
  I,X,X,X,X,X,X,X,X,I,I,0,
  I,X,X,X,X,X,I,I,I,I,I,0,
  I,X,X,I,X,X,X,I,I,0,0,0,
  I,X,I,I,I,X,X,I,I,0,0,0,
  I,I,I,0,I,X,X,X,I,0,0,0,
  I,0,0,0,I,I,X,X,I,0,0,0,
  0,0,0,0,I,I,I,I,I,0,0,0,
};

unsigned int ** mouseBuffer;

/* Funciones */
int getKey();
void setMouse();
void setBoundariesMouse(int x, int y);
void showMouse(int x, int y);
void hideMouse(int x, int y);
void getMouse(int *x, int *y, int *b);
void refreshMouse(int *x, int *y, int *b, int *tempx, int *tempy);
void setCursor(char x, char y);

//---------------------------------------------------------
// Obtiene respuesta del teclado.
//---------------------------------------------------------
int getKey(){
  int key;
  asm{
    MOV AH, 0CH               //Limpia el buffer.
    INT 21H                     
    MOV AH, 00H               //Obtiene resultado de teclado.
    INT 16H                   
    MOV AH, 00H               //Guarda el resultado.
    MOV key, AX
  }
  return key;
}

//---------------------------------------------------------
// Permite la utilización del mouse.
//---------------------------------------------------------
void setMouse(){
  asm{
    MOV AX, 00H                 //Inicializa el mouse.
    INT 33H           
  }
}

//---------------------------------------------------------
// Determina el tamaño de la pantalla para el mouse.
//---------------------------------------------------------
void setBoundariesMouse(int x, int y){
  asm{
    PUSH AX
    PUSH CX
    PUSH DX
    MOV AX,07h
    XOR CX,CX
    MOV DX,SS:[x]
    INT 33h
    MOV AX,08h
    XOR CX,CX
    MOV DX,SS:[y]
    INT  33h
    POP DX
    POP CX
    POP AX
  }
}

//---------------------------------------------------------
// Muestra el mouse en pantalla.
//---------------------------------------------------------
void showMouse(int x, int y){
  int i,j;
  mouseBuffer = (int*) malloc(sizeof(int) * 12);
  for(i=0; i<12; i++){
    mouseBuffer[i] = (int) malloc(sizeof(int) * 16);
    for(j=0; j<16; j++){
      mouseBuffer[i][j] = getPixel(x+i,y+j);
    }
  }

  for(i=0; i<16; i++){
    for(j=0; j<12; j++){
      if(pointer[12*i+j]!=0){
        putPixel(x+j, y+i, pointer[12*i+j],0);
      }
    }
  }
}

//---------------------------------------------------------
// Esconde el mouse de la pantalla.
//---------------------------------------------------------
void hideMouse(int x, int y){
  int i,j;
  for(i=0; i<12;i++){
    for(j=0; j<16;j++){
      putPixel(x+i,y+j,mouseBuffer[i][j],0);
    }
    free(mouseBuffer[i]);
  }
  free(mouseBuffer);
}

//---------------------------------------------------------
// Obtiene el estado del mouse y su pocisión.
//---------------------------------------------------------
void getMouse(int *x0, int *y0, int *b){
  int x, y, button;
  asm{
    MOV AX, 03H                 //Obtiene resultado del mouse.
    INT 33H         
    AND BX, 0000000000000011B
    MOV button, BX              //Guarda resultado.
    MOV x, CX             
    MOV y, DX             
  }
  *x0 = x;
  *y0 = y;
  *b = button;
}

//---------------------------------------------------------
// Refresca el mouse.
//---------------------------------------------------------
void refreshMouse(int *x, int *y, int *b, int *tempx, int *tempy){
  getMouse(x,y,b);
  if(*tempx!=*x || *tempy!=*y){
    hideMouse(*tempx, *tempy);
    showMouse(*x,*y);
    *tempx = *x; *tempy = *y;
  }
}

//---------------------------------------------------------
// Coloca el cursor de texto en la pantalla.
//---------------------------------------------------------
void setCursor(char x, char y){
  asm{
    PUSH AX
    PUSH BX
    PUSH DX
    MOV AH, 02H               //Petición para cursor.
    XOR BX, BX                //Página.
    MOV DH,SS:[y]             //Fila del cursor.
    MOV DL,SS:[x]             //Columna del cursor.
    INT 10H
    POP DX
    POP BX
    POP AX
  }
}