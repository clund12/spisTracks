#!/bin/bash
for i in {5201..5400};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer1_electrons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Inner/Electrons/run1 $i > /dev/null;
done
