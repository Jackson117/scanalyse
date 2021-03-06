OS = $(shell uname -s)
CXX = g++
DEBUG = yes

# Default mode is "Release"
DEFAULT_MODE  = Release
MODE         ?= $(DEFAULT_MODE)
# If mode is something other than "Debug" or "Release",throw a fit
ifneq ($(MODE),Debug)
ifneq ($(MODE),Release)
$(error MODE must be one of {Debug,Release})
endif
endif
# Flags for compiling the code
ifeq ($(MODE),Debug)
CXXFLAGS = -Wall -g3 -DDEBUG -std=c++0x -DVERBOSE -Ilib/ -I/usr/local/include/
CXXGSLFLAGS = -Wall -g3 -DDEBUG -std=c++0x -DVERBOSE -Ilib/ -I/usr/local/include/ -lgsl
else
CXXFLAGS = -Wall -O3 -ffast-math -Ilib/ -std=c++0x -DNDEBUG
CXXGSLFLAGS = -Wall -O3 -ffast-math -Ilib/ -std=c++0x -DNDEBUG -lgsl
endif
all: cellTest funTest linearRegressionTest
#ArgParserTest
cellTest: tests/cellTest.cpp lib/cell/cell.o
	${CXX} ${CXXFLAGS} -o $@ $^
funTest: tests/funTest.cpp lib/cell/cell.o lib/fun/fun.o
	${CXX} ${CXXFLAGS} -o $@ $^
linearRegressionTest: tests/linearRegressionTest.cpp lib/cell/cell.o lib/linearRegression/linearRegressionParameter.o lib/linearRegression/linearRegression.o
	${CXX} ${CXXGSLFLAGS} -o $@ $^
ArgParserTest: test/testargparser.cpp lib/argparser.o
	${CXX} ${CXXFLAGS} -o $@ $^
clean:
	rm lib/cell/*.o lib/fun/*.o lib/linearRegression/*.o cellTest funTest linearRegressionTest
