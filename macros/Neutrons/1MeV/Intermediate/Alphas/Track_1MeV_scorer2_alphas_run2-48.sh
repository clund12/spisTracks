#!/bin/bash
for i in {9601..9800};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer2_alphas.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Intermediate/Alphas/run2 $i > /dev/null;
done
