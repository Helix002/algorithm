PROG=sort_static

all: $(PROG)

sort_static:
	g++ -g  -c sort_cxx.cpp  		-o  sort_cxx.o          	-std=c++11
	g++ -g  -c sort_cxx_wrapper.c  	-o  sort_cxx_wrapper.o
	gcc -g  -c sort_c.c             -o  sort_c.o				-std=c99
	gcc -g  -c sort_test.c    		-o  sort_test.o				-std=c99
	g++ -g                      	-o 	sort  	sort_cxx.o  sort_cxx_wrapper.o  sort_c.o sort_test.o

sort_shared:
	g++ -g 		sort_cxx.cpp 	  	-shared  	-o  libsort_cxx.so                       	-fPIC -std=c++11
	g++ -g 		sort_cxx_wrapper.c 	-shared  	-o  libsort_cxx_wrapper.so  libsort_cxx.so 	-fPIC -Xlinker -rpath=./
	gcc -g 	-c 	sort_c.c                  	    -o  sort_c.o 	-std=c99
	gcc -g  -c 	sort_test.c    					-o  sort_test.o	-std=c99
	gcc -g 		           						-o  sort	libsort_cxx_wrapper.so sort_c.o sort_test.o

clean:
	rm -f *.o *.so *.exe $(PROG)