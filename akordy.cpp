#include "akordy.h"

string chords_names[48] = {
	"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "B", "H",
	"c", "c#", "d", "d#", "e", "f", "f#", "g", "g#", "a", "b", "h",
	"C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "B7", "H7",
	"c7", "c#7", "d7", "d#7", "e7", "f7", "f#7", "g7", "g#7", "a7", "b7", "h7"};

string get_chord(int chord_nr, int type){
	while(chord_nr<0) chord_nr+=12;
	while(chord_nr>=12) chord_nr-=12;
	if(type==3){
		return chords_names[chord_nr+12];
	}else if(type==5){
		return chords_names[chord_nr+36];
	}else if(type==6){
		return chords_names[chord_nr+24];
	}else{
		return chords_names[chord_nr];
	}
}
