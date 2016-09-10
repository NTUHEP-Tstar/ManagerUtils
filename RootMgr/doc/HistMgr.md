# `mgr::HistMgr` Class

In analysis, you might want to declare the same histrogram with the same settings for multiple samples. This samples gives you a an interface to do so. To use this class, it is advised to inherit this class, and define the histrograms on the constructor level to ensure every instance will have the same histograms defined. There will also to ensure similar styling across the class instance. For an example for the code recommended to be used, we use the example code below:

```c++
// Declaring class
class MyHistMgr : public mgr::HistMgr {
   MyHistMgr( const std::string name ):
      HistMgr( name )
   {
      AddHist( "JetPt" , "Jet p_{T}" , "GeV/c" , 50, 0, 1000);
   };
};

// In analysis
{
   MyHistMgr sample1("sample1");
   MyHistMgr sample2("sample2");

   // Filling histogram
   for( some loop ){ sample1.Hist("JetPt").Fill( something );  }
   for( some loop ){ sample2.Hist("JetPt").Fill( something );  }

   // Styling histogram
   sample1.SetColor( kRed );
   sample2.SetColor( kBlue );

   // Plotting histogram
   sample1.Hist("JetPt").Draw();
   sample2.Hist("JetPt").Draw("SAME");
}
```

Notice because of the nature of ROOT pointers, the copy constructor and the copy assignment operator have been deleted, meaning to use this class with STL container, you could not use `vector<MyHistMgr>` but only `vector<MyHistMgr*>` and the such.


## Defining Histograms
The function for defining histograms is defined by the protected method of
```c++
   void AddHist(
      const std::string& name,
      const std::string& x_label,
      const std::string& x_unit,
      const int          bin_size,
      const double       x_min,
      const double       x_max
   );
```
Where the `name` is what could be used to access the histogram via the `Hist(name)` method. The created histogram will have a blank title and the y title of "Yield [1/binwidth(x_unit)]". By default, all statistic options have been turned off.

## Styling Histogram.
You can of-course style the histogram individually by the `Hist(name)->Set(...)` functions, you could also style all the defined histograms in a sample using the `HistMgr->Set()` functions.
