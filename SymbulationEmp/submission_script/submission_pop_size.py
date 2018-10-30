from tempfile import mkstemp
from shutil import move
from os import fdopen, remove
import os

# Change to the filepath of your symbulation program
script_name = "/mnt/home/f0005303/test_pop_size/SymbulationEmp/symbulation"

treatments = ["250","500","750","1000","2000","3000","4000","5000","10000","15000","20000","25000","30000","35000","40000"]

# Change "/mnt/home/f0005303/test_pop_size/SymbulationEmp/VTR=0.0" to the folder where you want your output data files
# For other qsub options, see https://wiki.hpcc.msu.edu/display/hpccdocs/Scheduling+Jobs
header = "#!/bin/bash -login\n\n#PBS -l walltime=01:30:00\n#PBS -l nodes=1:ppn=1\n#PBS -l mem=300gb\n#PBS -N pop_size_tests\ncd /mnt/home/f0005303/test_pop_size/SymbulationEmp/VTR=0.0\n"

def replace(file_path, seed, pop):
        # Create a new configuration file in order to feed it as argument to the symbulation program. Replace 0.0 with the vertical transmission rate that we are currently testing.
        # "configs" is the name of the directory that I manually created for holding temporary configruation files. You might want to also create a directory and use its path here.
	fh = '/mnt/home/f0005303/test_pop_size/SymbulationEmp/configs/TempSettings_'+str(seed)+'_'+str(0.0)+'_'+str(pop)+'.cfg'
	with open(fh, 'w') as new_file:
		with open(file_path) as old_file:
			for line in old_file:
				if ("SEED" in line):
					line = "set SEED "+str(seed)+"\t# What value should the random seed be?\n"
				if ("POPULATION"in line):
					line = "set POPULATION "+str(pop)+"\t# Size of the populations\n"
				new_file.write(line)
	return fh


for t in range(len(treatments)):
	for seed in range(20):
		pop = treatments[t]              
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

