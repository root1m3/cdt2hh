PROT:=cdt2hh
R1:=cdt
R2:=hh
OBJR1:=${PROT}-${R1}.o
OBJR2:=${PROT}-${R2}.o
CPPS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(CPPS))
HS:=$(wildcard *.h)

all: ${OBJR1} ${OBJR2}

%.o: %.cpp
	${CXX} -fPIC -c ${CXXFLAGS} ${INC} $^ -o $@

${R1}/role.o:
	$(MAKE) CXXFLAGS="${CXXFLAGS}" -C ${R1};

${R2}/role.o:
	$(MAKE) CXXFLAGS="${CXXFLAGS}" -C ${R2};

${OBJR1}: ${OBJS} ${CPPS} ${HS} ${R1}/role.o
	ld -z defs -r ${R1}/role.o ${OBJS} -o ${OBJR1}

${OBJR2}: ${OBJS} ${CPPS} ${HS} ${R2}/role.o
	ld -z defs -r ${R2}/role.o ${OBJS} -o ${OBJR2}

clean:
	$(MAKE) clean -C ${R1};
	$(MAKE) clean -C ${R2};
	$(RM) -f *.o

.PHONY: all clean R1 R2


