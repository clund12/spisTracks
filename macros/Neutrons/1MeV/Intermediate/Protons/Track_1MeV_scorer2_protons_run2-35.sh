#!/bin/bash
for i in {7001..7200};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer2_protons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Intermediate/Protons/run2 $i > /dev/null;
done
