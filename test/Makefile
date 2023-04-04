#Disabling implicit rules
.SUFFIXES:

LDLIBS := -L/home/kevin/eclipse-workspace/CG/skills/ -Wl,-rpath=/home/kevin/eclipse-workspace/CG/skills
LDFLAGS := -lm -lmatrix
#CFLAGS := -I/home/kevin/eclipse-workspace/CG/include/ -I.
src := $(wildcard *.c)
obj := $(src:.c=.o)
headers := $(wildcard *.h)
deps := $(wildcard *.d)

#obj := $(obj) ../skills/sort.o
#obj := $(obj) ../skills/matrixcalc.o


main: $(obj)
	#make -C ../skills -f ../skills/Makefile
	gcc $^ $(LDLIBS) $(LDFLAGS) -o $@

%.o : %.c 
	gcc -c -g -Wall -MMD -o $@ $<  

# Specify the target for cleaning up the project
.PHONY : clean
clean:
	#make -C ../skills -f ../skills/Makefile clean
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
	echo $(src)
	echo $(headers)
	echo $(deps)
	echo $(obj)


-include $(deps)
