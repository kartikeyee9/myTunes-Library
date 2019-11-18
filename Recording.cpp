

#include "Track.h"
#include "Recording.h"
#include <string>
#include <vector>

using namespace std;


Recording::Recording(int id, string inTitle, string inArtist, int inYear, string inProducer) {
	recordingId = id;
	title = inTitle;
	artist = inArtist;
	year = inYear;
	producer = inProducer;
}

int Recording::getRecordingId() {
	return recordingId;
}

string Recording::getTitle() {
	return title;
}

string Recording::getArtist() {
	return artist;
}

int Recording::getYear(){
	return year;
}

string Recording::getProducer(){
	return producer;

}

void Recording::addTrack(Track* track){
	tracks.push_back(track);
}

bool Recording::removeTrack(int trackId){
	bool removed = false;
	for (int i = tracks.size() - 1; i >= 0 ; --i) {
		if(tracks[i]->getTrackId() == trackId) {
			tracks.erase(tracks.begin() + i);
			removed = true;
		}
	}

	return removed;
}




