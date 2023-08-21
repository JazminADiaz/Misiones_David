from bs4 import BeautifulSoup as bs

import os

import re

import subprocess
import random

b=61
mision="tuttiTamT"
for a in range(10):
    
    b+=1
    if b!=25 and b!=16 and b!=33 and b!=15:
        with open("/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/"+mision+".argos") as fp:
            soup = bs(fp, 'html.parser')

        tag = soup.experiment

        tag['random_seed'] = b
        print('tag='+str(tag.attrs))
        with open("/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/"+mision+".argos", "w") as outf:
            outf.write(str(soup))

        os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/build')
        os.system('make')


        os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/')
        os.system("cd ~/tuttifrutti/experiments-loop-functions/build")

        os.system("argos3 -c "+mision+".argos")


'''
for a in range(110):
    if a!=65 and a!=25 and a!=16 and a!=33 and a!=15 and a!=40 and a!= 52 and a!=109:

        with open("/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/tuttiTam.argos") as fp:
            soup = bs(fp, 'html.parser')

        tag = soup.experiment

        tag['random_seed'] = a
        print('tag='+str(tag.attrs))
        with open("/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/tuttiTam.argos", "w") as outf:
            outf.write(str(soup))

        os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/build')
        os.system('make')


        os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/')
        os.system("cd ~/tuttifrutti/experiments-loop-functions/build")

        os.system("argos3 -c tuttiTam.argos")


'''

        


    