#!/bin/bash
for i in {2401..2600};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer1_carbons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Inner/Carbons/run2 $i > /dev/null;
done
