#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void startpage(){
	initgraph(640, 480);
	IMAGE frontpage;
	loadimage(&frontpage, "img\\frontpage.png");
	putimage(0, 0, &frontpage);
	setcolor(RED);
	line(200, 240, 440, 240);
	line(320, 120, 320, 360);
	
	circle(320,240,20);
	circle(320,240,40);
	circle(320,240,60);
	circle(320,240,80);
	char c=0;
	while(c!='\n'){
		if (kbhit()){
			c = getch();
			return;
		}
		else
			c = '.';

	}
	closegraph();
}
void main()
{
	startpage();

	srand((unsigned)time(0));
	int wang_x=640,wang_y=0,hook_x,hook_y=100,bread_y=(rand() % (WINDOW_HEIGHT/2))+(WINDOW_HEIGHT/2-100),bread_x=rand() % (WINDOW_WIDTH);
	static int score=0;
	char c = 0;//c用来接收字符
	char str_score[]="";
	char down=0;//down用来控制方向
	static int millionsecond=0;
	static int second=60;
	char str_second[]="";

	IMAGE principle,hook,background,bread;// 定义 IMAGE 对象,王校长,钩子
	loadimage(&principle, "img\\wang.png");	//载入王校长
	loadimage(&hook,"img\\hook.png");//载入钩子
	loadimage(&background,"img\\bg.png");//载入钩子
	loadimage(&bread,"img\\bread.png");//载入钩子

	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);	//初始化窗口
	setbkcolor(WHITE);	//设置背景色为白色
	cleardevice();	//调用清屏cleardevice用背景色刷新背景

	int dir=0;//方向变量0


	while(c != 27){
		srand((unsigned)time(0));
		/*
		控制如果按下esc，则退出
		*/
		if (kbhit()){
			c = getch();
			/*
			控制如果按下down键，则王校长扔钩子
			*/
			hook_x=wang_x+20;
			int dir_hook=0;
			while(c==115){
				if(hook_y>WINDOW_HEIGHT) dir_hook=1;
				if(hook_y<100) c=23;//因为23不常用，修复钩子的遗漏bug

				if(dir_hook==0) hook_y++;
				else hook_y--;
				//一组图片填充
				BeginBatchDraw();
				putimage(0, 0, &background);
				putimage(wang_x, wang_y, &principle);
				putimage(hook_x, hook_y, &hook);
				putimage(bread_x,bread_y,&bread);
				outtextxy(10, WINDOW_HEIGHT-20, str_score);
				outtextxy(100, WINDOW_HEIGHT-20, str_second);
				FlushBatchDraw();
				EndBatchDraw();
				//end
				Sleep(5);
				if(hook_y>bread_y&&hook_x>=bread_x-50&&hook_x<=bread_x+100){
					dir_hook=1;
					bread_y=WINDOW_HEIGHT;//在主函数中进行随机，WINDOW_HEIGHT只是个标识
					score+=100;//分数加100
				}
			}
		}
		else
			c = '.';

		//钩子遗漏用白色色块填充，并让c变为'.'
		if(c==23) {
			
			c='.';
		}

		/*
		控制王校长的自由移动
		*/
		if(wang_x>=WINDOW_WIDTH-100) {
			dir=1;
		}

		if(wang_x<=0){
			dir=0;
		}

		/*
		控制王校长的自由移动方向
		*/
		if(dir==0) wang_x++;
		if(dir==1) wang_x--;
		
		//制作bread随机
		if(bread_y==WINDOW_HEIGHT){
			bread_y=(rand() % (WINDOW_HEIGHT/2))+(WINDOW_HEIGHT/2);
			bread_x=rand() % (WINDOW_WIDTH);
		}	

		//一组图片填充
		setcolor(RED);
		sprintf(str_score, "分数:%d", score);//转换数字为字符串
		sprintf(str_second, "时间:%d", second);
		BeginBatchDraw();
		putimage(0, 0, &background);
		putimage(wang_x, wang_y, &principle);
		putimage(bread_x,bread_y,&bread);
		outtextxy(10, WINDOW_HEIGHT-20, str_score);
		outtextxy(100, WINDOW_HEIGHT-20, str_second);
		FlushBatchDraw();
		EndBatchDraw();
		//end
		Sleep(5);//线程休眠5毫秒
		millionsecond+=5;
		if(millionsecond%1000==0){
			millionsecond=0;
			second--;
		}
		if(second==0) break;
	}
	sprintf(str_score, "游戏结束，您的分数:%d", score);
	outtextxy(WINDOW_WIDTH/2-70, WINDOW_HEIGHT/2-40, str_score);
	getch();//获取键值
	closegraph();//关闭窗口
}
