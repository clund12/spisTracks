#!/bin/bash
for i in {2201..2400};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer2_carbons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Intermediate/Carbons/run2 $i > /dev/null;
done
