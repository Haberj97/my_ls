# Groupe de hamia_r 944948

 ___       __   _______   ___       ________  ________  _____ ______   _______      
|\  \     |\  \|\  ___ \ |\  \     |\   ____\|\   __  \|\   _ \  _   \|\  ___ \     
\ \  \    \ \  \ \   __/|\ \  \    \ \  \___|\ \  \|\  \ \  \\\__\ \  \ \   __/|    
 \ \  \  __\ \  \ \  \_|/_\ \  \    \ \  \    \ \  \\\  \ \  \\|__| \  \ \  \_|/__  
  \ \  \|\__\_\  \ \  \_|\ \ \  \____\ \  \____\ \  \\\  \ \  \    \ \  \ \  \_|\ \ 
   \ \____________\ \_______\ \_______\ \_______\ \_______\ \__\    \ \__\ \_______\
    \|____________|\|_______|\|_______|\|_______|\|_______|\|__|     \|__|\|_______|
    

For create the executable you need to start by create the libmy.a please use following cmd in same directory of Makefiles:

gcc -c libmy/lmy_sources/*.c && ar -r libmy.a *.o && ranlib libmy.a && rm *.o

then you can use the cmd make to build executable called my_ls

if you need to know how to use this programe you can use following cmd to see man :

./my_ls -h

                          .___                       __  .__                
   ____   ____   ____   __| _/  __ __  ___________ _/  |_|__| ____   ____   
  / ___\ /  _ \ /  _ \ / __ |  |  |  \/  ___/\__  \\   __\  |/  _ \ /    \  
 / /_/  >  <_> |  <_> ) /_/ |  |  |  /\___ \  / __ \|  | |  (  <_> )   |  \ 
 \___  / \____/ \____/\____ |  |____//____  >(____  /__| |__|\____/|___|  / 
/_____/                    \/             \/      \/                    \/ 

