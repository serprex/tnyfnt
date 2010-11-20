#ifdef GLX
#include <GL/glx.h>
#else
#include <SDL.h>
#include <SDL_opengl.h>
#endif
#include "tnyfnt.h"
int main(int argc,char**argv){
	#ifdef SDL
	if(SDL_Init(SDL_INIT_VIDEO)==-1){
		fputs(SDL_GetError(),stderr);
		return 1;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_Surface*dpy=SDL_SetVideoMode(256,256,0,SDL_OPENGL);
	#else
	Display*dpy=XOpenDisplay(0);
	XVisualInfo*vi=glXChooseVisual(dpy,DefaultScreen(dpy),(int[]){GLX_RGBA,GLX_DOUBLEBUFFER,None});
	Window Wdo=XCreateWindow(dpy,RootWindow(dpy,vi->screen),0,0,256,256,0,vi->depth,InputOutput,vi->visual,CWColormap,(XSetWindowAttributes[]){{.colormap=XCreateColormap(dpy,RootWindow(dpy,vi->screen),vi->visual,AllocNone)}});
	XSetWMProtocols(dpy,Wdo,(Atom[]){XInternAtom(dpy,"WM_DELETE_WINDOW",False)},1);
	XMapWindow(dpy,Wdo);
	glXMakeCurrent(dpy,Wdo,glXCreateContext(dpy,vi,0,GL_TRUE));
	#endif
	glOrtho(0,256,256,0,1,-1);
	glColor3ub(255,255,255);
	for(;;){
		#ifdef GLX
		glXSwapBuffers(dpy,Wdo);
		#else
		SDL_GL_SwapBuffers();
		#endif
		glClear(GL_COLOR_BUFFER_BIT);
		tfDraw(16,16,"0123456789\nABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n\tTNYFNT IS A TINY FONT LIBRARY\nASDF\tQWERTY\n\tASDF\t\tQWERTY");
		#ifdef GLX
		glXSwapBuffers(dpy,Wdo);
		XEvent ev;
		if(XPending(dpy)){
			XNextEvent(dpy,&ev);
			if(ev.type==ClientMessage)return 0;
		}
		#else
		SDL_GL_SwapBuffers();
		SDL_Event ev;
		if(SDL_PollEvent(&ev)&&ev.type==SDL_QUIT)return 0;
		#endif
	}
}