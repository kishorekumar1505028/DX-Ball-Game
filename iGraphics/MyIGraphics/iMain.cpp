# include "iGraphics.h"
# include <stdlib.h>
#include<math.h>
FILE *fp;
int lv=0,lex=40,a[15],showx[15],showy[15],blo,lock=0,counter=0,highscore=0,x=750;
int c[260],bx[260],px[45],py[45],by[260],A=750,B=50,p=0,Dx=3,dx=3,dy=3,life=3,flagboundary=0,flagmagnet=0,flagmagnet2=0;
int high_score(void)
{
    fp=fopen("Highscore.txt","r");
    fscanf(fp,"%d",&highscore);
    fclose(fp);
    return highscore;

}
void ini(void)
{
    int i;
    A=x;
    B=50;
    highscore=high_score();
    for(i=0; i<15; i++)
    {
        if(showy[i]>0)
            showy[i]=-100;
    }
}
void level(int lv) //
{
    int i,counter2=0,j,t;
    blo=0;
    for(i=0; i<15; i++)
    {
        showx[i]=100;
        showy[i]=-100;
    }

    if(lv==0)
        fp=fopen("level0.txt","r");
    else if(lv==1)
        fp=fopen("level1.txt","r");
    else if(lv==2)
        fp=fopen("level2.txt","r");
    else if(lv==3)
        fp=fopen("level3.txt","r");
    else if(lv==4)
        fp=fopen("level4.txt","r");
    else if(lv==5)
        fp=fopen("level5.txt","r");
    else if(lv==6)
        fp=fopen("level6.txt","r");
    else if(lv==7)
        fp=fopen("level7.txt","r");
    for(i=0; i<260; i++)
    {
        fscanf(fp,"%d",&c[i]);
        bx[i]=50*(i%26);
        by[i]=575-25*(i/26);
        if(c[i])
            blo++;
    }
    fclose(fp);
    //to keep the random values of blocks in an array
    for(i=0;; i++)
    {
        t=rand()%260;
        if(c[i])
        {
            for(j=0; j<counter2; j++)
            {
                if(a[j]==t)
                    break;
            }
            if(j==counter2)
            {
                a[j]=t;
                counter2++;
            }
        }
        if(counter2==15)
            break;
    }
}
void xchange(void) //to move the bar
{
    if(x>(1290-lex))
        x=1290-lex;
    if(x<(lex+10))
        x=lex+10;
    if ((flagmagnet==1)&&( flagmagnet2==1))
    {
        A=x;
    }
}
int mod(int m)
{
    if(m>=0)

        return m;
    return -m;
}
void ballChange() //to change ball's co-ordinate
{
    int i,hit=0,j;
    double d1,d2,d3,d4;
    A+=dx;
    B+=dy;

    d1=sqrt((x-lex-A)*(x-lex-A)+(30-B)*(30-B));
    d2=sqrt((x+lex-A)*(x+lex-A)+(30-B)*(30-B));
    //side of bar
    if(d1<20||d2<20)
    {
        dy=-dy;
        if((d1<20&&dx>0)||(d2<20&&dx<0))
        {
            if ((flagmagnet==1))
            {
                dx=0 ;

                dy=0;
                flagmagnet2=1;
                p=0; //if p=0 ball is on the bar
            }
            else
                dx=-dx;
        }

        if((mod(dx)==Dx))
        {
            if ((flagmagnet==1))
            {
                dx=0 ;
                dy=0;
                flagmagnet2=1;
                p=0;
            }
            else
                dx=2*dx; //to change ball's speed
        }
    }
    //left and right wall
    if(A>1290||A<10)
        dx=-dx;
    //roof
    if(B>640)
        dy=-dy;

    if(flagboundary&&B<=22&&B>=20)
        dy=-dy;
    //bar
    if(B<50&&B>=45&&A<(x+lex)&&A>(x-lex))
    {
        if ((flagmagnet==1))
        {
            dx=0 ;
            dy=0;
            flagmagnet2=1;
            p=0;
        }
        else
        {
            dy=-dy;
            if(mod(dx)==Dx*2)
                dx/=2; // to change ball's speed
        }
    }
    //what happens after collision with blocks
    for(i=0; i<260; i++)
    {
        if(c[i])
        {
            if(A<=(bx[i]+50)&&A>=bx[i]&&((B>=(by[i]-10)&&B<=(by[i]-5))||(B<=(by[i]+35)&&B>=(by[i]+30))))
            {
                dy=-dy;
                if((c[i]!=8)&&(c[i]!=7)&&(c[i]!=5))
                {
                    c[i]=0;
                    hit=1;
                    counter++; // count = score
                    blo--; // number of remaining blocks
                }
                else if(c[i]==8||c[i]==7)
                    c[i]--;
            }
            if(B<=(by[i]+25)&&B>=by[i]&&((A>=(bx[i]-10)&&A<=(bx[i]-5))||(A<=(bx[i]+60)&&A>=(bx[i]+55))))
            {
                dx=-dx;

                if((c[i]!=8)&&(c[i]!=7)&&c[i]!=5)
                {
                    c[i]=0;
                    hit=1;
                    counter++;
                    blo--;
                }
                else if(c[i]==8||c[i]==7)
                    c[i]--;
            }
            // flagvanish=0;
            d1=sqrt((bx[i]-A)*(bx[i]-A)+(by[i]-B)*(by[i]-B));
            d2=sqrt((bx[i]+50-A)*(bx[i]+50-A)+(by[i]-B)*(by[i]-B));
            d3=sqrt((bx[i]-A)*(bx[i]-A)+(by[i]+25-B)*(by[i]+25-B));
            d4=sqrt((bx[i]+50-A)*(bx[i]+50-A)+(by[i]+25-B)*(by[i]+25-B));
            if(d1<10||d2<10||d3<10||d4<10)
            {
                dx=-dx;
                dy=-dy;
                if((c[i]!=8)&&(c[i]!=7)&&(c[i]!=5)) // if 8 3 time break , if 7 2 time break , if 5 never break
                {
                    c[i]=0;
                    hit=1;
                    counter++;
                    blo--;
                }
                else if(c[i]==8||c[i]==7)
                    c[i]--;
            }
            if(hit)
            {
                for(j=0; j<15; j++)
                {
                    if(a[j]==i) // show hidden block
                    {
                        showx[j]=50*(i%26);
                        showy[j]=575-25*(i/26);
                    }
                }
                hit=0;
            }
        }
    }
    //update high score
    if(counter>highscore)
    {
        highscore=counter;
        fp=fopen("Highscore.txt","w");
        fprintf(fp,"%d",highscore);
        fclose(fp);
    }
    if(B<-10) // what happens if ball is missed
    {
        if(life>0)
        {
            life--;
            //  flagrestart=1;
            p=0;
            flagmagnet=0;
        }
        else
            lock=3;

    }
}
void scoredraw(int sx,int sy,int sc) //sx & sy are co-ordinates of string
{
    switch(sc)
    {
    case 0:
        iText(sx,sy,"0",GLUT_BITMAP_TIMES_ROMAN_24);
        break;
    case 1:
        iText(sx,sy,"1",GLUT_BITMAP_TIMES_ROMAN_24);
        break;
    case 2:
        iText(sx,sy,"2",GLUT_BITMAP_TIMES_ROMAN_24);
        break;
    case 3:
        iText(sx,sy,"3",GLUT_BITMAP_TIMES_ROMAN_24);
        break;
    case 4:
        iText(sx,sy,"4",GLUT_BITMAP_TIMES_ROMAN_24);
        break;
    case 5:
        iText(sx,sy,"5",GLUT_BITMAP_TIMES_ROMAN_24);
        break;
    case 6:
        iText(sx,sy,"6",GLUT_BITMAP_TIMES_ROMAN_24);
        break;
    case 7:
        iText(sx,sy,"7",GLUT_BITMAP_TIMES_ROMAN_24);
        break;
    case 8:
        iText(sx,sy,"8",GLUT_BITMAP_TIMES_ROMAN_24);
        break;
    case 9:
        iText(sx,sy,"9",GLUT_BITMAP_TIMES_ROMAN_24);
        break;
    }
}
void func(void)
{
    int i=0;
    if(lock==1) // show playing page
    {
        if(!p)
            ini();
        if(p)
        {
            for(i=0; i<15; i++)
                showy[i]--;
            ballChange();
        }
        if (!blo)
        {
            lv++;
            level(lv);
            A=750;
            B=50;
            dx=Dx;
            dy=3;
            p=0;
        }
        for(i=0; i<15; i++)
        {
            if(showy[i]==40&&showx[i]>=(x-lex-50)&&showx[i]<=(x+lex))
            {
                if(i==0)
                    life++;
                if(i==5||i==10)
                {
                    life--;
                }
                if(i%5==1)
                {
                    lex+=10;
                }
                if(i%5==2)
                {
                    lex-=10;
                }
                if (i%5==3)
                {
                    flagmagnet=1 ;
                }
                if (i%5==4)
                {
                    flagboundary=1;
                }
                showy[i]=-100;
            }
        }
        if(flagboundary&&flagboundary<=800)
            flagboundary++;
        if(flagboundary==801)
            flagboundary=0;
    }
}
void iscore(void) // creating score
{
    int nscore;
    nscore=counter;
    scoredraw(150,50,nscore%10);
    nscore/=10;
    scoredraw(125,50,nscore%10);
    nscore/=10;
    scoredraw(100,50,nscore);
}
/*
	function iDraw() is called again and again by the system.
*/

void iDraw()
{
    int i,j,d,e,Px,Py;
    //place your drawing codes here
    iClear();

    if(lock==1)
    {
        for(i=0; i<15; i++)
        {
            if(i==0)
                iSetColor(0,255,0);
            else if(i==5||i==10)
                iSetColor(255,0,0);
            else if(i%5==1)
                iSetColor(255,255,0);
            else if(i%5==2)
                iSetColor(0,255,255);
            else if(i%5==3)
                iSetColor(255,0,255);
            else if(i%5==4)
                iSetColor(200,200,200);
            iFilledRectangle(showx[i],showy[i],50,25);
        }
        iSetColor(30,120,240);
        iText(50,50,"score:");
        iscore();
        iSetColor(216,216,216);
        iFilledRectangle(x-lex,20,2*lex,20);
        iFilledCircle(x-lex,30,10);
        iFilledCircle(x+lex,30,10);
        iSetColor(220,220,50);
        if(!p)
            iFilledCircle(x,50,10);
        else
            iFilledCircle(A,B,10);
        for(i=0; i<life; i++)
            iFilledCircle(50+50*i,625,10);
        for(i=0; i<260; i++)
        {
            if(c[i]==1)
                iSetColor(220,10,10);//red
            else if(c[i]==2)
                iSetColor(250,10,130);//Pink
            else if(c[i]==3)
                iSetColor(160,30,205);//light blue
            else if(c[i]==4)
                iSetColor(90,30,140);//blue
            else if(c[i]==5)
                iSetColor(117,103,103);
            else if(c[i]==6)
                iSetColor(128,0,0);
            else if(c[i]==7)
                iSetColor(0,255,255);
            else if(c[i]==8)
                iSetColor(128,128,0);//gray
            else if(c[i]==9)
                iSetColor(250,250,0);//yellow
            else
                iSetColor(0,0,0);
            if(c[i])
            {
                iFilledRectangle(bx[i],by[i],50,25);
                iSetColor(0,0,0);
                iRectangle(bx[i],by[i],50,25);
            }
            iSetColor(25,25,25);
            Px=50*(i%26);

            Py=625-25*(i/26);
            if ((flagboundary!=0)&&(flagboundary<=800))
            {
                iSetColor(0,255,0) ;
                iFilledRectangle(0,10,1400,2) ;
            }
        }
    }
    if(!lock)
    {
        iSetColor(255,0,255);
        iFilledCircle(250,250,75);
        iSetColor(255,0,0);
        iFilledCircle(600,250,75);
        iSetColor(0,0,255);
        iFilledCircle(950,250,75);
        iSetColor(0,255,0) ;
        iText(600,600,"DXBALLGAME",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0,0,0) ;
        iText(200,250,"PLAY GAME",GLUT_BITMAP_HELVETICA_18);
        iText(550,250,"HIGH SCORE",GLUT_BITMAP_HELVETICA_18);
        iText(910,250,"END GAME",GLUT_BITMAP_HELVETICA_18);
        counter=0;
    }
    if(lock==2)
    {
        iClear();
        highscore=high_score();
        iSetColor(200,200,200);
        iFilledCircle(600,250,75);
        iSetColor(30,30,30);
        iText(530,250,"High score:",GLUT_BITMAP_HELVETICA_18);
        scoredraw(660,250,highscore%10);
        scoredraw(645,250,(highscore/10)%10);
        scoredraw(630,250,(highscore/10)/10);

    }
    if(lock==3)
    {
        iClear();
        iSetColor(255,0,0);
        iFilledCircle(950,500,75);
        iSetColor(255,255,0);
        iFilledCircle(250,500,75);
        iSetColor(255,0,255);
        iFilledCircle(600,500,75);
        iSetColor(30,30,30);
        iText(200,500,"Game Over",GLUT_BITMAP_HELVETICA_18);
        iText(900,500,"Main Menu",GLUT_BITMAP_HELVETICA_18);
        iText(570,500,"exit",GLUT_BITMAP_HELVETICA_18);
        iText(190,470,"Your score:",GLUT_BITMAP_HELVETICA_18);
        scoredraw(305,470,counter%10);
        scoredraw(295,470,(counter/10)%10);
        scoredraw(285,470,(counter/10)/10);
        // if (lastlife==0) counter=0;
    }
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //place your codes here
    x=mx;
    xchange();
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my) // mouse er sathe programm er somonnoy
{
    double d1,d2,d3,d4,d5;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP&&lock==1)
    {
        if(p==0&&flagmagnet2==1)
        {
            dx=3;
            dy=3;
        }
        p=1;
        flagmagnet2=0;
        printf("%d",blo);
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        d1=sqrt((mx-250)*(mx-250)+(my-250)*(my-250));
        d2=sqrt((mx-600)*(mx-600)+(my-250)*(my-250));
        d3=sqrt((mx-950)*(mx-950)+(my-250)*(my-250));
        d4=sqrt((mx-950)*(mx-950)+(my-500)*(my-500));
        d5=sqrt((mx-600)*(mx-600)+(my-500)*(my-500));
        if(d1<75&&!lock)
            lock=1;
        if(d2<75&&lock==2)
            lock=0;
        else if(d2<75&&!lock)
            lock=2;
        if(d3<75&&!lock)
            exit(0);
        if(d4<75&&lock==3)
        {
            lock=0;
            A=750;
            B=50;
            x=750;
            dx=Dx;
            dy=3;
            p=0;
            flagmagnet2=0;
            lv=0;
            level(0);
            life=3;
        }
        if(d5<75&&lock==3)
        {
            A=750;
            B=50;
            dx=Dx;
            dy=3;
            p=0;
            exit(0);
        }
    }
}
/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    int t ;
    if(key == 'x')
    {
        //do something with 'x'
        exit(0);
    }
    if(key == 'l')
    {
        //do something with 'x'
        level(++lv);
        p=0;
    }
    if(key == 'w')
    {
        //do something with 'x'
        level(--lv);
        p=0;
    }
    if(key == 'b') // cheatcode
    {
        //do something with 'x'
        life++ ;

    }
    if(key == 'p')
    {
        //do something with 'x'
        iPauseTimer(t) ;

    }
    if(key == 'r')
    {
        //do something with 'x'
        iResumeTimer(t) ;

    }


    if(key == 'k') // cheatcode
    {
        //do something with 'x'
        flagboundary=1 ;
    }







    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END&&lock==1)
    {
        lock=0;
    }
    else if(key == GLUT_KEY_END&&!lock)
    {
        exit(0);
    }
    if(key == GLUT_KEY_LEFT)
    {
        x-=20;
        xchange();
    }
    if(key == GLUT_KEY_RIGHT)
    {
        x+=20;
        xchange();
    }
    if(key == GLUT_KEY_UP)
    {
        if(p==0&&flagmagnet2==1)
        {
            dx=3;
            dy=3;
        }
        flagmagnet2=0;
        p=1;
    }
    //place your codes for other keys here
}

int main()
{
    high_score();
    //block();
    level(0);
    iSetTimer(1,func);
    //place your own initialization codes here.
    iInitialize(1300, 650, "MouseDemo");
    return 0;
}
