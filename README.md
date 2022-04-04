# lz4hc

LZ4 single-block compressor.

Literally just a frontend for `LZ4_compress_HC`.  
Mainly intended for testing my [lz4dec](https://github.com/Siguza/lz4dec).

### Usage

Build with `make` and use like so:

    ./lz4hc <file >file.lz4

There are no command-line options.

### License

[2-clause BSD](https://github.com/Siguza/lz4hc/blob/master/LICENSE), same as the [lz4](https://github.com/lz4/lz4) library.
