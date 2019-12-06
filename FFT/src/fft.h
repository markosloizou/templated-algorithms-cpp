#ifndef FFT_H
#define FFT_H

#include <vector> 
#include <complex>
#include <type_traits> 

template<class T> struct is_complex : std::false_type {};
template<class T> struct is_complex<std::complex<T>> : std::true_type {};


template <typename T> 
typename std::enable_if<is_complex<T>::value, std::vector<T>>::type fft(std::vector<T> data);

template <typename T> 
typename std::enable_if<is_complex<T>::value, std::vector<T>>::type ifft(std::vector<T> data);


template <typename T> 
typename std::enable_if<is_complex<T>::value, void>::type doFFT(std::vector<T> &data);

/*
template<typename T> 
std::enable_if<!is_complex<T>::value, std::vector<std::complex<T>> > fft(std::vector<T> data);

template<typename T> 
std::enable_if<!is_complex<T>::value, std::vector<std::complex<T>> > ifft(std::vector<T> data);

template<typename T> 
std::enable_if<!is_complex<T>::value, std::vector<std::complex<T>> > doRealFFT(std::vector<T> data, int isign);
*/
template<typename T> 
void bitReversal(std::vector<T> &data);

template<typename T> 
std::vector<T> makePowerOf2(std::vector<T> data);

template<typename T, typename U> 
std::vector<std::pair<T,T>> FFT2PowerSpectrum(std::vector<std::complex<T>> data, U sampling_period, unsigned int samples = 0);

template<typename T> 
std::vector<std::pair<T,T>> shiftSpectrumFrequencies(std::vector<std::pair<T,T>> spectrum);

#endif
