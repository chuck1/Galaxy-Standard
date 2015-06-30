#include <iostream>

#include <gal/dll/helper_info.hpp>

//std::string gal::dll::helper_info::search_path_;

gal::dll::helper_info::helper_info():
	base_hc(0)
{

}
gal::dll::helper_info::helper_info(std::string search_path):
	base_hc(0)
{

}
gal::dll::helper_info::helper_info(std::string f, std::string c, std::type_index nti):
	file_name(f),
	class_name(c)
{
	base_name = nti.name();
	base_hc = nti.hash_code();
}
gal::dll::helper_info::helper_info(gal::dll::helper_info const & h):
	file_name(h.file_name),
	class_name(h.class_name),
	base_name(h.base_name),
	base_hc(h.base_hc)
{
}





	







