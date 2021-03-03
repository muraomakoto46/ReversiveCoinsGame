// Reverse5.cpp
//����F������(v)(�O�[�O)(v)
//�}�X��16�}�X�~16�}�X������A���o�[�X���V�ׂ�B
//.cpp������C����ŏ�����Ă��܂��B
//�L�[���͂�����A ���͌��ʂ� �����x��� ������xEnter�������Ɣ��f�����炵���B
//�x��������̂��s�������ǁA�_�ł��Â���ƖڂɈ������邩�� �ʂɂ��̂܂܂ł��������ȁB
//����ȊO�� ���ʂɓ����͂����B
//VisualStudio2008�ŃR���p�C������Ƃ����B

#include "stdafx.h"
#include<string.h>
#include<stdlib.h>
#include <conio.h>
#define HEIGHT 18//��1�}�X�{16�}�X+��1�}�X
#define WIDTH 18

#define NOSTONE 0//�΂���������܂���Ƃ������Ƃ�\��
#define WHITE 1  //���F�̐΂�����Ƃ����Ӗ�
#define BLACK -1 //���F�̈ӎv������Ƃ����Ӗ�
#define WHITESQUARE 3//�J�[�\���̌`�����ɂ��܂��Ƃ����Ӗ�
#define BLACKSQUARE 4//�J�[�\���̌`�����ɂ������Ă����Ӗ�
#define CURSOLMARK 7//�J�[�\���̌`��ʏ��?�ɂ������Ă����Ӗ�
#define WALL 8//�ǂ�����܂�����Ă����Ӗ��B
//alphabed��
void cleanDaishi(void);
int chooserChange(void);
void displayDaishiEgara(void);
void displayDaishiDecimal(void);//�f�o�b�O�p
void displayBlockDecimal(void);//�f�o�b�O�p

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
//��p��
int block[HEIGHT][WIDTH]={0};
int daishi[HEIGHT][WIDTH]={0};

//�I��
int chooser=WHITE;
int waiter=BLACK;


//�J�[�\��
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
	
	printf("Reverse Game %d �~ %d\n",WIDTH-2,HEIGHT-2);
	printf("�}�X���{�̑傫���B\n");
	printf("����\n");
	printf("����\n");
	printf("����F������(v)(�O�[�O)(v)\n");
	printf("Enter��x�������Ă��������ȁB\n");
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
		printf("Z �I��");
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
		//�����g�������ꂽ�Ƃ��̂݋N�������悤�ɂ���ׂ�
		turned=reverseSpread(CURY,CURX);
		
	}
	//printf("turned=%d\n",turned);
	if(turned!=0){
		//chooser����サ�悤�B
		//printf("-==chooserChange()==-\n");
		chooserChange();
		turned=0;
		//�N���A������ turned�̏������̃^�C�~���O�����Ƃ܂�ł��܂����ł��Ȃ��B
	}

	return count;
}
char mixture(void){
	int bx=0,by=0;
	int mixx=0,mixy=0;
	char available=' ';
	//printf("mixture()->daishi[][]��cleanDaishi()����\n");
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
	printf("���䎆\n");
	for(mixy=0;mixy<HEIGHT;mixy++){
		for(mixx=0;mixx<WIDTH;mixx++){
			printf("%d",daishi[mixy][mixx]);
		}
		printf("\n");
	}
	printf("\n");
}
//�䎆���G���ŕ\���������
void displayDaishiEgara(void){
	auto int y=0,x=0;
	system("cls");
	printf("������������Reverse %d �~ %d������������\n",WIDTH-2,HEIGHT-2);
	printf("       E:Up      Z: exit(0)\n");
	printf("S:Left  ������   F:Right \n");
	printf("       D:Down	P:Put into\n");
	if(chooser==WHITE){
		printf("WHITE ���̔Ԃł��B\n");
	}
	if(chooser==BLACK){
		printf("BLACK ���̔Ԃł��B\n");
	}
	for(y=0;y<HEIGHT;y++){
		for(x=0;x<WIDTH;x++){
			if(daishi[y][x]==WHITE){
				printf("��");
			}else if(daishi[y][x]==BLACK){
				printf("��");
			}else if(daishi[y][x]==WALL){
				printf("��");
			}else if(daishi[y][x]==NOSTONE){
				printf("  ");
			}else if(daishi[y][x]==CURSOLMARK){
				printf("�H");
			}else if(daishi[y][x]==WHITESQUARE){
				printf("��");
			}else if(daishi[y][x]==BLACKSQUARE){
				printf("��");
			}
		}
		printf("\n");
	}
	printf("BLACK=%d��  �_",countStone(BLACK));
	printf("WHITE=%d��\n",countStone(WHITE));
	//printf("inputXY()->CURY=%d   CURX=%d\n",CURY,CURX);
}
//������͏o���h�������܂�ǂ��Ƃ͂����Ȃ��B�����ɂ́A�����c���ǁB
int reverseSpread(int y,int x){
	auto int i=0,j=0;
	auto int swapY=y,swapX=x;
	auto unsigned int countReverse=0;
	printf("��viewBlock()\n");
	if(block[y][x]==NOSTONE){
		block[y][x]=chooser;
		/*
		if(chooser==WHITE){
			printf("chooser = WHITE\n");
		}else{
			printf("chooser==BLACK\n");
		}
		*/
		//�E��   �ꌩ�D��Ă���悤�ŁA�Ђ�����Ԃ��Ȃ��͂��Ȃ̂ɐ΂��u���Ă��܂��o�O������悤���B
		if(block[y][x+1]==waiter){
			for(;block[y][x+1]!=WALL;x++){
				/*for���̌p�������͂��ꂾ���͐�΂ɉz���Ă͂����Ȃ��Ƃ���
				�c�ň��̏󋵂�������ł���悤�ȏ������w�肵�Ă������̂��B
				�p�������ɂ͂��܂�ڂ��������Ȃ��̂ł��B
				���X�ׂ̍��Ȍp��������for���̓�����if(����){break;}�Ə����ق��������ł��傤�B
				�Ƃɂ���x��y �����i��j��WALL�̂���ʒu��˔j�������Ȃ���΁A
				�������[�͈̔͂��щz����Ƃ����ň��̃G���[�͉���ł���̂��B
				*/
				if(block[y][x+1]==NOSTONE){
					//  �Q�Q�������Q�Q
					//  �Q�Q���������Q
					/*
					if(block[y][x+1]==NOSTONE){break;} �ɂ���
					���ꂪ�Ȃ��ƁA���Ƃ��΁A
					�����ɍ���u����
					 ��
					[ ]�������Q�����Q�����Q�������Q��
					�����Ȃ�܂��B
					�����������������������������Q��
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
		//����      
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
		//��
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
		//��
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
		//����
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
		//����
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
		//����
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
		//���� ��������
		
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
//�f�o�b�O�p
void displayBlockDecimal(){
	int bx=0,by=0;
	printf("��block\n");
	for(by=0;by<HEIGHT;by++){
		for(bx=0;bx<WIDTH;bx++){
			printf("%d",block[by][bx]);
		}
		printf("\n");
	}
	printf("\n");
}
//�f�o�b�O�p
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
		printf("���̓~�X�ł��B\n");
		printf("���̓f�[�^�F");
	}
	return isuwch;
}
char input_char(void){
	auto char str[255];
	auto char mozi=0;
	auto int hantei=0;
	auto int n=255;
	while(1){
		fgets(str,n,stdin);//stdin�Ƃ͕W�����͂�����ĈӖ��B����*fp�Ńt�@�C������ǂނ��ǂ�����stdin�ɂ���ƃL�[�{�[�h����ǂނ��Ƃ��ł���B
		if(str[strlen(str)-1]=='\n'){//����ɉ��s�����������P
			str[strlen(str)-1]='\0';
		}
		hantei=sscanf_s(str,"%c",&mozi);
		if(hantei!=0){
			break;
		}
		printf("���̓~�X�ł��B\n");
		printf("���̓f�[�^�F");
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