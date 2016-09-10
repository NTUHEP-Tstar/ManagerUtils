# `BaseClass` package

A collection of general purpose utility classes written in STL C++ or powered by the boost library. Detailed documentations could be found in their dedicated documentation pages

## [`mgr::ConfigReader`](./doc/ConfigReader.md) class
A class wrapper for a [boost propertry tree](http://www.boost.org/doc/libs/1_61_0/doc/html/property_tree.html), creating a easy interface for classes to have setting loaded from a defined json file.

## [`mgr::Named`](./doc/Named.md) class
A base class for a constant name to be associated for an object. Not using the ROOT [`TNamed`](https://root.cern.ch/doc/master/classTNamed.html) class for better C++ compatibility with `std::string` objects, and remove from `ROOT` memory caching.
