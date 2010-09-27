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
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Kernel.o \
	${OBJECTDIR}/src/MapSAstar.o \
	${OBJECTDIR}/src/Player.o \
	${OBJECTDIR}/src/Map.o \
	${OBJECTDIR}/src/TechTree.o \
	${OBJECTDIR}/src/EntityInfo.o \
	${OBJECTDIR}/src/StraxLog.o \
	${OBJECTDIR}/src/Entity.o \
	${OBJECTDIR}/src/TechTreeBuilderFromXml.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/libstrategix.a

dist/Debug/GNU-Linux-x86/libstrategix.a: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${RM} dist/Debug/GNU-Linux-x86/libstrategix.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libstrategix.a ${OBJECTFILES} 
	$(RANLIB) dist/Debug/GNU-Linux-x86/libstrategix.a

${OBJECTDIR}/src/Kernel.o: src/Kernel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/local/boost_1_42_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Kernel.o src/Kernel.cpp

${OBJECTDIR}/src/MapSAstar.o: src/MapSAstar.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/local/boost_1_42_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MapSAstar.o src/MapSAstar.cpp

${OBJECTDIR}/src/Player.o: src/Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/local/boost_1_42_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Player.o src/Player.cpp

${OBJECTDIR}/src/Map.o: src/Map.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/local/boost_1_42_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Map.o src/Map.cpp

${OBJECTDIR}/src/TechTree.o: src/TechTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/local/boost_1_42_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TechTree.o src/TechTree.cpp

${OBJECTDIR}/src/EntityInfo.o: src/EntityInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/local/boost_1_42_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EntityInfo.o src/EntityInfo.cpp

${OBJECTDIR}/src/StraxLog.o: src/StraxLog.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/local/boost_1_42_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/StraxLog.o src/StraxLog.cpp

${OBJECTDIR}/src/Entity.o: src/Entity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/local/boost_1_42_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Entity.o src/Entity.cpp

${OBJECTDIR}/src/TechTreeBuilderFromXml.o: src/TechTreeBuilderFromXml.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/local/boost_1_42_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TechTreeBuilderFromXml.o src/TechTreeBuilderFromXml.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/libstrategix.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
