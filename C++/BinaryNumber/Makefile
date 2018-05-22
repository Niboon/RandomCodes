CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = a2q5
OBJECTS = a2q5.o binarynum.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
