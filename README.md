# [WIP]Road sign color enhancer

# Warning
This repository is not well documented/commented yet.
It is not beyond my personal demonstration.

# Description
For road sign recognition tasks, proper preprocessing is a key.
This program works as a filter which enhances contrast between road sign(vivid-coloured objects, strictly) and other objects, supposing following visual recognition tasks.

# Usage
(Under construction)

# Principle(WIP)
Basically, every part of the whole algorithm depends on histogram manipulation.

First, it expands intensity histogram from certain range into max range [0.0, 1.0] in all of RGB channels.
The original range is calculated as below:

> [pixel value of the pixel at (i_m * i_m / 1200.0) percentile, pixel value of the pixel at (i_m * i_m / 1200.0) percentile]

i_m denotes mean intensity value of all pixels in all (RGB) channels.

It is followed by steep histogram expansion in HSV colorspace.
Given percentile parameter p, in S (Saturation) channel, the range

>[pixel value of the pixel at p percentile, pixel value of the pixel at (100 - p) percentile]

will be expanded into [1.0, 1.0].

Finally, all pixel values in V channel(intensity) will be maxed out, except zero-value pixels.

# Results
![Result](https://i.imgur.com/6JfXGvu.jpg "result")


# Requirements
OpenCV2