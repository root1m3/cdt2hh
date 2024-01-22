PROT:=cdt2hh
R:=cdt
OBJ:=role.o
CPPS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(CPPS))
HS:=$(wildcard *.h)

all: ${OBJ}

${OBJ}: ${OBJS} ${CPPS} ${HS}
	ld -z defs -r ${OBJS} -o ${OBJ}

%.o: %.cpp
	${CXX} -fPIC -c ${CXXFLAGS} ${INC} -I.. $^ -o $@

clean:
	$(RM) -f *.o

.PHONY: all clean


