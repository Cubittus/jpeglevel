
# ⚠️🚧 In development and very experimental 🚧⚠️

# To do
- write the todo list
- get actions to use gcc-12+
- look at task lists
- switch to cmake / something modern?
- Consider plain C interface
- Write public API first
- Investigate variable quantization by edge/centre distance or mask

# jpeglevel

- Adjust jpeg luminosity and/or chroma levels without re-compressing and losing quality.
- Operates within YCbCr colour space by directly adjusting the JPEG DCT blocks.
- Does not need to make lossy requantisation or `YCbCr ➤ RGB ➤ YCbCr` conversion.
- Allows adjustments to brightness/contrast without affecting colour
- Allows adjustments to colour intensity
- Allows shifting Cb, Cr to ajust colour balance
- Analyses all YCbCr values to produce histograms and stats
- Calculates ranges of Y, Cb, Cr changes that remain within RGB colourspace
- Or allows changes that just push a specified number/percentage of pixels outside RGB colourspace

## Requirements

- Uses the [libjpeg-turbo](https://github.com/libjpeg-turbo/libjpeg-turbo) library C++ API [TurboJPEG](https://libjpeg-turbo.org/About/TurboJPEG)
- Written in C++ for GCC with -std=gnu++20
- Uses standard autotools
