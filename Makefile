OBJ = main.o MusicLibControl.o UI.o StringUtils.o Log.o Song.o Track.o Recording.o Playlist.o User.o

musiclib:	$(OBJ)
	g++ -g -o musiclib $(OBJ)

main.o:	main.cpp 
	g++ -c main.cpp

MusicLibControl.o:	MusicLibControl.cpp MusicLibControl.h UI.h Log.h
	g++ -c MusicLibControl.cpp

UI.o:	UI.cpp UI.h 
	g++ -c UI.cpp

Log.o:	Log.cpp Log.h 
	g++ -c Log.cpp

StringUtils.o:	StringUtils.cpp StringUtils.h
	g++ -c StringUtils.cpp

Song.o: Song.cpp Song.h
	g++ -c Song.cpp


Track.o: Track.cpp Track.h Song.h
	g++ -c Track.cpp

Recording.o: Recording.cpp Recording.h Track.h
	g++ -c Recording.cpp

Playlist.o: Playlist.cpp Playlist.h Track.h
	g++ -c Playlist.cpp


User.o: User.cpp User.h Playlist.h
	g++ -c User.cpp

clean:
	rm -f $(OBJ) musiclib
