#!/bin/bash
for i in {6401..6600};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer3_oxygens.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Outer/Oxygens/run1 $i > /dev/null;
done
