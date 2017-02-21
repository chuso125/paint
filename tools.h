typedef struct linkedList{
  int x;
  int y;
  struct Node* next;
}Node;
void push(int x, int y, Node ** f){
	Node *node;
	node = (Node*) malloc(sizeof(Node));
	node->x=x;
	node->y=y;
	node->next=NULL;
	(*f)->next=node;
	*f = (*f)->next;
}
void spray(int x, int y, char color,int thick){
	int i;
	int x1 = 0;
	int y1 = 0;
	for(i = 0; i< 100 ;i++){
		x1 = rand() % (2*thick);
		y1 = rand() % (2*thick);
		if( x1 % 2 == 0 && y1 % 2 == 0){
			putPixel(x+x1,y+y1,color,0);
		}else if( x1 % 2 != 0 && y1 % 2 != 0){
			putPixel(x-x1,y-y1,color,0);
		}else if( x1 % 2 != 0 && y1 % 2 == 0){
			putPixel(x-x1,y+y1,color,0);
		}else if( x1 % 2 == 0 && y1 % 2 != 0){
			putPixel(x+x1,y-y1,color,0);
		}
	} 
}
void floodFill(int x, int y, char actualColor, char replaceColor, int pattern){
	Node *start, *finish, *tmp;

	//inicializacion de la estrunctura
	start = (Node*) malloc(sizeof(Node));
	start->x=x;
	start->y=y;
	start->next=NULL;
	finish = start;

	while (start != NULL)
    {
    	if(getPixel(x+1,y) == actualColor){
    		//replaceColor = getPixel(241 + x%50, 32 + y%50);
    		putPixel(x+1,y,replaceColor,pattern);
    		push(x+1,y,&finish);
    	}
    	if(getPixel(x-1,y) == actualColor){
    		//replaceColor = getPixel(241 + x%50, 32 + y%50);
    		putPixel(x-1,y,replaceColor,pattern);
    		push(x-1,y,&finish);
    	}
    	if(getPixel(x,y+1) == actualColor){
    		//replaceColor = getPixel(241 + x%50, 32 + y%50);
    		putPixel(x,y+1,replaceColor,pattern);
    		push(x,y+1,&finish);
    	}
    	if(getPixel(x,y-1) == actualColor){
    		//replaceColor = getPixel(241 + x%50, 32 + y%50);
    		putPixel(x,y-1,replaceColor,pattern);
    		push(x,y-1,&finish);
    	}
    	tmp=start;
		start=start->next;
		x=start->x;
		y=start->y;
		free(tmp);         
    }
    free(start);
}
void scanLine(int a[20][2],int n,char color, char color2, int thick, int pattern){
	int i,j,k,dy,dx;
	int x,y,temp;
  	int xi[20];
  	float slope[20];
  	for(i=0;i<n-1;i++){
    	dy=a[i+1][1]-a[i][1];
    	dx=a[i+1][0]-a[i][0];

    	if(dy==0) 
      		slope[i]=1.0;
    	if(dx==0) 
      		slope[i]=0.0;

    	if((dy!=0)&&(dx!=0)) {
      		slope[i]=(float) dx/dy;
    	}
  	}

  	for(y=0; y < 600 ;y++){
		k=0;
		for(i=0;i<n-1;i++){
	  		if( ((a[i][1]<=y)&&(a[i+1][1]>y)) || ((a[i][1]>y)&&(a[i+1][1]<=y))){
	    		xi[k]=(int)(a[i][0] + slope[i] * (y-a[i][1]));
	    		k++;
	  		}
		}
	 	//sort 
	  	for(j=0;j<k-1;j++) 
	    	for(i=0;i<k-1;i++){
	      		if(xi[i]>xi[i+1]){
	        	temp=xi[i];
	        	xi[i]=xi[i+1];
	        	xi[i+1]=temp;
	      		}
	    	}

	  	for(i=0;i<k;i+=2){
	    	line(xi[i],y,xi[i+1]+1,y,color2,thick,pattern);
	  	}
	}
	//poligono
  	for(i=0;i<n-1;i++) {
    	line(a[i][0],a[i][1],a[i+1][0],a[i+1][1],color,thick,0);
  	}
}
void saveUndo(){
	FILE *f;
	int x0,y0,x1,y1, width,height, i,j;
	x0 = 129;
	y0 = 112;
	x1 = 800;
	y1 = 600;
	f = fopen("UNDO.TXT","w");
	for(j=y0;j<y1;j++){
		for(i=x0;i<x1;i++){
			fprintf(f, "%i\n", getPixel(i,j));
		}
		fprintf(f, "\n");
	}
	fclose(f);
}
void undo(){
	int y = 0;
	int i = 0;
	int temp;
	FILE *f1;
	char line[20];
	f1 = fopen("UNDO.TXT","r");
    while(fgets(line,sizeof(line),f1) != NULL) // To get you all the lines.
    {
    	if(line[0]!='\n'){
    		sscanf(line, "%i", &temp);
        	putPixel(129+i,112+y,temp,0);
        	i++;        
        }else{
        	i = 0;
        	y++;
        }
    }
	fclose(f1);
}
void copy(int x0, int y0, int x1, int y1){
	FILE *f;
	int j,i;
	f = fopen("COPY.TXT","w");
	if(y1>y0 && x1>x0)
		for(j=y0+1;j<y1;j++){
			for(i=x0+1;i<x1;i++){
				fprintf(f, "%i\n", getPixel(i,j));
			}
			fprintf(f, "\n");
		}
	else
		if(y1<y0 && x1>x0)
			for(j=y0+1;j>y1;j--){
				for(i=x0+1;i<x1;i++){
					fprintf(f, "%i\n", getPixel(i,j));
				}
				fprintf(f, "\n");
			}
		else if((y1<y0 && x1<x0))
				for(j=y0+1;j>y1;j--){
					for(i=x0+1;i>x1;i--){
						fprintf(f, "%i\n", getPixel(i,j));
					}
					fprintf(f, "\n");
				}
			else if((y1>y0 && x1<x0))
				for(j=y0+1;j<y1;j++){
					for(i=x0+1;i>x1;i--){
						fprintf(f, "%i\n", getPixel(i,j));
					}
					fprintf(f, "\n");
				}
	fclose(f);
}
void paste(x0,y0){
	int y = 0;
	int i = 0;
	int temp;
	FILE *f1;
	char line[20];
	f1 = fopen("COPY.TXT","r");
    while(fgets(line,sizeof(line),f1) != NULL) // To get you all the lines.
    {
    	if(line[0]!='\n'){
    		sscanf(line, "%i", &temp);
        	putPixel(x0+i,y0+y,temp,0);
        	i++;        
        }else{
        	i = 0;
        	y++;
        }
    }
	fclose(f1);
}