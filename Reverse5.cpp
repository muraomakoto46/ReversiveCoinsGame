// Reverse5.cpp
//制作：村尾誠(v)(＾ー＾)(v)
//マスが16マス×16マスもある、リバースが遊べる。
//.cppだけどC言語で書かれています。
//キー入力したら、 入力結果は 少し遅れて もう一度Enterを押すと反映されるらしい。
//遅延があるのが不満だけど、点滅しつづけると目に悪すぎるから 別にこのままでもいいかな。
//それ以外は 普通に動くはずだ。
//VisualStudio2008でコンパイルするといい。

#include "stdafx.h"
#include<string.h>
#include<stdlib.h>
#include <conio.h>
#define HEIGHT 18//壁1マス＋16マス+壁1マス
#define WIDTH 18

#define NOSTONE 0//石が何もありませんということを表す
#define WHITE 1  //白色の石があるという意味
#define BLACK -1 //黒色の意思があるという意味
#define WHITESQUARE 3//カーソルの形を◇にしますという意味
#define BLACKSQUARE 4//カーソルの形を◆にするよっていう意味
#define CURSOLMARK 7//カーソルの形を通常の?にするよっていう意味
#define WALL 8//壁がありますよっていう意味。
//alphabed順
void cleanDaishi(void);
int chooserChange(void);
void displayDaishiEgara(void);
void displayDaishiDecimal(void);//デバッグ用
void displayBlockDecimal(void);//デバッグ用

char input_char(void);
int inputXY(void);
int makeBoard(void);
char mixture(void);
int play(void);
int reverseSpread(int y,int x);
void setStone(void);
void setWall(void);
int countStone(int player);
int displayTitle(void);
//画用紙
int block[HEIGHT][WIDTH]={0};
int daishi[HEIGHT][WIDTH]={0};

//選手
int chooser=WHITE;
int waiter=BLACK;


//カーソル
int cursolshape=5;
int CURY=1;
int CURX=1;

int _tmain(int argc, _TCHAR* argv[])
{
	displayTitle();
	makeBoard();
	play();
	return 0;
}
int makeBoard(void){
	setWall();
	setStone();
	return 0;
}
int displayTitle(void){
	
	printf("Reverse Game %d × %d\n",WIDTH-2,HEIGHT-2);
	printf("マスが倍の大きさ。\n");
	printf("●○\n");
	printf("○●\n");
	printf("制作：村尾誠(v)(＾ー＾)(v)\n");
	printf("Enter二度押ししてくださいな。\n");
	input_char();//
	return 0;
}
int play(void){

	do{
		//displayBlockDecimal();
		//displayDaishiDecimal();
		inputXY();
		displayDaishiEgara();
	}while(1);
	return 0;
}
int chooserChange(){
	chooser=-chooser;
	waiter=-waiter;
	return chooser;
}
int inputXY(void){
	auto char available=' ';
	auto char direction=' ';
	auto int count=0;
	auto int turned=0;
	
	direction=input_char();
	system("cls");
	available=mixture();
	//printf("direction=%c,available=%d\n",direction,available);
	//exit
	if(direction == 'Z'||direction =='z'){
		printf("Z 終了");
		exit(0);
	}
	
	//Up
	if((direction =='E'||direction == 'e')&& CURY>1){
			CURY--;
			count++;
	}
	
	//Down
	if((direction == 'D'||direction == 'd') && CURY<HEIGHT-2){
			CURY++;
			count++;
	}
	//Left
	if((direction == 'S'|| direction == 's'||direction == 'l') && CURX>1){
			CURX--;
			count++;
	}
	//Right
	if((direction == 'F'|| direction == 'f') && CURX<WIDTH-2){
			CURX++;
			count++;
	}
	//Go
	if((direction=='P'||direction == 'p')&&(available=='Y')){
		//これをgが押されたときのみ起動されるようにするべき
		turned=reverseSpread(CURY,CURX);
		
	}
	//printf("turned=%d\n",turned);
	if(turned!=0){
		//chooserを交代しよう。
		//printf("-==chooserChange()==-\n");
		chooserChange();
		turned=0;
		//クリア初期化 turnedの初期化のタイミングを誤るとまるでうまく交代できない。
	}

	return count;
}
char mixture(void){
	int bx=0,by=0;
	int mixx=0,mixy=0;
	char available=' ';
	//printf("mixture()->daishi[][]をcleanDaishi()する\n");
	cleanDaishi();

	//printf("mixture\n");

	for(by=0,mixy=0;by<HEIGHT;by++,mixy++){
		for(bx=0,mixx=0;bx<WIDTH;bx++,mixx++){
			daishi[mixy][mixx]=block[by][bx];
		}
	}

	if(daishi[CURY][CURX]==NOSTONE){
		daishi[CURY][CURX]=CURSOLMARK;
		available='Y';//Yes
	}else if(daishi[CURY][CURX]==BLACK){
		daishi[CURY][CURX]=BLACKSQUARE;
	}else if(daishi[CURY][CURX]==WHITE){
		daishi[CURY][CURX]=WHITESQUARE;
		available='N';//No
	}else{
		;
	}
	//printf("mixture()->available=%c\n",available);
	return available;
}
void cleanDaishi(void){
	int mixx=0,mixy=0;
	//printf("cleanDaishi()\n");
	for(mixy=0;mixy<HEIGHT;mixy++){
		for(mixx=0;mixx<WIDTH;mixx++){
			daishi[mixy][mixx]=0;
		}
	}
	//printf("cleared daishi[][]\n");
}
void setWall(void){
	auto int y=0,x=0;
	for(y=0;y<HEIGHT;y++){
		for(x=0;x<WIDTH;x++){
			if(x==0||x==WIDTH-1||y==0||y==HEIGHT-1){
				block[y][x]=WALL;
			}
		}
	}
}
void setStone(void){
	block[HEIGHT/2 - 1][WIDTH/2 -1]=BLACK;
	block[HEIGHT/2 - 1][WIDTH/2   ]=WHITE;
	block[HEIGHT/2    ][WIDTH/2   ]=BLACK;
	block[HEIGHT/2    ][WIDTH/2 -1]=WHITE;
}
void displayDaishiDecimal(void){
	auto int mixx=0,mixy=0;
	printf("↓台紙\n");
	for(mixy=0;mixy<HEIGHT;mixy++){
		for(mixx=0;mixx<WIDTH;mixx++){
			printf("%d",daishi[mixy][mixx]);
		}
		printf("\n");
	}
	printf("\n");
}
//台紙を絵柄で表示させるんだ
void displayDaishiEgara(void){
	auto int y=0,x=0;
	system("cls");
	printf("□■◇◆○●Reverse %d × %d●○◆◇■□\n",WIDTH-2,HEIGHT-2);
	printf("       E:Up      Z: exit(0)\n");
	printf("S:Left  ←┼→   F:Right \n");
	printf("       D:Down	P:Put into\n");
	if(chooser==WHITE){
		printf("WHITE ○の番です。\n");
	}
	if(chooser==BLACK){
		printf("BLACK ●の番です。\n");
	}
	for(y=0;y<HEIGHT;y++){
		for(x=0;x<WIDTH;x++){
			if(daishi[y][x]==WHITE){
				printf("○");
			}else if(daishi[y][x]==BLACK){
				printf("●");
			}else if(daishi[y][x]==WALL){
				printf("壁");
			}else if(daishi[y][x]==NOSTONE){
				printf("  ");
			}else if(daishi[y][x]==CURSOLMARK){
				printf("？");
			}else if(daishi[y][x]==WHITESQUARE){
				printf("◇");
			}else if(daishi[y][x]==BLACKSQUARE){
				printf("◆");
			}
		}
		printf("\n");
	}
	printf("BLACK=%d個  ＼",countStone(BLACK));
	printf("WHITE=%d個\n",countStone(WHITE));
	//printf("inputXY()->CURY=%d   CURX=%d\n",CURY,CURX);
}
//↓これは出来栄えがあまり良いとはいえない。動くには、動く…けど。
int reverseSpread(int y,int x){
	auto int i=0,j=0;
	auto int swapY=y,swapX=x;
	auto unsigned int countReverse=0;
	printf("↓viewBlock()\n");
	if(block[y][x]==NOSTONE){
		block[y][x]=chooser;
		/*
		if(chooser==WHITE){
			printf("chooser = WHITE\n");
		}else{
			printf("chooser==BLACK\n");
		}
		*/
		//右→   一見優れているようで、ひっくり返せないはずなのに石が置けてしまうバグがあるようだ。
		if(block[y][x+1]==waiter){
			for(;block[y][x+1]!=WALL;x++){
				/*for文の継続条件はそれだけは絶対に越えてはいけないという
				…最悪の状況さえ回避できるような条件を指定しておくものだ。
				継続条件にはあまり詳しく書けないのです。
				処々の細かな継続条件はfor文の内側にif(条件){break;}と書くほうがいいでしょう。
				とにかくxやy それにiやjがWALLのある位置を突破さえしなければ、
				メモリーの範囲を飛び越えるという最悪のエラーは回避できるのだ。
				*/
				if(block[y][x+1]==NOSTONE){
					//  ＿＿●●●＿＿
					//  ＿＿●●●○＿
					/*
					if(block[y][x+1]==NOSTONE){break;} について
					これがないと、たとえば、
					ここに黒を置くと
					 ↓
					[ ]○○○＿○○＿○○＿○○●＿壁
					こうなります。
					●●●●●●●●●●●●●●＿壁
					*/
					break;
				}
				if(block[y][x+1]==chooser){
					for(j=x;block[y][j]==waiter;j--){
						block[y][j]=chooser;
						//printf("put y=%d,j=%d\n",y,j);
						countReverse++;
					}
					break;
				}
			}
		}
		y=swapY;
		x=swapX;
		//左←      
		if(block[y][x-1]==waiter){
			for(;block[y][x-1]!=WALL;x--){
				if(block[y][x-1]==NOSTONE){
					break;
				}
				if(block[y][x-1]==chooser){
					for(j=x;block[y][j]==waiter;j++){
						block[y][j]=chooser;
						countReverse++;
					}
					break;
				}
			}
		}
		y=swapY;
		x=swapX;
		//↓
		if(block[y+1][x]==waiter){
			for(;block[y+1][x]!=WALL;y++){
				if(block[y+1][x]==NOSTONE){
					break;
				}
				if(block[y+1][x]==chooser){
					for(i=y;block[i][x]==waiter;i--){
						block[i][x]=chooser;
						countReverse++;
					}
					break;
				}
			}
		}
		y=swapY;
		x=swapX;
		//↑
		if(block[y-1][x]==waiter){
			for(;block[y-1][x]!=WALL;y--){
				if(block[y-1][x]==NOSTONE){
					break;
				}
				if(block[y-1][x]==chooser){
					for(i=y;block[i][x]==waiter;i++){
						block[i][x]=chooser;
						countReverse++;
					}
					break;
				}
			}
		}
		y=swapY;
		x=swapX;
		//↑→
		if(block[y-1][x+1]==waiter){
			for(;block[y-1][x+1]!=WALL;y--,x++){
				if(block[y-1][x+1]==NOSTONE){
					break;
				}
				if(block[y-1][x+1]==chooser){
					for(i=y,j=x;block[i][j]==waiter;i++,j--){
						block[i][j]=chooser;
						countReverse++;
					}
					break;
				}
			}
		}
		y=swapY;
		x=swapX;
		//←↑
		if(block[y-1][x-1]==waiter){
			for(;block[y-1][x-1]!=WALL;y--,x--){
				if(block[y-1][x-1]==NOSTONE){
					break;
				}
				if(block[y-1][x-1]==chooser){
					for(i=y,j=x;block[i][j]==waiter;i++,j++){
						block[i][j]=chooser;
						countReverse++;
					}
					break;
				}
			}
		}
		y=swapY;
		x=swapX;
		//→↓
		if(block[y+1][x+1]==waiter){
			for(;block[y+1][x+1]!=WALL;y++,x++){
				if(block[y+1][x+1]==NOSTONE){
					break;
				}
				if(block[y+1][x+1]==chooser){
					for(i=y,j=x;block[i][j]==waiter;i--,j--){
						block[i][j]=chooser;
						countReverse++;
					}
					break;
				}
			}
		}
		y=swapY;
		x=swapX;
		//←↓ 左下方向
		
		if(block[y+1][x-1]==waiter){
			for(;block[y+1][x-1]!=WALL;y++,x--){
				if(block[y+1][x-1]==chooser){
					for(i=y,j=x;block[i][j]==waiter;i--,j++){
						block[i][j]=chooser;
						countReverse++;
					}
					break;
				}else if(block[y+1][x-1]==NOSTONE){
					break;
				}
			}
		}
		
	}
	if(countReverse==0){
		block[swapY][swapX]=NOSTONE;
	}else{
		
	}
	return countReverse;
}
//デバッグ用
void displayBlockDecimal(){
	int bx=0,by=0;
	printf("↓block\n");
	for(by=0;by<HEIGHT;by++){
		for(bx=0;bx<WIDTH;bx++){
			printf("%d",block[by][bx]);
		}
		printf("\n");
	}
	printf("\n");
}
//デバッグ用
int input_int(void){
	auto char str[255];
	auto int isuwch=0;
	auto int hantei=0;
	auto int n=255;
	while(1){
		fgets(str,n,stdin);
		if(str[strlen(str)-1]=='\n'){
			str[strlen(str)-1]='\0';
		}
		hantei=sscanf_s(str,"%d",&isuwch);
		if(hantei!=0){
			break;
		}
		printf("入力ミスです。\n");
		printf("入力データ：");
	}
	return isuwch;
}
char input_char(void){
	auto char str[255];
	auto char mozi=0;
	auto int hantei=0;
	auto int n=255;
	while(1){
		fgets(str,n,stdin);//stdinとは標準入力からって意味。普通*fpでファイルから読むけどここをstdinにするとキーボードから読むことができる。
		if(str[strlen(str)-1]=='\n'){//勝手に改行される問題を改善
			str[strlen(str)-1]='\0';
		}
		hantei=sscanf_s(str,"%c",&mozi);
		if(hantei!=0){
			break;
		}
		printf("入力ミスです。\n");
		printf("入力データ：");
	}
	return mozi;
}

int countStone(int player){
	auto int x=0;
	auto int y=0;
	auto int count=0;
	for(y=1;y<HEIGHT-2;y++){
		for(x=1;x<WIDTH-2;x++){
			if(block[y][x]==player){
				count++;
			}
		}
	}
	return count;
}