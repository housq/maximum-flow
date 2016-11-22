#-*- coding:utf-8 -*-
import os
import os.path as op
import logging
import sys

logging.basicConfig(format='%(asctime)s:%(levelname)s:%(message)s', level =logging.INFO)
dataset_dirs = ['./NETGEN', './VISION', './ROAD']
algorithms = ['ek', 'dinic']
print dataset_dirs

for aname in algorithms:
	for data_dir in dataset_dirs:
		files = os.listdir(data_dir)
		ds_index = files.index('.DS_Store')
		del files[ds_index]
		data_name = op.basename(data_dir)
		logging.info("Running {0} algorithm on {1} data, including {2} files".format(aname, op.basename(data_name), len(files)))
		for index, f in enumerate(files):
		  
			filename, format = op.splitext(f)
			logging.info("Examining file {0} {1}/{2}".format(filename, index + 1, len(files)))
			input_file_path = op.join(data_dir, f)
			output_dir = data_dir + "_RESULTS"
			output_file_path = op.join(output_dir, filename + ".txt")
			shell_command = "./{0} <{1} >{2}".format(aname, input_file_path, output_file_path)
			os.system(shell_command)