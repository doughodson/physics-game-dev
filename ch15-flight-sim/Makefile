
include ../makedefs

PGM = flight-sim

OBJS =  \
	BourgFDM.o \
	main.o

.PHONY: all
all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f $(PGM)
