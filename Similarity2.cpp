// Similarity2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
*/


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
typedef char* PCHAR;

const int MAX_WORDLEN = 60;

typedef map<string, int, less<string> > STRING2INT;
typedef map<string, double, less<string> > STRING2DBL;



  struct WordSorted
 {  
   int    features_count;
   int    corpus_count;
   PCHAR*  features;
   double*   values;
 };


  struct Word
 {  
   int    features_count;
   int    corpus_count;  
   STRING2DBL valuesMap;
 };

 typedef Word* WordPointer;
 Word* Words;
 PCHAR* Lemmas;
 int*  FeaturesCounts;
 int*  CorpusCounts;

 int TotalLemmas = 0;
 int WordsCount = 0;    


 class Corpus
 {
    public:

		STRING2INT           lemmaMap;
		STRING2INT::iterator lemmaIterator;
		STRING2DBL::iterator valuesIterator;

		PCHAR* Lemmas;        
        Word* Words;
		WordSorted* Sorted;

        int*  FeaturesCounts;

		int TotalLemmas;
	    int TotalWords;

		/*
            Corpus(char* fileName)
            {
             //ReadCorpus(fileName);                                                 
            }
			*/

			Corpus()
            {
             //ReadCorpus(fileName);                                                 
            }

			Corpus(char* c)
            {
             //ReadCorpus(fileName);                                                 
            }
            
            ~Corpus()
            {
				Dispose(); //Doesn't work
			}
			
			void Dispose()
			{
		    }   
		
		/*
			//Saves the data in binary format
			void Save(char* fileName)
			{
				int i, j;
				int len;				

				FILE* out;
				out = fopen(fileName, "wb");				

				cout << TotalLemmas;				
				fwrite(&TotalLemmas, sizeof(int), 1, out); 								
				fwrite(FeaturesCounts, sizeof(int), TotalLemmas, out);

				lemmaIterator = lemmaMap.begin();

				for(i=0; i<TotalLemmas; i++)
				{								    					
				
						len = strlen((*lemmaIterator).first.c_str());
						fwrite(&len, sizeof(int), 1, out);						
						fwrite(lemmaIterator->first.c_str(), len, 1, out);

					    fwrite(&Words[i].corpus_count,  sizeof(int), 1, out);											

					for(j = 0; j < FeaturesCounts[i]; j++)
					{
						len = strlen(Words[i].features[j]);
						fwrite(&len, sizeof(int), 1, out);
						fwrite(Words[i].features[j], strlen(Words[i].features[j]), 1, out);
						fwrite(&Words[i].values[j], sizeof(double), 1, out);
					}					
				  lemmaIterator++;
				}	
				fclose(out);
			}

			//Load from a binary file
			void Load(char* fileName, Corpus* corpus)
			{
				int i, j;
				int len;				
				int Counter = 0;
				char Buffer[255];
				bool Debug = false;

				lemmaMap.clear();

				FILE* out;				
				out = fopen(fileName, "rb");

				int Total, size;
				fread(&corpus->TotalLemmas, sizeof(int), 1, out);				
				
				cout << corpus->TotalLemmas;												

				corpus->Words = new Word[corpus->TotalLemmas];
				corpus->FeaturesCounts = new int[corpus->TotalLemmas];			
											
				size = fread(corpus->FeaturesCounts, sizeof(int), corpus->TotalLemmas, out);	

			if (Debug)
				for(i=0; i<corpus->TotalLemmas; i++)
				{
					cout << corpus->FeaturesCounts[i] <<endl;
					corpus->Words[i].features_count = corpus->FeaturesCounts[i];
				}


				for(i=0; i<TotalLemmas; i++)
				{								    					
					 fread(&len, sizeof(int), 1, out);					 
					 fread(&Buffer, len, 1, out);
					 Buffer[len] = 0;

			if (Debug)
				       cout << Buffer <<", ";


					 lemmaMap[Buffer] = Counter;
					 fread((int*)&corpus->Words[i].corpus_count,  sizeof(Words[i].corpus_count), 1, out);
					 corpus->Words[i].features = new PCHAR[corpus->FeaturesCounts[i]];
					 corpus->Words[i].values = new double[corpus->FeaturesCounts[i]];					 					 

					for(j = 0; j < corpus->FeaturesCounts[i]; j++)
					{
						fread(&len, sizeof(int), 1, out);					
						corpus->Words[i].features[j] = new char[len];

						fread(corpus->Words[i].features[j], len, 1, out);
						corpus->Words[i].features[j][len] = 0;					 	
						strcpy(Buffer, corpus->Words[i].features[j]);


					if (Debug)
						 cout << corpus->Words[i].features[j]<< " - ";
						

						fread(&corpus->Words[i].values[j], sizeof(double), 1, out);						
					}

				  if (Debug)
					     cout << endl;

					Counter++;
				}
				fclose(out);
			
				for(i=0; i<corpus->TotalLemmas; i++)
				{
				  if (Debug) 
					     cout << corpus->FeaturesCounts[i] <<endl;
				  corpus->Words[i].features_count = corpus->FeaturesCounts[i];  //Something overlays the values after they are written above?
				}

				if (Debug)                               
					for(i=0; i<corpus->TotalLemmas; i++)
				{
					cout << corpus->Words[i].features_count<<endl;					
				}

			if (Debug)
			{
				lemmaIterator = lemmaMap.begin();
				for( ; lemmaIterator!=lemmaMap.end(); lemmaIterator++)
				{
					cout << lemmaIterator->first << " == " << lemmaIterator->second << endl;
				}
			}

	   }
		
  */

			void SaveMap(char* fileName)
			{
				int i, j, k;
				int len;	
				unsigned char lenByte;
				char Buffer[250];

				FILE* out;
				out = fopen(fileName, "wb");				

				cout << TotalLemmas;				
				//fwrite(&TotalLemmas, sizeof(int), 1, out); 								
				fwrite(&TotalLemmas, sizeof(int), 1, out); 								
				fwrite(FeaturesCounts, sizeof(int), TotalLemmas, out);

				lemmaIterator = lemmaMap.begin();				
	        STRING2DBL::iterator valuesIterator;

				for(i=0; i<TotalLemmas; i++)
				{								    					
				
					  
						len = strlen((*lemmaIterator).first.c_str());
					    fwrite(&len, sizeof(int), 1, out);
						fwrite(lemmaIterator->first.c_str(), len, 1, out);
					
							/*
					          lenByte = (unsigned char) strlen((*lemmaIterator).first.c_str());
						      fwrite(&lenByte, sizeof(unsigned char), 1, out);
							   fwrite(lemmaIterator->first.c_str(), lenByte, 1, out);
							*/
												
													 
						fwrite(&lemmaIterator->second, sizeof(int), 1, out);
					    fwrite(&Words[i].corpus_count,  sizeof(int), 1, out);											

						//printf("\n%s -- %d", lemmaIterator->first.c_str(), lemmaIterator->second);
						// <<<

						valuesIterator = Words[i].valuesMap.begin();

						// cout << Words[i].valuesMap.size() <<"\n";

						//printf("\n%s,  %", valuesIterator->first.c_str(), valuesIterator->second);
						for( ; valuesIterator != Words[i].valuesMap.end(); valuesIterator++)
						{ 
							//strcpy(Buffer, valuesIterator->first.c_str);
							//len = strlen(Buffer); //&valuesIterator->first.c_str);
							// printf("\n%s,  %f", valuesIterator->first.c_str(), valuesIterator->second);

							
	
						
							len = strlen(valuesIterator->first.c_str());		                       
							fwrite(&len,  sizeof(int), 1, out);
							fwrite(valuesIterator->first.c_str(),  1, len, out);

							/*
							  lenByte = (unsigned char) strlen(valuesIterator->first.c_str());;
						      fwrite(&lenByte, sizeof(unsigned char), 1, out);							
							  fwrite(valuesIterator->first.c_str(),  1, lenByte, out);
							*/

							fwrite(&valuesIterator->second,  sizeof(double), 1, out);
						}						

			/*
					for(j = 0; j < FeaturesCounts[i]; j++)
					{
						len = strlen(Words[i].features[j]);
						fwrite(&len, sizeof(int), 1, out);
						fwrite(Words[i].features[j], strlen(Words[i].features[j]), 1, out);
						fwrite(&Words[i].values[j], sizeof(double), 1, out);
					}			
				*/
				  lemmaIterator++;
				}
				fclose(out);
			}							

			void LoadMap(char* fileName, Corpus* corpus)
			{
				int i, j, index;
				int len;				
				int Counter = 0;
				char Buffer[255];
				double Value;
				bool Debug = false;
				string s;

				lemmaMap.clear();
				
				FILE* out;				
				out = fopen(fileName, "rb");

				int Total, size;
				fread(&corpus->TotalLemmas, sizeof(int), 1, out);				
				
				cout << corpus->TotalLemmas;												

				corpus->Words = new Word[corpus->TotalLemmas];
				corpus->FeaturesCounts = new int[corpus->TotalLemmas];

				
				         //corpus->Sorted
				         //corpus->Sorted = new WordSorted[corpus->TotalLemmas];
				corpus->FeaturesCounts = new int[corpus->TotalLemmas];
															
				size = fread(corpus->FeaturesCounts, sizeof(int), corpus->TotalLemmas, out);	

				for(i=0; i<corpus->TotalLemmas; i++)
				{
			       if (Debug)	cout << corpus->FeaturesCounts[i] <<endl;
			       corpus->Words[i].features_count = corpus->FeaturesCounts[i];
				        // corpus->Sorted[i].features_count = corpus->FeaturesCounts[i];				   
				}

		for(i=0; i<TotalLemmas; i++)
		{								    			
					 fread(&len, sizeof(int), 1, out);					 
					 fread(&Buffer, len, 1, out);
					 fread(&index, sizeof(int), 1, out);
					 Buffer[len] = 0;

			if (Debug)
				       cout << i <<": " <<Buffer <<", ";

					 //lemmaMap[Buffer] = i;
			          lemmaMap[Buffer] = index;
					 //fread(corpus->Words[i].corpus_count,  sizeof(Words[i].corpus_count), 1, out);
					 fread(&corpus->Words[i].corpus_count,  sizeof(int), 1, out);

            // corpus->Sorted[i].corpus_count = corpus->Words[i].corpus_count;

			//		 corpus->Words[i].features = new PCHAR[corpus->FeaturesCounts[i]];
			//		 corpus->Words[i].values = new double[corpus->FeaturesCounts[i]];					 					 

					   // <<<
						//valuesIterator = Words[i].valuesMap.begin();					    
					 /*
						for( ; valuesIterator != Words[i].valuesMap.end(); valuesIterator++)
						{ 
							len = strlen(valuesIterator->first.c_str);
							fwrite(len,  sizeof(int), 1, out);
							fwrite(valuesIterator->fist.c_str,  1, len, out);
							fwrite(valuesIterator->second,  sizeof(double), 1, out);
						}
						*/

					 ///*
					     // corpus->Words[i].values = new double[FeaturesCounts[i]];
					     // corpus->Words[i].features = new PCHAR[FeaturesCounts[i]];
					 //*/

					           // corpus->Sorted[i].values = new double[FeaturesCounts[i]];
					           // corpus->Sorted[i].features = new PCHAR[FeaturesCounts[i]];

					 for (j=0; j<corpus->FeaturesCounts[i]; j++)
					 {					  
						if (Debug) cout << j <<endl;

						fread(&len, sizeof(int), 1, out); //Length of the feature
						fread(Buffer, 1, len, out); //Read a feature
						fread(&Value, sizeof(double), 1, out); //Read a feature
						Buffer[len] = 0;
						s.clear();
						s.insert(0, Buffer);
						corpus->Words[i].valuesMap[s] = Value;

					         //#  corpus->Words[i].features[j] = new char[len];

						            // corpus->Sorted[i].features[j] = new char[len];

							//# strcpy(corpus->Words[i].features[j], Buffer);
							//# corpus->Words[i].values[j] = Value;

									//strcpy(corpus->Sorted[i].features[j], Buffer);
									//corpus->Sorted[i].values[j] = Value;
					 }	

				  if (Debug)
					     cout << endl;

					//Counter++;
			     }
				fclose(out);
			
				for(i=0; i<corpus->TotalLemmas; i++)
				{
				  if (Debug) 
					     cout << corpus->FeaturesCounts[i] <<endl;
				  corpus->Words[i].features_count = corpus->FeaturesCounts[i];  //Something overlays the values after they are written above?
				                           //corpus->Sorted[i].features_count = corpus->FeaturesCounts[i];  //Something overlays the values after they are written above?
				}

				if (Debug)                               
					for(i=0; i<corpus->TotalLemmas; i++)
				{
					cout << corpus->Words[i].features_count<<endl;					
				}
			}
							
			void LoadMapSorted(char* fileName, Corpus* corpus)
			{
				int i, j, index;
				int len;				
				int Counter = 0;
				char Buffer[255];
				double Value;
				bool Debug = false;
				string s;

				cout << "lemmamapclear?  " << endl;
				lemmaMap.clear();				

				FILE* out;				
				out = fopen(fileName, "rb");

				int Total, size;
				fread(&corpus->TotalLemmas, sizeof(int), 1, out);				
				
				
				cout << corpus->TotalLemmas;												

				corpus->Sorted = new WordSorted[corpus->TotalLemmas];
				corpus->FeaturesCounts = new int[corpus->TotalLemmas];
															
				size = fread(corpus->FeaturesCounts, sizeof(int), corpus->TotalLemmas, out);	
				
								cout << "size?  " << endl;
                  
        
				for(i=0; i<corpus->TotalLemmas; i++)
				{
			       if (Debug)	cout << corpus->FeaturesCounts[i] << "\t";			       
				        corpus->Sorted[i].features_count = corpus->FeaturesCounts[i];				   
				}

        //Debug = true;

		for(i=0; i<TotalLemmas; i++)
		{								    					
					 fread(&len, sizeof(int), 1, out);					 
					 fread(&Buffer, len, 1, out);
					 fread(&index, sizeof(int), 1, out);
					 Buffer[len] = 0;

			if (Debug)
				       cout <<i <<": " << Buffer <<", ";
					 
			          lemmaMap[Buffer] = index;
			          
             if (Debug)
	       		      cout <<"lemmaMap?, FeaturesCount = " << FeaturesCounts[i];
	       		      
					 fread(&corpus->Sorted[i].corpus_count,  sizeof(int), 1, out);				
					 
		      if (Debug)
	       		      cout <<"fread ->sorted?";

					            corpus->Sorted[i].values = new double[FeaturesCounts[i]];
					            
			  if (Debug)
	       		      cout <<"New Double?";
	       		      
			  if (Debug)
	       		      cout <<"corpus->Sorted[i].features???" << corpus->Sorted[i].features;
	       		      
					            corpus->Sorted[i].features = new PCHAR[FeaturesCounts[i]];
               if (Debug)
	       		      cout <<"New PCHAR?";


                  if (Debug) cout << "(" << FeaturesCounts[i] << ")" <<endl;
                  
					 for (j=0; j<corpus->FeaturesCounts[i]; j++)
					 {					  
						if (Debug) cout << j <<endl;

						fread(&len, sizeof(int), 1, out); //Length of the feature
						fread(Buffer, 1, len, out); //Read a feature
						fread(&Value, sizeof(double), 1, out); //Read a feature
						Buffer[len] = 0;										

					    corpus->Sorted[i].features[j] = new char[len];

						strcpy(corpus->Sorted[i].features[j], Buffer);
						corpus->Sorted[i].values[j] = Value;						
					 }

				  if (Debug)
					     cout << endl;					
			     }
				fclose(out);
			
				for(i=0; i<corpus->TotalLemmas; i++)
				{
				  if (Debug) 
					     cout << corpus->FeaturesCounts[i] <<endl;
				  corpus->Sorted[i].features_count = corpus->FeaturesCounts[i];  //Something overlays the values after they are written above?				                      
				}

				if (Debug)                               
					for(i=0; i<corpus->TotalLemmas; i++)
				{
					cout << corpus->Sorted[i].features_count<<endl;					
				}
			}
			
/*
			WordElement* CreateElement(Word* word, int featureIndex, char* lemma )
			{			 
			  WordElement *NewElement = new WordElement;
		      strcpy(NewElement->word, word->features[featureIndex]);
			  NewElement->index = featureIndex;
		      NewElement->next  = NULL;
			  NewElement->value = word->values[featureIndex];
			  return NewElement;
			  
			}
			
			
		
			/*
		void Normalize(Word* words, int Length)
		{					
				int i,j;
				double swapValue;
				char   swapWord[200];
				for(i=0; i<Length; i++)			

					for(j=0; j<words[i].features_count; j++)
					{
					  printf("\n>>>>>%s (%s) - %f (%f) | %d/%d)", words[i].features[words[i].redirect[j]], words[i].features[j], words[i].values[words[i].redirect[j]], words[i].values[j], j, words[i].features_count);
					  swapValue = words[i].values[words[i].redirect[j]];
					  words[i].values[words[i].redirect[j]] = words[i].values[j];
					  words[i].values[j] = swapValue;					 

					  strcpy(swapWord, words[i].features[words[i].redirect[j]]);
					  strcpy(words[i].features[words[i].redirect[j]], words[i].features[j]);
					  strcpy(words[i].features[j], swapWord);
					  printf("\n<<<<<%s (%s) - %f (%f), %d/%d)", words[i].features[words[i].redirect[j]], words[i].features[j], words[i].values[words[i].redirect[j]], words[i].values[j], j, words[i].features_count);
					}
		}
		*/

/*
		void SortFeatures(Word* words, int Index)
			{				
				bool WasSet = false;
				int i;

				WordElement* Precedent = NULL;
				WordElement* Top = NULL;
				WordElement* FirstElement = NULL;

				Top = CreateElement(words, 0, Lemmas[Index]);
				FirstElement = Top;	
				
				for(i=1; i<words[Index].features_count; i++)
				{										 
				   WasSet = false;
				   Precedent = FirstElement;
				   Top = Precedent;				   
				   
					while (strcmp(words[Index].features[i], Top->word) >= 0)
					  {			

					    if (Top->next!=NULL)
						{
							Precedent = Top;						    
							Top = Top->next;
						}
					    else
						  {
						    WordElement *NewElement = CreateElement(&words[Index], i, Lemmas[Index]); //new WordElement;
							Top->next = NewElement;							
							WasSet = true;
						    break;
						  }
					  }
					  if (!WasSet)
					  {
						 if (Top == FirstElement)
						 {
						  WordElement *NewElement = CreateElement(&words[Index], i, Lemmas[Index]);						  
						  NewElement->next = FirstElement;						  
						  FirstElement = NewElement;					  						
						 }
						 else
						 {
						   WordElement *NewElement = CreateElement(&words[Index], i, Lemmas[Index]);						  
						   NewElement->next = Top;
						   Precedent->next = NewElement;						  
						 }

					  }					  
				}										
						
            Top = FirstElement;
			int Current = 0;
			bool bDebug = false;

			for(;;)
			{	
				if (bDebug)
					      printf("\n%d ---> %d", Current, Top->index);

//				words[Index].redirect[Current] = Top->index;
				//>>>>>>>>>>>>>>>>>>>>
				words[Index].features[Current] = Top->word;
				words[Index].values[Current] = Top->value;			
				//>>>>>>>>>>>>>>>>>>>>
				if (Top->next == NULL) break;
				Top = Top->next;
				Current++;
			}
	}            			

		*/
		
			Word* GetWord(char* lemma)
			{				
				lemmaIterator = lemmaMap.find(lemma);
                if (lemmaIterator != lemmaMap.end() )   // is 0 - 9
				{
					//cout << "FEATURES: " << Words[lemmaIterator->second].features_count <<endl;
					return &Words[lemmaIterator->second];
				}

				else return NULL;				
			}

			WordSorted* GetWordSorted(char* lemma)
			{
				lemmaIterator = lemmaMap.find(lemma);
                if (lemmaIterator != lemmaMap.end() )   // is 0 - 9
				{
					//cout << "FEATURES: " << Words[lemmaIterator->second].features_count <<endl;
					return &Sorted[lemmaIterator->second];
				}
				else return NULL;
			}

			
			void ReadCorpus(char* fileName, bool PrintAll) //void ReadCorpus(char* fileName, PCHAR* lemmas)
            {
				bool DebugRead = false;
				char Feature[100], Token[100], Noun[100];				
				char PreviousWord[100], CurrentWord[100];
				int Frequency=0, WordsCount=0, WordsCounter = 0, i;								

				FILE* fi = fopen(fileName, "rt");

				if (fi==NULL)
				{
					cout << "The file "<< fileName<<" is inaccessible!";
					return;
				}
				
			  ///////////////////////////////////////////////////////
			  // First Pass, reading the number of feature. Pass 1.//
			  //////////////////////////////////////////////////////

				if ( fscanf(fi,"%s%s%d", &Feature, &Token, &Frequency) != EOF)
				{
					strcpy(PreviousWord, Token);
				}else exit(0);
				
			while ( fscanf(fi,"%s%s%d", &Feature, &Token, &Frequency) != EOF)
			{			
				if (strcmp(PreviousWord, Token) != 0) 
				{
					WordsCounter++;
					strcpy(PreviousWord, Token);
				}
				
			 if (DebugRead)
				 printf("\n%d -- %s, %s, %d", WordsCounter, Feature, Token, Frequency);							
			}

			fclose(fi);

			TotalWords = WordsCounter;
		    TotalLemmas = TotalWords;
						
			//Allocations

//			Lemmas = new PCHAR[WordsCounter];

			//Words = new Word[WordsCounter];
			
			//Words = new Word[WordsCounter+1];

			Words = new Word[WordsCounter+1];
			FeaturesCounts = new int[WordsCounter];
			CorpusCounts   = new int[WordsCounter];

			for(i=0; i<WordsCounter; i++)
				FeaturesCounts[i] = 0;

			////////////////////////////////////////////////////////
			//Second Pass - reading the number of features. Pass 2.//
			///////////////////////////////////////////////////////
									
			fi = fopen(fileName, "rt");
			WordsCounter = 0;

			int corpus_count = 0;

			if ( fscanf(fi,"%s%s%d", &Feature, &Token, &Frequency) != EOF)
				{
					strcpy(PreviousWord, Token);
					FeaturesCounts[WordsCounter]++;
					corpus_count=Frequency;
				}else exit(0);

			while ( fscanf(fi,"%s%s%d", &Feature, &Token, &Frequency) != EOF)
			{								
				if (strcmp(PreviousWord, Token) != 0) 
				{				
					CorpusCounts[WordsCounter] = corpus_count;
					WordsCounter++;					
					FeaturesCounts[WordsCounter] = 1;//?????
                    if (DebugRead)
					   printf("\nPrevious features: %d; %d -- %s -- %s", FeaturesCounts[WordsCounter], WordsCounter, Feature, Token);
					strcpy(PreviousWord, Token);

					corpus_count = Frequency;
				}
				else								//Features of the same word
				{				
					FeaturesCounts[WordsCounter]++;
					corpus_count += Frequency;
					//int k = FeaturesCounts[WordsCounter];
				}							           
			}

		    CorpusCounts[WordsCounter] = corpus_count; //Last word
			WordsCounter++;

			fclose(fi);
			printf("WordsCounter = %d", TotalWords);

	  if (DebugRead)
			for (i=0; i<TotalWords; i++)
				printf("\n%d", FeaturesCounts[i]);		
							
			////////////////
			int Values[10000];
			int TopValues = 0;
			int TotalFrequency = 0;
			int featureIndex = 0;
			int Counter = 0;
			int Index   = 0;
			////////////////				

			Counter = 0;
			strcpy(PreviousWord," ");
			
			///////////////////////////////////////////////////////////////////
			// Third Pass - reading corpus data into the structures. Pass 3. //
			//////////////////////////////////////////////////////////////////

			bool useMap = true;
			bool useFeaturesMap = true;

	//		Words[Counter].features = new PCHAR[FeaturesCounts[0]];						
						
			string sFeature, sToken;

			ifstream fs(fileName, ios::in);            
			fs >> sFeature;
			fs >> sToken;
			fs >> Frequency;
			
			if (!fs.eof())
			{
				if (useMap)
				{			  	            
				    lemmaMap[sToken] = 0;   //(STRING2INT::value_type(Token, 0));  // lemmaMap.insert(STRING2INT::value_type(Token, 0));
				}				 

				 strcpy(Feature, sFeature.c_str());
				 strcpy(Token, sToken.c_str());				
				 featureIndex = 0;				 

				 if (useFeaturesMap)
				 {
				  Words[Counter].valuesMap[sFeature] = (double) Frequency/(double)CorpusCounts[Counter];
				 }
				
				   strcpy(PreviousWord, Token);
				   
				   //Allocate memory for the Features list				   
				   				   
		//		   Words[Counter].features[featureIndex] = new char[strlen(Feature)];
		//		   strcpy(Words[Counter].features[featureIndex], Feature);				  
				   featureIndex++;
				   Values[0] = Frequency;
				   TopValues = 1;		
				   
			}
	       else return;
							
		   char newLine[20];
		   
			while ( fscanf(fi,"%s%s%d", &Feature, &Token, &Frequency) != EOF)			
			{											
			   if (Counter % 1000 == 0) printf("%d, ", Counter);
							
			   if (DebugRead)
				    printf("\n%d - %s - %s - %d", Counter, Feature, Token, FeaturesCounts[Counter]);

				if (strcmp(PreviousWord, Token) == 0)
				{					

					 if (useFeaturesMap)
					 {
						sFeature.clear();
						sFeature.insert(0, Feature);
						if (DebugRead)
						      printf("\n%d: %s -- %s", Counter, Feature, sFeature.c_str());
						Words[Counter].valuesMap[sFeature] = (double) Frequency/(double)CorpusCounts[Counter];
						if (DebugRead)
						      printf("\n%d: %s -- %s ( %f )", Counter, Feature, sFeature.c_str(), (double) Frequency/(double)FeaturesCounts[Counter]);
					}

					 int L = FeaturesCounts[Counter];
			//	     Words[Counter].features[featureIndex] = new char[strlen(Feature)];
			//	     strcpy(Words[Counter].features[featureIndex], Feature); 
				     featureIndex++;
				     Values[TopValues++] = Frequency;						     					 
				}		
				else
				   //if (strcmp(PreviousWord, Token) != 0) //A new word
				   {
					   	if (useMap)
					{				 
					    //lemmaMap.insert(STRING2INT::value_type(Token, 0));
						sToken.clear();
						sToken.insert(0, PreviousWord);						
						lemmaMap[sToken] = Counter;						
					}				 

					strcpy(PreviousWord, Token);

                    TopValues = FeaturesCounts[Counter];
					TotalFrequency = 0;
					
					//Words[Counter].values   = new double[TopValues];
					//Words[Counter].redirect = new    int[TopValues];										
					
				 if (DebugRead)
					printf("\n%d -- Frequency: %d", Counter, TotalFrequency);
				
				   for(i=0; i<TopValues;i++)
						TotalFrequency += Values[i];
					/*	
					for(i=0; i<TopValues;i++)
					{						
						Words[Counter].values[i] = (double)Values[i]/(double)TotalFrequency;							
					}
					*/

					Words[Counter].features_count = TopValues;
					Words[Counter].corpus_count = TotalFrequency;


//				if (DebugRead)
	//				printf("\nTotal Frequency = %d, Frequency[0] == %f", TotalFrequency, Words[Counter].values[0]);
							   
					Counter++;
					 if ( (Counter % 1000) == 0)
				   {
					cout <<Counter;
				   }

					//For this element
					 if (useFeaturesMap)
					 {
						sFeature.clear();
						sFeature.insert(0, Feature);						
						Words[Counter].valuesMap[sFeature] = (double) Frequency/(double)CorpusCounts[Counter];
	//					if (DebugRead) 
		//					printf("\n%d: %s -- %s ( %f )", Counter, Feature, sFeature.c_str(), (double) Frequency/(double)FeaturesCounts[Counter]);
					 }
					 
				   				   
				//   Words[Counter].features = new PCHAR[FeaturesCounts[Counter]];
				  
				   featureIndex = 0;
				//   Words[Counter].features[featureIndex] = new char[strlen(Feature)];
				//   strcpy(Words[Counter].features[featureIndex], Feature); 				   
				   featureIndex++;
				   Values[0] = Frequency;
				   TopValues = 1;
				    
				} //if Previous Word is the same like the Current One > 0		
																								             
			}
			
			 /////////////////////////////////////////
			 //  Storing data for the last word     //
			 ////////////////////////////////////////
			{
			       //Lemmas[Counter] = new char[strlen(Token)];
				   //strcpy(Lemmas[Counter], PreviousWord);												

					if (useMap)
					{				 
					     // lemmaMap.insert(STRING2INT::value_type(Token, 0));
						sToken.clear();
						sToken.insert(0, Token);
						lemmaMap[sToken] = Counter;
					}		

					strcpy(PreviousWord, Token);

					//Allocate memory for the values
                    TopValues = FeaturesCounts[Counter];
					TotalFrequency = 0;

            //		Words[Counter].values   = new double[TopValues];
			//		Words[Counter].redirect = new    int[TopValues];					
					
					for(i=0; i<TopValues;i++)
						TotalFrequency += Values[i];

//				 if (DebugRead)
	//				printf("\n%d -- Frequency: %d", Counter, TotalFrequency);

				 if (DebugRead)
					printf("\n%d", TotalFrequency);
				 /*
					for(i=0; i<TopValues;i++)
					{						
						Words[Counter].values[i] = (double)Values[i]/(double)TotalFrequency;						
					}
                */

					Words[Counter].features_count = TopValues;

	//			if (DebugRead)
//					printf("\nTotal Frequency = %d, Frequency[0] == %f", TotalFrequency, Words[Counter].values[0]);

					Words[Counter].corpus_count = TotalFrequency;
			}

			fclose(fi);		

   /*
			PrintAll = false;

		if (PrintAll)
		{
			float Total;
			int wordI, featureJ;
			
			for(wordI=0; wordI<TotalWords; wordI++)			
			{
			if (DebugRead)
			  printf("\n%d - %s", wordI, Lemmas[wordI]);
			  Total = 0;
			    for(featureJ=0; featureJ < Words[wordI].features_count; featureJ++)
				{
					Total+=Words[wordI].values[featureJ];
				 if (DebugRead)
					printf("\n%s - %f (%f, %d/%d)", Words[wordI].features[featureJ], Words[wordI].values[featureJ], Total, featureJ, Words[wordI].features_count);					
				}
			}
		}		  			 
     */
   }


   /*
    void PrintCorpus(bool Redirect)
	{			
			float Total;
			int wordI, featureJ;			
			
			for(wordI=0; wordI<TotalLemmas; wordI++)
			{
			  printf("\n%d - %s", wordI, Lemmas[wordI]);
			  Total = 0;
			    for(featureJ=0; featureJ < Words[wordI].features_count; featureJ++)
				{
					if (!Redirect) Total+=Words[wordI].values[featureJ];
					//   else  Total+=Words[wordI].values[Words[wordI].redirect[featureJ]];

					//Words[wordI].features[Words[wordI].redirect[featureJ]], Words[wordI].features[featureJ], Words[wordI].values[Words[wordI].redirect[featureJ]];
					if (!Redirect) printf("\n%s - %f (%f, %d/%d)", Words[wordI].features[featureJ], Words[wordI].values[featureJ], Total, featureJ, Words[wordI].features_count);
					  //else					
					  // printf("\n%s (%s) - %f (%f) | %f, %d/%d)", Words[wordI].features[Words[wordI].redirect[featureJ]], Words[wordI].features[featureJ], Words[wordI].values[Words[wordI].redirect[featureJ]], Words[wordI].values[featureJ], Total, featureJ, Words[wordI].features_count);					   
										
				//	if (Total>0.97)
			//		{
			//			printf("");
			//		}
					
				}
		   }		   		
	}
 

	void PrintWords(char* outFile)
	{
	  FILE* fo = fopen(outFile, "wt");
	  //for(int i=0; i<this->

	  int i = 0;
	  this->lemmaIterator = this->lemmaMap.begin();
	  for(; this->lemmaIterator != this->lemmaMap.end(); this->lemmaIterator++)
	   {
		   

		   //if (this->lemmaIterator->first.length > 0)
		   // != NULL)
		   /*
		   if (this->lemmaIterator != NULL) // != NULL)
			   if (this->lemmaIterator->first.length > 0)
		           printf("\n%d - %s", i, this->lemmaIterator->first);
				   */ //?
			   //*/
		   //printf("\n%d - %s", i, Lemmas[i]);
   /*
		  i++;
	   }

	   fclose(fo);
	}
	*/
};



  void InputSequence(Corpus* corpus)
 {  	  
	  STRING2DBL::iterator vIterator;	  
	  char Inp[200];
	  strcpy(Inp, " ");

   while(strcmp(Inp,"q") != 0)
   {
     cout << "Enter a word..." << endl;
	 cin >> Inp;
	 
     Word* Out = corpus->GetWord(Inp);

	    if (Out!=NULL)
     {
	  cout << endl << "!!!!" << endl;	   
	  cout << "Occurences:" << Out->corpus_count <<endl;	   

	    int j = 0;
		double total = 0;
	    //corpus->lemmaIterator = corpus->lemmaMap.begin;
        //while (corpus->lemmaIterator != corpus->lemmaMap.end() )   // is 0 - 9

		vIterator = Out->valuesMap.begin();
		while(vIterator != Out->valuesMap.end())
		{		 			
		  //cout << j << " : "<< corpus->lemmaIterator->first.c_str() << corpus->lemmaIterator->second << endl;  //   Out->features[j] <<" ("<<Out->values[j]<<"); ";
			total += vIterator->second;
			cout << j << " : "<< vIterator->first.c_str() <<"  "<< vIterator->second << "("<< total <<")"<< endl;  //   Out->features[j] <<" ("<<Out->values[j]<<"); ";
			
		  j++;
		  vIterator++;
		}

	  /*
	  for(int j=0; j<Out->features_count; j++)
         cout << j << " - "<< Out->features[j] <<" ("<<Out->values[j]<<"); ";
		 */

     }
	 else
		cout << ">>" << Inp << "<< NOT FOUND!"<< endl;
     }
  }


  void InputSequenceSorted(Corpus* corpus)
 {  
	  double total = 0;
	  char Inp[200];
	  strcpy(Inp, " ");

   while(strcmp(Inp,"q") != 0)
   {
     cout << "Enter a word..." << endl;
	 cin >> Inp;

     WordSorted* Out = corpus->GetWordSorted(Inp);

	    if (Out!=NULL)
     {
	  cout << endl << "!!!!" << endl;	   
	  cout << "Occurences:" << Out->corpus_count <<endl;	   

	  for(int j=0; j<Out->features_count; j++)
	     {
		  total += Out->values[j];
          cout << j << " - "<< Out->features[j] <<"  " << Out->values[j]<< " (" << total << ") " << endl;
		 }
     }
	 else
		cout << ">>" << Inp << "<< NOT FOUND!"<< endl;
     }
  }

 void Demo()
 {
	int i;
    char input[250];
         strcpy(input, "test.txt");
		 strcpy(input, "ap.txt");
		 strcpy(input, "ap-s.txt");

//		 Corpus corpus(input);
		 Corpus corpus("");
		 printf("Select:\n 1. Read from text format and Save to binary\n 3. Load from map to map for feature->value \n 4. Load from map to sorted arrays (fast)");
		 scanf("%d", &i);
		 if (i==1)
		 {
			printf("Enter path to the corpus in text format...");
			scanf("%s", input);
			//Corpus corpus(input);
			corpus.ReadCorpus(input, false);

			/*
		       for(i=0; i<corpus.TotalLemmas; i++)
		           corpus.SortFeatures(&corpus.Words[i], 0);
		    */

		   char output[200];
		   strcpy(output, input);
		   strcat(output, ".dat");
//		   corpus.Save(output);

		   strcat(output, ".map");
		   corpus.SaveMap(output);
		 }		 
		 else if (i==3)
		 {
			 	printf("Enter path to the corpus for map...");

				scanf("%s", input);

				corpus.LoadMap(input, &corpus);
				//corpus.LoadMapSorted(input, &corpus);
				InputSequence(&corpus);
				return;
		 }
		 else if (i==4)
		 {
			 	printf("Enter path to the corpus for map...");
				scanf("%s", input);				
				                   // strcpy(input, "F:\\wolver\\similarity\\ap-sbig.map");
				corpus.LoadMapSorted(input, &corpus);
				InputSequenceSorted(&corpus);
				return;
		 }

			
 }

int main(int argc, char *argv[])
{
	 Demo();

    return EXIT_SUCCESS;
}
