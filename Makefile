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
<<<<<<< HEAD
	@- $(RM) ./build/source
	@- $(RM) ./build/test
	@- $(RM) ./build/vendor
	@- $(RM) ./build/bdwgc
=======
	@- $(RM) ./build/src
	@- $(RM) ./build/test
>>>>>>> 6460549d748e8ddb3c488a29ec31c2f804bb884a
	@- $(RM) ./build/CMake*
	@- $(RM) ./build/cmake.*
	@- $(RM) ./build/*.cmake
	@- $(RM) ./build/*.txt
<<<<<<< HEAD
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
=======
	@- $(RM) ./docs/*.html
	@- $(RM) ./docs/*.css
	@- $(RM) ./docs/*.png
	@- $(RM) ./docs/*.jpg
	@- $(RM) ./docs/*.gif
	@- $(RM) ./docs/*.tiff
	@- $(RM) ./docs/*.php
	@- $(RM) ./docs/search
	@- $(RM) ./docs/installdox
>>>>>>> 6460549d748e8ddb3c488a29ec31c2f804bb884a


ifeq ($(findstring distclean,$(MAKECMDGOALS)),)

    $(MAKECMDGOALS): ./build/Makefile
<<<<<<< HEAD
	@ $(MAKE) --silent -C build $(MAKECMDGOALS)
=======
	@ $(MAKE) -silent -C build $(MAKECMDGOALS)
>>>>>>> 6460549d748e8ddb3c488a29ec31c2f804bb884a

endif
