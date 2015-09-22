root_dir     = /home/chuck/git/nebula/external/Galaxy/components/std/test/serial
src_dir      = /home/chuck/git/nebula/external/Galaxy/components/std/test/serial/src
inc_dir      = /home/chuck/git/nebula/external/Galaxy/components/std/test/serial/include
build_dir    = /home/chuck/git/nebula/external/Galaxy/components/std/test/serial/build
inc          = -I/home/chuck/git/nebula/external/Galaxy/components/std/test/A/include -I/home/chuck/git/nebula/external/Galaxy/components/std/test/A/build/static/process/include -I/home/chuck/git/nebula/external/Galaxy/components/std/test/B/include -I/home/chuck/git/nebula/external/Galaxy/components/std/test/B/build/dynamic/process/include -I/home/chuck/git/nebula/external/Galaxy/components/std/include -I/home/chuck/git/nebula/external/Galaxy/components/std/build/static/process/include -I/home/chuck/usr/lib/pmake/include -I/home/chuck/usr/lib/pmake/build/static/process/include -I/home/chuck/usr/lib/pmake/include -I/home/chuck/usr/lib/pmake/build/static/process/include -I$(inc_dir)
define_str   = -DGLM_FORCE_RADIANS=1 -D_DEBUG=1 -DGLM_FORCE_RADIANS=1 -D_DEBUG=1
binary       = /home/chuck/git/nebula/build/galaxy_std_test_serial
lib_long_str = /home/chuck/git/nebula/external/Galaxy/components/std/test/A/build/static/libA.a libB.so /home/chuck/git/nebula/external/Galaxy/components/std/build/static/libgalaxy_std.a
lib_link_str = -l:/home/chuck/git/nebula/external/Galaxy/components/std/test/A/build/static/libA.a -l:libB.so -l:/home/chuck/git/nebula/external/Galaxy/components/std/build/static/libgalaxy_std.a -ldl -lboost_serialization -lboost_system
lib_dir_str  = -L/home/chuck/git/nebula/external/Galaxy/components/std/test/A/build/static -Wl,-rpath,/home/chuck/git/nebula/external/Galaxy/components/std/test/B/build/dynamic -L/home/chuck/git/nebula/external/Galaxy/components/std/build/static -L/home/chuck/usr/lib/pmake/build/static -L/home/chuck/usr/lib/pmake/build/static
compiler_dir = /home/chuck/git/pbs

depends_dir = $(build_dir)/depends
objects_dir = $(build_dir)/objects
process_dir = $(build_dir)/process

include $(compiler_dir)/makefiles/color.mk


#src    = $(shell find $(src_dir) -name '*.cpp')
#src_in = $(shell find $(src_dir) -name '*.cpp.in')

#inc_in = $(shell find $(inc_dir) -name '*.hpp.in')

#inc_processed = $(patsubst $(src_dir)/%.cpp.in, $(build_dir)/processed/include/%.hpp, $(inc_in))

#src_processed = $(patsubst $(src_dir)/%.cpp.in, $(build_dir)/processed/src/%.cpp,     $(src_in))
#obj_processed = $(patsubst $(src_dir)/%.cpp.in, $(build_dir)/objects/%.cpp.o, $(src_in))
#obj           = $(patsubst $(src_dir)/%.cpp,    $(build_dir)/objects/%.cpp.o, $(src))


CC = g++
CFLAGS = -g -std=c++0x -Wno-format-security -rdynamic

CARGS = $(define_str) $(CFLAGS) $(inc)

.PHONY: all

all: $(binary)
	@bash -c "echo -e \"$(COLOR_BLUE)$(build_dir)$(COLOR_RESET)\""


MAKEDEPEND = $(CC) -c $(CARGS) -MM $< -MF $(build_dir)/depends/$*.cpp.d -MT $(build_dir)/objects/$*.cpp.o

include $(compiler_dir)/makefiles/cpp_library.mk

$(binary): $(lib_long_str)

$(binary): $(obj)
	@bash -c "echo -e \"$(COLOR_BLUE)build $@$(COLOR_RESET)\""
	@$(CC) $(CARGS) $^ -o $@ $(lib_dir_str) $(lib_link_str) $(lib_link_str) $(lib_link_str) -lpthread


include $(compiler_dir)/makefiles/clean.mk
include $(compiler_dir)/makefiles/help.mk
include $(compiler_dir)/makefiles/depend.mk
include $(compiler_dir)/makefiles/doc.mk

