CXX?=clang++-6.0
#CXX?=g++-8
CXXFLAGS = -g -Wall -Werror=sign-compare -MMD -MF $@.d
OBJS =		playground.o \
	test/avl_tree.test.o  \
	test/simple_any.test.o \
	test/graph.test.o \
	test/weighted_jobs_scheduling_solver.test.o
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
