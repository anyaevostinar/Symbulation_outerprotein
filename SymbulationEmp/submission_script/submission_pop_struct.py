from tempfile import mkstemp
from shutil import move
from os import fdopen, remove
import os

# Change to the filepath of your symbulation program
script_name = "/mnt/home/f0005303/test_pop_struct/SymbulationEmp/symbulation"

treatments = ["0.0","0.1","0.2","0.3","0.4","0.5","0.6","0.7","0.8","0.9","1.0"]

# Change "/mnt/home/f0005303/test_pop_size/SymbulationEmp/VTR=0.0" to the folder where you want your output data files
# For other qsub options, see https://wiki.hpcc.msu.edu/display/hpccdocs/Scheduling+Jobs
header = "#!/bin/bash -login\n\n#PBS -l walltime=01:30:00\n#PBS -l nodes=1:ppn=1\n#PBS -l mem=300gb\n#PBS -N pop_struct_tests\ncd /mnt/home/f0005303/test_struct_size/SymbulationEmp/pop=40000\n"

def replace(file_path, VTR, seed):
        # Create a new configuration file in order to feed it as argument to the symbulation program. Replace 0.0 with the vertical transmission rate that we are currently testing.
        # "configs" is the name of the directory that I manually created for holding temporary configruation files. You might want to also create a directory and use its path here.
	fh = '/mnt/home/f0005303/test_pop_size/SymbulationEmp/configs/TempSettings_'+str(seed)+'_'+str(VTR)+'_'+str(40000)+'.cfg'
	with open(fh, 'w') as new_file:
		with open(file_path) as old_file:
			for line in old_file:
				if ("SEED" in line):
					line = "set SEED "+str(seed)+"\t# What value should the random seed be?\n"
				if ("VERTICAL_TRANSMISSION"in line):
					line = "set VERTICAL_TRANSMISSION "+str(VTR)+"\t# Value 0 to 1 of probability of symbiont vertically transmitting when host reproduces\n"
				new_file.write(line)
	return fh


for t in range(len(treatments)):
	for seed in range(20):
		VTR = treatments[t]              
                file_path = "/mnt/home/f0005303/test_pop_size/SymbulationEmp/SymSettings.cfg" # Change to the filepath of your SymSettings.cfg    
    		filepath = replace(file_path, seed+1, VTR)
		tempfilename = 'temp_'+'.qsub'
    		tempfile = open(tempfilename, 'w')
    		tempfile.write(header)
    		tempfile.write(script_name)
		tempfile.write(" ")
		tempfile.write(filepath)
    		tempfile.close()
    		os.system("qsub {0}".format(tempfilename))
    		print ("submitted "+ str(seed))
		os.system("rm {0}".format(tempfilename))

