MODNAME := thingworxV3
TEMPDIR := /tmp/module
IMGDIR  ?= .

# v3: arm v7l-timesys-linux-gnueabi
ifeq ($(PLATFORM), )
PLATFORM= armv7l-timesys-linux-gnueabi
endif

# set the build type, debug or release
ifeq ($(BUILD), )
BUILD=release
endif

export DESTDIR := $(TEMPDIR)/$(MODNAME)

all:
	# build timesys libs
	cp -r armv7l-timesys-linux-gnueabi/ ../../../tw-c-sdk/build/platforms/
	cp source/twLinux.h ../../../tw-c-sdk/src/porting/
	make -C ../../../tw-c-sdk/build PLATFORM=$(PLATFORM) BUILD=$(BUILD)
	# build application
	rm -rf $(DESTDIR)
	mkdir -p $(DESTDIR)
	cp -r merge/* $(DESTDIR)
	make -C source all install PLATFORM=$(PLATFORM) BUILD=$(BUILD)
	tar -C $(TEMPDIR) -czf $(IMGDIR)/$(MODNAME).tgz $(MODNAME)
	rm -rf $(DESTDIR)

clean:
	make -C source clean
	make -C ../../../tw-c-sdk/build clean
	rm -f $(IMGDIR)/$(MODNAME).tgz
