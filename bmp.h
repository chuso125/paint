
#ifndef __DOS_H
#include <dos.h>
#endif 

typedef unsigned char  byte;
typedef unsigned short word;
typedef struct tagBITMAP {
  word width;
  word height;
  char palette[256*3];
  byte *data;
} BITMAP;

void skipf(FILE *fp, int num_bytes);
void changePalette(char far *palette);

void openBMP(int x, int y, char *file, BITMAP *bitmap) 
{
  FILE *filepointer;
  long index;
  word numberColor;
  int i, j, ti;
  if ((filepointer = fopen(file, "rb")) == NULL) 
  {
    getch();
    return;
  }

  if(fgetc(filepointer)!= 'B' || fgetc(filepointer) != 'M')
  {
    fclose(filepointer);
    exit(1);
  }
  skipf(filepointer,16);
  fread(&bitmap->width,sizeof(word), 1, filepointer);
  skipf(filepointer,2);
  fread(&bitmap->height,sizeof(word), 1, filepointer);
  skipf(filepointer,22);
  fread(&numberColor,sizeof(word), 1, filepointer);
  skipf(filepointer,6);

  if(numberColor==0)
  {
    numberColor = 256;
  }
  for(index=0;index<numberColor;index++)
  {
    bitmap->palette[(int)(index*3+2)] = fgetc(filepointer) >> 2;
    bitmap->palette[(int)(index*3+1)] = fgetc(filepointer) >> 2;
    bitmap->palette[(int)(index*3+0)] = fgetc(filepointer) >> 2;
    fgetc(filepointer);
  }

  changePalette(bitmap->palette);
  for(j=(bitmap->height + y);j>=y;j--)
  {
    for(i=0; i<(bitmap->width); i++)
    {
      putPixel(i+x, j, fgetc(filepointer),0);
    }
  }
  fclose(filepointer);
}
void skipf(FILE *filepointer, int num_bytes){
   int i;
   for (i=0; i<num_bytes; i++)
      fgetc(filepointer);
}
void changePalette(char far *palette){
  asm {
  les dx, [palette]
  mov ax, 0x1012
  mov bx, 0
  mov cx, 256
  int 0x10
    }
}
void getPalette ( char far *palette)
{
   asm {
  les dx, [palette]
        mov ax, 0x1017
        mov bx, 0
        mov cx, 256
        int 0x10
    }
}
void saveImage(int x, int y, int width, int height, char file[]){
  FILE *fp;
  int count, i, j, tempi;
  unsigned char c, ch;
  unsigned long toWrite[13];
  unsigned long palette[256];
  char xInf[2] = "BM";
  fp = fopen(file, "wb");
  fwrite(xInf, sizeof(xInf[0]),2,fp);
  x--; y--;
  toWrite[0] = width * height + 1024 + 54;  //Tamaño
  toWrite[1] = 0;             // Reservado
  toWrite[2] = 1024 + 54;         // offset
  toWrite[3] = 40;            // Tamaño del header
  toWrite[4] = width;           // width
  toWrite[5] = height;          // height
  toWrite[6] = 0x80001;         // word planes
  toWrite[7] = 0;             // Compresión
  toWrite[8] = width*height;        // Tamaño del bmp
  toWrite[9] = 0;             // HPPM
  toWrite[10] = 0;            // VPPM
  toWrite[11] = 256;            // Colores utilizados
  toWrite[12] = 256;            // Importa colores
  fwrite(toWrite, sizeof(toWrite[0]), 13, fp);
  getPalette(palette);
  palette[0] = 0;
  palette[1] = 0x8;
  palette[2] = 0x800;
  palette[3] = 0x808;
  palette[4] = 0x80000;
  palette[5] = 0x80008;
  palette[6] = 0x80400;
  palette[7] = 0xC0C0C;
  palette[8] = 0x80808;
  palette[9] = 0xFF;
  palette[10] = 0xFF00;
  palette[11] = 0xFFFF;
  palette[12] = 0xFF0000;
  palette[13] = 0xFF00FF;
  palette[14] = 0xFFFF00;
  palette[15] = 0xFFFFFF;
  fwrite(palette, sizeof(unsigned long), 256, fp);
  count=0;
  for(j=(y+height); j>=y; j--){
    count++;
    for(i=x; i<=(width+x)-1; i++){
     c=getPixel(i, j);
     fwrite(&c,1,1,fp);
    }
  }
  count--;
  fclose(fp);
}