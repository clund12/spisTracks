#!/bin/bash
for i in {5201..5400};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer3_deuterons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Outer/Deuterons/run3 $i > /dev/null;
done
