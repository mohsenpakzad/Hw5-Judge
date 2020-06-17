#this obviously is for unix platforms, I'm working on an windows version
sudo apt-get install build-essential #making sure host system has gcc and all essentials

     #COMPILE PROGRESS
     gcc -c HelloWorld.c 2> INSTALL_LOG.txt
     gcc -o adjudicator HelloWorld.o -lm 2>> INSTALL_LOG.txt #UNFINISHED 
     #1- compilation still needs changes
     #2- gcc will get more arguments as development moves forward #adju is working program name as in adjudicator
     #3- "2> INSTALL_LOG.txt" writes compilation log in .txt

 #set to $PATH
 #export PATH=$PATH:/place/with/the/file #this has some security issues -but for now will be ignored-
 #have not managed to make this work yet

#ALTERNATIVE add to usr/bin
sudo cp adjudicator /usr/local/bin
