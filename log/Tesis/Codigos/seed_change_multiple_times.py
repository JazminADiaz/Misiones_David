from bs4 import BeautifulSoup as bs

import os, glob

import re

import subprocess
import random

b=0
mision="tuttiTamT"

dir = "/home/jazmin/tuttifrutti/log/Tesis/EventLogs_reboot/"
filelist = glob.glob(os.path.join(dir, "*"))

for f in filelist:
    os.remove(f)


for a in range(100):
    
    b+=1
    
    with open("/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/"+mision+".argos") as fp:
        soup = bs(fp, 'html.parser')

    tag = soup.experiment

    tag['random_seed'] = b
    f = open("/home/jazmin/tuttifrutti/log/wordlist.txt", "w")
    f.write(str(b))
    f.close()
    print('tag='+str(tag.attrs))
    with open("/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/"+mision+".argos", "w") as outf:
        outf.write(str(soup))

    os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/build')
    os.system('make')


    os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/')
    os.system("cd ~/tuttifrutti/experiments-loop-functions/build")

    os.system("argos3 -c "+mision+".argos")

