from bs4 import BeautifulSoup as bs

import os, glob

def simulacion(dir, repetition_numer,time):
    b=0
    mision="tuttiTamT"
    
    filelist = glob.glob(os.path.join(dir, "*"))
    for f in filelist:
        os.remove(f)
    for a in range(repetition_numer):
        b+=1
        with open("/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/"+mision+".argos") as fp:
            soup = bs(fp, 'html.parser')
        tag = soup.experiment
        tag['random_seed'] = b
        f = open("/home/jazmin/tuttifrutti/log/Tesis/mision_variables/seed.txt", "a")
        f.write("\n") 
        f.write("s= \""+str(b)+"\";")
        f.write("\n") 
        f.write("events_folder= \""+dir+"\";")
        f.write("\n") 
        f.write("timer_simulation= "+str(time)+";")
        f.close()
        print('tag='+str(tag.attrs))
        with open("/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/"+mision+".argos", "w") as outf:
            outf.write(str(soup))
        os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/build')
        os.system('make')
        os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/')
        os.system("cd ~/tuttifrutti/experiments-loop-functions/build")
        os.system("argos3 -c "+mision+".argos")
    return a 

if __name__ == "__main__":
    simulacion()