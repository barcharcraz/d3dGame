d3dGame
=======

This project is a 2D and eventually 3D engine written using Direct2D/Direct3D.

Also included is a basic windowing library written with the windows API and a 
project that outlines the intended architecture of the engine

Composition is used to encourage code reuse among various game components and 
interfaces are used wherever possible to facilitate testing (like dependency 
injection but without a framework beyond constructors and preprocessor things).

As of now this is a side project as I am spending most of my time on RTSGame 
made in unity


Build considerations
====================

The project requiers Boost::signals2 (recomended to build with the entire boost 
library) and eigen. the root directories for each library should be in your 
include path for example <boost/signals2.hpp> and <Eigen/core> not 
<signals2.hpp> and <core>. In addition you must build with a complier that has 
reasonable support for c++11, in g++ the -std=c++11 or -std=gnu++11 are both 
sufficent.

Note that some libraries will not build on all platforms or with all compilers. For
example the Direct3D, Direct2D, and Windows libraries are all specific to windows while
the XLib library is specific to systems with X windows.