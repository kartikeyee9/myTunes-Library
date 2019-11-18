#ifndef SONG_H
#define SONG_H
#include <string>
#include <iostream>
#include "StringUtils.h"

using namespace std;


class Song
{
  public:
    Song(int, string, string);
    
    string getTitle() const;
    string getComposer() const;
    int getSongId() const;
    friend ostream &operator<<( ostream &output, const Song &s ) { 
      output <<  "Song " <<  s.songId <<": " << StringUtils::toTitleCase(s.title) << " by " << StringUtils::toTitleCase(s.composer);
      return output;            
    }

    

  private:
    int songId;
    string title;
    string composer;
};

#endif
