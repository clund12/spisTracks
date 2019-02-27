#!/bin/bash
for i in {1..200};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer2_protons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Intermediate/Protons/run3 $i > /dev/null;
done
