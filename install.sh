
#this obviously is for unix platforms, I'm working on an windows version
sudo apt-get install build-essential #making sure host system has gcc and all essentials
rm -f /usr/local/bin/adjudicator
     #COMPILE PROGRESS

gcc -c main.c globalHeader.c generator/generator.c generator/generatorHeader.c judge/judgeHeader.c judge/judge.c #2> INSTALL_LOG.txt
gcc -o adjudicator main.o globalHeader.o generator.o generatorHeader.o judgeHeader.o judge.o -lm 2> INSTALL_LOG.txt #UNFINISHED 

     #1- "2> INSTALL_LOG.txt" writes compilation log in .txt


sudo apt install rename
sudo cp adjudicator /usr/local/bin
sudo rm -rf adjudicator
sudo rm -rf /usr/local/adjudicator
sudo mkdir /usr/local/adjudicator
sudo mkdir /usr/local/adjudicator/temp
rm *.o
