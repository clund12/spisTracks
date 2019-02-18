#!/bin/bash
for i in {1..10000};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer2_alphas.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Alphas $i > /dev/null;
done
