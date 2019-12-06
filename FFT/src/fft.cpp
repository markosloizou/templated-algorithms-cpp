#include "fft.h"

#include <iostream>
#include <utility>
#include <cmath>
#include <algorithm>

template <typename T> 
typename std::enable_if<is_complex<T>::value, std::vector<T>>::type fft(std::vector<T> data)
{
    if(data.size() & (data.size() - 1)) throw std::runtime_error("Data length must be a power of 2 in fft");
    doFFT(data);
    return data;
}

template <typename T> 
typename std::enable_if<is_complex<T>::value, std::vector<T>>::type ifft(std::vector<T> data)
{
    if(data.size() & (data.size() - 1)) throw std::runtime_error("Data length must be a power of 2 in fft");
    
    for(int i = 0 ; i < data.size(); i ++)
    {
        data[i] = std::conj(data[i]);
    }
    
    //doFFT(data);
    
    for(int i = 0 ; i < data.size(); i ++)
    {
        data[i] = std::conj(data[i]) / data.size();
    }
    
    return data;
}


template <typename T> 
typename std::enable_if<is_complex<T>::value, void>::type doFFT(std::vector<T> &data)
{
    const unsigned int n = data.size();
    
    if(n <= 1) return;

    std::vector<T> odd,even;
    
    //split into even and odd
    for(auto it = data.begin(); it != data.end(); it++ )
    {
        even.push_back(*it); //start at 0
        ++it;
        odd.push_back(*it);
    }
    
    doFFT(even);
    doFFT(odd);
    
    for(unsigned int i = 0; i < n/2; i++)
    {
        T t = std::polar(1.0, -2.0 * M_PI * i /n ) * odd[i];
        data[i] = even[i]+t;
        data[i+n/2] = even[i] - t;
    }
}


/*
template<typename T> 
std::enable_if<!is_complex<T>::value, std::vector<std::complex<T>> > fft(std::vector<T> data)
{
    return doRealFFT(data, 1);
}

template<typename T> 
std::enable_if<!is_complex<T>::value, std::vector<std::complex<T>> > ifft(std::vector<T> data)
{
    return doRealFFT(data, -1);
}

template<typename T> 
std::enable_if<!is_complex<T>::value, std::vector<std::complex<T>> > doRealFFT(std::vector<T> data, int isign)
{
    //do some other magic
}
*/

template<typename T> 
void bitReversal(std::vector<T> &data)
{
    if(data.size() & (data.size() - 1)) throw std::runtime_error("Data length must be a power of 2 in fft");
    
    
    unsigned int n = data.size();
    const unsigned int NUMBER_OF_BITS = log2(n); // must be power of 2 

    for(unsigned int i = 0; i < n; i++)
    {
        unsigned int rev = 0;
        for(int j = 0; j < NUMBER_OF_BITS; j++)
        {
            if(i & (1 << j)) 
            {
                rev |= 1 << ((NUMBER_OF_BITS - 1) - j);
            }
        }
        
        if(rev < i)
        {
            std::swap(data[i], data[rev]);
        }
    }
}


template<typename T> 
std::vector<T> makePowerOf2(std::vector<T> data)
{
    T t; 
    while(data.size()&(data.size()-1))
    {
        data.push_back(t);
    }
    return data;
}

template<typename T, typename U> 
std::vector<std::pair<T,T>> FFT2PowerSpectrum(std::vector<std::complex<T>> data, U dt, unsigned int samples)
{
    int n;
    if(samples == 0) n = data.size();
    else n = samples;
    
    std::vector<std::pair<T,T>> spectrum(data.size()); 
    T fresolution = 1/(n*dt);
    
    for(int i = 0; i < data.size(); i++)
    {
        T freq = i * fresolution;
        T mag = abs(data[i]);
        spectrum[i] = {freq, mag};
    }
    
    return spectrum;
}


template<typename T> 
std::vector<std::pair<T,T>> shiftSpectrumFrequencies(std::vector<std::pair<T,T>> spectrum)
{
    const int n = spectrum.size();
    T df = spectrum[1].first;
    
    for(int i = n/2; i < n; i++)
    {
        spectrum[i].first = (i - n)* df;
    }
    //sort based on freq
    sort(spectrum.begin(), spectrum.end(), [] (const auto & lhs, const auto &rhs) { return lhs.first < rhs.first; });
    //sort(spectrum.begin(), spectrum.end());
    return spectrum;
}
