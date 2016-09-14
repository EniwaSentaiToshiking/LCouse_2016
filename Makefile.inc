APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
PID.o \
SonarAlert.o \
TailControl.o \
Calibration.o \
RemoteStart.o \
UI.o \
LineTraceMethod.o \
GetLogData.o \
RunMethod.o \
BalancerCpp.o \
BalancingWalker.o \
gray_check.o \
Measure.o \
LookupMethod.o \
Stairs.o \
Garage.o \

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(WORKSPACE_LIB_DIR)/libcpp-ev3/Makefile

endif
