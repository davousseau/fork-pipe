# @author: David Brousseau

CFLAGS = -std=c99 -pedantic -W -Wall

.PHONY: all clean

default: bin
	gcc src/pipeline.c -g $(CFLAGS) -o bin/pipeline

bin:
	mkdir -p $@

doc:
	mkdir -p $@
	(cat Doxyfile ; echo "GENERATE_LATEX=NO";\
	echo "HAVE_DOT=NO";\
	echo "OPTIMIZE_OUTPUT_FOR_C=YES";\
	echo "OUTPUT_DIRECTORY="$@;\
	echo "OUTPUT_LANGUAGE=French";\
	echo "PROJECT_NAME=Communication inter-processus fork() et pipe()";\
	echo "RECURSIVE=YES") | doxygen -
	ln -rsf $@/html/index.html $@/index.html

clean:
	rm -rf bin doc