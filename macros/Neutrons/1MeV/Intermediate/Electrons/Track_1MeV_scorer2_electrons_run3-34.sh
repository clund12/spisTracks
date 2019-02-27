#!/bin/bash
for i in {6801..7000};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer2_electrons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Intermediate/Electrons/run3 $i > /dev/null;
done
