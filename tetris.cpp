/* Famous Tetris game, coded for Linux with SvgaLib    	*/
/* Alexandru Goia (aigoia@yahoo.com)		       	*/
/* Mon Mar 10 - Wed Mar 12  2008			*/
/* Compile with : g++ tetris-linux.cpp -o tetris -lvga  */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vga.h>
#include <vgakeyboard.h>

int matrice[12][24];
int scor;

int scorul()
    {
    printf("\nScorul obtinut este %d.\n", scor);
    }

int coboara_linii(int j);
int deseneaza_matrice();
int minim_linie(int j);

int verifica_linii()
    {
	int j;
ciclu:  for(j=23;j>=0;j--)
	if(minim_linie(j) > 0)
	    {
		scor++;
		coboara_linii(j);
		deseneaza_matrice();
		goto ciclu;
	    }
    }

int minim_linie(int j)
    {
    int a=matrice[0][j];
    int i;
    for(i=1;i<=11;i++)
	if(matrice[i][j]<a) a=matrice[i][j];
    return a;	
    }

int coboara_linii(int j)
    {
    int i,k;
    for(k=j;k>=1;k--)
	for(i=0;i<=11;i++)
	    matrice[i][k]=matrice[i][k-1];
    }

int deseneaza_matrice()
    {
    int i,j,m;
    for(j=23;j>=4;j--)
	for(i=0;i<=11;i++)
	    {
		vga_setcolor(matrice[i][j]);
		for(m=0;m<=19;m++)
		    vga_drawline(200+20*i, 20*j+m, 219+20*i,20*j+m);
	    }
    }
    
time_t *timp, timpul;

struct patratel
    {
	int x;
	int y;
    };

void desen_patratel(patratel p)
    {
	int m;
	for(m=0;m<=19;m++) 
		vga_drawline(200+20*p.x, 20*p.y+m, 219+20*p.x, 20*p.y+m);
    }

class figura
    {
	patratel pc;
	patratel p[4];
	int culoare;
public:	
	figura(long int nrfig, long int nrculoare);
	
	void preafiseaza();
	int initiaza();
	
	int afiseaza();
	int sterge();

	int stanga();
	int dreapta();
	int jos();
	int scroll_jos();
	int rotatie();
	
	int sfarsit();
    };

int figura::initiaza()
    {
	int i;
	pc.y = pc.y + 1;
	for(i=0;i<=3;i++)
	    p[i].y = p[i].y + 1;
    }
    
figura::figura(long int nrfig, long int nrculoare)
    {
	culoare = nrculoare;
	
	switch(nrfig)
	    {
	    	case 0: pc.x = 6;
	    		pc.y = 1;
	    		
	    		p[0].x = 6;
	    		p[0].y = 0; 
	    		
	    		p[1].x = 6;
	    		p[1].y = 1;
	    		
	    		p[2].x = 6;
	    		p[2].y = 2;
	    		
	    		p[3].x = 6;
	    		p[3].y = 3;
	    		
	    		break;
	    		
	    	case 1: pc.x = 5;
	    		pc.y = 2;
	    		
	    		p[0].x = 5;
	    		p[0].y = 2;
	    		
	    		p[1].x = 6;
	    		p[1].y = 2;
	    		
	    		p[2].x = 5;
	    		p[2].y = 3;
	    		
	    		p[3].x = 6;
	    		p[3].y = 3;
	    		
	    		break;
	    		
	    	case 2: pc.x = 6;
	    		pc.y = 3;
	    		
	    		p[0].x = 6;
	    		p[0].y = 2;
	    		
	    		p[1].x = 5;
	    		p[1].y = 3;
	    		
	    		p[2].x = 6;
	    		p[2].y = 3;
	    		
	    		p[3].x = 7;
	    		p[3].y = 3;
	    		
	    		break;
	    	
	    	case 3:	pc.x = 6;
	    		pc.y = 3;
	    		
	    		p[0].x = 6;
	    		p[0].y = 1;
	    		
	    		p[1].x = 6;
	    		p[1].y = 2;
	    		
	    		p[2].x = 5;
	    		p[2].y = 3;
	    		
	    		p[3].x = 6;
	    		p[3].y = 3;
	    		
	    		break;
	    	
	    	case 4:	pc.x = 5;
	    		pc.y = 3;
	    	
	    		p[0].x = 5;
	    		p[0].y = 1;
	    		
	    		p[1].x = 5;
	    		p[1].y = 2;
	    		
	    		p[2].x = 5;
	    		p[2].y = 3;
	    		
	    		p[3].x = 6;
	    		p[3].y = 3;
	    		
	    		break;
	    	
	    	case 5: pc.x = 6;
	    		pc.y = 2;
	    		
	    		p[0].x = 5;
	    		p[0].y = 2;
	    		
	    		p[1].x = 6;
	    		p[1].y = 2;
	    		
	    		p[2].x = 6;
	    		p[2].y = 3;
	    		
	    		p[3].x = 7;
	    		p[3].y = 3;
	    		
	    		break;
	    			    	
	    	case 6: pc.x = 5;
	    		pc.y = 2;
	    		
	    		p[0].x = 5;
	    		p[0].y = 2;
	    		
	    		p[1].x = 6;
	    		p[1].y = 2;
	    		
	    		p[2].x = 4;
	    		p[2].y = 3;
	    		
	    		p[3].x = 5;
	    		p[3].y = 3;
	    		
	    		break;
	    	
	    	default:break;	
	    };	
    }

void figura::preafiseaza()
    {
    int i;
    vga_setcolor(culoare);
    for(i=0;i<=3;i++)
	    {
		desen_patratel(p[i]);
	    }
    }

int figura::afiseaza()
    {
	int i;
	vga_setcolor(culoare);
	if( (matrice[p[0].x][p[0].y] != 0) || (matrice[p[1].x][p[1].y] != 0) ||
	    (matrice[p[2].x][p[2].y] != 0) || (matrice[p[3].x][p[3].y] != 0) ) 
	    return 0;
	for(i=0;i<=3;i++)
	    desen_patratel(p[i]);
	return 1;
    }

int figura::sterge()
    {
    int i;
    vga_setcolor(0);
    for(i=0;i<=3;i++)
	    {
		// matrice[p[i].x][p[i].y] = 0;
		// cica linia de mai sus trebuie sa fie !
		desen_patratel(p[i]);
	    }
    vga_setcolor(culoare);
    }

int figura::stanga()
    {
     sterge();
     vga_setcolor(culoare);
     if( p[0].x == 0 || p[1].x == 0 || p[2].x == 0 || p[3].x == 0)
	{
	    afiseaza();
	    return 0;
	}
     if( matrice[p[0].x-1][p[0].y] == 0 && matrice[p[1].x-1][p[1].y] == 0 &&
	matrice[p[2].x-1][p[2].y] == 0 && matrice[p[3].x-1][p[3].y] == 0)
	{
	    pc.x --;
	    p[0].x --;
	    p[1].x --;
	    p[2].x --;
	    p[3].x --;
	    afiseaza();
	    return 1;
	}
     afiseaza();
     return 0;
    }

int figura::dreapta()
    {
     sterge();
     vga_setcolor(culoare);
     if( p[0].x == 11 || p[1].x == 11 || p[2].x == 11 || p[3].x == 11)
	{
	    afiseaza();
	    return 0;
	}
     if( matrice[p[0].x+1][p[0].y] == 0 && matrice[p[1].x+1][p[1].y] == 0 &&
	matrice[p[2].x+1][p[2].y] == 0 && matrice[p[3].x+1][p[3].y] == 0)
	{
	    pc.x ++;
	    p[0].x ++;
	    p[1].x ++;
	    p[2].x ++;
	    p[3].x ++;
	    afiseaza();
	    return 1;
	}
     afiseaza();
     return 0;
    }    

int distantapt(patratel p1, patratel p2)
    {
	return ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }	

int figura::rotatie()
    {
	sterge();
	vga_setcolor(culoare);
	patratel P[4];
	int rotire=0;
	int i;
	for(i=0;i<=3;i++)
	    {
		P[i].x = pc.x + p[i].y - pc.y ;
		P[i].y = pc.y - p[i].x + pc.x ;
	    }
	    
	if( P[0].x < 0 || P[1].x < 0 || P[2].x < 0 || P[3].x < 0)
	    {
		afiseaza();
		return 0;
	    }
	    
	if( P[0].x > 11 || P[1].x > 11 || P[2].x > 11 || P[3].x > 11)
	    {
		afiseaza();
		return 0;
	    }
	    
	if( P[0].y > 23 || P[1].y > 23 || P[2].y > 23 || P[3].y > 23)
	    {
		afiseaza();
		return 0;
	    }        
	
	for(i=0;i<=3;i++)
	    {
	    
		if(	distantapt(p[i],pc) == 1 && 
			matrice[P[i].x][P[i].y] == 0 &&
	matrice[p[i].x+P[i].x-pc.x][p[i].y+P[i].y-pc.y] == 0)
		rotire++;
	
		if(     distantapt(p[i],pc) == 2 &&
			matrice[P[i].x][P[i].y] == 0 &&
	matrice[p[i].x+P[i].x-pc.x][p[i].y+P[i].y-pc.y] == 0 &&
	matrice[(p[i].x+P[i].x)/2][(p[i].y+P[i].y)/2] == 0 &&
	matrice[(p[i].x+3*P[i].x)/2-pc.x][(p[i].y+3*P[i].y)/2-pc.y] == 0 &&
	matrice[(3*p[i].x+P[i].x)/2-pc.x][(3*p[i].y+P[i].y)/2-pc.y] == 0)
		
		rotire++;
		
		if(	distantapt(p[i],pc) == 4 &&
			matrice[P[i].x][P[i].y] == 0 &&
	matrice[p[i].x+P[i].x-pc.x][p[i].y+P[i].y-pc.y] == 0 &&
	matrice[(p[i].x+P[i].x)/2][(p[i].y+P[i].y)/2] == 0 &&
	matrice[(p[i].x+pc.x)/2][(p[i].y+pc.y)/2] == 0 &&
	matrice[(P[i].x+pc.x)/2][(P[i].y+pc.y)/2] == 0 &&
	matrice[p[i].x+(P[i].x-pc.x)/2][p[i].y+(P[i].y-pc.y)/2] == 0 &&
	matrice[P[i].x+(p[i].x-pc.x)/2][P[i].y+(p[i].y-pc.y)/2] == 0)
		
		rotire++;
			
	    }
	if(rotire<3)
	    {
		afiseaza();
		return 0;
	    }
	if(rotire==3)
	    {
		for(i=0;i<=3;i++)
		    {
			p[i].x = P[i].x;
			p[i].y = P[i].y;
		    }
		afiseaza();
		return 1;
	    }                	
    }

int figura::scroll_jos()
    {
    vga_setcolor(culoare);
    while( matrice[p[0].x][p[0].y+1] == 0 && matrice[p[1].x][p[1].y+1] == 0 &&
	   matrice[p[2].x][p[2].y+1] == 0 && matrice[p[3].x][p[3].y+1] == 0
	   && p[0].y <= 22 && p[1].y <= 22 && p[2].y <=22 && p[3].y <= 22 )
	{
	    sterge();
	    jos();
	}
    }
    
int figura::jos()
    {
    vga_setcolor(culoare);
    if(p[0].y == 23 || p[1].y == 23 || p[2].y == 23 || p[3].y == 23) 
		{ 
	    afiseaza(); 
	    return 0;
		}
	
    if ( (matrice[p[0].x][p[0].y+1] == 0) && (matrice[p[1].x][p[1].y+1] == 0) &&
	 (matrice[p[2].x][p[2].y+1] == 0) && (matrice[p[3].x][p[3].y+1] == 0) )
	{
	    pc.y ++;
	    p[0].y ++;
	    p[1].y ++;
	    p[2].y ++;
	    p[3].y ++;
	    afiseaza();
	    return 1;
	} 
	else 
	{	
		afiseaza();
		return 0;
	}
    }
        
int figura::sfarsit()
    {
     int i;
     for(i=0;i<=3;i++)
        { 
    	    matrice[p[i].x][p[i].y] = culoare;
    	}
    };
    
void init()
    {
	scor = 0;
	int i,j;
	for(i=0;i<=11;i++)
	    for(j=0;j<=23;j++)
		matrice[i][j] = 0;
    }

void afis_ecran()
    {
	vga_init();
	vga_setmode(G640x480x16);
	vga_setcolor(15);
	vga_drawline(440,0,440,479);
	vga_drawline(199,0,199,479);
    }
    
void startjoc()
    {
	printf(" \n");
	printf("       TETRIS for Linux       \n");
	printf(" \n");
	printf("Famous Tetris game, coded in C/C++\n");
	printf("Alexandru Goia (aigoia@yahoo.com), march 2008\n");
	printf(" \n");
	sleep(5);
    }

void stopjoc()
    {
	printf(" \n");
	printf("       TETRIS for Linux        \n");
	printf(" \n");
	exit(0);
    }
	
int main()
    {
	startjoc();
	init();
	afis_ecran();
	
	keyboard_init();
	
start:	figura f = figura(random()%7, random()%15+1);
	f.preafiseaza();
	sleep(2);
	f.sterge();
	f.initiaza();			

joc:	if(f.afiseaza() == 0) goto stop; 
	timpul = time(timp);
		
key:	keyboard_update();
	
	if(keyboard_keypressed(SCANCODE_SPACE) && 
	keyboard_keypressed(SCANCODE_SPACE) &&
	keyboard_keypressed(SCANCODE_SPACE))	f.scroll_jos();
	
	if(keyboard_keypressed(SCANCODE_J) &&
	keyboard_keypressed(SCANCODE_J) &&
	keyboard_keypressed(SCANCODE_J))	f.rotatie();
	    		   
	if(keyboard_keypressed(SCANCODE_N) &&
	keyboard_keypressed(SCANCODE_N) &&
	keyboard_keypressed(SCANCODE_N))	f.stanga();

	if(keyboard_keypressed(SCANCODE_M) &&
	keyboard_keypressed(SCANCODE_M) &&
	keyboard_keypressed(SCANCODE_M))	f.dreapta();
			 	
	if(keyboard_keypressed(SCANCODE_Q))	goto stop;
	
	if ( time(NULL) - timpul <= 1.5) 	goto key;

	f.sterge();
	if (f.jos() == 0)
		{
		    f.sfarsit();
		    verifica_linii();
		    goto start;
		}
	goto joc;
	
stop:   sleep(2);
	vga_setmode(TEXT);
	keyboard_close();
	scorul();
	stopjoc();
    }
