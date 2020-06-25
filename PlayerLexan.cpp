#include "Ship.h"
#include "Player.h"

#include <stdio.h>
#include "stdafx.h"
#include <iostream>
#pragma warning(disable:4786)
#include <string>
#include <map>
using namespace std;
#include "PlayerLexan.h"

#define	Getc(s)			getc(s)
#define	Ungetc(c)		ungetc(c,IP_Input)


/*
 *	Lexical analyzer states.
 */
enum lexstate { L_START, L_INT, L_IDENT };

const int ERROR1 = 2;
const int IDENTIFIER = 4;
const int INTEGER1 = 5;
const int TOKENSTART = 305;
const int Orientation = 400;

//class CParser
//{
//public:
//
//	string yytext;												//input buffer
//	struct tyylval {											//value return
//		string s;												//structure
//		int i;
//	}yylval;
//	FILE* IP_Input;												//Input File
//	FILE* IP_Error;												//Error Output
//	FILE* IP_List;												//List Output
//	int  IP_LineNumber;											//Line counter
//	map<string, int> IP_Token_table;							//Tokendefinitions
//	map<int, string> IP_revToken_table;							//reverse Tokendefinitions
//
//
//	int CParser::yylex();										//lexial analyser
//	void CParser::yyerror(char* ers);							//error reporter
//	int CParser::IP_MatchToken(string& tok);					//checks the token
//	void CParser::InitParse(FILE* inp, FILE* err, FILE* lst);
//	int	CParser::yyparse(Player *iptat);						//parser
//	void CParser::pr_tokentable();								//test output for tokens
//	void CParser::IP_init_token_table();						//loads the tokens
//	void CParser::Load_tokenentry(string str, int index);		//load one token
//	CParser::CParser() { IP_LineNumber = 1; };					//Constructor
//};
//------------------------------------------------------------------------

void CParser::Load_tokenentry(string str, int index)
{
	IP_Token_table[str] = index;
	IP_revToken_table[index] = str;
}
void CParser::IP_init_token_table()
{
	Load_tokenentry("RIGHT", 400);	Load_tokenentry("right", 400);	Load_tokenentry("Right", 400);
	Load_tokenentry("DOWN", 401);	Load_tokenentry("down", 401);	Load_tokenentry("Down", 401);

	int ii = TOKENSTART;

	Load_tokenentry("Battleship", ii);	Load_tokenentry("battleship", ii);	Load_tokenentry("BATTLESHIP", ii);	ii--;
	Load_tokenentry("Cruiser", ii);		Load_tokenentry("cruiser", ii);		Load_tokenentry("CRUISER", ii);		ii--;
	Load_tokenentry("Destroyer", ii);	Load_tokenentry("destroyer", ii);	Load_tokenentry("DESTROYER", ii);	ii--;
	Load_tokenentry("Submarine", ii);	Load_tokenentry("submarine", ii);	Load_tokenentry("SUBMARINE", ii);	ii--;
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

int	CParser::yyparse(Player *iptat)								// Bekommt als Parameter den Pointer auf das Objekt in dem Lexan aufgerufen wird
{

	int tok = 0;
	bool alt = true;											// alternieren zwischen x- und y-Positionswert
	int ShipNo = 0;												// Schiffsnummerierung
	int BattleshipCounter = 0, CruiserCounter = 0, DestroyerCounter = 0, SubmarineCounter = 0; // Zähler für die Schiffsarten
	/*
	*	Go parse things!
	*/
	while ((tok = yylex()) != 0) {
		if (tok == ERROR1)
		{
			printf("\nFehler beim Eingabeformat der Datei. Auf Gross- und Kleinschreibung sowie die richtige Wortwahl achten! \n\n\n"); return -1;

		}
		else
			if (tok == INTEGER1)
			{
				switch (alt)
				{
				case true: iptat->Ships[ShipNo].StartPos.x = yylval.i; alt = 0; break;
				case false: iptat->Ships[ShipNo].StartPos.y = yylval.i;	 alt = 1; break;
				default: printf("Fehler beim Format der Datei (Startposition)!\n"); return -1;
				}
			}
			else
			{
				if (tok >= (TOKENSTART - 5))
				{
					if (tok > TOKENSTART)
					{
						switch (tok)
						{
							case 400: iptat->Ships[ShipNo].Orientation = Direction::Right; break; // RIGHT
							case 401: iptat->Ships[ShipNo].Orientation = Direction::Down; break; // DOWN
							default: printf("Fehler beim Format der Datei (Richtungswahl: Right oder Down)!\n"); return -1;
						}

					}
					else if (tok <= TOKENSTART)
					{
						switch (tok)
						{
						case 305: 
							if (BattleshipCounter < 1){ iptat->Ships[ShipNo].Length = (tok - 300); BattleshipCounter += 1;}
							else{ printf("Fehler beim Format der Datei (max. ein Battleship)!\n"); return -1;}
							break;
						case 304: 
							if (CruiserCounter < 2){ ShipNo += 1; iptat->Ships[ShipNo].Length = (tok - 300); CruiserCounter += 1;}
							else{ printf("Fehler beim Format der Datei (max. zwei Cruiser)!\n"); return -1;}
							break;
						case 303: 
							if (DestroyerCounter < 3){ ShipNo += 1; iptat->Ships[ShipNo].Length = (tok - 300); DestroyerCounter += 1;}
							else{ printf("Fehler beim Format der Datei (max. drei Destroyer)!\n"); return -1;}
							break;
						case 302: 
							if (SubmarineCounter < 4){ ShipNo += 1; iptat->Ships[ShipNo].Length = (tok - 300); SubmarineCounter += 1;}
							else{ printf("Fehler beim Format der Datei (max. vier Submarines)!\n"); return -1;}
							break;
						default: printf("Fehler beim Format der Datei (Schiffsart)!\n"); return -1;
						}
					}
				}
			}
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
				return (ERROR1); // IDENTIFIER);
			}

		default: printf("***Fatal Error*** Wrong case label in yylex\n");
		}
	}
}
//------------------------------------------------------------------------


