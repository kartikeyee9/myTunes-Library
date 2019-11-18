#include "Song.h"

#include <string>
using namespace std;

Song::Song(int inSongId, string inName, string inComposer) {
	songId = inSongId;
	title = inName;
	composer = inComposer;
}

string Song::getTitle() const{
	return title;
}

string Song::getComposer() const{
	return composer;
}

int Song::getSongId() const {
	return songId;
}

