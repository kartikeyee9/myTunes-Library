#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Track.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Playlist
{
public:
	Playlist(string);
	string getName();
	void addTrack(Track* track);
	bool removeTrack(int trackId);
	void printAllTracks(ostream &output);


	friend ostream &operator<<( ostream &output, const Playlist &p ) { 
		output << "Playlist: " << p.name << endl;
		output << "Tracks: " << endl;
		for(auto it = p.tracks.begin(); it != p.tracks.end(); ++it) {
			output << "\t" << **it << endl;
		}

		return output;

	}

private:
	string name;
	vector<Track*> tracks;

};
#endif

