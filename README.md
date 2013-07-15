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
include path for example "<boost/signals2.hpp>" and "<Eigen/core>" not 
"<signals2.hpp>" and "<core>". In addition you must build with a complier that has 
reasonable support for c++11, in g++ the -std=c++11 or -std=gnu++11 are both 
sufficent. Note that if you would like to build with MSVC you must use the MOST RECENT
version of the compiler. This means Visual C++ 2013 Preview at the moment. 

Note that some libraries will not build on all platforms or with all compilers. For
example the Direct3D, Direct2D, and Windows libraries are all specific to windows while
the XLib library is specific to systems with X windows. LibCommon is totally platform
independent (it needs a more or less c++11 complient compiler however). The notion is that
you can write components on any platform (and hopefully in any language) and have them just work.

Library Design
==============

At the core of the engine is Event.hpp and the Event class. Events are processed most unlike
most other event systems you may have used. Furthermore the event system is totally "open" meaning
that there is no need to "regester" and event type or to derive from a handler class. All you need to do
is call recieve.connect<EventType*>(callback) and callback will be called when you get an event
of EventType. Similarly if you would like to send an event you can say EventType msg; send(&msg);
and message will be sent.
Notice that there is no need to specify the target of a message, this is because there /is/ no target.
By default when you send a message from a component the entity that contains that component takes that
message and sends it to each of the components it contains. The means that you can actually handle a
message that you sent.
