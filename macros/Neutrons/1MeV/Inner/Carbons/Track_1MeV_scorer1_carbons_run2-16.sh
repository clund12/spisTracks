#!/bin/bash
for i in {3201..3400};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer1_carbons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Inner/Carbons/run2 $i > /dev/null;
done
