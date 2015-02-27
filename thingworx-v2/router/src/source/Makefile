# (c)2014 ThingWorx
# C SDK Example App Make file

ifeq ($(TW_SDK_PATH),)
TW_SDK_PATH = ../../../../tw-c-sdk
endif

################## APP SPECIFIC DEFINES #######################

# TW_APP_NAME is the desired name of the application executable
TW_APP_NAME      = module

# TW_APP_DIR is where your application directory is
TW_APP_DIR       := .

# TW_APP_INC_DIR is where your application source files are located
TW_APP_INC_DIR      := $(TW_APP_DIR)

# TW_APP_SRC_DIR is where your application source files are located
TW_APP_SRC_DIR       := $(TW_APP_DIR)

# TW_APP_SRC is a list of your source files
TW_APP_SRC     := module.c module_cfg.c

# Extra Preprocessor defines
TW_APP_DEFS      = -I../common
# Dependencies on external libraries
EXT_LIB_DEPS	 = -L../common -lcommon

# CGI 
MODULE_CGI_EXE = module_cgi
MODULE_CGI_OBJ = module_cgi.o module_cfg.o

CPPFLAGS += -I../common
LDFLAGS += -s -L../common
LDLIBS += -lcommon

#####################################################
# Should not need to Modify anything below this line
#####################################################
TW_SDK_LIB_NAME = Tw
TW_SDK_LIB_PATH = $(TW_SDK_PATH)/build/obj/$(PLATFORM)/$(BUILDDIR)

#SDK Include paths
SDK_INC_DIRS := $(patsubst %,-I %,$(shell find $(TW_SDK_PATH)/src -maxdepth 1 -type d))

# Default to an arm build
ifeq ($(PLATFORM),)
PLATFORM          = arm-926ejs-linux-gnueabi
endif

# Set our build type (debug or release), default is debug
ifeq ($(BUILD),debug)
DDEBUG          = -D"DEBUG" -g -O0 
BUILDDIR        = debug
else
DDEBUG          = -Os -s -fno-asynchronous-unwind-tables -Wl,--strip-all
BUILDDIR        = release
endif

#Include the platform specific compiler settings
include $(TW_SDK_PATH)/build/platforms/$(PLATFORM)/Makefile.$(PLATFORM)

.PHONY: all

all: $(MODULE_CGI_EXE) app 

sdk: lib

lib: obj $(TW_SDK_LIB_NAME) 

$(TW_SDK_LIB_NAME): $(LIB_OBJS) 
	$(AR) $@  $(patsubst %.c,obj/$(PLATFORM)/$(BUILDDIR)/%.o,$(notdir $(TW_SDK_SRC))) 
	$(RANLIB) $@
	mkdir -p $(LIBDEST) ; mv $@ $(LIBDEST)

obj:
	if [ ! -d obj ] ; then mkdir obj ; mkdir obj/$(BUILDDIR) ; fi


clean:
	rm -Rf obj/$(PLATFORM)/$(BUILDDIR)
	rm -Rf bin/$(PLATFORM)/$(BUILDDIR)
	rm -f core *.core core.*
	rm -f $(MODULE_EXE) $(MODULE_CGI_EXE) *.o

#
# compilation
#
vpath %.h .:$(INCDIR)

$(LIB_OBJS): 
#	$(ECHO) LIB_SRCS = $(TW_SDK_SRC) 
	$(CC) $(CC_OPTS) $(DEFS) -c $(subst obj/$(BUILDDIR)/,,$(subst .o,.c,$@)) 
	mkdir -p $(LIBDEST); mv $(notdir $(subst obj/$(BUILDDIR)/,,$(subst .c,.o, $@))) $(LIBDEST)/$(notdir $(subst obj/$(BUILDDIR)/,,$(subst .c,.o, $@))) 

app: $(LIBNAME)
	$(CC) $(CC_OPTS) $(DDEBUG) -c -I $(TW_APP_INC_DIR) $(TW_APP_DEFS) $(EXT_LIB_DEPS) $(SDK_INC_DIRS) $(DEFS) $(patsubst %,$(TW_APP_SRC_DIR)/%,$(TW_APP_SRC)) 
	mkdir -p obj/$(PLATFORM)/$(BUILDDIR); mv *.o  obj/$(PLATFORM)/$(BUILDDIR)
	$(LINKER) $(LIBOPTS) -L$(LIBDIR) -L$(TW_SDK_LIB_PATH) $(patsubst %.c,obj/$(PLATFORM)/$(BUILDDIR)/%.o,$(notdir $(TW_APP_SRC))) $(TW_APP_DEFS) $(EXT_LIB_DEPS) $(STATIC_LIBS) -l$(TW_SDK_LIB_NAME) $(LIB_DEPS) 
	mkdir -p bin/$(PLATFORM)/$(BUILDDIR) ; mv a.out bin/$(PLATFORM)/$(BUILDDIR)/$(TW_APP_NAME); rm -f $(subst .c,.o,$(TW_APP_SRC))

$(MODULE_CGI_EXE): $(MODULE_CGI_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(EXT_LIB_DEPS)

install:
	install -d $(DESTDIR)/bin/
	install -d $(DESTDIR)/www/
	install -m 755 bin/$(PLATFORM)/$(BUILDDIR)/$(TW_APP_NAME) $(DESTDIR)/bin/thingworxd
	install -m 755 $(MODULE_CGI_EXE) $(DESTDIR)/bin/cgi
	ln -s ../bin/cgi $(DESTDIR)/www/index.cgi
	ln -s ../bin/cgi $(DESTDIR)/www/set.cgi
	# ln -s /etc/htpasswd $(DESTDIR)/www/.htpasswd
