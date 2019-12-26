#include<fstream.h>                   //should run with courier new  @ 24
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>

using namespace std;

int end=1;

struct title    //Cards like Mumbai etc.
{
	char name[14],own[15],type;
   int code,unlock,nhu,nho;
   float price,rent,h1,h2,h3,ho,costh,mort;
   void display()
   {
     	cprintf("    %-3c %-7.1f %-16s %-6.1f %-7.1f",
              type,price,name, rent, mort);
   }
};

struct port            //cards like  Water Works etc.
{
	char name[19],own[15],spcl[19];
   float price;
   float rent,nrent,mort;
   int code,unlock;
   void display()
   {
   	cprintf("  %-5s %-7.1f %-16s %-6.1f %-7.1f",
              "Port",price,name, rent, mort);
   }
};

struct player
{
	char name[20];
   float bal, tot;
   int pos,di,turn,clr,i;   //turn = 1 or 0 next turn or not
};

struct bank
{
	float bal;
   int cont;
};

struct loca                    //all for animating
{
	int code,px,py,hx,hy,h;
   char name[20];
};

                                //All functions
int newfile(char*);
int noplayers();
int propfunc(title ti);
int propfunc(port po);
void write(title, int);
void read(title& ti, int);
void write(port po, int);
void read(port& po, int);
void write(bank ba);
void read(bank& ba);
void write(loca lo, int);
void read(loca& lo, int);
void write(player pl, int);
void read(player& pl, int);
void delay();
void fillwindow(int, int, int, int, int, int);
void fullwin();
void newgame();
void condition(loca, char*,int);
void animate(player pla);
void clrscrb(char*,int);
void startmenu();
void startgame();
void rungame();
void playerturn(player &pla);
void showdetails(char*, float);
void location(player pla);
void displaytitlexy(title ti, int, int);
void displayportxy(port po, int, int);
void payrent(player pla);
void buildhouhot(player pl, title &ti);
char moneycond(double pri, player &pla, int co=0);
void buyprop(player pla);
void jail(player pla);
void chance(player pla);
void communitychest(player pla);
int selling(player &pla);
int displaysellprop(player pla);
void displaysellhou(player pla);
void sell(title ti,player &pla);
void sell(port po,player &pla);
void sellh(title ti,player &pla);
void inloca(title ti);
int sellprop(player &pla);
void sellhouse(player &pla);
void enddisplay(player pl, int);
char endgame(player p);
void removepl(player pl);
void rem();

void main()
{
   randomize();
   /*player p;
   read(p,0);
   p.turn=2;
   write(p,0);*/
   startmenu();
}

int newfile(char str[])
{
	title ti;
   int n=0,si=sizeof(ti);
	ifstream fin("TCardsg.dat",ios::binary);
   ofstream fout("CardsT.dat",ios::binary);
   while(fin.read((char*)&ti,si))
   {
   	if(strcmpi(ti.own,str)==0)
   	{
         fout.write((char*)&ti,si);
         n+=1;
      }
   }
   fout.close(); fin.close();
   return n;
}

int noplayers()
{
   ifstream pli("Players.dat",ios::binary);
   pli.seekg(0,ios::end);
   int n=pli.tellg()/sizeof(player);
   pli.close();
   return n;
}

int propfunc(title ti)
{
	int k=0;
	title t;
	for(int i=0;i<20;i++)
   	{
   		read(t,i);
         if(strcmpi(t.own,ti.own)==0 && t.type==ti.type)
         	k++;
   	}
   return k;
}

int propfunc(port po)
{
	int k=0;
	port p;
	for(int i=0;i<6;i++)
   	{
   		read(p,i);
         if(strcmpi(p.own,po.own)==0 && strcmpi(p.spcl,po.name)==0)
         	k++;
   	}
   return k;
}

void write(title ti,int k)
{
	fstream tio("TCardsg.dat",ios::out | ios::in | ios::binary);
   tio.seekp(k*sizeof(ti));
   tio.write((char*)&ti,sizeof(ti));
   tio.close();
}

void read(title &ti, int k)
{
	fstream tii("TCardsg.dat",ios::out | ios::in | ios::binary);
   tii.seekg(k*sizeof(ti));
   tii.read((char*)&ti,sizeof(ti));
   tii.close();
}

void write(port po, int k)
{
	fstream poo("PCardsg.dat",ios::out | ios::in | ios::binary);
   poo.seekp(k*sizeof(po));
   poo.write((char*)&po,sizeof(po));
   poo.close();
}



void read(port &po, int k)
{
	fstream poi("PCardsg.dat",ios::out | ios::in | ios::binary);
   poi.seekg(k*sizeof(po));
   poi.read((char*)&po,sizeof(po));
   poi.close();
}

void write(bank ba)
{
	fstream bao("Bank.dat",ios::out | ios::in | ios::binary);
   bao.seekg(0);
   bao.write((char*)&ba,sizeof(ba));
   bao.close();
}

void read(bank &ba)
{
   fstream bao("Bank.dat",ios::out | ios::in | ios::binary);
   bao.seekg(0);
   bao.read((char*)&ba,sizeof(ba));
   bao.close();
}

void write(loca lo,int k)
{
	fstream lou("Location.dat",ios::out | ios::in | ios::binary);
   lou.seekp(k*sizeof(lo));
   lou.write((char*)&lo,sizeof(lo));
   lou.close();
}

void read(loca &lo, int k)
{
	fstream li("Location.dat",ios::out | ios::in | ios::binary);
	li.seekg(k*sizeof(lo));
   li.read((char*)&lo,sizeof(lo));
   li.close();
}

void write(player pl,int k)
{
	fstream plo("Players.dat",ios::out | ios::in | ios::binary);
   plo.seekp(k*sizeof(pl));
   plo.write((char*)&pl,sizeof(pl));
   plo.close();
}

void read(player &pl, int k)
{
	fstream pli("Players.dat",ios::out | ios::in | ios::binary);
	pli.seekg(k*sizeof(pl));
   pli.read((char*)&pl,sizeof(pl));
   pli.close();
}

void delay()
{
	for(double i=0;i<100000000;i+=1.0);
}


void fillwindow(int x1, int y1, int x2, int y2, int color,int txt)
{
	window(x1, y1, x2, y2);
	textbackground(color);
   textcolor(txt);
	clrscr();
}

void fullwin()
{
	fillwindow(1,1,111,42,BLACK,WHITE);
}

void topc()
{
	fillwindow(1,1,1,1,BLACK,LIGHTGRAY);
}

void midclr()
{
	fillwindow(21,6,90,36,BLACK,BLACK);
}

void rolldi()
{
   fillwindow(58,16,59,16,BLACK,WHITE);
	for(int i=0;i<250;i++)
   {
   	for(int k=0;k<13;k++)
   		cprintf("%i",k);
   }
}
void newgame()
{
	ofstream tpo("TCardsg.dat",ios::binary);
   ifstream tpi("TCards.dat",ios::binary);
   title ti;
   while(tpi.read((char*)&ti,sizeof(ti)))
   	tpo.write((char*)&ti,sizeof(ti));
   tpo.close(); tpi.close();
   tpo.open("PCardsg.dat",ios::binary);
   tpi.open("PCards.dat",ios::binary);
   port po;
   while(tpi.read((char*)&po,sizeof(po)))
   	tpo.write((char*)&po,sizeof(po));
   tpo.close(); tpi.close();
}

void animate(player pla)
{
   clrscrb(pla.name,1);
  	loca lo;
   int ip=+pla.pos;
   fillwindow(1,1,1,1,BLACK,0);
   for(int fp=(ip+pla.di);ip<=fp;ip++)
   {
   	int k=ip;
      if(ip>=36) k=ip-36;
      read(lo,k);
      fillwindow(lo.px+10,lo.py,lo.px+10,lo.py,pla.clr,0);
      delay();
      if(ip!=fp)
      	fillwindow(lo.px+10,lo.py,lo.px+10,lo.py,BLACK,0);
      condition(lo,pla.name,1);
   }
}

void condition(loca lo, char na[], int p)
{
	if(lo.h==1)
		fillwindow(lo.hx+10,lo.hy,lo.hx+10,lo.hy,GREEN,0);
	else if(lo.h==2)
      fillwindow(lo.hx+9,lo.hy,lo.hx+10,lo.hy,GREEN,0);
	else if(lo.h==3)
      fillwindow(lo.hx+10,lo.hy,lo.hx+10,lo.hy,RED,0);
	else if(lo.h==4)
      fillwindow(lo.hx+10,lo.hy,lo.hx+10,lo.hy,BLUE,0);
   int n=noplayers();
   player pl;
   for(int i=0;i<n;i++)
   {
      read(pl,i);
      if(lo.code==pl.pos && (strcmpi(pl.name,na)!=0 || p==0))
      	fillwindow(lo.px+10,lo.py,lo.px+10,lo.py,pl.clr,0);
   }
}

void dispcards(char na[])
{
   int l=0;
   fillwindow(21,15,41,15,BLACK,WHITE);
   cprintf("Your Cards : ");
	for(int i=1;i<=4;i++)
   {
   	int cl; char clr;
      switch(i)
      {
      	case 1 : cl=RED; clr='R'; break;
         case 2 : cl=YELLOW; clr='Y'; break;
         case 3 : cl=GREEN; clr='G'; break;
         case 4 : cl=BLUE; clr='B'; break;
      }
      for(int k=0;k<20;k++)
      {
         title ti; read(ti,k);
         if(strcmpi(ti.own,na)==0 && ti.type==clr)
         {	fillwindow(21,16+l,41,16+l,BLACK,cl);
         	cprintf("%s",ti.name); l++;
         }
      }
   }
   for(int i=0; i<6;i++)
   {
   	port po;
      read(po,i);
      if(strcmpi(po.own,na)==0)
      {
      	fillwindow(21,16+l,41,16+l,BLACK,WHITE);
      	cprintf("%s",po.name); l++;
      }
   }
}

void clrscrb(char na[]="",int p=0)
{
	loca lo;
   player pl;
	int x=91;
   fillwindow(10,1,x+10,42,BLACK,YELLOW);
   ifstream fin("Board.txt");
   char ch[93];
   while(fin.getline(ch,93))
   	cprintf("%s\n\r",ch);
   dispcards(na);
   for(int i=0;i<noplayers();i++)
   {
   	read(pl,i);
      if(strcmpi(pl.name,na)==0)
      {
      	bank ba;
      	read(ba);
      	fillwindow(20,7,43,10,BLACK,WHITE);
         cprintf("Your balance : %5.1f\n\n\r",pl.bal);
         cprintf("Bank : %5.1f\n", ba.bal);
      }
   }
  	for(int i=0;i<36;i++)
   {
   	read(lo,i);
      condition(lo,na,p);
   }
   fillwindow(77,7,90,25+noplayers(),BLACK,WHITE);
   cprintf("   = 1 House\n\n\r" );
   cprintf("   = 2 Houses\n\n\r" );
   cprintf("   = 3 Houses\n\n\r" );
   cprintf("   =   Hotel\n\n\r" );
   cprintf("   = Player 1\n\n\r" );
   cprintf("   = Player 2\n\n\r" );
   if(noplayers()==3)
   {
   	cprintf("   = Player 3\n\n\r" );
      fillwindow(78,19,78,19,3,0);
   }
   if(noplayers()==4)
   {
   	cprintf("   = Player 3\n\n\r" );
   	cprintf("   = Player 4\n\r" );
      fillwindow(78,19,78,19,3,0);
      fillwindow(78,21,78,21,4,0);
	}
	fillwindow(78,7,78,7,GREEN,0);
   fillwindow(77,9,78,9,GREEN,0);
   fillwindow(78,11,78,11,RED,0);
   fillwindow(78,13,78,13,BLUE,0);
   fillwindow(78,15,78,15,BLUE,0);
   fillwindow(78,17,78,17,2,0);
}

void startmenu()
{
	fillwindow(41,14,65,22,BLACK,WHITE);
	bank ba;
   read(ba);
   int ch;
   int k=1;
   if(ba.cont==1)
   {
   	gotoxy(1,k++);cprintf("1. Continue old game");
      gotoxy(1,k++); cprintf("2. Start new game");
      gotoxy(1,k++); cin>>ch;
      while(ch!=1 && ch!=2) cin>>ch;
      if(ch==1) rungame();
      else if(ch==2) startgame();
   }
   else
		startgame();
}

                         //only for start of new game
void startgame()
{
	int n;
	bank ba;
   fullwin(); rem();
   textcolor(CYAN);
   gotoxy(43,15);
   cprintf("Enter to START..."); getch(); clrscr();
   textcolor(RED);
   gotoxy(37,16);
   cprintf("Enter the number of players[2-4] : ");cin>>n;
   while(n>4 || n<2)
   {
   	gotoxy(37,17);cprintf("Enter properly : ");cin>>n;
   }
   clrscr();
   ba.bal=166500;
   newgame();
   for(int i=0;i<n;i++)
   {
   	ifstream pli;
   	player pl,plc;
   	gotoxy(43,16);
      cout<<"Enter Player "<<(i+1)<<" Name\n";
      gotoxy(45,17);
      gets(pl.name);clrscr();
      if(i!=0)
      {
      	pli.open("Players.dat",ios::binary);
      	while(pli.read((char*)&plc,sizeof(plc)))
      	{
				while(strcmpi(pl.name,plc.name)==0)
         	{
         		gotoxy(46,15);
         		cout<<"Same player Name";
            	gotoxy(41,16);
            	cout<<"Enter Player "<<(i+1)<<" Name Again";
            	gotoxy(45,17); gets(pl.name);clrscr();
         	}
      	}
         pli.close();
      }
      ba.cont=0;
      if(n==2)
   		pl.bal=50000;
      if(n==3)
   		pl.bal=43000;
      if(n==4)
   		pl.bal=33000;
      ba.bal-=pl.bal;
      pl.tot=(pl.bal);
      pl.pos=0;
      pl.turn=1;if(i==0) pl.turn=2;
      pl.clr=i+1;
      pl.i=i;
      write(pl,i);
      write(ba);
   }
   rungame();
}

                               //running the game
void rungame()
{
   _setcursortype(_NOCURSOR);
   int n=noplayers(); player pl;
   int i=0; read(pl,i);
   while(pl.turn==1)
   { i++; read(pl,i);}
   while(end)
   {
   	int fl=1;
      read(pl,i);
      playerturn(pl); write(pl,i);
      while(pl.turn && end==1)
      {
      	read(pl,i);
         if(fl==0) playerturn(pl);
         fl=0;
         if(end==1)
         {
         	bank ba;
         	read(ba);
            clrscrb(pl.name);
         	int k=(19-strlen(pl.name))/2;
            topc();
            fillwindow(41,14,65,22,BLACK,WHITE);
         	gotoxy(k,1); cprintf("%s's Turn",pl.name);
      		gotoxy(1,3); cprintf("Press Enter to Roll dice");
            getch();
            pl.di=2+random(11);
            fillwindow(41,14,65,22,BLACK,WHITE);
            gotoxy(1,3); cprintf("\rNumber on dice : ");
            rolldi();
            fillwindow(41,14,65,22,BLACK,WHITE);
            gotoxy(1,3); cprintf("\rNumber on dice : %i",pl.di);
            delay();
            animate(pl);
      		pl.pos+=pl.di;
      		if(pl.pos>=36)
      		{
      			pl.pos-=36;
         		pl.bal+=1500;
         		pl.tot+=1500;
         		ba.bal-=1500;
      		}
            write(ba);
      		pl.turn=1; write(pl,i);
            location(pl);
            if(pl.di==12) i--;
            i++;
         	if(i==n) i=0;
            read(pl,i);
         }
      } pl.turn=1;
      if(end==0) pl.turn=2;
      write(pl,i);
      i++;
      if(i==n) i=0;
   }
}
										//players turn
void playerturn(player &pla)
{
	bank ba;
   read(ba);
	char ch; int k;
   do
   {

   	clrscr();
      int len=strlen(pla.name);
      int k=(92-len)/2;
      clrscrb(pla.name);
      fillwindow(k+5,12,(k+len+12),12,BLACK,YELLOW);
   	cprintf("%s's Turn",pla.name);
      fillwindow(41,14,65,22,BLACK,WHITE);
   	cprintf("1. Show player details\n\r");
      cprintf("2. Roll Dice\n\r");
      cprintf("3. Sell Property/Houses\n\r");
      cprintf("4. See Bank details\n\r");
      cprintf("0. End Game\n\r"); ch=getch();
      switch(ch)
      {
      	case '1': showdetails(pla.name,pla.bal);break;
         case '2': ;break;
         case '3': k=selling(pla);break;
         case '4': showdetails("Bank",ba.bal);break;
         case '0': ch=endgame(pla);
      }
   }while(ch!='2');
   fullwin();
}

void showdetails(char str[],float bal)
{
	fullwin();	clrscr();
   int len=strlen(str);
   int k=(92-len)/2;
   textcolor(WHITE); clrscr();
   textbackground(CYAN);
   gotoxy(k,2);cprintf("%s's Details\n",str);
   textbackground(BLACK);
   fillwindow(20,4,31,4,CYAN,BLACK);
	gotoxy(20,4); cprintf("Properties");
   fillwindow(1,6,49,6,BLACK,CYAN);
   cprintf("  Type  Price   Name             Rent   Mort");
   /*fillwindow(70,17,87,17,LIGHTGRAY,BLACK);
   cprintf("Balance : %8.1f",bal);*/
   title obj; ifstream fin;
   int size=sizeof(obj),n=newfile(str);
   if(n<=13)
   {
   	fillwindow(1,n+8,49,n+14,BLACK,YELLOW);
   	port po;
   	fin.open("Pcardsg.dat",ios::binary);
		for(int i=0,k=0;i<6;i++)
   	{
   		gotoxy(1,k+1);
      	fin.read((char*)&po,sizeof(po));
      	if(strcmpi(po.own,str)==0)
      	{	po.display(); k++; }
   	}
   	fin.close();
   	fillwindow(1,n+15,49,n+15,BLACK,CYAN);
   	gotoxy(1, 1);
   	cprintf(" UP = %c    DOWN = %c", char(24), char(25));
   	gotoxy(30, 1); cprintf("EXIT = ESC");
   	fillwindow(1,7,49,7+n,BLACK,YELLOW);
   	gotoxy(1,1); int t;
      fin.open("CardsT.dat",ios::binary);
      do
      {
   		for(int k=0;k<n;k++)
      	{
      		fin.read((char*)&obj,size);
         	gotoxy(1,k+1);
         	obj.display();
      	}
      	t=getch(); fin.seekg(0);
      }while(t!=27);
	}
   if(n>13)
   {
   	fillwindow(1,21,49,26,BLACK,YELLOW);
      port po;
      ifstream fin("Pcardsg.dat",ios::binary);
      for(int i=0,k=0;i<6;i++)
      {
      	gotoxy(1,k+1);
         fin.read((char*)&po,sizeof(po));
         if(strcmpi(po.own,str)==0)
         {	po.display(); k++; }
      }
      fin.close();
      fillwindow(1,27,49,27,BLACK,CYAN);
      gotoxy(1, 1);
      cprintf(" UP = %c    DOWN = %c", char(24), char(25));
      gotoxy(30, 1);
      cprintf("EXIT = ESC");
      fillwindow(1,7,49,19,BLACK,YELLOW);
      gotoxy(1,1);
      fin.open("CardsT.dat",ios::binary);
      for (int k=0; k<13; k++)
      {
      	fin.read((char*)&obj, size);
         gotoxy(1, k+1);
         obj.display();
      }
      getch();
      int top=0, bot=12, done=0;
      _setcursortype(_NOCURSOR);
      do
   	{
   		int ch=getch();
      	switch (ch)
      	{
         	case 0:
            	ch=getch();
            	switch (ch)
            	{
               	case 72:
               		if (top>0)
                  	{
                  		bot--; top--;
               			gotoxy(1,13);
                  		delline();
                  		gotoxy(1,1);
                     	insline();
                     	fin.seekg(size*top);
                    	   fin.read((char*)&obj, size);
                     	obj.display();
                  	}
               		break;
               	case 80:
               		if (bot<n-1)
                  	{
                  		bot++; top++;
               			gotoxy(1,1);
                  		delline();
                  		gotoxy(1,13);
                     	fin.seekg(size*bot);
                     	fin.read((char*)&obj, size);
                     	obj.display();
                  	}
               		break;
            	}
            	break;
         	case 27 : done=1;
      	}
   	}
   	while (!done);
   }
   fin.close();
   remove("CardsT.dat");
   fullwin();
}
void location(player pla)
{
   buyprop(pla);
   if(pla.pos==9) jail(pla);
   if(pla.pos==7 || pla.pos==20) chance(pla);
   if(pla.pos==16 || pla.pos==29)
   	communitychest(pla);
}
                           //Displaying title cards at xy
void displaytitlexy(title t,int x, int y)
{
	int clr;
   if(t.type=='R') clr=RED;
   if(t.type=='G') clr=GREEN;
   if(t.type=='Y') clr=YELLOW;
   if(t.type=='B') clr=BLUE;
	fillwindow(x,y,x+20,y+15,BLACK,clr);
	cprintf("NAME            : \n\r");
   cprintf("PRICE           : \n\r");
   cprintf("    PROPERTY    : \n\r");
   cprintf("    HOUSE/HOTEL : \n\r");
   cprintf("RENT            : \n\r");
   cprintf("     PROPERTY   : \n\r");
   cprintf("     HOUSE 1    : \n\r");
   cprintf("     HOUSE 2    : \n\r");
   cprintf("     HOUSE 3    : \n\r");
   cprintf("     HOTEL      : \n\r");
   cprintf("SELLINGP        : \n\r");
   fillwindow(x+21,y,x+37,y+15,BLACK,WHITE);
   cprintf("%s\n\n\r",t.name);
   cprintf("%4.1f\n\r",t.price);
   cprintf("%4.1f\n\n\r",t.costh);
   cprintf("%4.1f\n\r",t.rent);
   cprintf("%4.1f\n\r",t.h1);
   cprintf("%4.1f\n\r",t.h2);
   cprintf("%4.1f\n\r",t.h3);
   cprintf("%4.1f\n\r",t.ho);
   cprintf("%4.1f\n\r",t.mort);
   fillwindow(x+4,y+12,x+33,y+14,BLACK,WHITE);
   cprintf("If you own 3 cards or more\n\r");
   cprintf("  of same color then the  \n\r");
   cprintf("     rent is doubled.     ");
}

                      //Display port at xy
void displayportxy(port p, int x, int y)
{
	fillwindow(x,y,x+35,y+7,BLACK,WHITE);
	cprintf("NAME     : %s\n\r",p.name);
   cprintf("TYPE     : Port\n\r");
   cprintf("PRICE    : %5.1f\n\r",p.price);
   if(p.code==12 || p.code==34)
   {
   	cprintf("RENT     : %4.1f * Dice Number\n\r",p.rent);
      cprintf("(IF YOU OWN %s )\n\r",p.spcl);
      cprintf("RENT     : %3.1f * Dice Number\n\r",p.nrent);
   }
   else
   {
   	cprintf("RENT     : %3.1f\n\r",p.rent);
      cprintf("(IF YOU OWN %s )\n\r",p.spcl);
      cprintf("RENT     : %3.1f\n\r",p.nrent);
   }
   cprintf("SELLINGP : %4.1f\n",p.mort);
}

void payrent(player pla)
{
	int n=noplayers();
   title ti;
   port po;
   player pl;
	int done=0,stop=0;
   fillwindow(33,15,77,19,BLACK,WHITE);
   for(int i=0;i<20 && done==0;i++)
   {
   	read(ti,i);
   	if(pla.pos==ti.code)
      {
      	for(int k=0;k<n && stop==0;k++)
         {
         	read(pl,k);
         	if(strcmpi(ti.own,pl.name)==0 && strcmpi(pl.name,pla.name)!=0)
            {
            	while(pla.bal<ti.rent)
               {
               	cprintf("You have to sell houses/properties to pay\n\r");
                  char ch=moneycond(ti.rent,pla,1);
               }
            	if(pla.bal>=ti.rent)
               {
               	pla.bal-=ti.rent;
                  pl.bal+=ti.rent;
                  pla.tot-=ti.rent;
                  pl.tot+=ti.rent;
                  fillwindow(37,15,60,19,BLACK,WHITE);
                  if(ti.nhu>=1 && ti.nhu<4) cprintf("%i house ",ti.nhu);
                  if(ti.nhu==4) cprintf("Hotel ");
                  cprintf("Rent    : %4.1f\n\r",ti.rent);
                  cprintf("Paid To : %s",pl.name);
                  stop=1;
                  write(pla,pla.i);
                  write(pl,k);  getch();
               }
            } done=1;
         }
      }
      if(i<6)
      {
      	read(po,i);
      	if(pla.pos==po.code)
      	{
      		for(int k=0;k<n;k++)
         	{
            	read(pl,k);
         		if(strcmpi(po.own,pl.name)==0 && strcmpi(pl.name,pla.name)!=0)
            	{
               	if(pla.bal<po.rent)
               	{
               		cprintf("You have to sell houses/properties to pay\n");
                  	cprintf("\rDo you want to continue?");
                     while(pla.bal<po.rent)
                     	char ch=moneycond(po.rent,pla,1);
               	}
            		if(pla.bal>=po.rent)
               	{
               		float rent=po.rent;
               		if(pla.pos==12 || pla.pos==34)
								rent*=pla.di;
               		pla.bal-=rent;
                  	pl.bal+=rent;
                  	pla.tot-=rent;
                  	pl.tot+=rent;
                     fillwindow(33,15,70,19,BLACK,WHITE);
                  	cprintf("Rent    : %4.1f\n\r",rent);
                  	cprintf("Paid To : %s",pl.name);
                     write(pl,k);
                  	write(pla,pla.i);
                     getch();
               	}
              	}
         	}
      	}
   	}
	}
}

void buildhouhot(player pl, title &ti)
{

	int k=1,b=0;
   title t;
   bank ba;
   loca lo;
   while(k && b<36)
   {
    	read(lo,b);
      if(strcmpi(lo.name,ti.name)==0)
      	k=0;
      b++;
   }
   b--;
   read(ba);
   k=propfunc(ti);

   if(k>=3)
   {

   	fillwindow(38 ,29,80,33,BLACK,WHITE);
      if(ti.unlock==5)
      	cprintf("You can't build houses/hotels anymore");
      else
      {
      	displaytitlexy(ti,38,12);
      	char ch;
         fillwindow(38 ,29,82,33,BLACK,WHITE);
       	cprintf("Do you want to build house/hotel here??[y/n]");
         ch=getch();
         while(ch!='n' && ch!='N' && ch!='y' && ch!='Y')
         	ch=getch();

         if(ch=='y' || ch=='Y')
         {
         	int done=1;
            for(int k=1;k<5 && done;k++)
            {
            	if(ti.unlock==k)
               {
               	int unl=0;
                  for(int i=0;i<20;i++)
                  {
                  	read(t,i);
                     if(strcmpi(t.own,ti.own)==0 && (t.type==ti.type
                        && t.unlock>=k))
                     	unl++;
                  }

                  if(unl>=3)
                  {
                  	if(pl.bal<ti.costh)
                     {
                     	clrscr();
                  		cprintf("You have to sell houses/properties to pay");
                        cprintf("\n\rDo you want to continue?");
                        ch=moneycond(ti.costh,pl,0);
                     }
                     if(pl.bal>=ti.costh && (ch=='y' || ch=='Y'))
                     {
                     	clrscr();
                        displaytitlexy(ti,38,12);
                        fillwindow(38 ,29,82,33,BLACK,WHITE);
                        cprintf("You sure you want to build house here?");
                        ch=getch();
                        while(ch!='y' && ch!='Y' && ch!='n' && ch!='N')
                        	ch=getch();
                        if(ch=='y' || ch=='Y')
                     	{
                        	ti.nhu++;
                        	lo.h=ti.nhu;
                        	write(lo,b);
                        	if(ti.nhu==1) ti.rent=ti.h1;
                        	if(ti.nhu==2) ti.rent=ti.h2;
                        	if(ti.nhu==3) ti.rent=ti.h3;
                        	if(ti.nhu==4) ti.rent=ti.ho;
                        	pl.bal-=ti.costh;
                        	pl.tot-=ti.costh;
                  			write(pl,pl.i);
                        	ba.bal+=ti.costh;
                        	ti.unlock=k+1;
                        	write(ba);
                        	cprintf("\n\rYou have built a house/hotel here");
                   		}
                     }
                  }
                  if(unl<3)
                  	cprintf("\n\rNot enough houses at other locations");
                  done=0;
               }
            }
         }
      }
   } getch();
}

void changerent(title &ti)
{
	int k=0;
	title t;
	for(int i=0;i<20;i++)
   {
   	read(t,i);
   	if(ti.type==t.type && strcmpi(ti.own,t.own)==0)
  			k++;
   }

   if(k==2)
   {
   	for(int i=0;i<20;i++)
      {
      	read(t,i);
         if(ti.type==t.type && strcmpi(ti.own,t.own)==0)
         {
         	t.unlock=1;
            t.rent=2*t.rent;
            write(t,i);
         }
      }
      ti.rent=2*ti.rent;
      ti.unlock=1;
   }
   if(k>=3)
   {
   	ti.rent=2*ti.rent;
      ti.unlock=1;
   }
}

char moneycond(double pri,player &pla,int co)
{
	char ch=getch();
   int no=1;
   while(ch!='n' && ch!='N' && ch!='y' && ch!='Y')
   	 ch=getch();
   	if(ch=='y' || ch=='Y')
   	{
      	no=selling(pla);
         while(pla.bal<pri && (ch=='y' || ch=='Y') && no)
         {
         	clrscr();
            fillwindow(41,14,80,22,BLACK,WHITE);
            cprintf("You still don't have enough money\n\r");
            cprintf("Do you still want to continue? ");
            ch=getch();
            if(ch=='y' || ch=='Y')
            	no=selling(pla);
         }
      }
   if(no && pla.bal<pri && ch=='y' && co)
   {
   	fillwindow(41,14,80,22,BLACK,WHITE);
      cprintf("Sorry You have no cards left\n");
      cprintf("  and you dont have enough \n");
      cprintf("    money to pay. So your \n");
      cprintf("        game is over.");
      removepl(pla);
   }
   else if(no && pla.bal<pri && ch=='y' && co!=0)
   	return 'n';
   return ch;
}

                            //buy property
void buyprop(player pla)
{
	char ch; clrscr();
   title ti;
   port po;
   bank ba;
   read(ba);
   for(int x=0;x<20;x++)
   {
   	read(ti,x);
   	if(pla.pos==ti.code)
      {
      	fillwindow(38,14,72,30,BLACK,WHITE);
      	if(strcmpi(ti.own,"bank")==0)
         {
            displaytitlexy(ti,38,12);
            //sidedetails(ti,pla);
   			fillwindow(38,27,72,31,BLACK,WHITE);
            cprintf("Do you want to buy? "); ch=getch();
            while(ch!='n' && ch!='N' && ch!='y' && ch!='Y')
            	ch=getch();
         	if(pla.bal<ti.price && (ch=='y' || ch=='Y'))
            {
					cprintf("You dont have enough money!!\n\r");
   				cprintf("Do you still want to buy? "); ch=getch();
            	ch=moneycond(ti.price,pla,0);
            }
            if(pla.bal>=ti.price)
            {
            	if(ch=='y' || ch=='Y')
            	{
            		strcpy(ti.own,pla.name);
               	pla.bal-=ti.price;
               	pla.tot-=ti.price;
                  write(pla,pla.i);
               	ba.bal+=ti.price;
                  changerent(ti);
               	write(ti,x);
               	write(ba);
            	}
            }
         }
         else if(strcmpi(ti.own,pla.name)==0)
         {
				buildhouhot(pla,ti);
            write(ti,x);
         }
         else if(strcmpi(ti.own,"bank")!=0)
            payrent(pla);

      }
      if(x<6)
      {
      	read(po,x);
      	if(pla.pos==po.code)
         {
         	fillwindow(38,14,72,30,BLACK,WHITE);
         	if(strcmpi(po.own,"bank")==0)
            {
            	displayportxy(po,38,12);
   				fillwindow(38,19,72,30,BLACK,WHITE);
            	cprintf("Do you want to buy? "); ch=getch();
               while(ch!='n' && ch!='N' && ch!='y' && ch!='Y')
            		ch=getch();
            	if(pla.bal<po.price && (ch=='y' || ch=='Y'))
            	{
            		cprintf("You dont have enough money!\n\r");
               	cprintf("Do you still want to buy? "); ch=getch();
                  ch=moneycond(po.price,pla,0);
            	}
               if(pla.bal>=po.price)
               {
               	if(ch=='y' || ch=='Y')
               	{
               		strcpy(po.own,pla.name);
                  	pla.bal-=po.price;
                  	pla.tot-=po.price;
                  	write(pla,pla.i);
                  	ba.bal+=po.price;
                     int pr=propfunc(po);
                     if(pr==1)
                     {
                     	port p;
                     	po.unlock=1;
                        po.rent=po.nrent;
                        for(int a=0;a<6;a++)
                        {
                        	read(p,a);
                           if(strcmpi(p.spcl,po.name)==0)
                           {
                           	p.unlock=1;
                        		p.rent=p.nrent;
                              write(p,a);
                           }
                        }
                     }
                     write(po,x);
                     write(ba);

               	}
               }   //mortagage if pla.bal<po.price
            }
            else if(strcmpi(po.own,"bank")!=0)
               payrent(pla);
         }
      }
   }
}
                       //Chance/Jail/Community Chest

void jail(player pla)
{
   char ch;
   bank ba;
   read(ba);
   fillwindow(37,15,72,19,BLACK,WHITE);
   cprintf("1. pay 500 and get out of jail\n\r");
   cprintf("2. Don't play next turn\n\r");
   cprintf("Option : "); ch=getch();
   while(ch!='1' && ch!='2')
   	ch=getch();
   if(ch=='1')
   {
   	if(pla.bal<500 && ch=='1')
      {
      	cprintf("You dont have enough money!!\n");
         cprintf("Do you still want to buy?[y/n] ");
         ch=moneycond(500,pla,0);
         fillwindow(37,15,72,19,BLACK,WHITE);
      }
   	if(pla.bal>=500)
      {
   		pla.bal-=500;
      	pla.tot-=500;
      	ba.bal=500+ba.bal;
         write(ba);
      	gotoxy(1,4);cprintf("You paid Rs. 500.0 to Bank");getch();
      }
      else pla.turn=0;
   }
   else if(ch=='2')
   	pla.turn=0;
   write(pla,pla.i);
}

void chance(player pla)
{
	bank ba;
   read(ba);
   float mon=0;
	fillwindow(21,11,90,29,BLACK,RED);
   ifstream fin("Chance.txt");
   char str[70];
   while(fin.getline(str,70))
   	cprintf("%s\n\r",str);
   fillwindow(42,30,75,33,BLACK,CYAN);
   switch(pla.di)
      {
      	case 2 : mon=-2000; break;
         case 3 : mon=2500; break;
         case 4 : mon=-1000; break;
         case 5 : mon=1000; break;
         case 6 : mon=-1500; break;
         case 7 : mon=2000; break;
         case 8 : mon=-3000; break;
         case 9 :
         			if(pla.pos==7)
         			{
         				pla.pos=23;
            			cprintf("You have reached Darjeeling");
                  }
         			if(pla.pos==20)
         			{
         				cprintf("You have reached Mumbai");
            			pla.pos=1;
                  } break;
         case 10 : gotoxy(1,1);
         			 pla.pos=9;
         			 cprintf("You are now at jail");
                   break;
         case 11 : mon=3000; break;
         case 12 : gotoxy(1,1);
         			 pla.pos=27;
         			 pla.turn=0;
         			 cprintf("Your next turn has been cancelled");
                   break;
      }
      char ch='y';
      if(pla.di%2==0 && pla.di!=10 && pla.di!=12)
      {
         if(pla.bal<mon)
         {
            while(pla.bal<mon)
            {
               cprintf("You don't have enough money\n\r");
            	cprintf("You have to sell property.");
            	ch=moneycond(mon,pla);
               fillwindow(42,30,75,33,BLACK,CYAN);
            }
         }
      }
      if(ch=='y')
      {
      	ba.bal-=mon;
      	pla.bal+=mon;
         pla.tot+=mon;
         write(ba);
      }
      if(pla.di%2==0 && pla.di!=10 && pla.di!=12)
      {
      	mon-=(2*mon);
      	cprintf("you have paid Rs. %4.1f\n\r",mon);
      	cprintf("      to the bank.");
      }
      else if(pla.di%2 && pla.di!=9)
      {
      	cprintf("You have recieved %4.1f\n\r",mon);
         cprintf("    from the bank.");
      }
   getch();
   write(pla,pla.i);
}

void communitychest(player pla)
{
	bank ba;
	read(ba);
   float mon=0;  char ch='y';
	fillwindow(21,11,90,31,BLACK,RED);
   ifstream fin("Community chest.txt");
   char str[70];
   while(fin.getline(str,70))
   	cprintf("%s\n\r",str);
   fillwindow(45,29,73,32,BLACK,CYAN);
   switch(pla.di)
   {
      	case 2 : {
         				mon=500*(noplayers()-1);
                     for(int i=0;i<noplayers();i++)
                     {
                     	player pl;
                        read(pl,i);
                     	if(strcmpi(pla.name,pl.name))
                        	pla.bal-=500;
                        write(pl,i);
                     }
                     cprintf("You recieved Rs. %4.1f\n\r",mon);
                     cprintf("    from everyone.  ");
         			}break;
      	case 3 : cprintf("You are now at jail");
         			pla.pos=9; break;
         case 4 : mon=2500; break;
         case 5 : mon=-1000; break;
         case 6 : mon=2000; break;
         case 7 : mon=-2000; break;
         case 8 : {
         				pla.pos=27; pla.turn=0;
                     cprintf("You can't play next turn");
         			} break;
         case 9 :
             {	for(int i=0;i<20;i++)
               {
               	title ti;
               	read(ti,i);
                  if(strcmpi(ti.own,pla.name)==0)
                  {
                  	if(ti.nhu==4) mon-=100;
                     if(ti.nhu<4) mon-=(ti.nhu*50);
                  }
               }
            		break;       }
         case 10 : mon=1500; break;
         case 11 : mon=-1500; break;
         case 12 : mon=3000; break;
      }
      if(pla.di%2 && pla.di!=9 && pla.di!=3)
      {
      	if(pla.bal<mon)
         {
            while(pla.bal<mon)
            {
               cprintf("You don't have enough money\n\r");
            	cprintf("You have to sell property.");
            	ch=moneycond(mon,pla);
            	fillwindow(45,29,73,33,BLACK,CYAN);
            }
         }
      }
      if(ch=='y')
      {
         ba.bal-=mon; write(ba);
         pla.bal+=mon;
         pla.tot+=mon;
      	if(pla.di%2==0 && pla.di!=2 && pla.di!=8)
      	{
      		cprintf("You have received Rs. %4.1f\n\r",mon);
         	cprintf("     from the Bank ");
      	}
      	if(pla.di%2 && pla.di!=3)
      	{
         	cprintf("You have paid %4.1f\n\r",mon);
         	cprintf("   to the bank.");
      	}
      }
   getch();
   write(pla,pla.i);
}
	/*
   else if(pla.di%2==1)
   {
   	float mon;
      switch(pla.di)
      {
      	case 3 : cprintf("You are now at jail");
         			pla.pos=9; break;
         case 5 : mon=1000; break;
         case 7 : mon=2000; break;
         case 11 : mon=1500; break;
         case 9 :
         	{
            	mon=0;
            	for(int i=0;i<20;i++)
               {
               	title ti;
               	read(ti,i);
                  if(strcmpi(ti.own,pla.name)==0)
                  {
                  	if(ti.nhu==4) mon+=100;
                     if(ti.nhu<4) mon+=(ti.nhu*50);
                  }
               }
            }break;
      }
      if(pla.di!=9 && pla.di!=3)
      {
      	if(pla.bal<mon)
         {
            while(pla.bal<mon)
            {
               cprintf("You don't have enough money\n\r");
            	cprintf("You have to sell property.");
            	char ch=moneycond(mon,pla);
            	fillwindow(45,29,73,33,BLACK,CYAN);
            }
         }
         cprintf("You have paid %4.1f\n\r",mon);
         cprintf("   to the bank.");
         ba.bal+=mon;
         pla.bal-=mon;
         pla.tot-=mon;
         bank ba;
         read(ba);
      }
   } */

                            //Selling property/houses

int selling(player &pla)
{
	clrscrb(pla.name);
	int ch,no;
   do
   {
   	clrscr();
		fillwindow(41,14,63,22,BLACK,WHITE);
      cprintf("1. Sell a Property\n\r");
      cprintf("2. Sell house/hotel\n\r");
      cprintf("0. Go Back\n\r");
      cprintf("Option : "); cin>>ch;
      switch(ch)
      {
      	case 1 : no=sellprop(pla); break;
         case 2 : sellhouse(pla); break;
      }
   }while(ch!=0);
   return no;
}


int sellprop(player &pla)
{
	title ti; port po;
	char na[18];      int fl=1;
   int no=displaysellprop(pla);
   if(no)
   {
   	fillwindow(65,14,90,27,BLACK,GREEN);
   	cprintf("What do you want to sell?\n\r");
   	gets(na);
   	for(int i=0;i<20 && fl;i++)
   	{
   		read(ti,i);
      	if(strcmpi(ti.name,na)==0 && strcmpi(ti.own,pla.name)==0)
      	{	sell(ti,pla); fl=0; }
      	else if(strcmpi(ti.name,na)==0 && strcmpi(ti.own,pla.name))
      	{	gotoxy(1,3);cprintf("You do not own this!!\n\r"); fl=0; }
			if(i<6)
      	{
      		read(po,i);
         	if(strcmpi(po.name,na)==0)
      		{	sell(po,pla); fl=0; }
      	}
   	}
   	if (fl==1)
   	{ gotoxy(1,3);	cprintf("Name entered incorrectly");}
   	getch();
   	clrscrb(pla.name);
   }
   getch();
   return no;
}

int displaysellprop(player pla)
{
	title ti;
   port po;
   int no=0;
	fillwindow(20,6,63,6,BLACK,CYAN);
   cprintf("Type  Name             Rent   Sellp  Houses");
   fillwindow(20,7,63,36,BLACK, BROWN);
   for(int i=1;i<5;i++)
   {
   	char ch;
      if(i==1) ch='R';
      if(i==2) ch='Y';
      if(i==3) ch='G';
      if(i==4) ch='B';
   	for(int k=0;k<20;k++)
      {
      	read(ti,k);
         if(ti.type==ch && strcmpi(ti.own,pla.name)==0)
         {
         	cprintf("%2c    %-17s%-6.1f %-6.1f   %-1i\n\r",
                    ch,ti.name,ti.rent,ti.mort,ti.nhu);
            no++;
         }
      }
   }
   for(int i=0;i<6;i++)
   {
   	read(po,i);
      if(strcmpi(po.own,pla.name)==0)
      {
      	cprintf("%4s  %-17s%-6.1f %-4.1f   -\n\r",
                 "Port",po.name,po.rent,po.mort);
         no++;
      }
   }
   if (no==0)
   	cprintf("       Sorry you don't have any cards");
   return no;
}

void sell(title ti,player &pla)
{
	title t;
   int flag=1;
   int k=3;
   if(ti.nhu!=0)
   {
   	gotoxy(1,k++);cprintf("You cannot sell this\n\r");
   	gotoxy(1,k++);cprintf("  you have built\n\r");
      gotoxy(1,k++);cprintf("  house(s)/hotel\n\r");
   	gotoxy(1,k++);cprintf("        here");
   	flag=0;
   }
   if(propfunc(ti)>=3 && flag)
   {
   	gotoxy(1,k++);cprintf("You have 2 or more\n\r");
      gotoxy(1,k++);cprintf("properties of same type\n\r");
      gotoxy(1,k++);cprintf("Are you sure you want to\n\r");
      gotoxy(1,k++);cprintf("     sell this?"); char ch;
      ch=getch();
   	while(ch!='n' && ch!='N' && ch!='y' && ch!='Y')
      	ch=getch();
      if(ch=='n' || ch=='N')
      	flag=0;
   }
	for(int i=0;i<20 && flag;i++)
   {
   	if(t.type==ti.type && strcmpi(t.name,ti.name)!=0)
      {
      	if(t.nhu>=1)
      	{
         	gotoxy(1,k++);cprintf("You cannot sell this\n\r");
            gotoxy(1,k++);cprintf("  you have built \n\r");
            gotoxy(1,k++);cprintf("  house(s)/hotel\n\r");
            gotoxy(1,k++);cprintf(" at %s\n\r",t.name);
            flag=0;
         }
      }
   }
   if(flag)
   {
   	int nfl=1;
      gotoxy(1,k++);cprintf("Are you sure you want to\n\r");
      gotoxy(1,k++);cprintf("     sell this?");
      char ch=1;
      while(ch!='n' && ch!='N' && ch!='y' && ch!='Y')
      	ch=getch();
      if(ch=='y' || ch=='Y')
      {
      	if(propfunc(ti)>3 || propfunc(ti)<3)
         {
         	fstream fio("Tcards.dat",ios::binary | ios::in | ios::out);
         	for(int p=0;p<20;p++)
            {
            	title tii; read(tii,p);
               if(ti.code==tii.code)
               {
               	gotoxy(1,k++);cprintf("You have sold\n\r");
                  gotoxy(1,k++);cprintf("%s",tii.name);
                  fio.seekg(p*sizeof(tii));
                  fio.read((char*)&tii,sizeof(tii));
                  write(tii,p);
                  pla.bal+=ti.mort;
                  pla.tot+=ti.mort;
                  write(pla,pla.i);
                  bank ba;
                  read(ba);
                  ba.bal-=ti.mort;
                  write(ba);
                  nfl=0; getch();
               }
            }
         }
         //else if(propfunc(ti)<3)
         else if(propfunc(ti)==3)
         {
         	for(int p=0;p<20;p++)
            {
            	title t; read(t,p);
               if(t.code==ti.code && t.nhu==0)
               {
               	strcpy(t.own,"BANK");
                  t.rent/=2;
                  t.unlock=0;
                  write(t,p);
                  gotoxy(1,k++);cprintf("You have sold\n\r");
                  gotoxy(1,k++);cprintf("%s \n\r",ti.name);
                  pla.bal+=ti.mort;
                  pla.tot+=ti.mort;
                  write(pla,pla.i);
                  bank ba;
                  read(ba);
                  ba.bal-=ti.mort;
                  write(ba);
                  nfl=0;
               }
               else if(t.type==ti.type && strcmpi(t.own,pla.name)==0)
               {
                  t.rent/=2;
                  t.unlock=0;
                  write(t,p);
               }
            }
         }
      }
   }
}

void sell(port po,player &pla)
{
	char ch;
   port p;
   int k=3;
	if(po.unlock==1)
   {
   	gotoxy(1,k++);cprintf("Your rent will\n\r");
      gotoxy(1,k++);cprintf("decrease if you\n\r");
      gotoxy(1,k++);cprintf("sell %s\n\r",po.name);
      gotoxy(1,k++);cprintf("You also own\n\r");
      gotoxy(1,k++);cprintf("%s\n\r",po.spcl);
   }
   gotoxy(1,k++);cprintf("Are you sure you\n\r");
   gotoxy(1,k++);cprintf("You want to sell?");
   ch=getch();
   while(ch!='y' && ch!='Y' && ch!='N' && ch!='n')
   	ch=getch();
   bank ba;
   read(ba);
   if((ch=='y' || ch=='Y') && po.unlock==0)
   {
   	for(int i=0;i<6;i++)
      {
      	read(p,i);
         if(p.code==po.code)
         {
         	strcpy(p.own,"BANK");
            pla.bal+=po.mort;
            pla.tot+=po.mort;
            write(pla,pla.i);
            ba.bal-=po.mort;
            write(ba);
            gotoxy(1,k++);cprintf("You have sold\n\r");
            gotoxy(1,k++);cprintf("%s\n\r",po.name);
         }
         write(p,i);
      }
   }
   else if((ch=='y' || ch=='Y') && po.unlock==1)
   {
   	int i=0;
   	ifstream fin("PCards.dat",ios::binary);
      while(fin.read((char*)&p,sizeof(p)))
      {
      	if(p.code==po.code|| strcmpi(p.name,po.spcl)==0)
         {
         	if(strcmpi(p.name,po.spcl)==0)
            	strcpy(p.own,pla.name);
            write(p,i);
            pla.bal+=po.mort;
            pla.tot+=po.mort;
            write(pla,pla.i);
            ba.bal-=po.mort;
            write(ba);
            gotoxy(1,k++);cprintf("You have sold\n\r");
            gotoxy(1,k++);cprintf("%s\n\r",po.name);
         } i++;
      }
   }
}

            //House selling
            //
void displaysellhou(player pla)
{
	title ti;
   fillwindow(20,6,63,6,BLACK,CYAN);
   cprintf("Type  Name             Houses HRent  Sellp ");
   fillwindow(20,7,63,36,BLACK, BROWN);
   for(int i=1;i<6;i++)
   {
   	char ch;
      if(i==1) ch='R';
      if(i==2) ch='Y';
      if(i==3) ch='G';
      if(i==4) ch='B';
   	for(int k=0;k<20;k++)
      {
      	read(ti,k);
         if(ti.type==ch && strcmpi(ti.own,pla.name)==0 && ti.nhu>0)
         	cprintf("%2c    %-17s  %-5i%-6.1f %4.1f\n\r",
                     ch,ti.name,ti.nhu,ti.rent,ti.costh/2);
      }
   }
}

void sellh(title ti, player &pla)
{
   char ch=1;
   title t;
   int k=4,flag=1;
   for(int i=0;i<20 && flag;i++)
   {
   	read(t,i);

      if(t.type==ti.type && strcmpi(t.own,ti.own)==0)
      {
      	if(t.nhu>ti.nhu)
         {
            gotoxy(1,k++);cprintf("You can't sell this house");
            gotoxy(1,k++);cprintf("You have more houses");
            gotoxy(1,k++);cprintf("at %s",t.name); flag=0;
         }
      }
   }
   if(flag)
   {
      gotoxy(1,k++); cprintf("If you sell this then");
      ifstream fin("TCards.dat",ios::binary);
		float re1;
      while(fin.read((char*)&t,sizeof(t)))
      {
      	if(t.code==ti.code)
         {
         	switch(ti.nhu)
            {
            	case 1 : re1=t.rent*2; break;
               case 2 : re1=ti.h1; break;
               case 3 : re1=ti.h2; break;
               case 4 : re1=ti.h3; break;
            }
         }
      }
      fin.close();
      gotoxy(1,k++);cprintf("rent decreases from");
      gotoxy(1,k++);cprintf("%4.1f to %4.1f",ti.rent,re1);
      gotoxy(1,k++); cprintf("Are you sure you want");
      gotoxy(1,k++); cprintf("   to sell this?");
      while(ch!='y' && ch!='Y' && ch!='N' && ch!='n')
   		ch=getch();
      if(ch=='y' || ch=='Y')
      {
      	int i=0; fin.open("TCards.dat",ios::binary);
         while(fin.read((char*)&t,sizeof(t)))
         {
         	if(t.code==ti.code)
            {
               ti.unlock--;
               switch(ti.nhu)
      			{
      				case 1 : ti.rent=t.rent*2; break;
         			case 2 : ti.rent=ti.h1; break;
         			case 3 : ti.rent=ti.h2; break;
         			case 4 : ti.rent=ti.h3; break;
      			}
               pla.bal+=(ti.costh/2);
               pla.tot+=(ti.costh/2);
               write(pla,pla.i);
               bank ba; read(ba);
               ba.bal-=(ti.costh/2); write(ba);
               inloca(ti);
               ti.nhu--; write(ti,i);
            } i++;
         }    fin.close();
      }
   }
}

void inloca(title ti)
{
	loca lo;
	for(int i=0;i<36;i++)
   {
   	read(lo,i);
      if(ti.code==lo.code)
      {
      	lo.h--;
         write(lo,i);
      }
   }
}

void sellhouse(player &pla)
{
   title ti;
   char na[18];
   displaysellhou(pla);
   fillwindow(65,14,90,27,BLACK,GREEN);
   gotoxy(1,1);cprintf("Which place's house\n\r");
   gotoxy(1,2);cprintf("do you want to sell?\n\r");
   gets(na);
   int fl=1;
   for(int i=0;i<20 && fl;i++)
   {
   	read(ti,i);
      if(strcmpi(ti.name,na)==0 && strcmpi(ti.own,pla.name)==0)
      {
      	if(ti.nhu!=0)
      	{	sellh(ti,pla); fl=0; }
         else
         {
         	gotoxy(1,4);cprintf("You don't have any house!");
            gotoxy(1,5);cprintf("        here");
         }
      }
      else if(strcmpi(ti.name,na)==0 && strcmpi(ti.own,pla.name))
      {	gotoxy(1,4);cprintf("You do not own this!!\n\r"); fl=0; }
   }
   if (fl==1)
   { gotoxy(1,4);	cprintf("Name entered incorrectly");}
   getch();
   clrscrb(pla.name);
}

                             //Game End

void enddisplay(player pl,int a)
{
	if(a==0)
   {
   	fillwindow(17,2,67,2,BLACK,GREEN);
      cprintf("WINNER - %s",pl.name);
   }
   else if(a==1)
   {
   	fillwindow(17,2,73,2,BLACK,RED);
      cprintf("1st RUNNER UP - %s",pl.name);
   }
   else if(a==2)
   {
   	fillwindow(17,2,73,2,BLACK,RED);
      cprintf("2nd RUNNER UP - %s",pl.name);
   }
   else if(a==3)
   {
   	fillwindow(17,2,73,2,BLACK,RED);
      cprintf("3rd RUNNER UP - %s",pl.name);
   }
	fillwindow(5,5,49,5,BLACK,CYAN);
   cprintf("TYPE  HOUSES  NAME             RENT   PRICE");
   fillwindow(5,6,49,29,BLACK,YELLOW);
   title ti;
   port po;
   int b=0;
   for(int k=0;k<4;k++)
   {
   	char ch;
   	switch(k)
      {
      	case 1 : ch='R'; break;
         case 2 : ch='Y'; break;
         case 3 : ch='G'; break;
         case 4 : ch='B'; break;
      }
   	for(int i=0;i<20;i++)
   	{
   		read(ti,i);
      	if(strcmpi(ti.own,pl.name)==0)
      	{
         	if(ti.type==ch)
            {
            	if(b==0)
               {
               	b++;
                  gotoxy(1,b);
               	cprintf("%3c%6i     %-17s%4.1f %4.1f",
                          ch,ti.nhu,ti.name,ti.rent,ti.price);
               }
               else
               {
               	b++;
                  gotoxy(1,b);
               	cprintf("   %6i     %-17s%4.1f %4.1f",
                          ti.nhu,ti.name,ti.rent,ti.price);
               }
            }
         }
   	}
   }
   for(int i=0;i<6;i++)
   {
   	read(po,i);
      if(strcmpi(po.own,pl.name)==0)
      {
      	if(!b)
         {
         	b++;
            gotoxy(1,b);
            cprintf("PORT%5c     %-17s%6.1f %4.1f",
                     '-',po.name,po.rent,po.price);
         }
         else
         {
         	b++;
            gotoxy(1,b);
            cprintf("    %5c     %-17s%6.1f %4.1f",
                    '-',po.name,po.rent,po.price);
         }
      }
   }
}



char endgame(player p)
{
   fullwin();
   fillwindow(34,19,80,25,BLACK,WHITE);
   char ch=1,k;
   cprintf("Are you sure you want to quit?");
   while(ch!='y' && ch!='Y' && ch!='n' && ch!='N')
   	ch=getch();
   k=ch;
   if(ch=='y' || ch=='Y')
   {
   	ch=1;
      gotoxy(1,1); cprintf("Do you want to continue later?");
      while(ch!='y' && ch!='Y' && ch!='n' && ch!='N')
   		ch=getch();
      if(ch=='n' || ch=='N')
      {
         fullwin();
   		player pl,pla[4];
         title ti;
         port po;
   		for(int i=0;i<noplayers();i++)
   		{
         	read(pl,i);
            for(int k=0;k<20;k++)
            {
            	read(ti,k);
               if(strcmpi(ti.own,pl.name)==0)
               {
               	pl.tot+=ti.mort;
                  pl.tot+=(ti.nhu*0.5*ti.costh);
               }
               if(k<6)
               {
               	read(po,k);
                  if(strcmpi(po.own,pl.name)==0)
               	{
               		pl.tot+=po.mort;
               	}
               }
            }
            write(pl,i);
            pla[i]=pl;
   		}
         for(int i=0;i<noplayers();i++)
         {
         	pl=pla[i];
            int pos=i;
            for(int k=i;k<noplayers();k++)
            {
            	if(pla[k].tot>pl.tot)
               {
               	pos=k;
                  pl=pla[k];
               }
            }
            pla[pos]=pla[i];
            pla[i]=pl;
         }
         for(int i=0;i<noplayers();i++)
         {
         	fullwin();
         	enddisplay(pla[i],i);
            ch=getch();
            if(ch==27) i--;
         }
         end=0;
         rem();
      }
      else if(ch=='y' || ch=='Y')
      {
      	bank ba;
         read(ba);
         ba.cont=1;
         write(ba);
         end=0;
      }
   }
   if(k=='y')
   	return '2';
   else
   	return 1;
}

void removepl(player pl)
{
	if(noplayers()==2)
	{
   	int i=0;
      if(pl.i==0)
      	i=1;
      player p;
      read(p,i);
      enddisplay(p,i);
      enddisplay(pl,pl.i);
      end=0;
      rem();
   }
   else
   {
   	for(int i=pl.i+1;i<noplayers();i++)
      {
      	player p;
         read(p,i);
         p.i=pl.i;
      	write(p,pl.i);
         pl.i++;
      }
   }
}
void rem()
{
	remove("TCardsg.dat");
   remove("PCardsg.dat");
   remove("Players.dat");
   remove("Bank.dat");
   for(int i=0;i<36;i++)
   {
   	loca lo;
      read(lo,i);
      lo.h=0;
      write(lo,i);
   }
}
