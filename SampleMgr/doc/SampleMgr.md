# `mgr::SampleMgr` Class

Typically in analysis, we are interested in a "sample" which should consist of a list of events with some common parameters shared among the events, such as the [cross section](https://en.wikipedia.org/wiki/Cross_section_(physics)), [selection efficiency](https://root.cern.ch/8-efficiency-calculation) of the samples, and the such. The could also be variables that are common to all the "samples" such as the luminosity of the analysis. This class is powered by the [`fwlite::ChainEvent`](https://cmssdt.cern.ch/SDT/doxygen/CMSSW_8_0_16/doc/html/dd/db4/classfwlite_1_1ChainEvent.html) to allow the loading of multiple [`EDM` files](https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookAnalysisOverviewIntroduction) (with similar formats of-course) while the variables are powered by the [`Parameter`](../Maths/) class.

A typical use of a `SampleMgr` in a stand alone C++ analysis code might look something like this:

```C++
mgr::SampleMgr mymgr( "MyMgr" );

mymgr.SetCrossSection( ... );
mymgr.FileList().push_back( "file.root");

for( mymgr.Event().toBegin() ; mymgr.Event().atEnd() ; ++mymgr.Event() ){
   // do event loop
}
```

To add support for the class to loading settings from files, this class inherites from [`Named`](../BaseClass/interface/Named.hpp) which requires the class to be initialized with a string (though not unique). To avoid ambiguity of the names, the copy constructor and assignment has be deleted, meaning that you could not use it directly with the `stl` containers such as `std::vector<SampleMgr>`, but only through pointers `std::vector<SampleMgr*>`.

## Supported static variables

* `double TotalLuminosity`: defaults to `0`
* `std::string FilePrefix`: a common string to put in-front of the file list. Default to a blank string.

For the settings/access functions, see the [header file](../interface/SampleMgr.hpp) directly

## Supported members functions

* `Parameter CrossSection`
* `Parameter KFactor`
* `Parameter SelectionEfficiency`
* `Parameter FileList`: Stores the actual strings inserted by the user. Notice that the user string will not be directly used for the events constructor! It is passed to a [Globbing(wildcard)](https://en.wikipedia.org/wiki/Glob_(programming)) [engine](http://man7.org/linux/man-pages/man7/glob.7.html). This means that:
   * Non-existing files will not be used for the Event construction WITHOUT any warning messages.
   * SHELL style globbing notations are supported! So `file_*.root`, will make the class try to load all of the files in this format.
   * The `FilePrefix` static variable is prefixed to **every** user entry.
   * The results of the globbing could be accessed by the `GlobbedFileList()` method, which returns a `std::vector<std::string>`
* `fwlite::ChainEvent Event`: a `ChainEvent` created using the globbed file list. This function should only be called after all the files have been included.

## Extended members functions  

* `std::vector<std::string> GlobbedFileList`: Returns the results of globbing. Handy for debugging and accessing `Run` and `LumiSection` information rather than just `Event` level data)
* `boost IsRealData`: check if the first event is flagged as a real data file ( always returns `false` if event-list is empty )
* EventsInFile (`size_t`): returns the size of the event created
* ExpectedYield(`Parameter`): returns the arithmatic results of `TotalLumimosity` times `CrossSection` times `KFactor` times `SelectionEfficiency`. Since it is known that the default arithmatics of the `Parameter` class is [problematic](../../Maths/doc/Parameter), this should only be used for quick checking and not for rigorus calculations.

## Loading from files
In the case you wish to initialized a `SampleMgr` class from a external file and not by raw `C++` control flow, could do so for both static variables and instance variables. For static variables, you will need to prepare a minimal json file that looks like:

```json
{
   "Total Luminosity" : 0.0,
   "File Prefix" : "some string"
}
```
This files will automatically be detected, and will be used to change the static variables. In the case that the required field is not found in the file, the values will be left unchanged and not excpetion will be thrown. The function could be called like: `mgr::SampleMgr::InitStaticFromFile( filename )`, where the filename is a string. Since this is powered by a [`mgr::ConfigReader`](../../BaseClass/doc/ConfigReader.md) class, one could also pass an instance of a `mgr::ConfigReader` to for initialization.

For member variables, you will need to prepare a file that looks like:

```json
{
   "MySample":{
      "Cross section": [ 0.0 , 0.0, 0.0 ],
      "KFactor" : [1.0],
      "Selection Efficiency": [ 0.0, 0.0, 0.0 ],
      "EDM Files": [
         "filename_1.root",
         "filenamt_2.root"
      ]
   }
}
```
The `MySample` is required to match the string associated with the `SampleMgr` declaration. This time, only the `Selection Efficiency` field is allowed to be omitted ( decision made after considering that selection efficiencies could be stored in the EDM files themselves). Any other missing fields will result in exceptions being raised. The `filename` themselves will be placed in the managers `FileList` without any additional error prevention, so the user is responsible for checking that the syntax inside is correct. You could call this by the function `mgr::SampleMgr::InitFromFile( filename )`, where `filename` is a string representing the path.
