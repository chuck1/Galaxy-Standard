
e = Executable("galaxy_std_test_registry")

e.require("galaxy_std")
e.require("boost_serialization")
e.require("boost_system")

e.make()



