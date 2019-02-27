#!/bin/bash
for i in {7001..7200};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer2_deuterons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Intermediate/Deuterons/run1 $i > /dev/null;
done
