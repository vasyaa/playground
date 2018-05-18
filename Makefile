CXX?=clang++-6.0
CXXFLAGS =	-std=c++17 -g -Wall -Werror -Werror=sign-compare -MMD -MF $@.d
OBJS =		main.test.o algorithms/avl_tree.t.o 
# algorithms/disjoint_set.t.o todo/shared_ptr.t.o

LIBS =

TARGET =	main.test

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) *.d */*.d 

run: $(TARGET)
	./$(TARGET)

-include *.d */*.d

