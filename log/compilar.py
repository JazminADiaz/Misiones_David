from bs4 import BeautifulSoup as bs

import os
mision="tuttiTam"
os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/build')
os.system('make')
os.system("make install")

os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/')
os.system("cd ~/tuttifrutti/experiments-loop-functions/build")
os.system("argos3 -c "+mision+".argos ")
#os.system("argos3 -c tuttiTamPar.argos ")
#os.system("argos3 -c tuttiTamSec.argos ")
