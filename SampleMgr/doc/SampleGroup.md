# `mgr::SampleGroup` Class
Sometimes is is handy to talk about a group of samples, samples with similar properties, treating backgrounds as a whole and the such. Here we implement a class that could help store the `SampleMgr` class mentioned above in groups. It is essentially a glorified version of the `std::vector<SampleMgr*>`. Again to allow for initialization by files, it inherits from the [`Named`](../BaseClass/doc/Named.md) class, requiring a string to be associated with it, and the copy constructor and assignement operator is delete.

## Member functions

* `Sample()` : returns a `SampleMgr` pointer to the first sample manger instance in the list, handy when there is only one sample present.
* `SampleList()` : direct access to the `std::vector<SampleMgr*>` used to store the manager instances.

## Initializing from file

Similar to the sample manager class, it is possible to initialized a group using a `json` file. This must be used along side `SampleMgr` settings files.  Begin the initializatoin with the command `mgr::SampleGroup::InitFromFile( filename )`. There are 4 supported formats for initializing a `SampleGroup` from a json file:

* Insert samples defined inside a json file.
```json
{
   "GroupName": {
      "Subset Json" : "jsonfilename.json",
      "Sample List" : [
         "sample1",
         "sample2"
      ]
   }
}
```

* Get all the samples defined in a list of json file.
```json
{
   "GroupName": {
      "File List": [
         "jsonfile1.json",
         "jsonfile2.json"
      ]
   }
}
```

* Defining a single sample group, will attempt to fill a signel sample with the same name in the given json file
```json
{
   "GroupName":{
      "Single Sample": "jsonfile.json"
   }
}
```
This is equivalent to the notation :
```json
{
   "GroupName":{
      "Subset Json" : "jsonfile.json",
      "Sample List" : ["GroupName"]
   }
}
```

* If the entry doesn't exist for the group, it will try to define a single sample defined with the same name under the `Default Json` tag in the given json file, for example, the following two snippets:
```json
{
   "Default Json" : "default.json"
}
```
```c++
mgr::SampleGroup* grp = new mgr::SampleGroup( "GroupName" );
grp->InitFromFile( "json.json" ) ; ## attempt to find "GroupName" in "default.json"
```
Will be equivalent to the json settings
```json
{
   "GroupName" : {
      "Sample Sample":"jsonfile.json"
   }
}
```

## Static member functions

The json files listed above will all have a common prefix added in front of them (defaults to `"./"` ). You can acces this string through `mgr::SampleGroup::SampleCfgPrefix()`. For setting, read the [header file](../interface/SampleGroup.hpp)
