#!/bin/bash
for i in {6201..6400};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer3_deuterons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Outer/Deuterons/run2 $i > /dev/null;
done
