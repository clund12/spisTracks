#!/bin/bash
for i in {4401..4600};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer1_deuterons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Inner/Deuterons/run2 $i > /dev/null;
done
