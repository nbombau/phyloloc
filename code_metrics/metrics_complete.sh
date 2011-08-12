#!/bin/bash

rm -rf metrics_complete
cd ../src
exclude="tree-gen|Console|ParserBak"

cccc `(find | egrep -v $exclude) | egrep "*(\.cpp|\.h)$"` --outdir=../code_metrics/metrics_complete


