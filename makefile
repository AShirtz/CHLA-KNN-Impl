CC = clang
CFLAGS = -g

TEST_CASE_OBJS = 	1tc.o \
			2tc.o \
			3tc.o \
			4tc.o \
			5tc.o \
			6tc.o \
			7tc.o \
			8tc.o \
			9tc.o \
			10tc.o 

UTIL_OBJS = 		Utils.o \
			Objects.o \
			FileIO.o \
			Queries.o

RELEASE_FILES = 	Preprocess.o \
			kNearestNeighbors.o

WORKSPACE = 		workspace.o

all: workspace

clean: 
	rm *.o target/test/* target/release/* 

workspace: workspaceFile
	

publish: releaseFiles

testCases: $(TEST_CASE_OBJS) $(UTIL_OBJS)
	$(CC) $(CFLAGS) 1tc.o $(UTIL_OBJS) -o target/test/1tc -lm
	$(CC) $(CFLAGS) 2tc.o $(UTIL_OBJS) -o target/test/2tc -lm
	$(CC) $(CFLAGS) 3tc.o $(UTIL_OBJS) -o target/test/3tc -lm
	$(CC) $(CFLAGS) 4tc.o $(UTIL_OBJS) -o target/test/4tc -lm
	$(CC) $(CFLAGS) 5tc.o $(UTIL_OBJS) -o target/test/5tc -lm
	$(CC) $(CFLAGS) 6tc.o $(UTIL_OBJS) -o target/test/6tc -lm
	$(CC) $(CFLAGS) 7tc.o $(UTIL_OBJS) -o target/test/7tc -lm
	$(CC) $(CFLAGS) 8tc.o $(UTIL_OBJS) -o target/test/8tc -lm
	$(CC) $(CFLAGS) 9tc.o $(UTIL_OBJS) -o target/test/9tc -lm
	$(CC) $(CFLAGS) 10tc.o $(UTIL_OBJS) -o target/test/10tc -lm

releaseFiles: $(RELEASE_FILES) $(UTIL_OBJS)
	$(CC) $(CFLAGS) Preprocess.o $(UTIL_OBJS) -o target/release/Preprocess -lm
	$(CC) $(CFLAGS) kNearestNeighbors.o $(UTIL_OBJS) -o target/release/kNearestNeighbors -lm

workspaceFile: $(WORKSPACE) $(UTIL_OBJS)
	$(CC) $(CFLAGS) workspace.o $(UTIL_OBJS) -o target/test/workspace -lm
	
%.o: src/%.c
	$(CC) $(CFLAGS) -c $(CFLAGS) $< -o $@

%.o: src/*/%.c
	$(CC) $(CFLAGS) -c $(CFLAGS) $< -o $@
