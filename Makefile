#Disabling implicit rules
.SUFFIXES:

GCC := gcc
LDLIBS := -L./ -L/home/kevin/eclipse-workspace/CG/glfw/build/src
LDFLAGS := -lGL -lglfw3 -ldl -lX11 -lctest -lm -lpthread
CFLAGS := -I/home/kevin/eclipse-workspace/CG/include/ -I.
src := $(wildcard *.c)
obj := $(src:.c=.o)
headers := $(wildcard *.h)
deps := $(wildcard *.d)



# Specify how the object files should be created from the source files
main: $(obj)
	$(GCC)  $^ $(LDLIBS) $(LDFLAGS) -o $@

%.o : %.c 
	$(GCC) -c -g -Wall -MMD -o $@ $< $(CFLAGS) 

# Specify the target for cleaning up the project
.PHONY : clean
clean:
	rm -f $(obj) main $(deps) 

.PHONY : createDep
createDep:
	$(GCC) -E -MMD $(src) $(CFLAGS)
	
libctest.a: ctest1.o ctest2.o
	ar -cvq libctest.a ctest1.o ctest2.o
	
#ctest1.o: ctest1.c
#	gcc -c ctest1.c
	
#ctest2.o: ctest2.c
#	gcc -c ctest2.c

hi:
	echo $(src)
	echo $(headers)
	echo $(deps)


test: utils.o
	gcc $< -o $@




-include $(deps)
