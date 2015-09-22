
root_dir   = /home/chuck/git/nebula/external/Galaxy/components/std/test/A
src_dir    = /home/chuck/git/nebula/external/Galaxy/components/std/test/A/src
inc_dir    = /home/chuck/git/nebula/external/Galaxy/components/std/test/A/include
build_dir  = /home/chuck/git/nebula/external/Galaxy/components/std/test/A/build/static
inc        = -I/home/chuck/git/nebula/external/Galaxy/components/std/include -I/home/chuck/git/nebula/external/Galaxy/components/std/build/static/process/include -I/home/chuck/usr/lib/pmake/include -I/home/chuck/usr/lib/pmake/build/static/process/include -I/home/chuck/usr/lib/pmake/include -I/home/chuck/usr/lib/pmake/build/static/process/include -I/home/chuck/git/nebula/external/Galaxy/components/std/test/A/include -I/home/chuck/git/nebula/external/Galaxy/components/std/test/A/build/static/process/include 
define_str = -DGLM_FORCE_RADIANS=1 -D_DEBUG=1 -DGLM_FORCE_RADIANS=1 -D_DEBUG=1
binary     = /home/chuck/git/nebula/external/Galaxy/components/std/test/A/build/static/libA.a
compiler_dir = /home/chuck/git/pbs
master_config_dir = /home/chuck/git/nebula
makefile          = /home/chuck/git/nebula/external/Galaxy/components/std/test/A/build/static/Makefile
project_name      = A
library_type      = static

depends_dir = $(build_dir)/depends
objects_dir = $(build_dir)/objects
process_dir = $(build_dir)/process

include $(compiler_dir)/makefiles/color.mk

CFLAGS  = -g -std=c++0x -rdynamic -fPIC
CFLAGS += -Wno-format-security
CFLAGS += -Wall -Werror
CFLAGS += -Wno-unused-local-typedefs -Wno-unknown-pragmas

CARGS = $(CFLAGS) $(inc) $(define_str)

.PHONY: all

all: $(binary)
	@bash -c "echo -e \"$(COLOR_BLUE)$(build_dir)$(COLOR_RESET)\""
	@echo CC=$(CC)

MAKEDEPEND = $(CC) -c $(CARGS) -MM $< -MF $(depends_dir)/$*.cpp.d -MT $(objects_dir)/$*.cpp.o


include $(compiler_dir)/makefiles/cpp_library.mk

precompiler: $(pre)

$(binary): $(makefile)

$(binary): $(obj)
	@bash -c "echo -e \"$(COLOR_BLUE)build $@$(COLOR_RESET)\""
	@mkdir -p $(dir $@)
	@ar rcs $@ $(filter %.cpp.o, $^)


include $(compiler_dir)/makefiles/clean.mk
include $(compiler_dir)/makefiles/help.mk
include $(compiler_dir)/makefiles/depend.mk
include $(compiler_dir)/makefiles/doc.mk



