##############################################################
#               CMake Project Wrapper Makefile               #
##############################################################

SHELL := /bin/bash
RM    := rm -rf

all: ./build/Makefile
	@ $(MAKE) --silent -C build

./build/Makefile:
	@ (cd build >/dev/null 2>&1 && cmake ..)

distclean:
	@- (cd build >/dev/null 2>&1 && cmake .. >/dev/null 2>&1)
	@- $(MAKE) --silent -C build clean || true
	@- $(RM) ./build/Makefile
	@- $(RM) ./build/source
	@- $(RM) ./build/test
	@- $(RM) ./build/vendor
	@- $(RM) ./build/bdwgc
	@- $(RM) ./build/CMake*
	@- $(RM) ./build/cmake.*
	@- $(RM) ./build/*.cmake
	@- $(RM) ./build/*.txt
	@- $(RM) ./build/Doxyfile
	@- $(RM) ./doc/api/*.html
	@- $(RM) ./doc/api/*.css
	@- $(RM) ./doc/api/*.png
	@- $(RM) ./doc/api/*.jpg
	@- $(RM) ./doc/api/*.gif
	@- $(RM) ./doc/api/*.tiff
	@- $(RM) ./doc/api/*.php
	@- $(RM) ./doc/api/*.js
	@- $(RM) ./doc/api/search
	@- $(RM) ./doc/api/installdox


ifeq ($(findstring distclean,$(MAKECMDGOALS)),)

    $(MAKECMDGOALS): ./build/Makefile
	@ $(MAKE) --silent -C build $(MAKECMDGOALS)

endif
