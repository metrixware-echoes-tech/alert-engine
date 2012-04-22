#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/MessageManager.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/ConnectionManager.o \
	${OBJECTDIR}/src/SensorMessage.o \
	${OBJECTDIR}/src/ConnectionTCP.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lboost_system -lpthread -lboost_thread -lboost_serialization

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/engine

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/engine: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/engine ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/MessageManager.o: src/MessageManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MessageManager.o src/MessageManager.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/ConnectionManager.o: src/ConnectionManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ConnectionManager.o src/ConnectionManager.cpp

${OBJECTDIR}/src/SensorMessage.o: src/SensorMessage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SensorMessage.o src/SensorMessage.cpp

${OBJECTDIR}/src/ConnectionTCP.o: src/ConnectionTCP.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ConnectionTCP.o src/ConnectionTCP.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/src/TestConnectionTCP.o ${TESTDIR}/tests/main.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/src/TestConnectionTCP.o: tests/src/TestConnectionTCP.cpp 
	${MKDIR} -p ${TESTDIR}/tests/src
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Iinclude -I../UnitTest++/src -MMD -MP -MF $@.d -o ${TESTDIR}/tests/src/TestConnectionTCP.o tests/src/TestConnectionTCP.cpp


${TESTDIR}/tests/main.o: tests/main.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Iinclude -I../UnitTest++/src -MMD -MP -MF $@.d -o ${TESTDIR}/tests/main.o tests/main.cpp


${OBJECTDIR}/src/MessageManager_nomain.o: ${OBJECTDIR}/src/MessageManager.o src/MessageManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/MessageManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MessageManager_nomain.o src/MessageManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/MessageManager.o ${OBJECTDIR}/src/MessageManager_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/src/ConnectionManager_nomain.o: ${OBJECTDIR}/src/ConnectionManager.o src/ConnectionManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ConnectionManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ConnectionManager_nomain.o src/ConnectionManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ConnectionManager.o ${OBJECTDIR}/src/ConnectionManager_nomain.o;\
	fi

${OBJECTDIR}/src/SensorMessage_nomain.o: ${OBJECTDIR}/src/SensorMessage.o src/SensorMessage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/SensorMessage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SensorMessage_nomain.o src/SensorMessage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/SensorMessage.o ${OBJECTDIR}/src/SensorMessage_nomain.o;\
	fi

${OBJECTDIR}/src/ConnectionTCP_nomain.o: ${OBJECTDIR}/src/ConnectionTCP.o src/ConnectionTCP.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ConnectionTCP.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ConnectionTCP_nomain.o src/ConnectionTCP.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ConnectionTCP.o ${OBJECTDIR}/src/ConnectionTCP_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/engine

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
