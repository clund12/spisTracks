#!/bin/bash
for i in {trackRange};
do /home/chris/geant4/work/spisTracks/build/spisTracks {macroName} {outputName} $i > /dev/null;
done
