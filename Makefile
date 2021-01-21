# @author: David Brousseau

CFLAGS = -std=c99 -pedantic -W -Wall

.PHONY: default memcheck clean
.SILENT: doc memcheck

default:
	mkdir -p bin
	gcc src/pipeline.c -g $(CFLAGS) -o bin/pipeline

doc:
	mkdir -p $@
	(cat Doxyfile 2> doxygen.log;\
	echo 'GENERATE_LATEX=NO';\
	echo 'HAVE_DOT=NO';\
	echo 'OPTIMIZE_OUTPUT_FOR_C=YES';\
	echo 'OUTPUT_DIRECTORY=$@';\
	echo 'PROJECT_NAME="fork() & pipe()"';\
	echo 'RECURSIVE=YES') | doxygen - >> doxygen.log
	ln -rsf $@/html/index.html $@/index.html

memcheck: default
	echo 'abc123' > tmp
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	--log-file=valgrind.log \
	bin/pipeline tmp > /dev/null
	rm tmp

clean:
	rm -rf bin doc *.log