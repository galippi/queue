##################################################################
#CFLAGS_DEBUG= -gstabs
CFLAGS_DEBUG= -gdwarf-2
#CFLAGS_DEBUG= -gdwarf -g3

WARNINGS = -Wall -Wextra
WARNINGS += -Wwrite-strings -Wcast-qual -Wpointer-arith -Wsign-compare
WARNINGS += -Wundef
WARNINGS += -Wmissing-declarations
WARNINGS += -Werror

#CFLAGS_OPTIM= -O6
#CFLAGS_NO_CYGWIN_DLL=-mno-cygwin
CC       = gcc
#CC       = i686-pc-mingw32-gcc.exe
LL       = gcc
#LL       = ld
#LL       = i686-pc-mingw32-gcc.exe
CFLAGS   = $(WARNINGS) $(CFLAGS_OPTIM) -Wall $(CFLAGS_DEBUG) $(CFLAGS_NO_CYGWIN_DLL)
#CFLAGS  += -I/usr/include/SDL
#CFLAGS  += -std=c11
CFLAGS  += -std=c99
CPPFLAGS   = $(CFLAGS) -fno-rtti

#LDFLAGS_STRIP_DEVUG_INFO = -s
# LDFLAGS  = -s  $(CFLAGS_NO_CYGWIN_DLL) -lcrypto -lssl #-lsocket -lnsl
LDFLAGS  = $(LDFLAGS_STRIP_DEVUG_INFO)  $(CFLAGS_NO_CYGWIN_DLL) #-lsocket -lnsl
#LDFLAGS += -L./pc-libs
LDFLAGS += -Wl,--enable-stdcall-fixup
#LDFLAGS += --disable-stdcall-fixup
LDFLAGS += -L./lib
#LDLIBS := -lcygwin
LDLIBS :=
#LDLIBS += -lEcuTalk
#LDLIBS += -lltdl
#LDLIBS += -lcygwin
#LDLIBS += -lz
#LDLIBS += -lSDL
#it's necessary for the new SDL library
#LDLIBS += -lwinmm
#LDLIBS += -lmsvcrt70
#LDLIBS += -lmsvcrt
#LDLIBS += -lgdi32
#LDLIBS += -ldxguid
#LDLIBS += -lstdc++
MAKEFILE=Makefile
##################################################################
TARGET=test1
TARGET_DIR=obj/

#CPPFILES = $(TARGET).cpp
#CPPFILES+= TestList.cpp
#CPPFILES+= debug.cpp
#CPPFILES+= osm_xml.cpp
#CFILES    = $(TARGET).c
#CFILES   += debug.c
CFILES   += queue_test.c
CFILES   += queue.c

#SUBDIRS := debug

VPATH := $(SUBDIRS) $(TARGET_DIR)
OBJECTS = $(CPPFILES:.cpp=.o) $(CFILES:.c=.o)
DEPFILES = $(addprefix $(TARGET_DIR),$(CPPFILES:.cpp=.d) $(CFILES:.c=.d))
INCDIRS = $(addprefix -I./,$(SUBDIRS))
INCDIRS += -I.
CFLAGS += $(INCDIRS)

DUMMY_DIR_FILE := $(TARGET_DIR)dummy

TARGET_EXE = $(TARGET_DIR)$(TARGET).exe
all : $(TARGET_EXE)

$(TARGET_EXE) : $(OBJECTS)
	$(LL) $(LDFLAGS) $(addprefix $(TARGET_DIR),$(OBJECTS)) $(LDLIBS) -o $@

#%.o: %.c $(MAKEFILE)
%.o: %.c $(DUMMY_DIR_FILE)
	@echo Building $@
	$(CC) $(CFLAGS) -c -o $(TARGET_DIR)$@ $<
	-@rm -f $(@:.o=.d)
	$(CC) -M $(CFLAGS) -c -o $(TARGET_DIR)$(@:.o=.d) $<

#%.o: %.cpp $(MAKEFILE)
%.o: %.cpp $(DUMMY_DIR_FILE)
	@echo Building $@
	$(CC) $(CPPFLAGS) -c -o $(TARGET_DIR)$@ $<
	-@rm -f $(@:.o=.d)
	$(CC) -M $(CPPFLAGS) -c -o $(TARGET_DIR)$(@:.o=.d) $<
#	$(CC) --version

$(DUMMY_DIR_FILE):
	-mkdir $(TARGET_DIR)
	echo Dummy file >$@

targetdir:
	-mkdir $(sort $(dir $(OBJECTS)))

##################################################################
# cleaning rule
##################################################################

clean:
	rm -f $(addprefix $(TARGET_DIR), *.o *.d *~ $(TARGET))
	rm -f $(OBJECTS)
	rm -f $(OBJECTS:.o=.d)
	rm -f version.h
	rm -r $(TARGET_DIR)

dep_test:
	@echo DEPFILES=$(DEPFILES)
	@echo wildcard=$(wildcard $(DEPFILES))

include version.mk
$(TARGET).o: version.h

include $(wildcard $(DEPFILES))
