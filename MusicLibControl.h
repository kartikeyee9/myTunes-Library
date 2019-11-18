#ifndef MUSICLIBCONTROL_H
#define MUSICLIBCONTROL_H

#include <vector> 
#include "UI.h"
#include "Log.h"
#include "Song.h"
#include "Recording.h"
#include "Track.h"
#include "User.h"

using namespace std;

class MusicLibControl
{
  public:
    void launch(int, char*[]);
    Recording* findRecording(int id);
    Song* findSong(int id);
    Track* findTrack(int id);
    User* findUser(string id);


  private:
    UI  view;
    Log log;
    vector<Song> songs;
	vector<Recording> recordings;
	vector<Track> tracks;
	vector<User> users;
    void parseCommand(string command, vector<string>& commandDetails);
    void processCommand(string& command, vector<string>& commandDetails, bool interactive);
    void showHelp();
    void runScript(string scriptFile);
    void processAddCommand(vector<string>& commandDetails);
    void processShowCommand(vector<string>& commandDetails);
    void processDeleteCommand(vector<string>& commandDetails);
    void deleteSong(int id);
    void deleteRecording(int id);
    void deleteUser(string id);
    void deleteTrack(int id);
    void deleteTracksWithSong(int songId);
    void deleteTrackFromRecordings(int trackId);
    void deleteTrackFromUsers(int trackId);
};
#endif