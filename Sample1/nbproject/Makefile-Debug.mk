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
	${OBJECTDIR}/OgreWrap/src/MyMouseListener.o \
	${OBJECTDIR}/OgreWrap/src/MapTexture.o \
	${OBJECTDIR}/src/Sample1.o \
	${OBJECTDIR}/OgreWrap/src/MyManager.o \
	${OBJECTDIR}/OgreWrap/src/MovingManager.o \
	${OBJECTDIR}/OgreWrap/src/MyFrameListener.o \
	${OBJECTDIR}/OgreWrap/src/OgreWrap.o \
	${OBJECTDIR}/OgreWrap/src/LabelManager.o \
	${OBJECTDIR}/OgreWrap/src/EntityManager.o \
	${OBJECTDIR}/OgreWrap/src/ObjectTitle.o


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
LDLIBSOPTIONS=-L/usr/lib -L/usr/lib/OGRE -lOgreMain -lOIS ../Strategix/dist/Debug/GNU-Linux-x86/libstrategix.a -lCEGUIOpenGLRenderer -lboost_filesystem

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/sample1

dist/Debug/GNU-Linux-x86/sample1: ../Strategix/dist/Debug/GNU-Linux-x86/libstrategix.a

dist/Debug/GNU-Linux-x86/sample1: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sample1 ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/OgreWrap/src/MyMouseListener.o: OgreWrap/src/MyMouseListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/OgreWrap/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../common_include -IOgreWrap/include -I../Strategix/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -MMD -MP -MF $@.d -o ${OBJECTDIR}/OgreWrap/src/MyMouseListener.o OgreWrap/src/MyMouseListener.cpp

${OBJECTDIR}/OgreWrap/src/MapTexture.o: OgreWrap/src/MapTexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/OgreWrap/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../common_include -IOgreWrap/include -I../Strategix/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -MMD -MP -MF $@.d -o ${OBJECTDIR}/OgreWrap/src/MapTexture.o OgreWrap/src/MapTexture.cpp

${OBJECTDIR}/src/Sample1.o: src/Sample1.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../common_include -IOgreWrap/include -I../Strategix/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sample1.o src/Sample1.cpp

${OBJECTDIR}/OgreWrap/src/MyManager.o: OgreWrap/src/MyManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/OgreWrap/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../common_include -IOgreWrap/include -I../Strategix/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -MMD -MP -MF $@.d -o ${OBJECTDIR}/OgreWrap/src/MyManager.o OgreWrap/src/MyManager.cpp

${OBJECTDIR}/OgreWrap/src/MovingManager.o: OgreWrap/src/MovingManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/OgreWrap/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../common_include -IOgreWrap/include -I../Strategix/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -MMD -MP -MF $@.d -o ${OBJECTDIR}/OgreWrap/src/MovingManager.o OgreWrap/src/MovingManager.cpp

${OBJECTDIR}/OgreWrap/src/MyFrameListener.o: OgreWrap/src/MyFrameListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/OgreWrap/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../common_include -IOgreWrap/include -I../Strategix/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -MMD -MP -MF $@.d -o ${OBJECTDIR}/OgreWrap/src/MyFrameListener.o OgreWrap/src/MyFrameListener.cpp

${OBJECTDIR}/OgreWrap/src/OgreWrap.o: OgreWrap/src/OgreWrap.cpp 
	${MKDIR} -p ${OBJECTDIR}/OgreWrap/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../common_include -IOgreWrap/include -I../Strategix/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -MMD -MP -MF $@.d -o ${OBJECTDIR}/OgreWrap/src/OgreWrap.o OgreWrap/src/OgreWrap.cpp

${OBJECTDIR}/OgreWrap/src/LabelManager.o: OgreWrap/src/LabelManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/OgreWrap/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../common_include -IOgreWrap/include -I../Strategix/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -MMD -MP -MF $@.d -o ${OBJECTDIR}/OgreWrap/src/LabelManager.o OgreWrap/src/LabelManager.cpp

${OBJECTDIR}/OgreWrap/src/EntityManager.o: OgreWrap/src/EntityManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/OgreWrap/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../common_include -IOgreWrap/include -I../Strategix/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -MMD -MP -MF $@.d -o ${OBJECTDIR}/OgreWrap/src/EntityManager.o OgreWrap/src/EntityManager.cpp

${OBJECTDIR}/OgreWrap/src/ObjectTitle.o: OgreWrap/src/ObjectTitle.cpp 
	${MKDIR} -p ${OBJECTDIR}/OgreWrap/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I../common_include -IOgreWrap/include -I../Strategix/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -MMD -MP -MF $@.d -o ${OBJECTDIR}/OgreWrap/src/ObjectTitle.o OgreWrap/src/ObjectTitle.cpp

# Subprojects
.build-subprojects:
	cd ../Strategix && ${MAKE}  -f Makefile CONF=Debug
	cd ../Strategix && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/sample1

# Subprojects
.clean-subprojects:
	cd ../Strategix && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Strategix && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
