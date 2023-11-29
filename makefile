compiler=g++
bin=bin
exe=ims
obj=obj
src=src
inc=include

all:  $(obj)/highway.o $(obj)/car.o $(obj)/$(exe).o $(bin)/$(exe)

$(obj)/highway.o: $(src)/highway.cpp
	$(compiler) -c $^ -o $@

$(obj)/car.o: $(src)/car.cpp
	$(compiler) -c $^ -o $@

$(obj)/$(exe).o: $(src)/main.cpp
	$(compiler) -c $^ -o $@

$(bin)/$(exe): $(obj)/highway.o $(obj)/car.o $(obj)/$(exe).o
	$(compiler) $^ -o $@

clean:
	rm -f $(obj)/*.o $(bin)/$(exe)

run:
	$(bin)/./$(exe)
