#!/bin/bash
for i in {801..1000};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer1_nitrogens.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Inner/Nitrogens/run3 $i > /dev/null;
done
