compboth: testfilecomp spellcheckercomp
testfilecomp:
	cl test.cpp BinarySearchTree.lib /EHsc
spellcheckercomp:
	cl spell_checker.cpp BinarySearchTree.lib /EHsc
testfile:
	test	
spellcheckersentences:
	spell_checker -i sentences_test.txt
spellcheckersingle:
	spell_checker -i single_words_test.txt
clean:
	del *.obj
	del *.exe
	del *.asm