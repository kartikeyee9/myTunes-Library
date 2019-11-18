

#include "Track.h"
#include "Playlist.h"
#include <string>
#include <vector>

using namespace std;


Playlist::Playlist(string inTitle) {
	name = inTitle;
}

string Playlist::getName() {
	return name;
}


void Playlist::addTrack(Track* track){
	tracks.push_back(track);
}

bool Playlist::removeTrack(int trackId){
	bool removed = false;
	for (int i = tracks.size() - 1; i >= 0 ; --i) {
		if(tracks[i]->getTrackId() == trackId) {
			tracks.erase(tracks.begin() + i);
			removed = true;
		}
	}

	return removed;
}

void Playlist::printAllTracks(ostream &output){
	if(tracks.size() == 0)
		output << "No tracks in this playlist";
	else{
		for(auto it = tracks.begin(); it != tracks.end(); ++it) {
			output << **it << endl;
		}
	}
	
}




