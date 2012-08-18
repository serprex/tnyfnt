#include <GL/glx.h>
#include "tnyfnt.h"
int main(int argc,char**argv){
	Display*dpy=XOpenDisplay(0);
	XVisualInfo*vi=glXChooseVisual(dpy,DefaultScreen(dpy),(int[]){GLX_RGBA,GLX_DOUBLEBUFFER,None});
	Window Wdo=XCreateWindow(dpy,RootWindow(dpy,vi->screen),0,0,256,256,0,vi->depth,InputOutput,vi->visual,CWColormap,(XSetWindowAttributes[]){{.colormap=XCreateColormap(dpy,RootWindow(dpy,vi->screen),vi->visual,AllocNone)}});
	XSetWMProtocols(dpy,Wdo,(Atom[]){XInternAtom(dpy,"WM_DELETE_WINDOW",False)},1);
	XMapWindow(dpy,Wdo);
	glXMakeCurrent(dpy,Wdo,glXCreateContext(dpy,vi,0,GL_TRUE));
	glOrtho(0,256,256,0,1,-1);
	glColor3ub(255,255,255);
	for(;;){
		glClear(GL_COLOR_BUFFER_BIT);
		tfDraw(16,16,"0123456789\nABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n\tTNYFNT IS A TINY FONT LIBRARY\nASDF\tQWERTY\n\tASDF\t\tQWERTY");
		glXSwapBuffers(dpy,Wdo);
		XEvent ev;
		if(XPending(dpy)){
			XNextEvent(dpy,&ev);
			if(ev.type==ClientMessage)return 0;
		}
	}
}