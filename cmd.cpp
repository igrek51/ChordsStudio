#include "app.h"

void App::exec_cmd(){
	char *str2 = new char[256];
	GetWindowText(hctrl[0],str2,256);
	if(strlen(str2)==0){
		SetWindowText(hctrl[0],last_cmd.c_str());
		return;
	}
	SetWindowText(hctrl[0],"");
	exec_cmd(str2);
	last_cmd=str2;
	delete[] str2;
}

void App::exec_cmd(char *str2){
	stringstream s1;
	s1<<"> "<<str2;
	if(strcmp(str2,"p")==0){
		param = last_cmd;
		ss_clear(ss);
		ss<<"Parametr ["<<param.length()<<"]: "<<param;
		echo(ss.str());
	}else if(strcmp(str2,"param")==0){
		SetWindowText(hctrl[0],param.c_str());
	}else if(strcmp(str2,"log")==0){
		ShellExecute(0,"open","log.txt","",0,SW_SHOW);
	}else if(strcmp(str2,"config")==0){
		ShellExecute(0,"open","conf.ini","",0,SW_SHOW);
	}else if(strcmp(str2,"reload")==0){
		reload_config();
		echo("Ustawienia wczytane");
	}else if(strcmp(str2,"dir")==0){
		ShellExecute(0,"open",".","",0,SW_SHOW);
	}else if(strcmp(str2,"clear")==0){
		SetWindowText(hctrl[1],"");
	}else if(strcmp(str2,"exit")==0){
		DestroyWindow(hwnd);
	}else if(strcmp(str2,"what")==0){
		char *str2 = new char[512];
		GetWindowText(hctrl[1],str2,512);
		message(str2);
		delete[] str2;
	}else if(strcmp(str2,"capo0")==0){
		capo_add(-kapodaster);
	}else if(strcmp(str2,"help")==0){
		ss_clear(ss);
		ss<<"Polecenia:"<<endl;
		message(ss.str());
	}else if(strcmp(str2,"test")==0){

	}else{
		ss_clear(s1);
		s1<<"! Nie znaleziono polecenia: "<<str2;
	}
	echo(s1.str());
}
