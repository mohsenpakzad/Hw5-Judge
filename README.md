# Getting started

This program works in Windows OS only.

### Requirements ###

gcc compiler(latest version recommended)

### Installation ###

In the directory of this program, open cmd and run the command below :

```
gcc main.c generator/generator.c judge/judge.c -o main
```

and run "main.exe"

## *Main program* ##

![](https://github.com/AmirHosein-Gharaati/Hw5-Judge/blob/master/screenShots/menu.PNG)

### Generate test case ###

In this choice you can generate main code outputs.

#### How to use ####

At first you have to enter the path of the inputs folder. There are 3 ways:

    1-Drag and drop the folder into the .exe window
    
    
![](https://github.com/AmirHosein-Gharaati/Hw5-Judge/blob/master/screenShots/dragAndDrop.png)


    2-Enter the path manually(Don't forget to use the quotations e.g : "D:\inputs")
    
    
![](https://github.com/AmirHosein-Gharaati/Hw5-Judge/blob/master/screenShots/enterInputsManually.PNG)


    3-Press d to use the default path(.\main\inputs)


If the path was correct, it will ask you to confirm the inputs.


![](https://github.com/AmirHosein-Gharaati/Hw5-Judge/blob/master/screenShots/InputsConfirmation.PNG)



Then you have to enter the path of the C-main-file. The ways are the same.


Notes: 
    If there were any mistakes in entering the paths, you will know it.
    The maximum number of test cases is 500.


### Judge ###


Note: You have to generate test cases at first, to access this option.

In this choice you can generate user code outputs and check for results.

Enter the path of C-user-file as same as you did at first step.


## Features

    1-You can enter 'd' if you don't want to drag and drop or copy paste.

    2-In every step that you have to enter a path, you can simply type "back" to go back.
    
    3-Every name for inputs are allowed
    
    4-Loading screen


#### Folders descriptions ####

main: There are 4 folders in this folder:

    1-CFileForGenerator: You can put the main C-main-file in this folder (Multiple files are not allowed.)
    
    2-CFileForJudge: You can put the main C-user-file in this folder (Multiple files are not allowed.)
    
    3-inputs: You can put inputs in this folder.
    
    4-miscellaneous: Not important.
    

Output: There are 2 folders in this folder:

    1-judgeOutput: The outputs of judge will be generated here.
    
    2-mainOutput: The ouputs of "generate test cases" will be generated here.


result: You can see the saved results.
    

# Any Questions? ✩◝(◍⌣̎◍)◜✩ #

## See You !!! ##
