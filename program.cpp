#include "app.h"
#include "akordy.h"

void App::change_font(HWND hwdp){
	if(hwdp==NULL) return;
	HFONT hFont=CreateFont(fontsize,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,0,0,0,0,fontface.c_str());
	SendMessage(hwdp,WM_SETFONT,(WPARAM)hFont,true);
}

void App::checkbox1_click(int set){
	if(set==0) checkbox1=0;
	else if(set==1) checkbox1=1;
	else if(set==2) checkbox1=1-checkbox1;
	if(checkbox1==1) SendMessage(hctrl[2],BM_SETCHECK,BST_CHECKED,0);
	else SendMessage(hctrl[2],BM_SETCHECK,BST_UNCHECKED,0);
}

void App::radiobutton1_click(int set){
	radiobutton1=set;
	for(int i=0; i<6; i++){
		SendMessage(hctrl[17+i],BM_SETCHECK,BST_UNCHECKED,0);
	}
	SendMessage(hctrl[16+radiobutton1],BM_SETCHECK,BST_CHECKED,0);
	refresh_buttons12();
}

void App::capo_add(int add){
	kapodaster+=add;
	ss_clear(ss);
	ss<<"Kapodaster: ";
	if(kapodaster>0) ss<<"+";
	ss<<kapodaster;
	if(kapodaster<0){
		int kapo2 = kapodaster;
		while(kapo2<0) kapo2+=12;
		ss<<" (";
		if(kapo2>0) ss<<"+";
		ss<<kapo2<<")";
	}
	SetWindowText(hctrl[23],ss.str().c_str());
	refresh_buttons12();
}

void App::volume_add(int add){
	volume+=add;
	if(volume<0) volume=0;
	if(volume>100) volume=100;
	ss_clear(ss);
	ss<<"G³oœnoœæ: "<<volume<<"/100";
	SetWindowText(hctrl[28],ss.str().c_str());
}

void App::refresh_buttons12(){
	for(int i=0; i<12; i++){
		ss_clear(ss);
		ss<<get_chord(i,radiobutton1);
		if(kapodaster%12!=0){
			ss<<" ("<<get_chord(i+kapodaster,radiobutton1)<<")";
		}
		SetWindowText(hctrl[4+i],ss.str().c_str());
	}
}

void App::button_chord(int button_nr){
	if(button_nr>=0&&button_nr<=keyshift-1) midi_play_chord(basetone+button_nr+kapodaster,radiobutton1);
	if(button_nr>=keyshift&&button_nr<=11) midi_play_chord(basetone-12+button_nr+kapodaster,radiobutton1);
	ss_clear(ss);
	ss<<"Akord: "<<get_chord(basetone+button_nr+kapodaster,radiobutton1);
	echo(ss.str());
}
