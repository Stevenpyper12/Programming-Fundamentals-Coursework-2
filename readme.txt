First make sure to compile the program as this is required before any of the rest of the nmake commands will work, this is done by typing nmake compboth(which will compile both programs) or nmake testfilecomp and nmake spellcheckercomp which will compile each program seperately
nmake compboth 			-compiles both programs
nmake testfilecomp 		-compiles the test file
nmake spellcheckercomp		-compiles the spell checker file

The test file can be run by using these:
nmake testfile 			- this runs the test program
nmake clean			- this deletes all .obj,.exe and .asm files(including the test files objects and execuatables)

There are different options for running the spell checker program depending on what file is required to be read.
Theses options are:
nmake spellcheckersentences	- this runs the spellchecker file which will check the sentences_test.txt file. 
nmake spellcheckersingle	- this runs the spellchecker file which will check the single_words_test.txt file. 
nmake clean			- this deletes all .obj,.exe and .asm files(including the test files objects and execuatables)

This code will will take in a string or characters from a file and will check if the word is contained inside the dictionary.txt file.
if you want to manually check a file compile the spellchecker program and then in the command prompt use spell_checker -i filename.txt
The -i filename arguement can be added which allows you to select the file you want to read from, a example would be spell_checker -i sentences_test.txt" this would read from the sentences_test.txt.

This code was designed and compiled in the Microsoft Visual Studio 2017 Developer Command Prompt v15.5.6.








