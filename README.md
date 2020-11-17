# Similarity-NLP-Corpus-CPP

### Ported to C++ by Todor Arnaudov from a project in Python by Viktor Pekar in 2007.
## Similarity

Important:

   
  Developed for Visual Studio 2003+
  Remove "include stdafx.h" for use with other IDEs.
 
       
 -- DevC++ 4.990 produces unknown zero-pointer error in LoadMapSorted()
    I couldn't find a reason, though, and an executable, compiled with Visual Studio 2003 works fine.

Under Cygwin, the program seems to crash here:

```c++
void  LoadMapSorted(
       ...
 
      if (Debug)
                         cout <<"corpus->Sorted[i].features???" << corpus->Sorted[i].features;
                        
----->>>>>  corpus->Sorted[i].features = new PCHAR[FeaturesCounts[i]]; <<<<<<<<------
               if (Debug)
                         cout <<"New PCHAR?";
```

However, Sorted[] is properly allocated and "i" is counted the normal way - no undefined values. It's proven by the fact it runs under other compiler.


  Main Structures:

```c++
  struct Word
 { 
   int    features_count;
   int    corpus_count; 
   STRING2DBL valuesMap;
 };
  
  //Faster reading
  struct WordSorted
 { 
   int    features_count;
   int    corpus_count;
   PCHAR*  features;
   double*   values;  
 };

 class Corpus
 {
 ...
 }
```

  Use:


**Reading is designed for the format of the given example corpus:**

```c++
acknowledge ability    1
acquire ability    1
claim abuse    2
combat abuse    10
commit abuse    2
conceal abuse    2
wasn't boy    1
watch boy    1
whip boy    1

feature1 LEMMA1 frequency1
feature2 LEMMA1 frequency2
feature3 LEMMA1 frequency3
...

featureN LEMMA1 frequencyN
feature1 LEMMA2 frequency1
feature2 LEMMA2 frequency2
...
```


1. One run to convert a corpus:

```c++
       Corpus corpus("");
       corpus.ReadCorpus("corp.txt");
       corpus.SaveMap("output.map");
```

2. Then the data could be read in one of the two structures:

A) Word
 
   Each lemma has a map for features and values:

```c++
 Corpus corpus("");
 corpus.LoadMap("output.dat");          
 Word word = corpus.GetWord("lemma");
```
  
B) WordSorted

   Features and values are stored in sorted arrays (sorted while preparing the binary file), aligned by their index.

   If the program is compiled as a release version with VS2003, at my machine an 11 MB test corpus seems to load for about 1.2 sec, compared to 1.7 sec for the structure with feature-values maps.

```c++
   Corpus corpus("");
   corpus.LoadMapSorted("output.map");
   WordSorted wordS = corpus.GetWordSorted("lemma");
```
...

```c++
  Demo
  InputSequence
  InputSequenceSorted
```

- Demonstrate uses ot the Corpus class

   **Suggestions:**

   The format could be optimized for space, if the lengths of the strings are limited to 255 or so characters, and the
lengths are not stored in int, but in unsigned char or short int.

   There are examples, commented in the code, like:

```c++
  //lenByte = (unsigned char) strlen((*lemmaIterator).first.c_str()); ...
```
   ...

* It's a good idea disposer functions to be developed.
* Debug outputs with flags could be removed, as well as commented code, but some fragments may be useful for test output or for something else.
* There are redundant variables, a compilation with VS will indicate them.

............


* Other notes

 ...**"the core functionality":**

-- Reading corpus in a text format, building target data structures.
-- Access to the structure by a lemma.
-- Saving the structures in a binary format.
-- Loading data structures from a binary file.

This is the main structure:

```c++
 typedef char* PCHAR;

 struct Word
 { 
   int    features_count;
   int    corpus_count;
   PCHAR*  features;
   double*   values;
   int*    redirect;          //debug variable
 };
```

An array of words is encapsulated in a class.

The function for getting the data structure for a given lemma is:

```c++
Word* GetWord(char* lemma)
            {
                lemmaIterator = lemmaMap.find(lemma);
                if (lemmaIterator != lemmaMap.end() )
                     return &Words[lemmaIterator->second];
                else return NULL;
              }
```

*** 

I did implement storing and accessing the features and values by a map, but I am not sure about the performance differences in bad cases (i.e. reverse sorted or that really need a sort).

However, the process of dynamically building a map from the binary file appears to be very slow - the 10 MB corpus loads in about 20 sec(!), compared to just about 2-3 sec without building a map. Access time is the same, since both implementations use a map for the lemmas.

If we presume map is faster in sorting bad cases than my list, I  think a good idea is two data structures to be used, instead of just one:

1. The first structure would consist of a feature-to-value map, and will be used when reading a corpus in text format. This structure will be used for the creation of the binary file.

2. The second structure will have features and values in simple dynamically allocated arrays, which will be created and filled with data from an already sorted binary file. That way the indexes of features and values will be aligned, like they are in my non-features-map implementation.
