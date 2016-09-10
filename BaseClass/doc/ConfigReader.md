# `mgr::ConfigReader` class

A wrapper class powered by the boost [propertry tree](http://www.boost.org/doc/libs/1_61_0/doc/html/property_tree.html) to allow for a intuitive interface to initialized a class by a configuration file in [json](http://www.json.org/) format.

A class typically contain static variables, and individual instance variable that we wish to initialize when beginning our program. A structure for a list of classes we want to could be written in a [json](http://www.json.org) file as something like this:

```json
{
   "Static Var Label 1" : "Static value 1",
   "Static Var Label 2" : 2.00000000000000,
   "Static Var Label 3" : "Static value 3",
   "Static List Var":[ "static1" , "static2" ],

   "Instance Label 1" : {
      "Instance Var Label 1" : "Instance value 1-1",
      "Instance Var Label 2" : 1.200000000000000000,
      "Instance List Var Label 1" : [ 1.0, 2.0, 3.0, 4.0 ],
      "Instance List Var Label 2" : [ "string1", "string2", "string3" ]
   },

   "Instance Label 2" : {
      "Instance Var Label 1" : "Instance value 1-2",
      "Instance Var Label 2" : 2.2000000000000000000,
      "Instance List Var Label 1" : [ 1.0, 2.0, 3.0, 4.0 ],
      "Instance List Var Label 2" : [ "string1", "string2", "string3" ]
   }

}
```

We might wish that we could load the file in to our reader class, and use the class to initialize the various label like:

```C++
ConfigReader myreader( "myjson.json" );
MyClass inst1, inst2;

MyClass::InitStatic( myreader );
inst1.InitFromFile( "Instance Label 1" , myreader );
inst2.InitFromFile( "Instance Label 2" , myreader );
```

In the `MyClass` implementation of the method `InitStatic` and `InitFromFile`, one could then access the variables stored in the reader class to initialized the class.
This class is aimed to do just that with the power of boost property tree, with some premade helper function to help access the data stored in the property tree. The reader could also be initialized from a property tree to potentially allow for class nesting, though as of writing there is no help function to help with nested classes, only allowed acces to the direct property tree created by reading the file.

## Member functions

The static and the instance variables could be accessed by similar function, the only difference is that one needs add an extra string for the instance identification. An example of the similarity between accessing static and instance variable are the two functions:

```c++
double GetStaticDouble( const string& tag ) const ;
double GetDouble( const string& inst_tag, const string tag ) const ;
```

The first is for accessing the double value stored as a static instance in the property tree, while the second is to get the double value stored as a class instance. For the purpose of analysis, some casting is already written to help access the variables more easily when initializing a class. There is the list of types the have already been implemented.

* `double`
* `std::string`
* `std::vector<double>`
* `std::vector<std::string>`
* [`Parameter`](../Maths/doc/Parameter.md). This should be in the format of:
  * `[central]`: Initializes a parameter with 0 zero
  * `[central , error]`: returns a parameter with symmetric errors
  * `[central , error up, error down]`: return a parameter with asymmetric error

  Note that in the case for doubles are placed in the array, the entries beyond the third ones will be truncated out.

There are additional helper function to help with options input tags without the need for user exception handling: `HasStaticTag`/`HasTag`.

In the case that on might wish to get all the class instances defined in the file. There is also the method `std::vector<std::string> GetInstanceList()`, where it returns all the first level tag stored in the property tree. Since the `ConfigReader` makes no assumptions about the structure of the class, static tags will be missidentified by this function to be an instance tag! The user is recommended to separate files for static variable in this case.

## Json file commenting
There is not official way to add comments in json files. We opt for the solution for writting comments in json files as something like this:

```json
{
   "__Comment__" : """==============================
   Strings between triple quotation could be arbitrarily
   long and include break line
   ================================================="""
}
```

So any tag beginning with the special character `_` will be ignored by the parser. Please keep this in mind when choosing you tag names.
