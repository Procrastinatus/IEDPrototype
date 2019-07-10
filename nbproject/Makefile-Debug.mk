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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/controller/measurement_controller.o \
	${OBJECTDIR}/controller/protection_controller.o \
	${OBJECTDIR}/controller/status_controller.o \
	${OBJECTDIR}/goose_in.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/mms_server_module.o \
	${OBJECTDIR}/model/LIED10_model.o \
	${OBJECTDIR}/model/dynamic_model.o \
	${OBJECTDIR}/sv_in.o


# C Compiler Flags
CFLAGS=-pthread -lrt -g

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

${OBJECTDIR}/controller/measurement_controller.o: controller/measurement_controller.c
	${MKDIR} -p ${OBJECTDIR}/controller
	${RM} "$@.d"
	$(COMPILE.c) -g -I.install/include -I.install/hal/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/controller/measurement_controller.o controller/measurement_controller.c

${OBJECTDIR}/controller/protection_controller.o: controller/protection_controller.c
	${MKDIR} -p ${OBJECTDIR}/controller
	${RM} "$@.d"
	$(COMPILE.c) -g -I.install/include -I.install/hal/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/controller/protection_controller.o controller/protection_controller.c

${OBJECTDIR}/controller/status_controller.o: controller/status_controller.c
	${MKDIR} -p ${OBJECTDIR}/controller
	${RM} "$@.d"
	$(COMPILE.c) -g -I.install/include -I.install/hal/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/controller/status_controller.o controller/status_controller.c

${OBJECTDIR}/goose_in.o: goose_in.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I.install/include -I.install/hal/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/goose_in.o goose_in.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I.install/include -I.install/hal/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/mms_server_module.o: mms_server_module.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I.install/include -I.install/hal/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mms_server_module.o mms_server_module.c

${OBJECTDIR}/model/LIED10_model.o: model/LIED10_model.c
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.c) -g -I.install/include -I.install/hal/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/LIED10_model.o model/LIED10_model.c

${OBJECTDIR}/model/dynamic_model.o: model/dynamic_model.c
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.c) -g -I.install/include -I.install/hal/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/dynamic_model.o model/dynamic_model.c

${OBJECTDIR}/sv_in.o: sv_in.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I.install/include -I.install/hal/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sv_in.o sv_in.c

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
