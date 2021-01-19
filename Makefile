# @author: David Brousseau

CFLAGS = -std=c99 -pedantic -W -Wall

.PHONY: all clean

default: bin
	gcc src/pipeline.c -g $(CFLAGS) -o bin/pipeline

bin:
	mkdir -p $@

doc:
	mkdir -p $@
	(cat Doxyfile ; echo 'GENERATE_LATEX=NO';\
	echo 'HAVE_DOT=NO';\
	echo 'OPTIMIZE_OUTPUT_FOR_C=YES';\
	echo 'OUTPUT_DIRECTORY=$@';\
	echo 'PROJECT_NAME="fork() & pipe()"';\
	echo 'RECURSIVE=YES') | doxygen -
	ln -rsf $@/html/index.html $@/index.html

memcheck: default
	echo 'abc123' >> tmp
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	--log-file=valgrind.log \
	bin/pipeline tmp
	rm tmp

clean:
	rm -rf bin doc valgrind.log