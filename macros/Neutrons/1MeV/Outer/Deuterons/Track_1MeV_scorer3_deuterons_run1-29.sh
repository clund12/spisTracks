#!/bin/bash
for i in {5801..6000};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer3_deuterons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Outer/Deuterons/run1 $i > /dev/null;
done
