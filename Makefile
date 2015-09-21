# 
# Copyright (c) Jonathan Howard
# MIT License
# 

UNAME := $(shell uname)
ifeq ($(UNAME),$(filter $(UNAME),Linux Darwin FreeBSD GNU/kFreeBSD))
ifeq ($(UNAME),$(filter $(UNAME),Darwin))
OS=darwin
else
ifeq ($(UNAME),$(filter $(UNAME),FreeBSD GNU/kFreeBSD))
OS=bsd
else
OS=linux
endif
endif
else
OS=windows
endif

GENIE=ext/bx/tools/bin/$(OS)/genie

osx-build:
	$(GENIE) --file=genie/genie.lua --compiler=osx gmake
osx-debug:
	make -R -C build/projects/osx config=debug64
osx-development:
	make -R -C build/projects/osx config=development64
osx-release:
	make -R -C build/projects/osx config=release64
osx: osx-debug osx-development osx-release

windows-build:
	$(GENIE) --file=genie/genie.lua vs2013
windows-debug:
	devenv build/projects/windows/senior.sln /Build "debug|x64"
windows-development:
	devenv build/projects/windows/senior.sln /Build "development|x64"
windows-release:
	devenv build/projects/windows/senior.sln /Build "release|x64"

.PHONY: clean
clean:
	@echo Cleaning...
	-@rm -rf build
