ROOT = ..

include ${ROOT}/makedefs

LDFLAGS += -nostdlib

VPATH=./VL53L7CX_ULD_API/src
VPATH+=./Platform

IPATH=../inc

all: ${COMPILER}
all: ${COMPILER}/vl53l7cx.a

clean:
	@rm -rf ${COMPILER} ${wildcard *~}

${COMPILER}:
	@mkdir -p ${COMPILER}

${COMPILER}/vl53l7cx.a: ${COMPILER}/vl53l7cx_api.o
${COMPILER}/vl53l7cx.a: ${COMPILER}/platform.o

ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif