import json
import sys


if (len(sys.argv) != 2):
	print "error: no file passed!"
	exit(84)
else:
	name = sys.argv[1]

name2 = name[:-5]	
fichier2 = open(name2+".h", "w")
fichier2.write("#pragma once\n\n")
fichier2.write("#include <nds.h>\n\n")
fichier = open(name2+".c", "w")
fichier.write("#include <nds.h>\n")

with open(name) as json_data:
	data_dict = json.load(json_data)
	for i in range(0, len(data_dict["layers"])):
		incr = 0
		y = 0
		fichier.write("\n\n//LAYER n "+str(i)+"\n")
		for k in range(0, data_dict["layers"][i]["width"]/16):
			x = y
			y = y + 16
			fichier.write("\nu16	Layer"+str(i)+str(k)+"[256] = {")
			fichier2.write("\nextern u16	Layer"+str(i)+str(k)+"[];\n")
			for p in range(0, data_dict["layers"][i]["height"]):
				fichier.write("\n    ")
				for j in range(x, x + 16):
                                        my_data = data_dict["layers"][i]["data"][j];
                                        if (my_data != 0):
                                                my_data -= 1
					fichier.write(str(my_data)+", ")
				x = x + data_dict["layers"][i]["width"]
			fichier.write("\n};\n")
fichier.close()
fichier2.close()
