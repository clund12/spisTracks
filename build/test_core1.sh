#!/bin/bash
for i in {6..10};
do /home/chris/geant4/work/spisTracks/build/spisTracks test.mac /home/chris/geant4/work/Data/Tracks/Neutrons/Testing $i;
done
