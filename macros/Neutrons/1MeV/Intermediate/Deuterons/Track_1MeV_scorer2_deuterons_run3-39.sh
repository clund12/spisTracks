#!/bin/bash
for i in {7801..8000};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer2_deuterons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Intermediate/Deuterons/run3 $i > /dev/null;
done
