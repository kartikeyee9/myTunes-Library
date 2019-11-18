#ifndef TRACK_H
#define TRACK_H

#include "Song.h"
#include "StringUtils.h"
#include <string>
#include <iostream>

using namespace std;

class Track
{
public:
	Track(int, string, Song*, int);
	string getMp3File();
	Song* getSong();
	int getTrackId();
	int getTrackNumber();
	
	friend ostream &operator<<( ostream &output, const Track &t ) { 
      output <<  "Track - ID:" << t.trackId << ", MP3 File: " << t.mp3_file << ", Song: " << (t.song)->getTitle() << ", Track #" << t.trackNumber;
      return output;
    }


private:
	int trackId;
	string mp3_file;
	Song* song;
	int trackNumber;
};
#endif
