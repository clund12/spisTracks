#!/bin/bash
for i in {601..800};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer3_carbons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Outer/Carbons/run1 $i > /dev/null;
done
