// ICTCLAS_DOS.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "ICTCLAS.h"
#include <string.h>
int main(int argc, char* argv[])
{
	//Sample1: Sentence or paragraph lexical analysis with only one result

    char sSentence[2000],sSentenceResult[5000];
	ICTCLAS_Init();
	printf("Input sentence now!\n");
	scanf("%s",sSentence);
	while(_stricmp(sSentence,"q")!=0)
	{
		ICTCLAS_ParagraphProcess(sSentence,sSentenceResult);
		printf("%s\nInput string now!\n",sSentenceResult);
		scanf("%s",sSentence);
	}
    ICTCLAS_Exit();

	//Sample2: File segmentation and POS tagging
/* 
    ICTCLAS_Init();	
	ICTCLAS_FileProcess("E:\\Sample\\Corpus_NewPOS\\199802_Org.txt","E:\\Sample\\Corpus_NewPOS\\199802_Org_cla.txt");
	ICTCLAS_Exit();
*/

	//Sample3: Sentence segmentation and POS tagging with multiple result
/* 
    char sSentence[2000],**sSentenceResult;
	int i;
	sSentenceResult=new char*[5];
	for(i=0;i<5;i++)
		sSentenceResult[i]=new char[5000];		

	ICTCLAS_Init();
	printf("Input sentence now!\n");
	scanf("%s",sSentence);
	while(_stricmp(sSentence,"q")!=0)
	{
		ICTCLAS_SentenceProcess(sSentence,5,sSentenceResult);
		for(i=0;i<5;i++)
			printf("Result%d:%s\n",i+1,sSentenceResult[i]);
		printf("Input string now!\n");
		scanf("%s",sSentence);
	}
    ICTCLAS_Exit();
	
	for(i=0;i<5;i++)
		delete[] sSentenceResult[i];		
	delete [] sSentenceResult;
*/
	return 0;
}
