#!/bin/bash
for i in {1601..1800};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer2_oxygens.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Intermediate/Oxygens/run3 $i > /dev/null;
done
