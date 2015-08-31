#include "app.h"

void App::load_config(){
	log("Wczytywanie ustawieñ");
	if(!file_exists("conf.ini")) echo("! Brak pliku konfiguracyjnego");
	char *temp = new char [512];
	//GetPrivateProfileString("paths","songs_dir",".",temp,512,".\\conf.ini");
	delete[] temp;
	instrument=GetPrivateProfileInt("midi","instrument",25,".\\conf.ini");
	basetone=GetPrivateProfileInt("midi","basetone",60,".\\conf.ini");
	keyshift=GetPrivateProfileInt("midi","keyshift",4,".\\conf.ini");
}

void App::reload_config(){
	midi_close(midi_device);
	load_config();
	midi_device=midi_init();
}
