#include "Song.h"
#include "Track.h"

#include <string>
using namespace std;

Track::Track(int inTrackId, string inMp3File, Song* inSong, int inTrackNum){
	trackId = inTrackId;
	mp3_file = inMp3File;
	song = inSong;
	trackNumber = inTrackNum;
}

string Track::getMp3File() {
	return mp3_file;
}

Song* Track::getSong(){
	return song;
}

int Track::getTrackId(){
	return trackId;
}

int Track::getTrackNumber(){
	return trackNumber;
}



