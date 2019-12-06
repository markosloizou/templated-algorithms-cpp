# Topological Sort

Source code can be found in the src directory. There is a non templated version of topological sort working with ints and a templated version. 

To use the templated topological sort it is necessary to copy the files "templated_topological_sort.cpp" *and*  "templated_topological_sort.h" to your project and include both in the source file using the algorithm. 

The code inserts the data into an unordered map, for ***custom classess*** the class must  implement a comparison function   for equality  (overlading the == operator) and also provide a hash function (perhaps by specializeing the std::hash template).
