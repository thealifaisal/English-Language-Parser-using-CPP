#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Queue.h"

using namespace std;

/*
	-------------------------------- CFG 'GRAMMAR RULES' ---------------------------------
	
	S --> NP VP
	
	NP --> Pronoun | Proper-Noun | Determiner NOMINAL
	
	NOMINAL --> Noun NOMINAL | Noun
	
	VP --> Verb | Verb NP | Verb NP PP | Verb PP
	
	PP --> Preposition NP
	
*/

// Non-Terminal Funcion Prototypes
int S(string sen, Queue<string> &q, Queue<string> &out);
int NP(string sen, Queue<string> &q, Queue<string> &out);
int VP(string sen, Queue<string> &q, Queue<string> &out);
int PP(string sen, Queue<string> &q, Queue<string> &out);
int NOMINAL(string sen, Queue<string> &q, Queue<string> &out);

// utility functions
void pushWordsToQueue(string sen, Queue<string> &q);

// global variables
string _s = "S", _np = "NP", _vp = "VP", _nom = "NOM", _pp = "PP"; // Non-Terminals
string _det = "Det", _pron = "ProN", _prop = "ProP", _verb = "Verb", _prep = "PreP", _noun = "Noun"; // Terminals

// main
int main()
{
	Queue<string> q;
	Queue<string> out;
	
	string sen;
	
	cout<<"Input Sentence: ";
	getline(cin, sen);
	
//	sen = "the man read a book.";
//	cout<<"Input Sentence: "<<sen;
	
	cout<<"\n\n";
	
	if(!sen.length())
	{
		cout<<"\nInvalid Sentence.\n";
		return 0;
	}
	
	pushWordsToQueue(sen, q);
	
	if(!S(sen, q, out))
	{
		cout<<"\nInvalid Sentence.\n";
	}
	else
	{
		cout<<"\nValid Sentence.\n\n";
		
//		out.displayQ();
	}
	
	return 0;
}

int S(string sen, Queue<string> &q, Queue<string> &out)
{
//	S --> NP VP

//	out.enQueue(_s);
//	
//	out.enQueue(_np + "\t" +_vp);
	
	if(NP(sen, q, out))
	{	
		return VP(sen, q, out);
	}
	else
	{
		return 0;
	}
	
}

int NP(string sen, Queue<string> &q, Queue<string> &out)
{
//	NP --> Pronoun | Proper-Noun | Determiner NOMINAL
	
	if(q.emptyQ())
	{
		return 0;
	}
	
	ifstream inFile1, inFile2, inFile3;
	
	inFile1.open("Pronouns.txt", ios::in);
	inFile2.open("Proper-Nouns.txt", ios::in);
	inFile3.open("Determiners.txt", ios::in);
	
	string wordI = q.peekQ() , wordF;
	
	while(inFile1 >> wordF)
	{
		if(wordF == wordI)
		{
//			out.enQueue(_pron + "\t" + _vp);
//			out.enQueue(wordI + "\t" +_vp);
			
			q.deQueue();
			return 1;
		}
	}
	
	while(inFile2 >> wordF)
	{
		if(wordF == wordI)
		{
//			out.enQueue(_prop + "\t" + _vp);
//			out.enQueue(wordI + "\t" +_vp);
			
			q.deQueue();
			return 1;
		}
	}
	
	while(inFile3 >> wordF)
	{
		if(wordF == wordI)
		{
//			out.enQueue(_det + "\t" + _nom + "\t" + _vp);
//			
//			_det = wordI;
//			
//			out.enQueue(_det + "\t" + _nom + "\t" +_vp);
			
			q.deQueue();
			return NOMINAL(sen, q, out);
		}
	}
}

int VP(string sen, Queue<string> &q, Queue<string> &out)
{
//	VP --> Verb | Verb NP | Verb NP PP | Verb PP
	
	if(q.emptyQ())
	{
		return 0;
	}
	
	ifstream inFile1;
	
	inFile1.open("Verbs.txt", ios::in);
	
	string wordI = q.peekQ() , wordF;
	bool checkV = 0;
	
	while(inFile1 >> wordF)
	{
		if(wordF == wordI)
		{
			q.deQueue();
			checkV = 1;
			break;
		}
	}
	
	if(!checkV)
	{
		return 0;
	}
	
	// AT THIS POINT THERE IS A VERB
	
	if(NP(sen, q, out))
	{
		if (q.emptyQ())
		{
//			out.enQueue(_det + "\t" + _nom + "\t" + _verb + "\t" + _np);
//			
//			_verb = wordI;
//			
//			out.enQueue(_det + "\t" + _nom + "\t" + _verb + "\t" + _np);
			
			return 1;
		}
		else
		{
//			out.enQueue(_det + "\t" + _nom + "\t" + _verb + "\t" + _np + "\t" + _pp);
//			
//			_verb = wordI;
//			
//			out.enQueue(_det + "\t" + _nom + "\t" + _verb + "\t" + _np + "\t" + _pp);
			
			return  PP(sen, q, out);
		}
		 
		return 1;
	}
	
	
	if(PP(sen, q, out))
	{
//		out.enQueue(_det + "\t" + _nom + "\t" + _verb + "\t" + _pp);
//			
//		_verb = wordI;
//			
//		out.enQueue(_det + "\t" + _nom + "\t" + _verb + "\t" + _pp);
		
		return 1;
	}
	
//	out.enQueue(_det + "\t" + _nom + "\t" + _verb);
//			
//	_verb = wordI;
//			
//	out.enQueue(_det + "\t" + _nom + "\t" + _verb);
	
	return 1;
}

int PP(string sen, Queue<string> &q, Queue<string> &out)
{
//	PP --> Preposition NP
	
	if(q.emptyQ())
	{
		return 0;
	}
	
	ifstream inFile1;
	
	inFile1.open("Prepositions.txt", ios::in);
	
	string wordI = q.peekQ() , wordF;
	bool checkP = 0;
	
	while(inFile1 >> wordF)
	{
		if(wordF == wordI)
		{
//			out.enQueue(_det + "\t" + _nom + "\t" + _verb + "\t" + _np);
//			
//			_verb = wordI;
//			
//			out.enQueue(_det + "\t" + _nom + "\t" + _verb + "\t" + _np);
			
			q.deQueue();
			checkP = 1;
			break;
		}
	}
	
	if(!checkP)
	{
		return 0;
	}
	else
	{
		return NP(sen, q, out);
	}
}

int NOMINAL(string sen, Queue<string> &q, Queue<string> &out)
{
//	NOMINAL --> Noun NOMINAL | Noun
	
	if(q.emptyQ())
	{
		return 0;
	}
		
	ifstream inFile1;
	
	inFile1.open("Nouns.txt", ios::in);
	
	string wordI = q.peekQ() , wordF;
	bool checkN = 0;
	
	while(inFile1 >> wordF)
	{
		if(wordF == wordI)
		{
			_nom = wordI;
			
//			out.enQueue(_det + "\t" + _nom + "\t" +_vp);
			
			q.deQueue();
			checkN = 1;
			break;
		}
	}
	
	if(!checkN)
	{
		return 0;
	}
	else
	{
		NOMINAL(sen, q, out);
		return 1;
	}
}

// utlity functions
void pushWordsToQueue(string sen, Queue<string> &q)
{
	int i = 0;
	string words;
		
	while(i != sen.length())
	{
		if(sen[i] == ' ' || sen[i] == '.' || sen[i] == '!' || sen[i] == '?')
		{
			q.enQueue(words);
			words.clear();
		}
		else
		{
			words = words + sen[i];
		}
		
		i++;
	}
}
