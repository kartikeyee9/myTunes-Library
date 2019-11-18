#ifndef USER_H
#define USER_H

#include "Playlist.h"
#include "Track.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User
{
public:
	User(string, string);
	string getUserId();
	string getName();
	void addPlaylist(Playlist* playlist);
	bool removePlaylist(string name);
	Playlist* findPlaylist(string name);
	void addTrackToPlaylist(string playlistName, Track* track);
	void printAllPlaylists(ostream &output);
	void printTracksInPlaylist(string playlistName, ostream &output);
	void removeTrack(int trackId);


	friend ostream &operator<<( ostream &output, const User &u ) { 
		output << "User: " << u.name << "(" << u.userId << ")" << endl;
		output << "Playlists: " << endl;
		for(auto it = u.playlists.begin(); it != u.playlists.end(); ++it) {
			output << **it << endl;
		}

		return output;
	}

private:
	string userId;
	string name;
	vector<Playlist*> playlists;

};
#endif

