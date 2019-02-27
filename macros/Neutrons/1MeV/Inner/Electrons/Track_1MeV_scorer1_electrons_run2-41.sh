#!/bin/bash
for i in {8201..8400};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer1_electrons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Inner/Electrons/run2 $i > /dev/null;
done
