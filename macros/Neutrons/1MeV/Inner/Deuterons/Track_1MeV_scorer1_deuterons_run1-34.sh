#!/bin/bash
for i in {6801..7000};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer1_deuterons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Inner/Deuterons/run1 $i > /dev/null;
done
