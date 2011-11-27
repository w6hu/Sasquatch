CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD -DIMPLTYPE_${TYPE}
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS =Bank.o BottlingPlant.o NameServer.o Parent.o Printer.o ProcessConfigFile.o Student.o Truck.o VendingMachine.o WATCard.o WATCardOffice.o a6main.o# object files forming 1st executable with prefix "q2"
EXEC = soda
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"

#################################################################

.PHONY : clean

all : ${EXEC} # build all executables

${EXEC} : ${OBJECTS}
	${CXX} $^ -o $@

#################################################################
${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC} *.class ImplType
