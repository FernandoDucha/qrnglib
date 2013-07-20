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
	${OBJECTDIR}/source/BinaryRandomWalk.o \
	${OBJECTDIR}/source/Cronometro.o \
	${OBJECTDIR}/source/DataPoints.o \
	${OBJECTDIR}/source/DataPointsSet.o \
	${OBJECTDIR}/source/FileRawBuffer.o \
	${OBJECTDIR}/source/GeneralUsage.o \
	${OBJECTDIR}/source/ProbabilityBase.o \
	${OBJECTDIR}/source/RandomNumberGenerator.o \
	${OBJECTDIR}/source/RandomWalkVecSet.o \
	${OBJECTDIR}/source/RandomWalkVector.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lgmp -lgmpxx `pkg-config --libs gsl` -lrt  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librandomfwk.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librandomfwk.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librandomfwk.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librandomfwk.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librandomfwk.a

${OBJECTDIR}/source/BinaryRandomWalk.o: source/BinaryRandomWalk.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude `pkg-config --cflags gsl` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/BinaryRandomWalk.o source/BinaryRandomWalk.cpp

${OBJECTDIR}/source/Cronometro.o: source/Cronometro.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude `pkg-config --cflags gsl` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Cronometro.o source/Cronometro.cpp

${OBJECTDIR}/source/DataPoints.o: source/DataPoints.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude `pkg-config --cflags gsl` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/DataPoints.o source/DataPoints.cpp

${OBJECTDIR}/source/DataPointsSet.o: source/DataPointsSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude `pkg-config --cflags gsl` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/DataPointsSet.o source/DataPointsSet.cpp

${OBJECTDIR}/source/FileRawBuffer.o: source/FileRawBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude `pkg-config --cflags gsl` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/FileRawBuffer.o source/FileRawBuffer.cpp

${OBJECTDIR}/source/GeneralUsage.o: source/GeneralUsage.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude `pkg-config --cflags gsl` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/GeneralUsage.o source/GeneralUsage.cpp

${OBJECTDIR}/source/ProbabilityBase.o: source/ProbabilityBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude `pkg-config --cflags gsl` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/ProbabilityBase.o source/ProbabilityBase.cpp

${OBJECTDIR}/source/RandomNumberGenerator.o: source/RandomNumberGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude `pkg-config --cflags gsl` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/RandomNumberGenerator.o source/RandomNumberGenerator.cpp

${OBJECTDIR}/source/RandomWalkVecSet.o: source/RandomWalkVecSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude `pkg-config --cflags gsl` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/RandomWalkVecSet.o source/RandomWalkVecSet.cpp

${OBJECTDIR}/source/RandomWalkVector.o: source/RandomWalkVector.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude `pkg-config --cflags gsl` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/RandomWalkVector.o source/RandomWalkVector.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librandomfwk.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
