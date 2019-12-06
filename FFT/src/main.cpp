#include <iostream>
#include <vector> 
#include <string> 
#include <cmath>
#include <complex>
#include <fstream> 

#include "fft.h"
#include "fft.cpp"

using namespace std;

template<typename T> 
void printIndexedVector(vector<T> v);

template<typename T> 
void printComplexVector(vector<complex<T>> v);

template<typename T>
void saveComplexCSV(vector<complex<T>> v);

template<typename T> 
void saveSpectrumCSV(vector<pair<T,T>> s);

template<typename T> 
void printVector(vector<T> v)
{
    for(T x : v)
    {
        cout << x << " "; 
    }
    cout << endl;
}



int main()
{
    vector<string> test1 = {"000", "001", "010", "011", "100", "101", "110", "111"};    
    
    printVector(test1);
    bitReversal(test1);
    printVector(test1);
    
    const int samples = 128;
    vector<complex<double>> test2;
    const double dt = 0.01; 
    const double freq = 4.0;
    
    for(int i = 0; i < samples; i++)
    {
        test2.push_back(sin(2.0* M_PI * freq * i* dt));
    }
    
    printIndexedVector(test2);
    vector<complex<double>> output = fft(test2);
    printIndexedVector(output);
    saveComplexCSV(output);
    
    auto spectrum = FFT2PowerSpectrum(output, dt);
    auto centered = shiftSpectrumFrequencies(spectrum);
    
    saveSpectrumCSV(centered);
    
    return 0;
}

template<typename T> 
void printIndexedVector(vector<T> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        cout << i << ", " << v[i] << endl;
    }
}


template<typename T> 
void printComplexVector(vector<complex<T>> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

template<typename T>
void saveComplexCSV(vector<complex<T>> v)
{
    ofstream o;
    o.open("./output/out.csv", ios::out);
    
    for(auto x : v)
    {
        o << x.real() << ", " << x.imag() << ", " << abs(x)<< endl;
    }
    o.close();
}

template <typename T> 
void saveSpectrumCSV(vector<pair<T,T>> s)
{
    ofstream o;
    o.open("./output/spec.csv", ios::out);
    
    for(auto x : s)
    {
        o << x.first << ", " << x.second << endl;
    }
    o.close();
}
