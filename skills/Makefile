#Disabling implicit rules
.SUFFIXES:

#LDLIBS := -L./ -L/home/kevin/eclipse-workspace/CG/glfw/build/src
#LDFLAGS := -lGL -lglfw3 -ldl -lX11 -lctest -lm -lpthread
#CFLAGS := -I/home/kevin/eclipse-workspace/CG/include/ -I.
src := $(wildcard *.c)
obj := $(src:.c=.o)
headers := $(wildcard *.h)
deps := $(wildcard *.d)



# Specify how the object files should be created from the source files
#main: $(obj)
#	gcc $^ $(LDLIBS) $(LDFLAGS) -o $@

main: $(obj)
	gcc $^ -lm -o $@

%.o : %.c 
	gcc -c -g -Wall -MMD -o $@ $<  

# Specify the target for cleaning up the project
.PHONY : clean
clean:
	rm -f $(obj) main $(deps) 

.PHONY : createDep
createDep:
	gcc -E -MMD $(src) $(CFLAGS)
	
libctest.a: ctest1.o ctest2.o
	ar -cvq libctest.a ctest1.o ctest2.o
	
#ctest1.o: ctest1.c
#	gcc -c ctest1.c
	
#ctest2.o: ctest2.c
#	gcc -c ctest2.c

hi:
	echo "dio merda"
	echo $(src)
	echo $(headers)
	echo $(deps)


-include $(deps)
