/****************************************************************************
 *
 * Copyright (c) 2002~2005
 *     Software Research Lab.
 *     Institute of Computing Tech.
 *     Chinese Academy of Sciences
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Institute of Computing Tech. and the posession or use of this file requires 
 * a written license from the author.
 * Filename: ICTCLAS.h
 * Abstract:
 *           interface for ICTCLAS(Institute of Computing Tech.,Chinese Lexical Analysis).
 * Author:   Kevin Zhang 
 * Email:    zhanghp@software.ict.ac.cn
 * Homepage: pipy_world.y365.com
 *
 * Date:     2002-8-2
 *
 * Notes:  1. All function will return true if success or false if failure
 *         2. Opearion failure maybe: 
 *            1) The data dir or data file missing
 *            2) Not invoke init() before any current operation
 *            3) Other: you could contact the author.
 ****************************************************************************/
#if !defined(__ICTCLAS_DLL_INCLUDED__)
#define __ICTCLAS_DLL_INCLUDED__

#define ICTCLAS_API  extern "C" __declspec(dllexport)//

ICTCLAS_API bool ICTCLAS_Init();
//Init the program and malloc memory
//The function must be invoked before any operation listed as following
ICTCLAS_API bool ICTCLAS_Exit();
//Exit the program and free memory
//The function must be invoked while you needn't any lexical anlysis
ICTCLAS_API bool ICTCLAS_SetOutputFormat(int nOutputFormat);
//Set output string format;default value is 0
//0:PKU criterion;
//i.e. 张/nr  华平/nr  于/p  1978年/t  3月/t  9日/t  出生/v  于/p  江西省/ns  波阳县/ns  。/w 
//1:973 criterion;
//i.e. 张\[nh]华平\[nh]于\[p]1978年\[nt]3月\[nt]9日\[nt]出生\[v]于\[p]江西省\[ns]波阳县\[ns]。\[w]
//2: XML criterion;
//i.e. <any type="nh"><src>张</src></any><any type="nh"><src>华平</src></any>
//     <any type="p"><src>于</src></any><any type="m"><src>1978</src></any>
//     <any type="q"><src>年</src></any><any type="nt"><src>3月</src></any>
//     <any type="nt"><src>9日</src></any><any type="v"><src>出生</src></any>
//     <any type="p"><src>于</src></any><any type="ns"><src>江西省</src></any>
//     <any type="ns"><src>波阳县</src></any><any type="w"><src>。</src></any>
ICTCLAS_API bool ICTCLAS_SetOperType(int nOperateType);
//Set operation Type; default value is 0
//0:Word Segmentation;
//i.e. 张  华平  于  978  年  3月  9日  出生  于  江西省  波阳县  。  
//1:Word segmentation and tagging with upper POS
//i.e. 张/n  华平/n  于/p  978/m  年/q  3月/t  9日/t  出生/v  于/p  江西省/n  波阳县/n  。/w  
//2:Word segmentation and tagging with total POS
//i.e. 张/nr  华平/nr  于/p  1978年/t  3月/t  9日/t  出生/v  于/p  江西省/ns  波阳县/ns  。/w 
ICTCLAS_API bool ICTCLAS_SentenceProcess(char *sSentence,unsigned int nResultCount,char **sResult);
//Process a sentence
//sSentence: the source sentence
//nResultCount: the count of result, the value cannot more than 10
//**sResult: the results buffer 
//i.e. 张华平于1978年3月9日出生于江西省波阳县。(nResultCount=5)
//Result 1(Score=-63.360033):张/nr  华平/nr  于/p  1978年/t  3月/t  9日/t  出生于/v  江西省/ns  波阳县/ns  。/w  
//Result 2(Score=-65.161371):张/nr  华平/nr  于/p  1978年/t  3月/t  9日/t  出生/v  于/p  江西省/ns  波阳县/ns  。/w  
//Result 3(Score=-73.205565):张/nr  华平/nr  于/p  1978年/t  3月/t  9日/t  出生/v  于/p  江西/ns  省/n  波阳县/ns  。/w  
//Result 4(Score=-80.693838):张/nr  华平/nr  于/p  1978年/t  3月/t  9/m  日出/v  生/v  于/p  江西省/ns  波阳县/ns  。/w  
//Result 5(Score=-82.372596):张/nr  华平/nr  于/p  1978年/t  3月/t  9日/t  出生/v  于/p  江西省/ns  波/n  阳/ag  县/n  。/w  

ICTCLAS_API bool ICTCLAS_ParagraphProcess(char *sParagraph,char *sResult);
//Process a paragraph
//sParagraph: The source paragraph 
//sResult: The result
//i.e. 张华平于1978年3月9日出生于江西省波阳县。(nResultCount=5)
//Result: 张/nr  华平/nr  于/p  1978年/t  3月/t  9日/t  出生于/v  江西省/ns  波阳县/ns  。/w  
ICTCLAS_API bool ICTCLAS_FileProcess(char *sSourceFilename,char *sResultFilename);
//Process a text file
//sSourceFilename: The source file name  
//sResultFilename: The result file name 
//i.e. FileProcess("E:\\Sample\\Corpus_NewPOS\\199802_Org.txt","E:\\Sample\\Corpus_NewPOS\\199802_Org_cla.txt");

#endif//#define __ICTCLAS_DLL_INCLUDED__