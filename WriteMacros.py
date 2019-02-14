import argparse
import numpy as np
import sys

################################################################################

# open the template macro file and the submission_script template
template_file = open('Track_template.mac')
submission_file = open('Bash_template.sh')

# read them into strings, then close them
template_string = template_file.read()
template_file.close()

submission_string = submission_file.read()
submission_file.close()

if len(sys.argv) == 1:
    pname = input('Particle type: ')

    scorer = input('Scorer number (1=inner, 2=intermediate, 3=outer): ')

    ekin = input('Initial neutron kinetic energy (with units): ')

    trackNumber = input('Number of tracks to be generated: ')


elif len(sys.argv) == 5:
    pname = sys.argv[1]
    scorer = sys.argv[2]
    ekin = sys.argv[3]
    trackNumber = sys.argv[4]

else:
    print('Provide, in order:'+'\n'
            +'the csv file containing the list of energies to be simulated (provide only this to be prompted for the rest),'+'\n'
            +'the name of the particle to be simulated,'+'\n'
            +'the scorer,'+'\n'
            +'the starting kinetic energy of the incident neutrons'+'\n'
            +'Otherwise, provide no input and follow the prompts.')
    sys.exit()

################################################################################

histoPath = '/home/chris/geant4/work/Data/Spectra/Neutrons/Histos/2019-01-25/'
histoFileName = pname+'_scorer'+scorer+'_energy_histogram_'+ekin+'.dat'

fileName = histoPath+histoFileName
with open(fileName, 'r') as f:
    histoData = f.read()


# write a new macro file, where all strings matching entries in a dictionary being replaced by the chosen values
trackRange = '{1..'+trackNumber+'}'
macroName = 'Track_'+ekin+'_scorer'+scorer+'_'+pname+'.mac'
outputName = '/home/chris/geant4/work/Data/Tracks/Neutrons/'+ekin+'/'+pname.title()

params = {
        'pName':pname,
        'histo':histoData
        }

subparams = {
        'trackRange':trackRange,
        'macroName':macroName,
        'outputName':outputName
        }

with open(macroName, 'w') as f:
    f.write(template_string.format(**params))

bashName = macroName[:-4]+'.sh'
with open(bashName, 'w') as f:
    f.write(submission_string.format(**subparams))

# create a bash file to call all scripts in one go
#with open('pass-to-blade.sh','a') as bladefile:
#    bladefile.write('sbatch -p batch -N1 -n'+str(nthreads)+' Cluster'+forname+'.sh'+'\n')
#    bladefile.write('sbatch -p batch -N1 -n1 Cluster'+forname+'.sh'+'\n')

################################################################################
