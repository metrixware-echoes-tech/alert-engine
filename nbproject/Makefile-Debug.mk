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
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/Parser.o \
	${OBJECTDIR}/src/ToolsEngine.o \
	${OBJECTDIR}/src/AlertProcessor.o \
	${OBJECTDIR}/src/AlertSender.o

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
LDLIBSOPTIONS=-L../dbo/dist/SharedObject/GNU-Linux-x86 -lboost_system -lpthread -lboost_thread -lboost_serialization -lboost_filesystem -lwt -lwtdbo -ldbo -lboost_program_options

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/engine

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/engine: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/engine ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -I../dbo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/Parser.o: src/Parser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -I../dbo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Parser.o src/Parser.cpp

${OBJECTDIR}/src/ToolsEngine.o: src/ToolsEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -I../dbo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ToolsEngine.o src/ToolsEngine.cpp

${OBJECTDIR}/src/AlertProcessor.o: src/AlertProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -I../dbo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AlertProcessor.o src/AlertProcessor.cpp

${OBJECTDIR}/src/AlertSender.o: src/AlertSender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -I../dbo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AlertSender.o src/AlertSender.cpp

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
	$(COMPILE.cc) -g -I. -Iinclude -I../UnitTest++/src -I../dbo/include -MMD -MP -MF $@.d -o ${TESTDIR}/tests/src/TestConnectionTCP.o tests/src/TestConnectionTCP.cpp


${TESTDIR}/tests/main.o: tests/main.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -Iinclude -I../UnitTest++/src -I../dbo/include -MMD -MP -MF $@.d -o ${TESTDIR}/tests/main.o tests/main.cpp


${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -I../dbo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/src/Parser_nomain.o: ${OBJECTDIR}/src/Parser.o src/Parser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Parser.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -I../dbo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Parser_nomain.o src/Parser.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Parser.o ${OBJECTDIR}/src/Parser_nomain.o;\
	fi

${OBJECTDIR}/src/ToolsEngine_nomain.o: ${OBJECTDIR}/src/ToolsEngine.o src/ToolsEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ToolsEngine.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -I../dbo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ToolsEngine_nomain.o src/ToolsEngine.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ToolsEngine.o ${OBJECTDIR}/src/ToolsEngine_nomain.o;\
	fi

${OBJECTDIR}/src/AlertProcessor_nomain.o: ${OBJECTDIR}/src/AlertProcessor.o src/AlertProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/AlertProcessor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -I../dbo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AlertProcessor_nomain.o src/AlertProcessor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/AlertProcessor.o ${OBJECTDIR}/src/AlertProcessor_nomain.o;\
	fi

${OBJECTDIR}/src/AlertSender_nomain.o: ${OBJECTDIR}/src/AlertSender.o src/AlertSender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/AlertSender.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -I../UnitTest++/src -I../dbo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AlertSender_nomain.o src/AlertSender.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/AlertSender.o ${OBJECTDIR}/src/AlertSender_nomain.o;\
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
