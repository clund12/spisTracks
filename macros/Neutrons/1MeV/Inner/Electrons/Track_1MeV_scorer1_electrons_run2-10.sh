#!/bin/bash
for i in {2001..2200};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer1_electrons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Inner/Electrons/run2 $i > /dev/null;
done
