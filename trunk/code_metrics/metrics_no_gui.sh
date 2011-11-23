#!/bin/bash

rm -rf metrics_no_gui
cd ../src
exclude="tree-gen|Console|ParserBak|PhyloGUI"

cccc `(find | egrep -v $exclude) | egrep "*(\.cpp|\.h)$"` --outdir=../code_metrics/metrics_no_gui


