#!/bin/bash
for i in {8001..8200};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer2_nitrogens.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Intermediate/Nitrogens/run2 $i > /dev/null;
done
