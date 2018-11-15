########################################################################################
TARGET_CPP_FILES =  $(wildcard *.cpp)
TARGET_EXECUTABLES = $(patsubst %.cpp, %, $(TARGET_CPP_FILES) )
CPPFLAGS := -std=c++11
IFLAGS := -I ../../../include
LDFLAGS :=  -lopencv_highgui  -lopencv_imgcodecs   -lopencv_imgproc  -lopencv_core

#####################################################################################
#	some customization for the linking phase, add the modules you want to link in 
#	these two variables:
CORE_MODULES := gui
ALG_MODULES  :=

####################################################################################
LOGG := ../../..
CORE_MODULES := $(addprefix $(LOGG)/core/, $(addsuffix /lib, $(CORE_MODULES)) )
ALG_MODULES := $(addprefix $(LOGG)/alg/, $(addsuffix /lib, $(ALG_MODULES)) )
LIB_CORE_FILES := $(foreach dir, $(CORE_MODULES), $(wildcard $(dir)/*.o) )
LIB_ALG_FILES := $(foreach dir, $(ALG_MODULES), $(wildcard $(dir)/*.o) )

LIB_FILES := $(LIB_ALG_FILES) $(LIB_CORE_FILES)



all:  $(TARGET_EXECUTABLES)
$(TARGET_EXECUTABLES): % :   %.cpp $(LIB_FILES)
	g++ $(CPPFLAGS)	 -o $@ $^  $(IFLAGS) $(LDFLAGS) 

clean:
	rm -f *o
	rm -f $(TARGET_EXECUTABLES)
