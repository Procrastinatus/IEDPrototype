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
CND_PLATFORM=GNU-Linux
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
	${OBJECTDIR}/goose_in.o \
	${OBJECTDIR}/goose_out.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/mms_server_module.o \
	${OBJECTDIR}/model/dynamic_model.o \
	${OBJECTDIR}/model/static_model.o


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
LDLIBSOPTIONS=.install/lib/libiec61850.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iedprototype

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iedprototype: .install/lib/libiec61850.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iedprototype: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iedprototype ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/goose_in.o: goose_in.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/goose_in.o goose_in.c

${OBJECTDIR}/goose_out.o: goose_out.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/goose_out.o goose_out.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/mms_server_module.o: mms_server_module.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mms_server_module.o mms_server_module.c

${OBJECTDIR}/model/dynamic_model.o: model/dynamic_model.c
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/dynamic_model.o model/dynamic_model.c

${OBJECTDIR}/model/static_model.o: model/static_model.c
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/static_model.o model/static_model.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
