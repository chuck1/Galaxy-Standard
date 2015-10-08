
root_dir              = /home/chuck/git/nebula/external/Galaxy/components/std/test/B
src_dir               = /home/chuck/git/nebula/external/Galaxy/components/std/test/B/src
inc_dir               = /home/chuck/git/nebula/external/Galaxy/components/std/test/B/include
build_dir             = /home/chuck/git/nebula/external/Galaxy/components/std/test/B/build/dynamic
inc                   = -I/home/chuck/git/nebula/external/Galaxy/components/std/test/A/include -I/home/chuck/git/nebula/external/Galaxy/components/std/test/A/build/static/process/include -I/home/chuck/git/nebula/external/Galaxy/components/std/include -I/home/chuck/git/nebula/external/Galaxy/components/std/build/static/process/include -I/home/chuck/usr/lib/pmake/include -I/home/chuck/usr/lib/pmake/build/static/process/include -I/home/chuck/usr/lib/pmake/include -I/home/chuck/usr/lib/pmake/build/static/process/include -I/home/chuck/git/nebula/external/Galaxy/components/std/test/B/include -I/home/chuck/git/nebula/external/Galaxy/components/std/test/B/build/dynamic/process/include 
define_str            = -DGLM_FORCE_RADIANS=1 -D_DEBUG=1 -DGLM_FORCE_RADIANS=1 -D_DEBUG=1
binary                = libB.so
compiler_dir          = /home/chuck/git/pbs
master_config_dir     = /home/chuck/git/nebula
lib_long_str          = /home/chuck/git/nebula/external/Galaxy/components/std/test/A/build/static/libA.a /home/chuck/git/nebula/external/Galaxy/components/std/build/static/libgalaxy_std.a
lib_link_str_whole    = 
lib_link_str_no_whole = -l:/home/chuck/git/nebula/external/Galaxy/components/std/test/A/build/static/libA.a -l:/home/chuck/git/nebula/external/Galaxy/components/std/build/static/libgalaxy_std.a -ldl -lboost_serialization -lboost_system

lib_dir_str       = -L/home/chuck/git/nebula/external/Galaxy/components/std/test/A/build/static -L/home/chuck/git/nebula/external/Galaxy/components/std/build/static -L/home/chuck/usr/lib/pmake/build/static -L/home/chuck/usr/lib/pmake/build/static
makefile          = /home/chuck/git/nebula/external/Galaxy/components/std/test/B/build/dynamic/Makefile
project_name      = B
library_type      = dynamic

depends_dir = $(build_dir)/depends
objects_dir = $(build_dir)/objects
process_dir = $(build_dir)/process

include $(compiler_dir)/makefiles/color.mk

CFLAGS = -fPIC -g -std=c++0x -Wno-format-security -Wall -Werror -Wno-unknown-pragmas -Wno-unused-local-typedefs -rdynamic

CARGS = $(inc) $(define_str) $(CFLAGS)

MAKEDEPEND = $(CC) -c $(CARGS) -MM $< -MF $(build_dir)/depends/$*.cpp.d -MT $(build_dir)/objects/$*.cpp.o

.PHONY: all

all: $(binary)
	@bash -c "echo -e \"$(COLOR_BLUE)$(build_dir)$(COLOR_RESET)\""

$(obj): $(makefile) $(lib_long_str)

include $(compiler_dir)/makefiles/cpp_library.mk



link1 = -Wl,-whole-archive $(lib_link_str_whole) -Wl,-no-whole-archive
link2 = $(lib_link_str_no_whole)

$(binary): $(lib_long_str)

$(binary): $(obj)
	@bash -c "echo -e \"$(COLOR_BLUE)build $@$(COLOR_RESET)\""
	@$(CC) -shared $(lib_dir_str) $(link1) -Wl,-soname,$@.1 -o $@.1.0 $^ $(link2)
	@ln -sf $@.1.0 $@.1
	@ln -sf $@.1.0 $@


include $(compiler_dir)/makefiles/clean.mk
include $(compiler_dir)/makefiles/help.mk
include $(compiler_dir)/makefiles/depend.mk
include $(compiler_dir)/makefiles/doc.mk


