#!/bin/bash
for i in {2601..2800};
do /home/chris/geant4/work/spisTracks/build/spisTracks Track_1MeV_scorer2_deuterons.mac /home/chris/geant4/work/Data/Tracks/Neutrons/1MeV/Intermediate/Deuterons/run2 $i > /dev/null;
done
