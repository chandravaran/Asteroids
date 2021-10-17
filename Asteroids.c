#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <process.h>
#include <string.h>
#include <time.h>
union REGS i, o;
void showmouseptr()
{
	i.x.ax = 1;
	int86(0x33, &i, &o);
}
void restrictmouseptr(int x1, int y1, int x2, int y2)
{
	i.x.ax = 7;
	i.x.cx = x1;
	i.x.dx = x2;
	int86(0x33, &i, &o);
	i.x.ax = 8;
	i.x.cx = y1;
	i.x.dx = y2;
	int86(0x33, &i, &o);
}
void getmousepos(int *button, int *x, int *y)
{
	i.x.ax = 3;
	int86(0X33, &i, &o);

	*button = o.x.bx;
	*x = o.x.cx;
	*y = o.x.dx;
}
int bx[300], by[300], bc[300], ax[300], at[300], bx1[500], by1[500], bc1[500], ax1[500], at1[500];
void spaceship(int a, int b, int g)
{
	rectangle(a, b - 10, a + 30, b);
	rectangle(a + 10, b - 20, a + 20, b - 10);
	line(a + 15, b - 25, a + 15, b - 20);
	settextstyle(0, 0, 0);
	outtextxy(g - 140, b - 20, "press esc to exit");
	rectangle(g - 150, b - 20, g, b);
	showmouseptr();
	restrictmouseptr(480, 0, 620, 480);
}
void bullet(int d, int e)
{
	line(d + 15, e - 25, d + 15, e - 20);
	//	delay(10);
}
void enemies(int ax[], int at[], int *t, int k, int y)
{
	int b;
	ax[y] = k;
	at[*t] = 0;
	//*t++;
	setcolor(WHITE);
	for (b = 0; b < (*t - 1); b++)
	{
		if (at[b] != -100)
		{
			circle(ax[b], at[b], 2);
		} //delay(0);
	}
	setcolor(BLACK);
	for (b = 0; b < (*t - 1); b++)
	{
		if (at[b] != -100)
		{
			circle(ax[b], at[b] - 10, 2);
		}
	}
	//at[*t]=0;
	for (b = 0; b < (*t - 1); b++)
	{
		if (at[b] != -100)
		{
			at[b] += 10;
		}
	}
}
void enemies1(int ax[], int at[], int *t, int k, int y)
{
	int b;
	ax[y] = k;
	//*t++;
	setcolor(WHITE);
	for (b = 0; b < (*t - 1); b++)
	{
		if (at[b] != -100)
		{
			circle(ax[b], at[b], 4);
		} //delay(0);
	}
	setcolor(BLACK);
	for (b = 0; b < *t - 1; b++)
	{
		if (at[b] != -100)
		{
			circle(ax[b], at[b] - 15, 4);
		}
	}
	at[*t] = 0;
	for (b = 0; b < *t - 1; b++)
	{
		if (at[b] != -100)
		{
			at[b] += 15;
		}
	}
}
int main()
{
	//srand(time(0));
	int c, i, button, h, j, x = 0, y = 0, sx = 10, sy, gd = DETECT, gm, ch, bn = 0, n = 0, f, p = -1, d, k = 5, e;
	char a[50];
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); //reteving the bgi file
	c = getmaxx();
	sy = getmaxy();
	while (1) //infinite loop
	{
		if (y < 50)
		{
			srand(time(0));
			/*setcolor(BLACK);
		settextstyle(2,0,5);
		sprintf(a,"x=%d y=%d",h,j);
		outtextxy(480,15,a);*/
			sprintf(a, "score=%d", y); //outtextxy(480,15,"adklwilejh")
			outtextxy(480, 70, a);
			outtextxy(480, 15, "Get a score greater");
			outtextxy(480, 30, "than 50 to reach L-2");
			getmousepos(&button, &h, &j);
			if ((h > c - 140) && (h < c) && (j > sy - 20) && (j < sy) && (button == 1))
			{
				closegraph();
				exit(10);
			}
			setcolor(WHITE);
			//settextstyle(2,0,5);
			//sprintf(a,"x=%d y=%d",h,j);
			//outtextxy(480,15,a);
			sprintf(a, "score=%d", y);
			outtextxy(480, 70, a);
			outtextxy(480, 15, "Get a score greater");
			outtextxy(480, 30, "than 50 to reach L-2");
			setcolor(WHITE);
			rectangle(sx, sy - 10, sx + 30, sy);
			rectangle(sx + 10, sy - 20, sx + 20, sy - 10);
			line(sx + 15, sy - 25, sx + 15, sy - 20);
			settextstyle(0, 0, 0);
			outtextxy(c - 140, sy - 10, "press esc to exit");
			if (kbhit())
			{
				ch = getch();
				switch (ch)
				{
				case 100:
					//srand(time(0));
					//enemies(ax,at,&n,f,p);
					if (sx < 450)
					{
						setcolor(BLACK);
						spaceship(sx, sy, c);
						x = 20;
						sx = sx + x;
						setcolor(WHITE);
						spaceship(sx, sy, c);
						setcolor(BLACK);
						for (i = 0; i < bn; i++)
						{
							if ((by[i] != -100))
							{
								bullet(bx[i], (by[i] - 5 - bc[i]));
							}
						}
						setcolor(WHITE);
						for (i = 0; i < bn; i++)
						{
							if (by[i] != -100)
							{
								bc[i] += 10;
							}
						}
						for (i = 0; i < bn; i++)
						{
							for (e = 0; e < n; e++)
							{
								if (((by[i] - 5 - bc[i]) > at[e] - 10) && ((by[i] - 5 - bc[i]) < at[e] + 10) && (by[i] != -100) && (ax[e] == (bx[i] + 15)) && (at[e] != -100))
								{
									sound(1000);
									//delay(50);
									setcolor(BLACK);
									circle(ax[e], at[e] - 10, 2);
									by[i] = -100;
									at[e] = -100;
									setcolor(BLACK);
									//settextstyle(2,0,5);
									sprintf(a, "score=%d", y);
									outtextxy(480, 70, a);
									y++;
									setcolor(WHITE);
									//settextstyle(2,0,5);
									sprintf(a, "score=%d", y);
									outtextxy(480, 70, a);
									outtextxy(480, 15, "Get a score greater");
									outtextxy(480, 30, "than 50 to reach L-2");
									nosound();
								}
							}
						}
						for (i = 0; i < bn; i++)
						{
							if (by[i] != -100)
							{
								bullet(bx[i], (by[i] - 5 - bc[i]));
							}
						}
					}
					break;
				case 97: //left
					//enemies(ax,at,&n,f,p);
					if (sx > 0)
					{
						setcolor(BLACK);
						spaceship(sx, sy, c);
						x = -20;
						sx = sx + x;
						setcolor(WHITE);
						spaceship(sx, sy, c);
						setcolor(BLACK);
						for (i = 0; i < bn; i++)
						{
							if ((by[i] != -100))
							{
								bullet(bx[i], (by[i] - 5 - bc[i]));
							}
						}
						setcolor(WHITE);
						for (i = 0; i < bn; i++)
						{
							if (by[i] != -100)
							{
								bc[i] += 10;
							}
						}
						for (i = 0; i < bn; i++)
						{
							for (e = 0; e < n; e++)
							{
								if (((by[i] - 5 - bc[i]) > at[e] - 10) && ((by[i] - 5 - bc[i]) < at[e] + 10) && (by[i] != -100) && (at[e] != -100) && (ax[e] == (bx[i] + 15)))
								{
									sound(1000);
									//delay(50);
									setcolor(BLACK);
									circle(ax[e], at[e] - 10, 2);
									by[i] = -100;
									at[e] = -100;
									setcolor(BLACK);
									//settextstyle(2,0,5);
									sprintf(a, "score=%d", y);
									outtextxy(480, 70, a);
									y++;
									setcolor(WHITE);
									//settextstyle(2,0,5);
									sprintf(a, "score=%d", y);
									outtextxy(480, 70, a);
									outtextxy(480, 15, "Get a score greater");
									outtextxy(480, 30, "than 50 to reach L-2");
									nosound();
								}
							}
						}
						for (i = 0; i < bn; i++)
						{
							if (by[i] != -100)
								bullet(bx[i], (by[i] - 5 - bc[i]));
						}
					}
					break;
				case ' ':
					//spaceship(sx,sy,c);
					bx[bn] = sx;
					by[bn] = sy;
					bc[bn + 1] = 0;
					bn++;
					//enemies(ax,at,&n,f,p);
					setcolor(BLACK);
					for (i = 0; i < bn; i++)
					{
						if (by[i] != -100)
						{
							bullet(bx[i], (by[i] - 5 - bc[i]));
						}
					}
					setcolor(WHITE);
					for (i = 0; i < bn; i++)
					{
						if (by[i] != -100)
						{
							bc[i] += 10;
						}
					}
					for (i = 0; i < bn; i++)
					{
						for (e = 0; e < n; e++)
						{
							if (((by[i] - 5 - bc[i]) > at[e] - 10) && ((by[i] - 5 - bc[i]) < at[e] + 10) && (by[i] != -100) && (ax[e] == (bx[i] + 15)) && (at[e] != -100))
							{
								sound(1000);
								//delay(50);
								setcolor(BLACK);
								circle(ax[e], at[e] - 10, 2);
								by[i] = -100;
								at[e] = -100;
								setcolor(BLACK);
								//settextstyle(2,0,5);
								sprintf(a, "score=%d", y);
								outtextxy(480, 70, a);
								y++;
								setcolor(WHITE);
								//settextstyle(2,0,5);
								sprintf(a, "score=%d", y);
								outtextxy(480, 70, a);
								outtextxy(480, 15, "Get a score greater");
								outtextxy(480, 30, "than 50 to reach L-2");
								nosound();
							}
						}
					}
					for (i = 0; i < bn; i++)
					{
						if (by[i] != -100)
							bullet(bx[i], (by[i] - 5 - bc[i]));
					}
					bullet(bx[bn], by[bn]);
					break;
				case 27: //leave program
					exit(0);
				default:
					break;
				}
			}
			delay(50);
			if (!kbhit())
			{
				if (k > 0)
				{
					setcolor(BLACK);
					for (i = 0; i < bn; i++)
					{
						if ((by[i] != -100))
						{
							bullet(bx[i], (by[i] - 5 - bc[i]));
						}
					}
					setcolor(WHITE);
					spaceship(sx, sy, c);
					for (i = 0; i < bn; i++)
					{
						if (by[i] != -100)
						{
							bc[i] += 10;
						}
					}
					for (i = 0; i < bn; i++)
					{
						for (e = 0; e < n; e++)
						{
							if (((by[i] - 5 - bc[i]) > at[e] - 10) && ((by[i] - 5 - bc[i]) < at[e] + 10) && (by[i] != -100) && (ax[e] == (bx[i] + 15)) && (at[e] != -100))
							{
								sound(1000);
								//delay(50);
								setcolor(BLACK);
								circle(ax[e], at[e] - 10, 2);
								by[i] = -100;
								at[e] = -100;
								setcolor(BLACK);
								//settextstyle(2,0,5);
								sprintf(a, "score=%d", y);
								outtextxy(480, 70, a);
								y++;
								setcolor(WHITE);
								//settextstyle(2,0,5);
								sprintf(a, "score=%d", y);
								outtextxy(480, 70, a);
								outtextxy(480, 15, "Get a score greater");
								outtextxy(480, 30, "than 50 to reach L-2");
								nosound();
							}
						}
					}
					for (i = 0; i < bn; i++)
					{
						if (by[i] != -100)
							bullet(bx[i], (by[i] - 5 - bc[i]));
					}
					--k;
				}
				else
				{
					f = rand() % 480;
					d = f % 20;
					f = f - d + 5;
					p++;
					n++;
					enemies(ax, at, &n, f, p);
					k = 10;
				}
			}
		}
		else
		{
			cleardevice();
			settextstyle(0, 0, 2);
			outtextxy(50, 200, "NEXT LEVEL");
			outtextxy(50, 300, "PRESS P FOR LEVEL 2");
			outtextxy(50, 400, "PRESS ESC TO EXIT");
			c = getch();
			if (c == 112)
			{
				goto down;
			}
			if (c == 27)
			{
				exit(0);
			}
		}
	}
down:
{
	cleardevice();
	y = 0;
	c = getmaxx();
	sy = getmaxy();
	n = 0;
	bn = 0;
	p = -1;
	while (1)
	{
		if (y < 500)
		{
			srand(time(0));
			//setcolor(BLACK);
			settextstyle(0, 0, 0);
			//sprintf(a,"x=%d y=%d",h,j);
			//outtextxy(480,15,a);
			outtextxy(480, 15, "high score is 500");
			sprintf(a, "score=%d", y);
			outtextxy(480, 70, a);
			getmousepos(&button, &h, &j);
			if ((h > c - 140) && (h < c) && (j > sy - 20) && (j < sy) && (button == 1))
			{
				closegraph();
				exit(10);
			}
			setcolor(WHITE);
			////settextstyle(2,0,5);
			//sprintf(a,"x=%d y=%d",h,j);
			//outtextxy(480,15,a);
			sprintf(a, "score=%d", y);
			outtextxy(480, 70, a);
			outtextxy(480, 15, "high score is 500");
			setcolor(WHITE);
			rectangle(sx, sy - 10, sx + 30, sy);
			rectangle(sx + 10, sy - 20, sx + 20, sy - 10);
			line(sx + 15, sy - 25, sx + 15, sy - 20);
			//settextstyle(0,0,0);
			outtextxy(c - 140, sy - 10, "press esc to exit");
			if (kbhit())
			{
				ch = getch();
				switch (ch)
				{
				case 100:
					//srand(time(0));
					//enemies(ax,at,&n,f,p);
					if (sx < 450)
					{
						setcolor(BLACK);
						spaceship(sx, sy, c);
						x = 20;
						sx = sx + x;
						setcolor(WHITE);
						spaceship(sx, sy, c);
						setcolor(BLACK);
						for (i = 0; i < bn; i++)
						{
							if ((by1[i] != -100))
							{
								bullet(bx1[i], (by1[i] - 5 - bc1[i]));
							}
						}
						setcolor(WHITE);
						for (i = 0; i < bn; i++)
						{
							if (by1[i] != -100)
							{
								bc1[i] += 10;
							}
						}
						for (i = 0; i < bn; i++)
						{
							for (e = 0; e < n; e++)
							{
								if (((by1[i] - 5 - bc1[i]) > at1[e] - 15) && ((by1[i] - 5 - bc1[i]) < at1[e] + 15) && (by1[i] != -100) && (ax1[e] == (bx1[i] + 15)) && (at1[e] != -100))
								{
									sound(1000);
									//delay(50);
									setcolor(BLACK);
									circle(ax1[e], at1[e] - 15, 4);
									by1[i] = -100;
									at1[e] = -100;
									setcolor(BLACK);
									//settextstyle(2,0,5);
									sprintf(a, "score=%d", y);
									outtextxy(480, 70, a);
									y++;
									setcolor(WHITE);
									//settextstyle(2,0,5);
									sprintf(a, "score=%d", y);
									outtextxy(480, 70, a);
									outtextxy(480, 15, "high score is 500");
									nosound();
								}
							}
						}
						for (i = 0; i < bn; i++)
						{
							if (by1[i] != -100)
								bullet(bx1[i], (by1[i] - 5 - bc1[i]));
						}
					}
					break;
				case 97: //left
					//enemies(ax,at,&n,f,p);
					if (sx > 0)
					{
						setcolor(BLACK);
						spaceship(sx, sy, c);
						x = -20;
						sx = sx + x;
						setcolor(WHITE);
						spaceship(sx, sy, c);
						setcolor(BLACK);
						for (i = 0; i < bn; i++)
						{
							if ((by1[i] != -100))
							{
								bullet(bx1[i], (by1[i] - 5 - bc1[i]));
							}
						}
						setcolor(WHITE);
						for (i = 0; i < bn; i++)
						{
							if (by1[i] != -100)
							{
								bc1[i] += 10;
							}
						}
						for (i = 0; i < bn; i++)
						{
							for (e = 0; e < n; e++)
							{
								if (((by1[i] - 5 - bc1[i]) > at1[e] - 15) && ((by1[i] - 5 - bc1[i]) < at1[e] + 15) && (by1[i] != -100) && (at1[e] != -100) && (ax1[e] == (bx1[i] + 15)))
								{
									sound(1000);
									//delay(50);
									setcolor(BLACK);
									circle(ax1[e], at1[e] - 15, 4);
									by1[i] = -100;
									at1[e] = -100;
									setcolor(BLACK);
									//settextstyle(2,0,5);
									sprintf(a, "score=%d", y);
									outtextxy(480, 70, a);
									//outtextxy(480,15,"high score is 500");
									y++;
									setcolor(WHITE);
									//settextstyle(2,0,5);
									sprintf(a, "score=%d", y);
									outtextxy(480, 70, a);
									outtextxy(480, 15, "high score is 500");
									nosound();
								}
							}
						}
						for (i = 0; i < bn; i++)
						{
							if (by1[i] != -100)
								bullet(bx1[i], (by1[i] - 5 - bc1[i]));
						}
					}
					break;
				case ' ':
					//spaceship(sx,sy,c);
					bx1[bn] = sx;
					by1[bn] = sy;
					bc1[bn + 1] = 0;
					bn++;
					//enemies(ax,at,&n,f,p);
					setcolor(BLACK);
					for (i = 0; i < bn; i++)
					{
						if (by1[i] != -100)
						{
							bullet(bx1[i], (by1[i] - 5 - bc1[i]));
						}
					}
					setcolor(WHITE);
					for (i = 0; i < bn; i++)
					{
						if (by1[i] != -100)
						{
							bc1[i] += 10;
						}
					}
					for (i = 0; i < bn; i++)
					{
						for (e = 0; e < n; e++)
						{
							if (((by1[i] - 5 - bc1[i]) > at1[e] - 15) && ((by1[i] - 5 - bc1[i]) < at1[e] + 15) && (by1[i] != -100) && (ax1[e] == (bx1[i] + 15)) && (at1[e] != -100))
							{
								sound(1000);
								//delay(50);
								setcolor(BLACK);
								circle(ax1[e], at1[e] - 15, 4);
								by1[i] = -100;
								at1[e] = -100;
								setcolor(BLACK);
								//settextstyle(2,0,5);
								sprintf(a, "score=%d", y);
								outtextxy(480, 70, a);
								y++;
								setcolor(WHITE);
								//settextstyle(2,0,5);
								sprintf(a, "score=%d", y);
								outtextxy(480, 70, a);
								outtextxy(480, 15, "high score is 500");
								nosound();
							}
						}
					}
					for (i = 0; i < bn; i++)
					{
						if (by1[i] != -100)
							bullet(bx1[i], (by1[i] - 5 - bc1[i]));
					}
					bullet(bx1[bn], by1[bn]);
					break;
				case 27: //leave program
					exit(0);
				default:
					break;
				}
			}
			delay(50);
			if (!kbhit())
			{
				if (k > 0)
				{
					setcolor(BLACK);
					for (i = 0; i < bn; i++)
					{
						if ((by1[i] != -100))
						{
							bullet(bx1[i], (by1[i] - 5 - bc1[i]));
						}
					}
					setcolor(WHITE);
					spaceship(sx, sy, c);
					for (i = 0; i < bn; i++)
					{
						if (by1[i] != -100)
						{
							bc1[i] += 10;
						}
					}
					for (i = 0; i < bn; i++)
					{
						for (e = 0; e < n; e++)
						{
							if (((by1[i] - 5 - bc1[i]) > at1[e] - 15) && ((by1[i] - 5 - bc1[i]) < at1[e] + 15) && (by1[i] != -100) && (ax1[e] == (bx1[i] + 15)) && (at1[e] != -100))
							{
								sound(1000);
								//delay(50);
								setcolor(BLACK);
								circle(ax1[e], at1[e] - 15, 4);
								by1[i] = -100;
								at1[e] = -100;
								setcolor(BLACK);
								//settextstyle(2,0,5);
								sprintf(a, "score=%d", y);
								outtextxy(480, 70, a);
								y++;
								setcolor(WHITE);
								//settextstyle(2,0,5);
								sprintf(a, "score=%d", y);
								outtextxy(480, 70, a);
								nosound();
								outtextxy(480, 15, "high score is 500");
							}
						}
					}
					for (i = 0; i < bn; i++)
					{
						if (by1[i] != -100)
							bullet(bx1[i], (by1[i] - 5 - bc1[i]));
					}
					--k;
				}
				else
				{
					f = rand() % 480;
					d = f % 20;
					f = f - d + 5;
					p++;
					n++;
					enemies1(ax1, at1, &n, f, p);
					k = 10;
				}
			}
		}
		else
		{
			cleardevice();
			settextstyle(0, 0, 2);
			outtextxy(50, 200, "YOU WIN");
			outtextxy(50, 300, "PRESS ESC TO EXIT");
			ch = getch();
			if (ch == 27)
			{
				exit(0);
			}
		}
	}
}
}
