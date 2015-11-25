# Introduction #

For installing phyloloc in Mac OSX, please follow the next steps.

# Details #

  1. Install qt
    1. Download and install the lastest version of Qt Libraries for Mac from [here](http://qt.nokia.com/downloads).
  1. Install mili library
    1. svn checkout http://mili.googlecode.com/svn/trunk/ mili-read-only
    1. The previous command downloads mili in the folder mili-read-only.
      1. cd mili-read-only
      1. sudo ./install.sh
  1. Download and compile phyloloc
    1. svn checkout http://phyloloc.googlecode.com/svn/trunk/ phyloloc-read-only
    1. The previous command generates the folder phyloloc-read-only.
      1. cd phyloloc-read-only/src
      1. qmake -spec macx-g++ phyloloc.pro
      1. make
  1. Run phyloloc
    1. A phyloloc.app application will be generated in the source (phyloloc-read-only/src) folder. Double click on it to execute phyloloc.