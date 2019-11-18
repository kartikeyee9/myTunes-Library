#include <string>
#include "MusicLibControl.h"
#include "StringUtils.h"
#include <vector> 
#include <iostream>
#include <fstream>

using namespace std;



void MusicLibControl::launch(int argc, char* argv[]) {
	bool quit = false;
	string command;
	while(quit == false) {
		view.promptForStr("CMD or .quit:", command);
		if(command == ".quit") {
			quit = true;
			break;
		}
		else {
			vector<string> commandDetails;
			parseCommand(command, commandDetails);
			processCommand(command, commandDetails, true);
		}
	}
}

void MusicLibControl::parseCommand(string command, vector<string>& commandDetails) {
	
	if(command.find("//") == 0) {
		commandDetails.push_back(command);
		return;
	}


	string keyword = "";
	int i = 0;



	while(i < command.size()) {
		if(command[i] == ' ') {
			if(keyword.size() > 0)
				commandDetails.push_back(keyword);
			keyword = "";
		} else if(command[i] == '"') {
			i++;
			while(command[i] != '"') {
				keyword += command[i];
				i++;
			}
			commandDetails.push_back(keyword);
			keyword = "";
		} else 
			keyword += command[i];

		i++;
	}

	if(keyword.size() > 0)
		commandDetails.push_back(keyword);

	
}

void MusicLibControl::showHelp() {
	string fileName = "help.txt";
	ifstream file(fileName, ifstream::in);
	if(!file){
		cout << "ERROR: could not open file " << fileName << endl;
		log.addToLog("ERROR: could not open file " + fileName, false);
		return;
	} 

	string input;
	while(getline(file, input)){
		cout << input << endl;
		log.addToLog(input, false);
	}
}





void MusicLibControl::processCommand(string& command, vector<string>& v, bool interactive) {
	if(command.size() == 0)
			return;

	string commandName = v[0];


	if(StringUtils::startsWith(commandName, "//")) {
		if(interactive) {
			log.addToLog(command, true);
		}
	} 
	else if(commandName == ".help") {
		if(interactive) {
			log.addToLog(command, true);
			showHelp();
		}
	} else if(commandName == ".trim") {
		if(interactive) {
			log.addToLog(command, true);
			string output = StringUtils::trim(v[1]);
			view.printMessage(output);
			log.addToLog(output, false);
		}
	} else if(commandName == ".startsWith") {
		if(interactive) {
			log.addToLog(command, true);
			string output = StringUtils::toString(StringUtils::startsWith(v[1], v[2]));
			view.printMessage(output);
			log.addToLog(output, false);
		}
	} else if(commandName == ".endsWith") {
		if(interactive) {
			log.addToLog(command, true);
			string output = StringUtils::toString(StringUtils::endsWith(v[1], v[2]));
			view.printMessage(output);
			log.addToLog(output, false);
		}
	} else if(commandName == ".toTitleCase") {
		if(interactive) {
			log.addToLog(command, true);
			string output = StringUtils::toTitleCase(v[1]);
			view.printMessage(output);
			log.addToLog(output, false);
		}
	} else if(commandName == ".read") {
		if(interactive) {
			log.addToLog(command, true);
			runScript(v[1]);
		}
	} else if(commandName == ".quit") {
		if(interactive) {
			log.addToLog(command, true);
		}
	} else if(commandName == ".log") {
		log.addToLog(command, true);
		if(v[1] == "clear") {
			log.clear();
		}
		else if(v[1] == "start") {
			log.logCommands();
		}
		else if(v[1] == "start_output") {
			log.logOutputs();
		}
		else if(v[1] == "start_both"){
			log.logBoth();
		}
		else if(v[1] == "stop"){
			log.stopLogging();
		}
		else if(v[1] == "save") {
			log.save(v[2]); 
		} else if(v[1] == "show") {
			view.printParsedCommand(log.getLog());
		}
	} 
	else if(commandName == "add") {
		log.addToLog(command, true);

		view.printMessage("Executing: " + command);
		log.addToLog("Executing: " + command, false);
		processAddCommand(v);


	} else if(commandName == "delete") {
		log.addToLog(command, true);
		view.printMessage("Executing: " + command);
		log.addToLog("Executing: " + command, false);
		processDeleteCommand(v);

	}  else if(commandName == "show") {
		log.addToLog(command, true);
		view.printMessage("Executing: " + command);
		log.addToLog("Executing: " + command, false);
		processShowCommand(v);



	} 
	
}

void MusicLibControl::runScript(string scriptFile) {
	ifstream file(scriptFile, ifstream::in);
	if(!file){
		cout << "ERROR: could not open file " << scriptFile << endl;
		return;
	} 

	string input;
	while(getline(file, input)){
		vector<string> commandDetails;
		parseCommand(input, commandDetails);
		processCommand(input, commandDetails, false);
	}
}

void MusicLibControl::processAddCommand(vector<string>& commandDetails) {
	// add -s song_id title composer
	if(commandDetails[1] == "-s") {
		Song *s = new Song(stoi(commandDetails[2]), commandDetails[3], commandDetails[4]);
		songs.push_back(*s); 
	}

	else if(commandDetails[1] == "-r") {
		// nt id, string inTitle, string inArtist, int inYear, string inProducer
		// recording_id title artist producer year
		Recording *recording = new Recording(stoi(commandDetails[2]), commandDetails[3], commandDetails[4], stoi(commandDetails[6]), commandDetails[5]);
		recordings.push_back(*recording);
	}

	else if(commandDetails[1] == "-u") {
		User* user = new User(commandDetails[2], commandDetails[3]);
		users.push_back(*user);
	}

	else if(commandDetails[1] == "-t") {
		// add -t track_id album_id song_id track_number
		Recording* recording = findRecording(stoi(commandDetails[3]));
		Song* song = findSong(stoi(commandDetails[4]));
		
		Track* track = new Track(stoi(commandDetails[2]), "unknown", song, stoi(commandDetails[5]));
		tracks.push_back(*track);
		recording->addTrack(track);
	}



	else if(commandDetails[1] == "-p") {
		// add -p ajones "Driving Songs"
		User* user  = findUser(commandDetails[2]);
		Playlist* playlist = new Playlist(commandDetails[3]);
		user->addPlaylist(playlist);
	}

	else if(commandDetails[1] == "-l") {
		// add -l ajones "Driving Songs" 1001
		User* user  = findUser(commandDetails[2]);
		Track* track = findTrack(stoi(commandDetails[4]));
		user->addTrackToPlaylist(commandDetails[3], track);
	}
}

Recording* MusicLibControl::findRecording(int id) {
	for (int i = 0; i < recordings.size(); ++i)
	{
		if(recordings[i].getRecordingId() == id)
			return &recordings[i];
	}

	return NULL;
}

Song* MusicLibControl::findSong(int id) {
	for (int i = 0; i < songs.size(); ++i)
	{
		if(songs[i].getSongId() == id)
			return &songs[i];
	}

	return NULL;
}

Track* MusicLibControl::findTrack(int id) {
	for (int i = 0; i < tracks.size(); ++i)
	{
		if(tracks[i].getTrackId() == id)
			return &tracks[i];
	}

	return NULL;
}

User* MusicLibControl::findUser(string id) {
	for (int i = 0; i < users.size(); ++i)
	{
		if(users[i].getUserId() == id)
			return &users[i];
	}

	return NULL;
}

void MusicLibControl::processShowCommand(vector<string>& commandDetails) {

	if(commandDetails[1] == "songs") {
		if(commandDetails.size() == 2) {
			// show songs
			for (int i = 0; i < songs.size(); ++i){
				cout << songs[i] << endl;
			}
		} else {
			// show songs -u user_id -p playlist_name
			User* user = findUser(commandDetails[3]);
			user->printTracksInPlaylist(commandDetails[5], cout);
		}
	}


	else if(commandDetails[1] == "users") {
		// show users
		for (int i = 0; i < users.size(); ++i){
			cout << users[i] << endl << endl;
		}
		
	}

	else if(commandDetails[1] == "playlists") {
		// show playlists -u user_id
		User* user = findUser(commandDetails[3]);
		user->printAllPlaylists(cout);
	}

	else if(commandDetails[1] == "playlists") {
		// show playlists -u user_id
		User* user = findUser(commandDetails[3]);
		user->printAllPlaylists(cout);
	} 

	else if(commandDetails[1] == "tracks") {
		// show tracks
		for (int i = 0; i < tracks.size(); ++i){
				cout << tracks[i] << endl;
		}
	}

	else if(commandDetails[1] == "recordings") {
		// show tracks
		for (int i = 0; i < recordings.size(); ++i){
			cout << recordings[i] << endl;
		}
	}

	
	
}

void MusicLibControl::processDeleteCommand(vector<string>& commandDetails) {

	if(commandDetails[1] == "-s") {
		if(commandDetails.size() == 3) {
			// delete -s song_id
			int songId = stoi(commandDetails[2]);
			deleteSong(songId);
		} else {
			// delete -s track_id -p playlist_name -u user_name
			int trackId = stoi(commandDetails[2]);
			string playlistName = commandDetails[4];
			string userId = commandDetails[6];
			User* user = findUser(userId);
			Playlist* playlist = user->findPlaylist(playlistName);
			playlist->removeTrack(trackId);
		}
	} 


	else if(commandDetails[1] == "-t") {
		if(commandDetails.size() == 3) {
			// delete -t track_id
			int trackId = stoi(commandDetails[2]);
			deleteTrack(trackId);
		} else {
			// delete -t track_id -p playlist_name -u user_name
			int trackId = stoi(commandDetails[2]);
			string playlistName = commandDetails[4];
			string userId = commandDetails[6];
			User* user = findUser(userId);
			Playlist* playlist = user->findPlaylist(playlistName);
			playlist->removeTrack(trackId);
		}
	} 

	else if(commandDetails[1] == "-r") {
		// delete -r recording_id
		deleteRecording(stoi(commandDetails[2]));
	} 

	else if(commandDetails[1] == "-u") {
		// delete -r recording_id
		deleteUser(commandDetails[2]);
	} 

	else if(commandDetails[1] == "-p") {
		// delete -p playist_name -u user_id
		string playlistName = commandDetails[2];
		string userId = commandDetails[4];
		User* user = findUser(userId);
		user->removePlaylist(playlistName);
	} 

	else if(commandDetails[1] == "-GLOBAL") {
		//delete -Global -s track_id -p playlist_name -u user_name  //DEPRECATED but still supported
    	// delete -Global -t track_id -p playlist_name -u user_name
		int trackId = stoi(commandDetails[3]);
		string playlistName = commandDetails[5];
		string userId = commandDetails[7];
		User* user = findUser(userId);
		Playlist* playlist = user->findPlaylist(playlistName);
		playlist->removeTrack(trackId);
	}


}

void  MusicLibControl::deleteSong(int id){
	deleteTracksWithSong(id);
	for (int i = songs.size() - 1; i >= 0 ; --i){
		if(songs[i].getSongId() == id) {
			songs.erase(songs.begin() + i);
		}
	}
}

void  MusicLibControl::deleteRecording(int id){
	for (int i = recordings.size() - 1; i >= 0 ; --i){
		if(recordings[i].getRecordingId() == id) {
			recordings.erase(recordings.begin() + i);
		}
	}
}

void  MusicLibControl::deleteUser(string id){
	for (int i = users.size() - 1; i >= 0 ; --i){
		if(users[i].getUserId() == id) {
			users.erase(users.begin() + i);
		}
	}
}

void  MusicLibControl::deleteTrack(int id){
	deleteTrackFromUsers(id);
	deleteTrackFromRecordings(id);
	for (int i = tracks.size() - 1; i >= 0 ; --i){
		if(tracks[i].getTrackId() == id) {
			tracks.erase(tracks.begin() + i);
		}
	}
}

void  MusicLibControl::deleteTracksWithSong(int songId){
	for (int i = tracks.size() - 1; i >= 0 ; --i)
	{
		if(tracks[i].getSong()->getSongId() == songId) {
			deleteTrackFromUsers(tracks[i].getTrackId());
			deleteTrackFromRecordings(tracks[i].getTrackId());
			tracks.erase(tracks.begin() + i);
		}
	}
}

void  MusicLibControl::deleteTrackFromUsers(int trackId){
	for (int i = users.size() - 1; i >= 0 ; --i) {
		users[i].removeTrack(trackId);
	}
}


void  MusicLibControl::deleteTrackFromRecordings(int trackId){
	for (int i = recordings.size() - 1; i >= 0 ; --i) {
		recordings[i].removeTrack(trackId);
	}
}


	




