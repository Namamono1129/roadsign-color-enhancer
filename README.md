# [WIP]Road sign color enhancer

# Warning
This repository is not well documented/commented yet.
It is not beyond my personal demonstration.

# Description
For road sign recognition tasks, proper preprocessing is a key.
This program works as a filter which enhances contrast between road sign(vivid-coloured objects, strictly) and other objects, supposing following visual recognition tasks.

# Usage
Give directory path for pictures to process as command line variable.
(Under construction)

# Principle(WIP)
Basically, every part of the whole algorithm depends on histogram manipulation.

First, it expands intensity histogram from [min_intensity, max_intensity] into max range [0.0, 1.0] in all of RGB channels.
(a.k.a. White Balance Collection, Same algorithm as GIMP: https://docs.gimp.org/en/gimp-layer-white-balance.html)

It is followed by steep histogram expansion in HSV colorspace.
Given percentile parameter p, in S (Saturation) channel, the range
[pixel value of the pixel at p percentile, pixel value of the pixel at (100 - p) percentile]
will be expanded into [1.0, 1.0].

Finally, all pixel values in V channel(intensity) will be maxed out, except zero-value pixels.

# Results
https://i.imgur.com/6JfXGvu.jpg

# Requirements
OpenCV2