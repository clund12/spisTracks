#!/bin/bash
for i in {4201..4400};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer3_electrons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Outer/Electrons/run2 $i > /dev/null;
done
