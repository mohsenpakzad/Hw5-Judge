
#this obviously is for unix platforms, I'm working on an windows version
sudo apt-get install build-essential #making sure host system has gcc and all essentials
rm -f /usr/local/bin/adjudicator
     #COMPILE PROGRESS

gcc -c HW2.4.c globalHeader.c generator.c generatorHeader.c judgeHeader.c Judge.c #2> INSTALL_LOG.txt
gcc -o adjudicator HW2.4.o globalHeader.o generator.o generatorHeader.o judgeHeader.o Judge.o -lm 2> INSTALL_LOG.txt #UNFINISHED 
     #1- compilation still needs changes
     #2- gcc will get more arguments as development moves forward #adju is working program name as in adjudicator
     #3- "2> INSTALL_LOG.txt" writes compilation log in .txt

 #set to $PATH
 #export PATH=$PATH:/place/with/the/file #this has some security issues -but for now will be ignored-

#ALTERNATIVE add to usr/bi

sudo cp adjudicator /usr/local/bin
sudo rm -rf /usr/local/adjudicator
sudo mkdir /usr/local/adjudicator
sudo mkdir /usr/local/adjudicator/temp
#sudo cp -R Script /usr/local/adjudicator
rm *.o
#NOTES For unistall
#1- remove from bin
#2- remove from local
