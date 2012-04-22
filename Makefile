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
	@- $(RM) ./build/CMake*
	@- $(RM) ./build/cmake.*
	@- $(RM) ./build/*.cmake
	@- $(RM) ./build/*.txt
	@- $(RM) ./build/Doxyfile
	@- $(RM) ./doc/*.html
	@- $(RM) ./doc/*.css
	@- $(RM) ./doc/*.png
	@- $(RM) ./doc/*.jpg
	@- $(RM) ./doc/*.gif
	@- $(RM) ./doc/*.tiff
	@- $(RM) ./doc/*.php
	@- $(RM) ./doc/*.js
	@- $(RM) ./doc/search
	@- $(RM) ./doc/installdox


ifeq ($(findstring distclean,$(MAKECMDGOALS)),)

    $(MAKECMDGOALS): ./build/Makefile
	@ $(MAKE) --silent -C build $(MAKECMDGOALS)

endif
