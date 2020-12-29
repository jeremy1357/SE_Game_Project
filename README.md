# Zombie Onslaught
## Picture of Final Product
![Alt text](/"Zombie Onslaught Picture.png"?raw=true?raw=true "")

# Read this before doing anything! 
##Verify Visual Studio is configured properly! See below!

## Rundown: 
To gain access to the external hardware a PC has attached, we will use SDL. I already added SDL to the project, and you can see the include file in the main.cpp. This will allow us to read the keyboard and mouse and output to the speakers. To get access to the code you CANNOT just simply download the folder from the GitHub. You must follow the steps below. When you guys commit, give meaningful commit messages so we can track changes. Additionally, we are compiling the code in 64-bit so select x64 at the top in Visual Studio. The dependencies are in 64-bit as well. Viewing the directory of the project you may have notice a folder named “deps.” This directory contains all the external dependencies our project requires to run like OpenGL and SDL. You do not need to change anything in here. 
We will be using these guidelines for coding. Great resource https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#main

## Visual Studio Installation
1.	Install Visual Studio Community 2019 from its website. If already installed, see 1.A
2.	Select the checkbox for "Desktop development with C++" -> Click "Modify" on bottom right
3.	Click install

1.A. IF YOU ALREADY HAVE VISUAL STUDIO INSTALLED, READ -> Go to the Windows search pane in your taskbar -> Type "Apps & features" -> Search for Visual Studio -> Click on Visual Studio -> Click on the "Modify" button -> Click "Yes". This will bring up the window for part 2 above.


## Setting Up Git & Cloning Repository
We will use Git from Visual Studio only. You can do it from the command pane but that will be too complicated. You must connect to the remote repository to obtain the code. This document from the URL below is helpful with showing you how to do it.
https://docs.microsoft.com/en-us/visualstudio/get-started/tutorial-open-project-from-repo?view=vs-2019
I will sum it up this way too.
### Cloning the repository locally to your computer:
1.	Open Visual Studio Community 2019 (different version may be different)
2.	Click clone a repository on the right
3.	Enter the URL of the GitHub repository. May ask you to sign in if not. Must also have access to the repository
4.	Click clone
5.	The repository is now stored locally on your computer

## To sync your changes with the repository:
1.	Make changes with the code
2.	Click on the “Team Explorer” tab on the bottom. You will likely be within the solution explorer. Can also click View -> Team Explorer
3.	Click “Changes”
4.	Add a message that gets linked to your commit. Be concise. Stay on the “Master” branch
5.	Click “Commit All”
6.	Click “Sync” to upload your changes to the repository
7.	The “Synchronization” window will pop up now. Your commit should be stored under “Outgoing Commits.” Click “Push”

## Syncing your local repository with new changes from the remote repository:
Read this good example: https://www.git-tower.com/learn/git/faq/difference-between-git-fetch-git-pull
### TLDR: Try to use “Fetch” since “Pull” can cause issues with the code you’re directly working on.
Do not pull without committing!
