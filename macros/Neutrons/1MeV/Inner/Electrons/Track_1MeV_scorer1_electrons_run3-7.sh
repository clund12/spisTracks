#!/bin/bash
for i in {1401..1600};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer1_electrons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Inner/Electrons/run3 $i > /dev/null;
done
