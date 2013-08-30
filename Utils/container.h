//! \brief this header file contains
//! templates and typedefs for containers
//! in some cases a container may have typedefs
//! for selecting between multiple drop-in
//! containers (eg. boost::flat_map instead of std::map
#include "config.h"
#ifdef BOOST_USE_FLATMAPS
#include <boost/container/flat_map.hpp>
#else
#include <map>
#include <set>
#endif



#ifndef UTILS_CONTAINER_H
#define UTILS_CONTAINER_H

namespace utils {


}
#endif
