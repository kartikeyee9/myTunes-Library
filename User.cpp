

#include "User.h"
#include "Playlist.h"
#include <string>
#include <vector>

using namespace std;


User::User(string inUserId, string inName) {
	userId = inUserId;
	name = inName;
}

string User::getUserId() {
	return userId;
}

string User::getName() {
	return name;
}

Playlist* User::findPlaylist(string name){
	for (int i = 0; i < playlists.size(); ++i)
	{
		if(playlists[i]->getName() == name)
			return playlists[i];
	}

	return NULL;
}

void User::addPlaylist(Playlist* playlist){
	playlists.push_back(playlist);
}

bool User::removePlaylist(string name){
	bool removed = false;
	for (int i = playlists.size() - 1; i >= 0 ; --i) {
		if(playlists[i]->getName() == name) {
			playlists.erase(playlists.begin() + i);
			removed = true;
		}
	}

	return removed;
}

void User::addTrackToPlaylist(string playlistName, Track* track) {
	Playlist* playlist = findPlaylist(playlistName);
	playlist->addTrack(track);
}

void User::printAllPlaylists(ostream &output) {
	if(playlists.size() == 0)
		output << "No Playlist";
	else {
		for(auto it = playlists.begin(); it != playlists.end(); ++it) {
			output << **it << endl;
		}
	}
}

void User::printTracksInPlaylist(string playlistName, ostream &output) {
	Playlist* playlist = findPlaylist(playlistName);
	playlist->printAllTracks(output);
}


void User::removeTrack(int trackId) {
	for (int i = 0; i < playlists.size(); ++i) {
		playlists[i]->removeTrack(trackId);
	}
}