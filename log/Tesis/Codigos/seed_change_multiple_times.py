from bs4 import BeautifulSoup as bs
import os
import glob
import argparse

def simulacion(directorio, repetition, time):
    #print("Simulación aqui.")

    mision = "tuttiTamT"

    filelist = glob.glob(os.path.join(directorio, "*"))
    for f in filelist:
        os.remove(f)

    for b in range(1, repetition + 1):
        with open(f"/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/{mision}.argos") as fp:
            soup = bs(fp, 'html.parser')
        
        tag = soup.experiment
        tag['random_seed'] = b
        
        with open("/home/jazmin/tuttifrutti/log/Tesis/mision_variables/seed.txt", "w"):
            pass
        
        with open("/home/jazmin/tuttifrutti/log/Tesis/mision_variables/seed.txt", "a") as f:
            f.write("\n")
            f.write(f"s= \"{b}\";\n")
            f.write(f"events_folder= \"{directorio}\";\n")
            f.write(f"timer_simulation= {time};\n")
        
        with open(f"/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/{mision}.argos", "w") as outf:
            outf.write(str(soup))
        
        os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/build')
        os.system('make')
        os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/')
        #os.system("cd ~/tuttifrutti/experiments-loop-functions/build")
        os.system(f"argos3 -c {mision}.argos")

def main():
    parser = argparse.ArgumentParser(description="Descripción de tu script.")
    parser.add_argument('--directorio', type=str, help='Ruta al directorio')
    parser.add_argument('--repetition', type=int, default=1, help='Número de repeticiones (por defecto: 1)')
    parser.add_argument('--time', type=int, default=0, help='Valor de time (por defecto: 0)')
    args = parser.parse_args()

    simulacion("/home/jazmin/tuttifrutti/log/Tesis/Codigos/seed_change_multiple_times.py", 2, 2000)
    #simulacion(args.directorio, args.repetition, args.time)
    print("Simulación completada.")

if __name__ == "__main__":
    main()
