#include <GL/gl.h>
#include <stdint.h>
#define OOXOO 12
#define OOOXX 11
#define OOOOX 10
#define OXOXO 9
#define XOOOO 8
#define XOOOX 7
#define XOOXO 6
#define XOOXX 5
#define XOXOX 4
#define XXOOX 3
#define XXOXX 2
#define XXXXO 1
#define XXXXX 0
static const uint64_t row=0x4c41418a7359edff;
#define A(a,b,c,d,e) a|b<<4,c|d<<4,e
#define B(a,b,c,d,e) |a<<4,b|c<<4,d|e<<4,
static const uint8_t abc[]={
	A(
	XXXXX,
	XOOOX,
	XXXXX,
	XOOOX,
	XOOOX)
	B(
	XXXXX,
	XOOOX,
	XXXXO,
	XOOOX,
	XXXXX)
	A(
	XXXXX,
	XOOOO,
	XOOOO,
	XOOOO,
	XXXXX)
	B(
	XXXXO,
	XOOOX,
	XOOOX,
	XOOOX,
	XXXXO)
	A(
	XXXXX,
	XOOOO,
	XXXXO,
	XOOOO,
	XXXXX)
	B(
	XXXXX,
	XOOOO,
	XXXXO,
	XOOOO,
	XOOOO)
	A(
	XXXXX,
	XOOOO,
	XOOXX,
	XOOOX,
	XXXXX)
	B(
	XOOOX,
	XOOOX,
	XXXXX,
	XOOOX,
	XOOOX)
	A(
	XXXXX,
	OOXOO,
	OOXOO,
	OOXOO,
	XXXXX)
	B(
	OOOXX,
	OOOOX,
	OOOOX,
	XOOOX,
	XXXXX)
	A(
	XOOOX,
	XOOXO,
	XXXXO,
	XOOXO,
	XOOOX)
	B(
	XOOOO,
	XOOOO,
	XOOOO,
	XOOOO,
	XXXXX)
	A(
	XOOOX,
	XXOXX,
	XOXOX,
	XOOOX,
	XOOOX)
	B(
	XOOOX,
	XXOOX,
	XOXOX,
	XOOXX,
	XOOOX)
	A(
	XXXXX,
	XOOOX,
	XOOOX,
	XOOOX,
	XXXXX)
	B(
	XXXXO,
	XOOOX,
	XXXXO,
	XOOOO,
	XOOOO)
	A(
	XXXXX,
	XOOOX,
	XOOOX,
	XXXXX,
	OOXOO)
	B(
	XXXXO,
	XOOOX,
	XXXXO,
	XOOOX,
	XOOOX)
	A(
	XXXXX,
	XOOOO,
	XXXXX,
	OOOOX,
	XXXXX)
	B(
	XXXXX,
	OOXOO,
	OOXOO,
	OOXOO,
	OOXOO)
	A(
	XOOOX,
	XOOOX,
	XOOOX,
	XOOOX,
	XXXXX)
	B(
	XOOOX,
	XOOOX,
	OXOXO,
	OXOXO,
	OOXOO)
	A(
	XOOOX,
	XOOOX,
	XOXOX,
	XOXOX,
	OXOXO)
	B(
	XOOOX,
	OXOXO,
	OOXOO,
	OXOXO,
	XOOOX)
	A(
	XOOOX,
	XOOOX,
	OXOXO,
	OOXOO,
	OOXOO)
	B(
	XXXXX,
	OOOOX,
	XXXXX,
	XOOOO,
	XXXXX)
};
static void tfChar(int x,int y,int c){
	for(int j=0;j<5;j++)
		for(int i=0;i<5;i++)
			if((row>>5*(abc[c*5+j>>1]>>(((c^j)&1)<<2)&15))&1<<i)glVertex2i(x+i,y+j);
}
void tfDraw(int x,int y,char*s){
	int xo=0;
	glBegin(GL_POINTS);
	for(;;s++){
		switch(*s){
		case 0:return;
		case'\n':
			xo=0;
		case'\v':
			y+=7;
		continue;case'\t':
			xo+=12;
		continue;case'A'...'Z':tfChar(x+xo,y,*s-'A');
		break;case'a'...'z':tfChar(x+xo,y,*s-'a');
		}
		xo+=6;
	}
	glEnd();
}