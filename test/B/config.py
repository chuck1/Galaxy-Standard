import pbs.classes.Dynamic

e = pbs.classes.Dynamic.Dynamic("B", self)

e.require("A")
e.require("galaxy_std")
e.require("boost_serialization")
e.require("boost_system")

e.make()



