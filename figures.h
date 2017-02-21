void line(int x0, int y0, int x1, int y1, char color, int thick, int pattern){
  int i, dx, dy, sx, sy, x, y, px, py;
  dx = x1 - x0;
  dy = y1 - y0;
  //sx
  if(dx<0)
    sx = -1;
  else 
    if(dx>0)
      sx = 1;
    else
      sx = 0;
  //sy
  if(dy<0)
    sy = -1;
  else 
    if(dy>0)
      sy = 1;
    else
      sy = 0;
  //abs dx
  if (dx < 0){
    dx = dx * -1;
  }
  //abs dy
  if (dy < 0){
    dy = dy * -1;
  }

  x = dy>>1;
  y = dx>>1;  

  px = x0;
  py = y0;

  if(dx >= dy){
    for(i=0; i<dx; i++){
      y += dy;
      if(y >= dx){
        y -= dx;
        py += sy;
      }
      px+=sx;
      putThickPixel(px, py, color, thick, pattern);
    }
  }else{
    for(i=0; i<dy; i++){
      x += dx;
      if (x >= dy){
        x -= dy;
        px += sx;
      }
      py+=sy;
      putThickPixel(px, py, color, thick, pattern);
    }
  }
}
void rectangle(int x0, int y0, int x1, int y1, char color, int thick){
  line(x0,y0,x1,y0,color,thick, 0);
  line(x1,y0,x1,y1,color,thick, 0);
  line(x1,y1,x0,y1,color,thick, 0);
  line(x0,y1,x0,y0,color,thick, 0);
}
void fillRectangle(int x0, int y0, int x1, int y1, char color, char fillColor, int thick,int pattern){
  int i;
  if(y1>y0)
    for(i=y0; i<=y1; i++){
      line(x0,i,x1,i,fillColor, thick,pattern);
    }
  else
    for(i=y0; i>=y1; i--){
      line(x0,i,x1,i,fillColor, thick,pattern);
    }
  rectangle(x0,y0,x1,y1,color,thick);
}

void ellipse(int xc, int yc, int rx, int ry, char color, int thick){
  int x,y;
  float p;
  p=(ry*ry)-(rx*rx*ry)+((rx*rx)/4.0);
  x=0;
  y=ry;
  while(2.0*ry*ry*x <= 2.0*rx*rx*y){
    if(p < 0)
    {
      x++;
      p = p+2.0*ry*ry*x+(float)ry*ry;
    }
    else
    {
      x++;
      y--;
      p = p+2.0*ry*ry*x-2.0*rx*rx*y-(float)ry*ry;
    }
    putThickPixel(xc+x,yc+y,color,thick, 0);
    putThickPixel(xc+x,yc-y,color,thick, 0);
    putThickPixel(xc-x,yc+y,color,thick, 0);
    putThickPixel(xc-x,yc-y,color,thick, 0);
   }

  //Region 2
  p=((float)x+0.5)*((float)x+0.5)*ry*ry+((float)y-1.0)*((float)y-1.0)*rx*rx-(float)rx*rx*ry*ry;
  while(y > 0){
    if(p <= 0){
      x++;
      y--;
      p = p+2.0*ry*ry*x-2.0*rx*rx*y+(float)rx*rx;
    }
    else{
      y--;
      p = p-2.0*rx*rx*y+(float)rx*rx;
    }
    putThickPixel(xc+x,yc+y,color,thick,0);
    putThickPixel(xc+x,yc-y,color,thick,0);
    putThickPixel(xc-x,yc+y,color,thick,0);
    putThickPixel(xc-x,yc-y,color,thick,0);
  }
}
void fillEllipse(int xc, int yc, int rx, int ry, char color, char color1, int thick,int pattern){
  int x,y;
  double dx,dy;
  for( y=-ry; y<=ry; y++) {
    for( x=-rx; x<=rx; x++) {
        dx = (double)x / (double)rx;
        dy = (double)y / (double)ry;
        if(dx*dx+dy*dy <= 1)
            putThickPixel(xc+x,yc+y,color1,thick,pattern);
    }
}
  ellipse(xc,yc,rx,ry,color,thick);
}