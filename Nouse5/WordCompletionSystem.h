#pragma once

#define NUM_LETTERS 26
#define MAX_NUM_WORDS_PER_PREFIX 300
#define MAX_LETTERS_PER_WORD 20
#define MAX_WORDS_QUERIED 20

class CWordCompletionSystem  
{
public:
	CWordCompletionSystem(char* strFilename);
	virtual ~CWordCompletionSystem();

	void queryPrefix(char* strPrefix); // Return the actual number of words stored
	char m_strQueryResults[MAX_WORDS_QUERIED][MAX_LETTERS_PER_WORD];
	void clearQuery();

	int m_nWordsFound;

private:
	char m_dictionary[NUM_LETTERS][MAX_NUM_WORDS_PER_PREFIX][MAX_LETTERS_PER_WORD]; //Use a one letter prefix
	int m_arrNumWordsForPrefix[NUM_LETTERS];
	void convertStringToLowercase(char* str);

	

};
