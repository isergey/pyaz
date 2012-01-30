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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/zrecord.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/zquery.o \
	${OBJECTDIR}/zconnection.o \
	${OBJECTDIR}/zoptions.o \
	${OBJECTDIR}/zscanset.o \
	${OBJECTDIR}/zresultset.o \
	${OBJECTDIR}/zpackage.o


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
LDLIBSOPTIONS=-lyaz -lboost_python

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libpyaz.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libpyaz.so: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libpyaz.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/zrecord.o: zrecord.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/boost -I/usr/include/python2.7 -I/usr/include/yaz -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/zrecord.o zrecord.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/boost -I/usr/include/python2.7 -I/usr/include/yaz -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/zquery.o: zquery.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/boost -I/usr/include/python2.7 -I/usr/include/yaz -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/zquery.o zquery.cpp

${OBJECTDIR}/zconnection.o: zconnection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/boost -I/usr/include/python2.7 -I/usr/include/yaz -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/zconnection.o zconnection.cpp

${OBJECTDIR}/zoptions.o: zoptions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/boost -I/usr/include/python2.7 -I/usr/include/yaz -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/zoptions.o zoptions.cpp

${OBJECTDIR}/zscanset.o: zscanset.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/boost -I/usr/include/python2.7 -I/usr/include/yaz -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/zscanset.o zscanset.cpp

${OBJECTDIR}/zresultset.o: zresultset.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/boost -I/usr/include/python2.7 -I/usr/include/yaz -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/zresultset.o zresultset.cpp

${OBJECTDIR}/zpackage.o: zpackage.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/boost -I/usr/include/python2.7 -I/usr/include/yaz -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/zpackage.o zpackage.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libpyaz.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
