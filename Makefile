G++ = g++
CFLAGS= -std=c++11 
LIBS = -lpthread
OPTS = -O3
DEBUG = -g

# App name
APPNAME = recommender

#Object
OBJS = *.cpp *.h
		
release : ; $(G++) $(OBJS) -o $(APPNAME) $(LIBS) $(CFLAGS) $(OPTS)

debug	: ; $(G++) $(OBJS) -o $(APPNAME) $(LIBS) $(CFLAGS) $(DEBUG)
	 gdb --args ./recommender content.csv ratings.csv targets.csv

all	:
clean :
	rm -f $(APPNAME) *.o
