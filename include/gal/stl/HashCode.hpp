#ifndef GAL_STL_HASH_CODE_HPP
#define GAL_STL_HASH_CODE_HPP

#include <map>
#include <exception>

//#include <boost/function.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

//#include <Nebula/App/BaseFactory.hh>

//#include <gal/managed_object.hpp>
//#include <gal/stl/factory.hpp>
#include <gal/typedef.hpp>
#include <gal/verb/Verbosity.hpp>
//#include <gal/dll/helper.hpp>

namespace ba = boost::archive;

namespace gal { namespace stl {
	class HashCode:
		public gal::verb::Verbosity<HashCode>
	{
		public:
			HashCode(): hc(0) {}
			HashCode(gal::hash_type nhc): hc(nhc) {}

			template<class Archive> void	load(Archive & ar, unsigned int const & version)
			{
				/// @TODO fix this
				/*
				   if(version == 0)
				   {
				   std::string name;

				   ar >> boost::serialization::make_nvp("name", name);

				   hc = gal::managed_object::to_hash_code(name);
				   }
				   else if(version == 1)
				   {
				   ar >> hc;
				   }
				   else throw InvalidVersion(version);
				   */
			}
			template<class Archive> void	save(Archive & ar, unsigned int const & version) const
			{
				/// @TODO fix this
				/*
				   if(version == 0)
				   {
				   std::string name = gal::managed_object::to_string(hc);

				   ar << boost::serialization::make_nvp("name", name);
				   }
				   else if(version == 1)
				   {
				   ar << hc;
				   }
				   else throw InvalidVersion(version);
				   */
			}
			void		load(
					ba::xml_iarchive & ar,
					unsigned int const & version)
			{
				std::string name;

				//ar >> boost::serialization::make_nvp("name", name);

				//hc = gal::managed_object::to_hash_code(name);
			}
			void		save(
					ba::xml_oarchive & ar,
					unsigned int const & version) const
			{
				//std::string name = gal::managed_object::to_string(hc);

				//ar << boost::serialization::make_nvp("name", name);
			}
			void		load(
					ba::binary_iarchive & ar,
					unsigned int const & version)
			{
				ar >> hc;
			}
			void		save(
					ba::binary_oarchive & ar,
					unsigned int const & version) const
			{
				ar << hc;
			}

			BOOST_SERIALIZATION_SPLIT_MEMBER();

			gal::hash_type	hc;
	};
}}

#endif



