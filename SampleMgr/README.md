# `SampleMgr` Package

Handy classes for bundling up `EDM` files for the high level control flow used in analysis. This files are used only for `EDM` file management, if you are interested in `root` object management, see the classes defined int the [`RootMgr`](../RootMgr/) package.


## [`mgr::SampleMgr`](./doc/SampleMgr.md) class
Pack a list of `EDM` files together to easy event looping as well as associating handy physical variable of a sample, such as cross section, selection efficiency and others.


## [`mgr::SampleGroup`](./doc/SampleGroup.md) Class
Packing a list of [`SampleMgr`](./doc/SampleMgr.md) classes together. Note that this class contains nothing but a vector of SampleMgrs, so it is advised to add your own desired variables by inheriting this class. Handy for analysis level object handling (ex, I want a "background" pdf,  I want a "signal" data-set) that requires the jont properties of multiple samples. 
