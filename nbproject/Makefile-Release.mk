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
	${OBJECTDIR}/controller/cb_failure_controller.o \
	${OBJECTDIR}/controller/ctrl_controller.o \
	${OBJECTDIR}/controller/meas_controller.o \
	${OBJECTDIR}/controller/overcurrent_controller.o \
	${OBJECTDIR}/controller/prot_controller.o \
	${OBJECTDIR}/goose_in.o \
	${OBJECTDIR}/ied_server.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/model/BIED100_model.o \
	${OBJECTDIR}/model/LIED10_model.o \
	${OBJECTDIR}/model/LIED11_model.o \
	${OBJECTDIR}/model/TIED13_model.o \
	${OBJECTDIR}/model/UFIED_model.o \
	${OBJECTDIR}/model/dynamic_model.o \
	${OBJECTDIR}/sv_in.o


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

${OBJECTDIR}/controller/cb_failure_controller.o: controller/cb_failure_controller.c
	${MKDIR} -p ${OBJECTDIR}/controller
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/controller/cb_failure_controller.o controller/cb_failure_controller.c

${OBJECTDIR}/controller/ctrl_controller.o: controller/ctrl_controller.c
	${MKDIR} -p ${OBJECTDIR}/controller
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/controller/ctrl_controller.o controller/ctrl_controller.c

${OBJECTDIR}/controller/meas_controller.o: controller/meas_controller.c
	${MKDIR} -p ${OBJECTDIR}/controller
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/controller/meas_controller.o controller/meas_controller.c

${OBJECTDIR}/controller/overcurrent_controller.o: controller/overcurrent_controller.c
	${MKDIR} -p ${OBJECTDIR}/controller
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/controller/overcurrent_controller.o controller/overcurrent_controller.c

${OBJECTDIR}/controller/prot_controller.o: controller/prot_controller.c
	${MKDIR} -p ${OBJECTDIR}/controller
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/controller/prot_controller.o controller/prot_controller.c

${OBJECTDIR}/goose_in.o: goose_in.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/goose_in.o goose_in.c

${OBJECTDIR}/ied_server.o: ied_server.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ied_server.o ied_server.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/model/BIED100_model.o: model/BIED100_model.c
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/BIED100_model.o model/BIED100_model.c

${OBJECTDIR}/model/LIED10_model.o: model/LIED10_model.c
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/LIED10_model.o model/LIED10_model.c

${OBJECTDIR}/model/LIED11_model.o: model/LIED11_model.c
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/LIED11_model.o model/LIED11_model.c

${OBJECTDIR}/model/TIED13_model.o: model/TIED13_model.c
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/TIED13_model.o model/TIED13_model.c

${OBJECTDIR}/model/UFIED_model.o: model/UFIED_model.c
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/UFIED_model.o model/UFIED_model.c

${OBJECTDIR}/model/dynamic_model.o: model/dynamic_model.c
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/dynamic_model.o model/dynamic_model.c

${OBJECTDIR}/sv_in.o: sv_in.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I.install/include -include .install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sv_in.o sv_in.c

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
