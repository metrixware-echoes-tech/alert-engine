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
CCC=g++-4.4
CXX=g++-4.4
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Parser.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/ToolsEngine.o \
	${OBJECTDIR}/src/AlertProcessor.o \
	${OBJECTDIR}/src/AlertSender.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-DNDEBUG -std=c++0x
CXXFLAGS=-DNDEBUG -std=c++0x

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/var/lib/jenkins/jobs/ea-dbo-develop/workspace/default/dist/Release_SharedObject/GNU-Linux-x86 -L../dbo/dist/Release_SharedObject/GNU-Linux-x86 -lboost_system -lpthread -lboost_thread -lboost_serialization -lboost_filesystem -lwt -lwtdbo -ldbo -lboost_program_options -lboost_unit_test_framework -lboost_signals

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/engine

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/engine: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/engine -s ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/Parser.o: src/Parser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../UnitTest++/src -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-develop/workspace/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Parser.o src/Parser.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../UnitTest++/src -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-develop/workspace/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/ToolsEngine.o: src/ToolsEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../UnitTest++/src -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-develop/workspace/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ToolsEngine.o src/ToolsEngine.cpp

${OBJECTDIR}/src/AlertProcessor.o: src/AlertProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../UnitTest++/src -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-develop/workspace/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AlertProcessor.o src/AlertProcessor.cpp

${OBJECTDIR}/src/AlertSender.o: src/AlertSender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../UnitTest++/src -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-develop/workspace/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AlertSender.o src/AlertSender.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/engine

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
