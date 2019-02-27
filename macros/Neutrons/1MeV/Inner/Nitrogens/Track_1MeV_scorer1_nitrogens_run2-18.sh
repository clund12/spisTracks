#!/bin/bash
for i in {3601..3800};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer1_nitrogens.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Inner/Nitrogens/run2 $i > /dev/null;
done
