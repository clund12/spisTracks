#!/bin/bash
for i in {8401..8600};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer2_carbons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Intermediate/Carbons/run1 $i > /dev/null;
done
