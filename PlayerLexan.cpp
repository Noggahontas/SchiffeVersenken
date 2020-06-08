#include "Ship.h"
#include "Player.h"

#include <stdio.h>
#include "stdafx.h"
#include <iostream>
#pragma warning(disable:4786)
#include <string>
#include <map>
using namespace std;

#define	Getc(s)			getc(s)
#define	Ungetc(c)		ungetc(c,IP_Input)


/*
 *	Lexical analyzer states.
 */
enum lexstate { L_START, L_INT, L_IDENT };

const int IDENTIFIER = 4;
const int INTEGER1 = 5;
const int TOKENSTART = 300;

class CParser
{
public:

	string yytext;								//input buffer
	struct tyylval {							//value return
		string s;								//structure
		int i;
	}yylval;
	FILE* IP_Input;								//Input File
	FILE* IP_Error;								//Error Output
	FILE* IP_List;								//List Output
	int  IP_LineNumber;							//Line counter
	map<string, int> IP_Token_table;			//Tokendefinitions
	map<int, string> IP_revToken_table;			//reverse Tokendefinitions


	int CParser::yylex();								//lexial analyser
	void CParser::yyerror(char* ers);					//error reporter
	int CParser::IP_MatchToken(string& tok);				//checks the token
	void CParser::InitParse(FILE* inp, FILE* err, FILE* lst);
	int	CParser::yyparse(Player *iptat);					//parser
	void CParser::pr_tokentable();						//test output for tokens
	void CParser::IP_init_token_table();					//loads the tokens
	void CParser::Load_tokenentry(string str, int index);//load one token
	CParser::CParser() { IP_LineNumber = 1; };			//Constructor
};
//------------------------------------------------------------------------

void CParser::Load_tokenentry(string str, int index)
{
	IP_Token_table[str] = index;
	IP_revToken_table[index] = str;
}
void CParser::IP_init_token_table()
{
	Load_tokenentry("IDENTIFIER", 4);
	Load_tokenentry("INTEGER1", 5);

	int ii = TOKENSTART;
	Load_tokenentry("AND", ii++);
	Load_tokenentry("OR", ii++);
	Load_tokenentry("Begin", ii++);
	Load_tokenentry("End", ii++);
}
//------------------------------------------------------------------------

void CParser::pr_tokentable()
{

	typedef map<string, int>::const_iterator CI;
	const char* buf;

	printf("Symbol Table ---------------------------------------------\n");

	for (CI p = IP_Token_table.begin(); p != IP_Token_table.end(); ++p) {
		buf = p->first.c_str();
		printf(" key:%s", buf);
		printf(" val:%d\n", p->second);;
	}
}
//------------------------------------------------------------------------

int	CParser::yyparse(Player *iptat)
{
	// static int x;
	// static int y;
	bool nr = 0;
	bool ident = 0;
	int ShipNo = 0;

	int tok;
	/*
	*	Go parse things!
	*/
	while ((tok = yylex()) != 0) {
		if (tok == INTEGER1)

			if (nr == 0)
			{
				iptat->Ships[ShipNo].StartPos.x = yylval.i;			
				//x = yylval.i; printf("x = %d, ", yylval.i);
				nr = 1;
			}
			else
			{
				iptat->Ships[ShipNo].StartPos.y = yylval.i;
				//y = yylval.i; printf("y = %d, ",  yylval.i);
				nr = 0;
			}

		else
			if (tok == IDENTIFIER)
				if (ident == 0)
				{
					//printf("Schiff: %s, ", yylval.s.c_str());			// Ausgabe zur Kontrolle
					ident = 1;
					
					if (yylval.s == "Battleship")
					{
						iptat->Ships[ShipNo].Length = 5;
					}
					else if (yylval.s == "Cruiser")
					{
						ShipNo += 1;
						iptat->Ships[ShipNo].Length = 4;
					}
					else if (yylval.s == "Destroyer")
					{
						ShipNo += 1;
						iptat->Ships[ShipNo].Length = 3;
					}
					else if (yylval.s == "Submarine")
					{
						ShipNo += 1;
						iptat->Ships[ShipNo].Length = 2;
					}


				}
				else
				{
					//printf("Richtung: %s ", /*IP_revToken_table[tok].c_str(),*/ yylval.s.c_str());		// Ausgabe zur Kontrolle
					ident = 0;
					if (yylval.s == "RIGHT")
					{
						iptat->Ships[ShipNo].Orientation = Direction::Right;
					}
					else if (yylval.s == "DOWN")
					{
						iptat->Ships[ShipNo].Orientation = Direction::Down;
					}
					//printf("\n");
				}

			else
				if (tok >= TOKENSTART)
					printf("a: %s ", IP_revToken_table[tok].c_str());
				else ;
				//printf("Seperator: %c ",tok);
		//printf("\n");
	}
	return 0;

}
//------------------------------------------------------------------------

/*
 *	Parse Initfile:
 *
 *	  This builds the context tree and then calls the real parser.
 *	It is passed two file streams, the first is where the input comes
 *	from; the second is where error messages get printed.
 */
void CParser::InitParse(FILE* inp, FILE* err, FILE* lst)

{

	/*
	*	Set up the file state to something useful.
	*/
	IP_Input = inp;
	IP_Error = err;
	IP_List = lst;

	IP_LineNumber = 1;
	/*
	*	Define both the enabled token and keyword strings.
	*/
	IP_init_token_table();
}
//------------------------------------------------------------------------

/*
 *	yyerror:
 *
 *	  Standard error reporter, it prints out the passed string
 *	preceeded by the current filename and line number.
 */
void CParser::yyerror(char* ers)

{
	fprintf(IP_Error, "line %d: %s\n", IP_LineNumber, ers);
}
//------------------------------------------------------------------------

int CParser::IP_MatchToken(string& tok)
{
	int retval;
	if (IP_Token_table.find(tok) != IP_Token_table.end()) {
		retval = (IP_Token_table[tok]);
	}
	else {
		retval = (0);
	}
	return retval;
}

//------------------------------------------------------------------------

/*
 *	yylex:
 *
 */
int CParser::yylex()
{
	//Locals
	int c;
	lexstate s;
	/*
	*	Keep on sucking up characters until we find something which
	*	explicitly forces us out of this function.
	*/
	for (s = L_START, yytext = ""; 1;) {
		c = Getc(IP_Input);
		yytext = yytext + (char)c;
		switch (s) {
			//Starting state, look for something resembling a token.
		case L_START:
			if (isdigit(c)) {
				s = L_INT;
			}
			else if (isalpha(c)) {
				s = L_IDENT;
			}
			else if (isspace(c)) {
				if (c == '\n') {
					IP_LineNumber += 1;
				}
				yytext = "";
			}
			else if (c == EOF) {
				return ('\0');
			}
			else {
				return (c);
			}
			break;

			/*
			 *	Suck up the integer digits.
			 */
		case L_INT:
			if (isdigit(c)) {
				break;
			}
			else {
				Ungetc(c);
				yylval.s = yytext.substr(0, yytext.size() - 1);
				yylval.i = atoi(yylval.s.c_str());
				return (INTEGER1);
			}
			break;

			/*
			 *	Grab an identifier, see if the current context enables
			 *	it with a specific token value.
			 */

		case L_IDENT:
			if (isalpha(c) || isdigit(c) || c == '_')
				break;
			Ungetc(c);
			yytext = yytext.substr(0, yytext.size() - 1);
			yylval.s = yytext;
			if (c = IP_MatchToken(yytext)) {
				return (c);
			}
			else {
				return (IDENTIFIER);
			}

		default: printf("***Fatal Error*** Wrong case label in yylex\n");
		}
	}
}
//------------------------------------------------------------------------

/*
void Player::lex(string FileName)
{
	FILE* inputFile;														// File-Ptr für die Schiffspositionsdateien
	char inputFileName[20];													// Name der Datei als char-Array (aus Parameter)
	strncpy_s(inputFileName, FileName.c_str(), sizeof(inputFileName));		// string in char-Array kopieren


	fopen_s(&inputFile, inputFileName, "r");

	if (inputFile == NULL) {
		cout << "Cannot open input file" << FileName << endl;
		return;
	}
	cout << "Open: " << inputFileName << endl;

	CParser obj;
	obj.InitParse(inputFile, stderr, stdout);
	obj.yyparse(this);


	return;
}
*/

