import argparse
import numpy as np
import sys

################################################################################

def updatePname(x):
    if x == 'electron':
        x = 'e-'
    elif x == 'deuteron':
        x = 'proton'
    elif x == 'carbon':
        x = 'GenericIon'+'\n'+'/gps/ion 6 12'
    elif x == 'nitrogen':
        x = 'GenericIon'+'\n'+'/gps/ion 7 14'
    elif x == 'oxygen':
        x = 'GenericIon'+'\n'+'/gps/ion 8 16'
    else:
        x = x
    return x

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
histoFileName = pname+'s_scorer'+scorer+'_energy_histogram_'+ekin+'.dat'

fileName = histoPath+histoFileName
with open(fileName, 'r') as f:
    histoData = f.read()


# write a new macro file, where all strings matching entries in a dictionary being replaced by the chosen values
macroName = 'Track_'+ekin+'_scorer'+scorer+'_'+pname+'s.mac'

scorerName = {
        '1':'Inner',
        '2':'Intermediate',
        '3':'Outer'
        }

trackRange = '{1..'+trackNumber+'}'

for i in range(3):
    outputSuffix = ekin+'/'+scorerName[scorer]+'/'+pname.title()+'s'
    outputName = '/home/chris/geant4/work/Data/Tracks/Neutrons/'+outputSuffix+'/run'+str(i+1)
    macroFolder = 'macros/Neutrons/'+outputSuffix
    #outputName = './'

    for j in range(50):
        start = j*int(trackNumber) + 1
        end = start + int(trackNumber) - 1
        trackRange = '{'+str(start)+'..'+str(end)+'}'

        subparams = {
                'trackRange':trackRange,
                'macroName':macroName,
                'outputName':outputName
                }

        bashName = macroName[:-4]+'_run'+str(i+1)+'-'+str(j)+'.sh'
        bashPath = macroFolder+'/'+bashName
        #bashPath = bashName

        with open(bashPath, 'w') as f:
            f.write(submission_string.format(**subparams))

        with open('pass-to-blade.sh', 'a') as f:
            f.write('sbatch -p batch -N1 -n1 '+bashName+'\n')
 

pname = updatePname(pname)

params = {
        'pName':pname,
        'histo':histoData
        }

with open(macroFolder+'/'+macroName, 'w') as f:
    f.write(template_string.format(**params))

#################################################################################
