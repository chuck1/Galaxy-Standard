import pbs.classes.Executable

e = pbs.classes.Executable.Executable("galaxy_std_test_factory_map", self)

e.require("galaxy_std")
e.require("boost_serialization")
e.require("boost_system")

e.make()



