CXX?=clang++-6.0
#CXX?=g++-8
CXXFLAGS = -g -Wall -Werror=sign-compare -MMD -MF $@.d
OBJS =		playground.o algorithms/avl_tree.test.o  incubator/simple_any.test.o
# algorithms/disjoint_set.t.o todo/shared_ptr.t.o

LIBS =

TARGET =	playground

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) *.d */*.d 

run: $(TARGET)
	./$(TARGET)

-include *.d */*.d
