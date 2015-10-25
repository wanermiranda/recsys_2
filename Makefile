G++ = g++
CFLAGS= -std=c++11 
LIBS = -lpthread
OPTS = -O3
DEBUG = -g

# App name
APPNAME = recommender

#Object
OBJS = main.cpp CSVReader.cpp CSVReader.h StringUtils.cpp StringUtils.h ArrayUtils.h ArrayUtils.cpp
release : ; $(G++) $(OBJS) -o $(APPNAME) $(LIBS) $(CFLAGS) $(OPTS)

debug	: ; $(G++) $(OBJS) -o $(APPNAME) $(LIBS) $(CFLAGS) $(DEBUG)

all	:
clean :
	rm -f $(APPNAME) *.o
