CC=gcc

movieTheaterDB: movieTheaterDB.o movieTheaterDB_movie.o movieTheaterDB_actor.o
	$(CC) -o movieTheaterDB movieTheaterDB.o movieTheaterDB_movie.o movieTheaterDB_actor.o

movieTheaterDB.o: movieTheaterDB.c movieTheaterDB.h
	$(CC) -c movieTheaterDB.c

movieTheaterDB_movie.o: movieTheaterDB_movie.c movieTheaterDB_movie.h
	$(CC) -c movieTheaterDB_movie.c

movieTheaterDB_actor.o: movieTheaterDB_actor.c movieTheaterDB_actor.h
	$(CC) -c movieTheaterDB_actor.c

clean:
	rm -f movieTheaterDB movieTheaterDB.o movieTheaterDB_movie.o movieTheaterDB_actor.o
