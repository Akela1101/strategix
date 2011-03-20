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
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/TechTreesBuilderFromXml.o \
	${OBJECTDIR}/src/Kernel.o \
	${OBJECTDIR}/src/EntiInfo.o \
	${OBJECTDIR}/src/Unit.o \
	${OBJECTDIR}/src/Player.o \
	${OBJECTDIR}/src/Map.o \
	${OBJECTDIR}/src/TechTree.o \
	${OBJECTDIR}/src/Log.o \
	${OBJECTDIR}/src/Enti.o \
	${OBJECTDIR}/src/KernelBase.o \
	${OBJECTDIR}/src/Mediator.o


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
	"${MAKE}"  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/libstrategix.a

dist/Release/GNU-Linux-x86/libstrategix.a: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${RM} dist/Release/GNU-Linux-x86/libstrategix.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libstrategix.a ${OBJECTFILES} 
	$(RANLIB) dist/Release/GNU-Linux-x86/libstrategix.a

${OBJECTDIR}/src/TechTreesBuilderFromXml.o: src/TechTreesBuilderFromXml.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../common_include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TechTreesBuilderFromXml.o src/TechTreesBuilderFromXml.cpp

${OBJECTDIR}/src/Kernel.o: src/Kernel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../common_include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Kernel.o src/Kernel.cpp

${OBJECTDIR}/src/EntiInfo.o: src/EntiInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../common_include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EntiInfo.o src/EntiInfo.cpp

${OBJECTDIR}/src/Unit.o: src/Unit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../common_include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Unit.o src/Unit.cpp

${OBJECTDIR}/src/Player.o: src/Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../common_include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Player.o src/Player.cpp

${OBJECTDIR}/src/Map.o: src/Map.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../common_include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Map.o src/Map.cpp

${OBJECTDIR}/src/TechTree.o: src/TechTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../common_include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TechTree.o src/TechTree.cpp

${OBJECTDIR}/src/Log.o: src/Log.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../common_include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Log.o src/Log.cpp

${OBJECTDIR}/src/Enti.o: src/Enti.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../common_include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Enti.o src/Enti.cpp

${OBJECTDIR}/src/KernelBase.o: src/KernelBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../common_include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/KernelBase.o src/KernelBase.cpp

${OBJECTDIR}/src/Mediator.o: src/Mediator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../common_include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Mediator.o src/Mediator.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/libstrategix.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
