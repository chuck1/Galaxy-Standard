
l = pbs.classes.Static.Static("galaxy_std", self)

l.libs.append("dl")

l.tests.append("galaxy_std_test_registry");
l.tests.append("galaxy_std_test_map");
l.tests.append("galaxy_std_test_serial");
l.tests.append("galaxy_std_test_weak_ptr");
l.tests.append("galaxy_std_test_tuple");

l.make()

self.include("test")


