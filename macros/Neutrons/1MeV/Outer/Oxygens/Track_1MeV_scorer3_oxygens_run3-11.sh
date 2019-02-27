#!/bin/bash
for i in {2201..2400};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer3_oxygens.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Outer/Oxygens/run3 $i > /dev/null;
done
