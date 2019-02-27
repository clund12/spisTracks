#!/bin/bash
for i in {5401..5600};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer3_oxygens.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Outer/Oxygens/run2 $i > /dev/null;
done
