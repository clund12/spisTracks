#!/bin/bash
for i in {1401..1600};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer1_alphas.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Inner/Alphas/run2 $i > /dev/null;
done
