# AudioLPF
AudioPLF is a program for cutting high frequencies in an audio signal using a FIR filter.
FIR filters (low pass & band stop) are selected for filtering because they are flexible, easily customizable.

Short description of the program:
- the program works with .wav audio files of the format PCM.
- the program accepts the path to the audio file needed for work as an argument. After executing the program, a file is created with the name test, in which the desired frequencies are cut
- cutoff frequencies and filter type are configurable in inc/audioipf.h
- the sampling frequency is not fixed depends on the sampling frequency of data in the file
- there is notebook FFTViewer.ipynb to select the desired cutoff frequency

The physics of whistling in a microphone
- high frequencies are re-reflected, which causes the amplitude of the corresponding high frequencies to increase the signal
