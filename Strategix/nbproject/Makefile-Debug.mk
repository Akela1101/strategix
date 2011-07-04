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
	${OBJECTDIR}/src/MapLocal.o \
	${OBJECTDIR}/src/EntiSlot.o \
	${OBJECTDIR}/src/Kernel.o \
	${OBJECTDIR}/src/MapFull.o \
	${OBJECTDIR}/src/Player.o \
	${OBJECTDIR}/src/StrategixLog.o \
	${OBJECTDIR}/src/FeatureMove.o \
	${OBJECTDIR}/src/FeatureCollect.o \
	${OBJECTDIR}/src/MapsPathsFinder.o \
	${OBJECTDIR}/src/TechTree.o \
	${OBJECTDIR}/src/FeatureAttack.o \
	${OBJECTDIR}/src/Enti.o \
	${OBJECTDIR}/src/KernelBase.o \
	${OBJECTDIR}/src/FeatureHealth.o \
	${OBJECTDIR}/src/CoordStructs.o


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

${OBJECTDIR}/src/MapLocal.o: src/MapLocal.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MapLocal.o src/MapLocal.cpp

${OBJECTDIR}/src/EntiSlot.o: src/EntiSlot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EntiSlot.o src/EntiSlot.cpp

${OBJECTDIR}/src/Kernel.o: src/Kernel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Kernel.o src/Kernel.cpp

${OBJECTDIR}/src/MapFull.o: src/MapFull.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MapFull.o src/MapFull.cpp

${OBJECTDIR}/src/Player.o: src/Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Player.o src/Player.cpp

${OBJECTDIR}/src/StrategixLog.o: src/StrategixLog.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/StrategixLog.o src/StrategixLog.cpp

${OBJECTDIR}/src/FeatureMove.o: src/FeatureMove.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FeatureMove.o src/FeatureMove.cpp

${OBJECTDIR}/src/FeatureCollect.o: src/FeatureCollect.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FeatureCollect.o src/FeatureCollect.cpp

${OBJECTDIR}/src/MapsPathsFinder.o: src/MapsPathsFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MapsPathsFinder.o src/MapsPathsFinder.cpp

${OBJECTDIR}/src/TechTree.o: src/TechTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TechTree.o src/TechTree.cpp

${OBJECTDIR}/src/FeatureAttack.o: src/FeatureAttack.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FeatureAttack.o src/FeatureAttack.cpp

${OBJECTDIR}/src/Enti.o: src/Enti.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Enti.o src/Enti.cpp

${OBJECTDIR}/src/KernelBase.o: src/KernelBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/KernelBase.o src/KernelBase.cpp

${OBJECTDIR}/src/FeatureHealth.o: src/FeatureHealth.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FeatureHealth.o src/FeatureHealth.cpp

${OBJECTDIR}/src/CoordStructs.o: src/CoordStructs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -Isrc -I../include_common -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CoordStructs.o src/CoordStructs.cpp

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
