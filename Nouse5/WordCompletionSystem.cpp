#include "stdafx.h"
#include "WordCompletionSystem.h"

CWordCompletionSystem::CWordCompletionSystem(char* strFilename)
{
	CString m_strFileName(strFilename);
	CString strLine;
	char word[MAX_LETTERS_PER_WORD];
	int i;
	for(i=0; i<NUM_LETTERS; ++i)
		m_arrNumWordsForPrefix[i] = 0;
	CFileStatus status;
	if (CFile::GetStatus(m_strFileName, status))
	{
		CStdioFile file(m_strFileName, CFile::modeRead);
		while ( file.ReadString(strLine))//fscanf(file.ReadString(), "%s", word) != EOF)
		{
			if (strLine.GetLength() > 2)
			{
				int char1 = strLine.GetAt(0) - 'a';

				strcpy(m_dictionary[char1][m_arrNumWordsForPrefix[char1]++], (char*)strLine.GetBuffer());
			}
		}
		file.Close();
	}
/*	FILE* in = fopen(strFilename, "r");

	char word[MAX_LETTERS_PER_WORD];
	while (fscanf(in, "%s", word) != EOF)
	{
		if(strlen(word) > 2) {
			int char1 = word[0] - 'a';

			strcpy(m_dictionary[char1][m_arrNumWordsForPrefix[char1]++], word);
		}
	}
	fclose(in);
	*/
	clearQuery();
}

CWordCompletionSystem::~CWordCompletionSystem()
{

}

void CWordCompletionSystem::queryPrefix(char* strPrefix) {
	m_nWordsFound = 0;

	int nPrefixLength = strlen(strPrefix);
	if(nPrefixLength == 0)
		return;

	convertStringToLowercase(strPrefix);
	int char1 = strPrefix[0] - 'a';

	for(int i=0; i<m_arrNumWordsForPrefix[char1]; ++i) {
		char* strCurrentDictionaryWord = m_dictionary[char1][i];
		char* strstrResult = strstr(strCurrentDictionaryWord, strPrefix);
		if(strstrResult && (nPrefixLength != strlen(strCurrentDictionaryWord)) && !strcmp(strCurrentDictionaryWord, strstrResult)) {
			strcpy(m_strQueryResults[m_nWordsFound++], strCurrentDictionaryWord);
			if(m_nWordsFound == MAX_WORDS_QUERIED)
				return;
		}
	}
}

void CWordCompletionSystem::convertStringToLowercase(char* str) {
	for(int i=0; i<strlen(str); ++i)
		str[i] = tolower(str[i]);
}

void CWordCompletionSystem::clearQuery() {
	m_nWordsFound = 0;
}
