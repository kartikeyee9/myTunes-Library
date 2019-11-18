#ifndef RECORDING_H
#define RECORDING_H

#include "Track.h"
#include <string>
#include <vector>
#include "StringUtils.h"

using namespace std;

class Recording
{
public:
	Recording(int, string, string, int, string);
	int getRecordingId();
	string getTitle();
	string getArtist();
	int getYear();
	string getProducer();
	void addTrack(Track* track);
	bool removeTrack(int trackId);
	friend ostream &operator<<( ostream &output, const Recording &r ) { 
		output << "Recording "<<r.recordingId<<" : " << StringUtils::toTitleCase(r.title) 
			<<", Artist: " << StringUtils::toTitleCase(r.artist) 
			<< ", Year: " 
			<< r.year << ", Producer: " << r.producer << endl;
		output << "Tracks in the recording: " << endl;
		for(int i = 0; i < r.tracks.size(); i++) {
			output << "\t" << *r.tracks[i] << endl;
		}

		return output;

	}

private:
	int recordingId;
	string title;
	string artist;
	int year;
	string producer;
	vector<Track*> tracks;

};
#endif

