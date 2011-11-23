#!/bin/sh
#To build autotools package

aclocal
autoconf
libtoolize
automake --foreign --add-missing
