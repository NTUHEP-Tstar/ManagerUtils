# `mgr::Named` Class
With the case of ROOT, it is common we need to associated a unique string to a declared object. So when we write classes to manage root objects, our classes themselves might benifit from having a name to help with name management. Here, we will be using a custom `Named` class rather than a standard ROOT [`TNamed`](https://root.cern.ch/doc/master/classTNamed.html) because:

* I want to use C++ flavoured string for name management most of the time, since the [STL](http://www.cplusplus.com/reference/string/string/) and [boost string algorithm](http://www.boost.org/doc/libs/1_61_0/doc/html/string_algo.html) has a much more complete set of function to use there.

* I don't want to meddle with the `ROOT` memory management quirks when writting my own classes. It might unsure uniqueness of the string I an using, but I am still worried about it's robustness.

## Member functions

Each class will have string associated to them during declaration, and it could not be change at all. So while there is a `Name()` function similar to the `GetName()` function for `TNamed()` classes, there will be no corresponding `SetName()` function for our classes.

There is also a similar flexible string called `LatexName()` that could be called changed at anytime during the objects life time. There is a `RootName()` that attempt to translate the `LatexName()` into a [`ROOT` flavoured latex](https://root.cern.ch/doc/master/classTLatex.html) string. But the translation is unreliable. It is under consideration that these two names be split into to different variables.
