#!/bin/bash
for i in {9201..9400};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer2_nitrogens.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Intermediate/Nitrogens/run1 $i > /dev/null;
done
