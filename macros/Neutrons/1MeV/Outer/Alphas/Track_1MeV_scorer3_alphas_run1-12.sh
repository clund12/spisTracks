#!/bin/bash
for i in {2401..2600};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer3_alphas.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Outer/Alphas/run1 $i > /dev/null;
done
