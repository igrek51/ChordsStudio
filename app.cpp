#include "app.h"

App::App(int w, int h, string version, int ctrls){
	this->version = version;
	window_w=w;
	window_h=h;
	ctrls_num = ctrls;
	if(ctrls>0){
		hctrl = new HWND [ctrls_num];
		wndproc_old = new WNDPROC [ctrls_num];
		for(int i=0; i<ctrls_num; i++){
			hctrl[i]=NULL;
			wndproc_old[i]=NULL;
		}
	}else{
		hctrl = NULL;
		wndproc_old = NULL;
	}
}

App::~App(){
	log("Clean up...");
	UnhookWindowsHookEx(hHookkb);
	midi_close(midi_device);
	for(int i=0; i<ctrls_num; i++){
		un_subclass(i);
		if(hctrl[i]!=NULL) DestroyWindow(hctrl[i]);
	}
	log("Goodbye World...");
	PostQuitMessage(0);
}

void App::setInstance(HINSTANCE *hInst){
	this->hInst = hInst;
}
