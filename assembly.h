
void putPixel(int x, int y, char color, int pattern);
char getPixel(int x, int y);
long limitX, limitY;
char currentBank;

char getPatternOnePixel(int x, int y){
  return getPixel(181 + x%50, 32 + y%50);
}

char getPatternTwoPixel(int x, int y){
  return getPixel(241 + x%50, 32 + y%50);
}

int setVideoSVGA(int mode, long w, long h){
  long banks;
  banks = ((w*h)/65536L);
  limitX = w-1;
  limitY = h-1;
  asm{
    MOV AX, 4F02H
    MOV BX, [mode]
    INT 10H                     
    CMP AX, 004FH
    JNE Error
  }
  return(1);
  Error:;
  return(0);
}

void unSetVideoSVGA(){
  asm{
    MOV AX, 0003H
    XOR BX, BX
    INT 10H
  }
}

void setSVGABank(char bank){
  asm{
    MOV AL, [bank]
    CMP[currentBank], AL
    JE noSwitchBank // esto es para ver que el current bank no es el mismo que el bank
    MOV [currentBank], AL //settear en currentbank el puntero a AL
    MOV AX, 4F05H
    XOR BX, BX //settear a 0 BX
    XOR DX, DX //settear a 0 DX
    MOV DL, [bank] //mover a DL lo que esta en el banco
    INT 10H //llamada a la interrupcion 0x10
  }
  noSwitchBank:;
}
void putThickPixel(int x, int y, char color, int thick, int pattern)
{
  int i,j;
  for(i=0;i<thick;i++)
    for(j=0;j<thick;j++)
      putPixel(x+i,y+j,color,pattern);
}


void putPixel(int x, int y, char color, int pattern){
  long memoryPosition;
  int pixelOffset;
  char bank;

  if(x>limitX || x<0 || y>limitY || y<0){
    return;
  }
  if( pattern == 1){
    color = getPatternOnePixel(x,y);
  }else if( pattern == 2){
    color = getPatternTwoPixel(x,y);
  }

  memoryPosition = (y*(limitX+1))+x;
  bank = memoryPosition>>16;
  pixelOffset = memoryPosition-(bank<<16);

  //Se cambia al banco correcto.
  if(bank != currentBank){
    setSVGABank(bank);
    currentBank = bank;
  }

  asm{
    MOV AX, 0A000H 
    MOV ES, AX //mover a ES el puntero de Ax
    MOV DI, [pixelOffset] //mover a DI lo que se encuentra en pixeloffset
    MOV AL, [color] //mover a AL lo que se encuentra en drawcolor
    MOV ES:[DI], AL //mover lo que esta en AL al segmento ES con offset DI
  }
}

char getPixel(int x, int y){
  long memoryPosition;
  int pixelOffset;
  char bank, color;

  if(x>limitX || x<0 || y>limitY || y<0){
    return;
  }

  memoryPosition = (y*(limitX+1))+x;
  bank = memoryPosition>>16;
  pixelOffset = memoryPosition-(bank<<16);

  if(bank != currentBank){
    setSVGABank(bank);
    currentBank = bank;
  }

  asm{
    MOV AX, 0A000H
    MOV ES, AX
    MOV DI, [pixelOffset]
    MOV AL, ES: [DI]
    MOV [color], AL 
  }
  return (color);
}