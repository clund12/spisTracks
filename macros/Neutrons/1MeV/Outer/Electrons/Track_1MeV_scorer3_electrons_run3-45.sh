#!/bin/bash
for i in {9001..9200};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer3_electrons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Outer/Electrons/run3 $i > /dev/null;
done
