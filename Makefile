G++ = g++
CFLAGS= -std=c++11 
LIBS = -lpthread
OPTS = -O3
DEBUG = -g

# App name
APPNAME = recommender

#Object
OBJS = *.cpp *.h
		
release 	: ; $(G++) $(OBJS) -o $(APPNAME) $(LIBS) $(CFLAGS) $(OPTS) 

debug  		: ; $(G++) -DDEBUG $(OBJS) -o $(APPNAME) $(LIBS) $(CFLAGS) $(DEBUG)

run_debug	: ; make debug
	 	gdb --args ./recommender content.csv ratings.csv targets.csv

run_test        : ; $(G++) -DEVAL -DDEBUG $(OBJS) -o $(APPNAME) $(LIBS) $(CFLAGS) $(OPTS)   
		time -v ./recommender content.csv ratings.csv targets.csv > out.stat

run_local_test	: ; $(G++) -DEVAL $(OBJS) -o $(APPNAME) $(LIBS) $(CFLAGS) $(OPTS)   
		time -v ./recommender content.csv ratings.csv target_tests.csv > out.stat

run		: ; make release 
		./recommender content.csv ratings.csv targets.csv > out.stat
all		:
clean :
	rm -f $(APPNAME) *.o
