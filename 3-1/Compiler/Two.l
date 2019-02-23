%option noyywrap

%{
#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>

using namespace std;

int line_count=1;
int error_count=1;


FILE *logout;
FILE *tokenout;

class SymbolInfo
{
    string SymbolName, SymbolType;

public:

    SymbolInfo *symbolPointer;
    SymbolInfo()
    {
        symbolPointer=NULL;
	SymbolName="";
	SymbolType="";
   }
    SymbolInfo(string name,string type)
    {
        SymbolName=name;
        SymbolType=type;
        symbolPointer=NULL;
    }
    void setName(string name);
    string getName();
    void setType(string type);
    string getType();
};

void SymbolInfo::setName(string name)
{
    SymbolName=name;
}
string SymbolInfo::getName()
{
    return SymbolName;
}

void SymbolInfo::setType(string type)
{
    SymbolType=type;
}

string SymbolInfo::getType()
{
    return SymbolType;
}



class ScopeTable
{
public:

    SymbolInfo *pointer_ara;
    ScopeTable *parentScope;
    int id;
    int buck_len;
    ScopeTable()
    {
        pointer_ara=new SymbolInfo[7];
        parentScope=NULL;
        buck_len=7;
        //table_id_stat++;
        id=1;
    }
    ScopeTable(int n)
    {
        //table_id=0;
        buck_len=n;
        pointer_ara=new SymbolInfo[7];
        parentScope=NULL;
        //table_id_stat++;
        id=1;
    }
    ~ScopeTable()
    {
        //table_id_stat--;
        delete[] pointer_ara;
        delete parentScope;
    }
    int hashFunc(string key_name);
    bool insert(SymbolInfo *obj);
    SymbolInfo* ScopeLookUp(string key);
    bool ScopeDelete(string key);
    void print();
};

//int ScopeTable::table_id_stat=0;

int ScopeTable::hashFunc(string key_name)
{
    int total=0;
    for(int i=0; i<key_name.length(); i++)
    {
        total+=key_name[i];
    }
    int key=(total*(key_name.length())+5)%buck_len;
    //cout<<key;
    return key;
}

bool ScopeTable::insert(SymbolInfo *obj)
{

    int key=hashFunc(obj->getName());
    SymbolInfo *temp=new SymbolInfo;
    temp=&pointer_ara[key];
    int i=0;

    while(temp->symbolPointer!=NULL)
    {

        if(temp->symbolPointer->getName()==obj->getName())
        {
            //cout<<"Input already inserted in this Scope"<<endl;
            return false;
        }
        temp=temp->symbolPointer;
        i++;
    }
    //cout<<"hi"<<endl;
    temp->symbolPointer=obj;
    //cout<<"Inserted in ScopeTable #"<<id<<" at position "<<key<<", "<<i<<endl;
    return true;
}

SymbolInfo* ScopeTable::ScopeLookUp(string key_name)
{
    int key=hashFunc(key_name);
    SymbolInfo *temp=new SymbolInfo;
    temp=&pointer_ara[key];
    int i=0;
    while(temp!=NULL)
    {
        if(temp->getName()==key_name)
        {
            printf("Found in ScopeTable #%d at position %d %d\n",id, key, i-1) ;
            return temp;
        }
        temp=temp->symbolPointer;
        i++;
    }
    //cout<<"Not Found"<<endl;
    return temp;
}

bool ScopeTable::ScopeDelete(string key_name)
{
    int key=hashFunc(key_name);
    SymbolInfo *temp=new SymbolInfo;
    temp=&pointer_ara[key];
    int i=0;
    while(temp->symbolPointer!=NULL)
    {
        if(temp->symbolPointer->getName()==key_name)
        {
            temp->symbolPointer=temp->symbolPointer->symbolPointer;
            //cout<<"Deleted entry at "<< key<<", "<<i<<" from current ScopeTable"<<endl;
            //delete temp_2;
            return true;
        }
        i++;
        temp=temp->symbolPointer;
    }
    if(temp->getName()==key_name)
    {

    }
    //cout<<key_name<<" not Found"<<endl;
    return false;
}

void ScopeTable::print()
{
    fprintf(logout, "ScopeTable # 1\n");
   
    for(int i=0; i<7; i++)
    {
        SymbolInfo *temp3=new SymbolInfo;
        temp3=pointer_ara[i].symbolPointer;
        //cout<<temp;
        //cout<<i<<"---> ";
	fprintf(logout,"%d--> ", i);
        while(temp3!=NULL)
        {
           //cout<<temp->SymbolName;
           //string s1=temp->getName();
           //cout <<" < "<<temp3->SymbolName<<" : "<<temp3->SymbolType<<" >  ";
            fprintf(logout,"<%s : %s>" , temp3->getName().c_str(),  temp3->getType().c_str()) ;
            temp3=temp3->symbolPointer;
        }
        fprintf(logout,"\n");
    }
    fprintf(logout,"\n");
}


ScopeTable st;

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
SPECIALCHAR (\')(\\)[ntafrbv0\\](\')
CHAR [\'][!-~][\']
DIGIT [0-9]
FLOAT [-+]?[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?

MULTICOMMENT [/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]
MULTICOMMENT2 [/][/]([^\n]*(\\)(\n))+[^\n]*(\n)
SINGLECOMMENT [/][/][^\n]*("\n") 
ERROR_COMMENT ^"/*"[^"*/"]* 
IDENTIFIER [A-Za-z][0-9A-Za-z_]*
ERROR_IDENTIFIER [0-9][0-9A-Za-z_]*
ERROR_IIL_DIG [0-9]*[E]?[0-9]+\.[0-9]+
ERROR_DEC_DIG [0-9]*\.([0-9]*\.)+[0-9]*
ERROR_CHAR  [\'][^\']+[\']
ERROR_UNTER_CHAR [\'](\\)[\']
ERROR_EMPTY_CHAR \'\'
ERROR_CHAR_UNFINISH [\'][^\n\']*
STRING \"[!-~]*(\")


NEWLINE \n

%%

{NEWLINE} {line_count++;}


{STRING} 	{
			fprintf(tokenout,"<STRING,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <STRING> Lexeme %s found\n",line_count,yytext);
		}




"if"		{
			fprintf(tokenout,"<IF>");
			fprintf(logout,"Line no %d: TOKEN <IF> Lexeme %s found\n",line_count,yytext);
		}
		
"else"		{
			fprintf(tokenout,"<ELSE>");
			fprintf(logout,"Line no %d: TOKEN <ELSE> Lexeme %s found\n",line_count,yytext);
		}

"for"		{
			fprintf(tokenout, "<FOR>");
			fprintf(logout, "Line no %d: TOKEN <FOR> lexeme %s found\n" ,line_count,yytext);

		}



"while"		{	
			fprintf(tokenout, "<WHILE>");
			fprintf(logout, "Line no %d: TOKEN <WHILE> lexeme %s found\n", line_count,
			yytext);
		}

"do"		{	
			fprintf(tokenout, "<DO>");
			fprintf(logout, "Line no %d: TOKEN <DO> lexeme %s found\n", line_count,
			yytext);
		}


"break"		{	
			fprintf(tokenout, "<BREAK>");
			fprintf(logout, "Line no %d: TOKEN <BREAK> lexeme %s found\n", line_count,
			yytext);
		}


"int"		{	
			fprintf(tokenout, "<INT>");
			fprintf(logout, "Line no %d: TOKEN <INT> lexeme %s found\n", line_count,
			yytext);
		}


"char"		{	
			fprintf(tokenout, "<CHAR>");
			fprintf(logout, "Line no %d: TOKEN <CHAR> lexeme %s found\n", line_count,
			yytext);
		}


"float"		{	
			fprintf(tokenout, "<FLOAT>");
			fprintf(logout, "Line no %d: TOKEN <FLOAT> lexeme %s found\n", line_count,
			yytext);
		}


"double"	{	
			fprintf(tokenout, "<DOUBLE>");
			fprintf(logout, "Line no %d: TOKEN <DOUBLE> lexeme %s found\n", line_count,
			yytext);
		}


"void"		{	
			fprintf(tokenout, "<VOID>");
			fprintf(logout, "Line no %d: TOKEN <VOID> lexeme %s found\n", line_count,
			yytext);
		}


"return"	{	
			fprintf(tokenout, "<RETURN>");
			fprintf(logout, "Line no %d: TOKEN <RETURN> lexeme %s found\n", line_count,
			yytext);
		}


"SWITCH"	{	
			fprintf(tokenout, "<SWITCH>");
			fprintf(logout, "Line no %d: TOKEN <SWITCH> lexeme %s found\n", line_count,
			yytext);
		}


"case"		{	
			fprintf(tokenout, "<CASE>");
			fprintf(logout, "Line no %d: TOKEN <CASE> lexeme %s found\n", line_count,
			yytext);
		}


"default"	{	
			fprintf(tokenout, "<DEFAULT>");
			fprintf(logout, "Line no %d: TOKEN <DEFAULT> lexeme %s found\n",line_count,
			yytext);
		}


"continue"	{	
			fprintf(tokenout, "<CONTINUE>");
			fprintf(logout, "Line no %d: TOKEN <CONTINUE> lexeme %s foun\n",line_count,
			yytext);
		}


{MULTICOMMENT}	{
			fprintf(logout,"Line no %d: TOKEN <COMMENT> :  %s found \n", line_count, yytext);
		}

{MULTICOMMENT2}	{
			fprintf(logout,"Line no %d: TOKEN <COMMENT> :  %s found \n", line_count, yytext);
		}


{SINGLECOMMENT}	{
			fprintf (logout,"Line no %d: TOKEN <COMMENT> : %s found \n", line_count, yytext);
			line_count++;
		}

{ERROR_COMMENT}	{
			fprintf (logout,"Error at line %d: Unterminated comment %s\n",line_count,yytext);
			error_count++;
		}


{IDENTIFIER}    {
				fprintf(tokenout,"<ID,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <ID> Lexeme %s found\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
				SymbolInfo *si=new SymbolInfo(string(yytext),"ID");
				st.insert(si);
				st.print();
		}

		
{DIGIT}+ 	{
				fprintf(tokenout,"<CONST_INT,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <CONST_INT> Lexeme %s found\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
				SymbolInfo *si=new SymbolInfo(string(yytext),"CONST_INT");
				st.insert(si);
			}


{FLOAT} 	{
				fprintf(tokenout,"<CONST_FLOAT,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <CONST_FLOAT> Lexeme %s found\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
				SymbolInfo *si=new SymbolInfo(string(yytext),"CONST_INT");
				st.insert(si);
		}

{SPECIALCHAR}    {
 				char ch;
				if(yytext[2]=='t'){ch=9; }
				else if(yytext[2]=='a'){ch =7;}
				else if(yytext[2]=='n'){ch =10;}
				else if(yytext[2]=='b'){ch =8;}
				else if(yytext[2]=='r'){ch =13;}
				else if(yytext[2]=='f'){ch =12;}
				else if(yytext[2]=='v'){ch =11;}
				else if(yytext[2]=='0'){ch =0;}
				else if(yytext[2]=='\\'){ch =92;}
				fprintf(tokenout,"<CONST_CHAR,%c>",ch);
				fprintf(logout,"Line no %d: TOKEN <CONST_CHAR> Lexeme %c found\n",line_count,ch);
				//insert in symbol table and print symbol table content(only non empty buckets)
				SymbolInfo *si=new SymbolInfo( string(yytext),"CONST_CHAR");
				st.insert(si);
						
		}


{ERROR_UNTER_CHAR}	{
			
				fprintf (logout,"Error at line %d: Unterminated character found %s\n",line_count,yytext);
				error_count++;
			}


{ERROR_EMPTY_CHAR}	{
				fprintf (logout,"Error at line %d: Empty character constant error %s\n",line_count,yytext);
				error_count++;
			}


{CHAR}		{
				fprintf(tokenout,"<CONST_CHAR,%c>",yytext[1]);
				fprintf(logout,"Line no %d: TOKEN <CONST_CHAR> Lexeme %s found\n",line_count,yytext);
				SymbolInfo *si=new SymbolInfo(string(yytext),"CONST_CHAR");
				st.insert(si);
				st.print();
		}


{ERROR_CHAR}	{
		
				fprintf(logout,"Error at line %d: Multi character constant error %s",line_count,yytext);
				error_count++;
		}

{ERROR_CHAR_UNFINISH}   {
				
				fprintf(logout,"Error at line %d: Unfinished character error %s",line_count,yytext);
				error_count++;
			}




"+"		|

"-"		{
			fprintf(tokenout,"<ADDOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ADDOP> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}



"*"		|
"/"		|
"%" 		{
			fprintf(tokenout,"<MULOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <MULOP> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		} 

"++"		|
"--"		{
			fprintf(tokenout,"<INCOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <INCOP> Lexeme %s found\n",line_count,yytext);
		}


"<="		|
">="		|
"<"		|
">"		|
"=="		|
"!=" {
			fprintf(tokenout,"<RELOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <RELOP> Lexeme %s found\n",line_count,yytext);
		}


"||"		|
"&&" {
			fprintf(tokenout,"<LOGICOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <LOGICOP> Lexeme %s found\n",line_count,yytext);
		}


"="		{
			fprintf(tokenout,"<ASSIGNOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ASSIGNOP> Lexeme %s found\n",line_count,yytext);
		}


"!" 		{
			fprintf(tokenout,"<NOT,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <NOT> Lexeme %s found\n",line_count,yytext);
		}

"(" 		{
			fprintf(tokenout,"<LPAREN,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <LPAREN> Lexeme %s found\n",line_count,yytext);
		}

")"	 	{
			fprintf(tokenout,"<RPAREN,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <RPAREN> Lexeme %s found\n",line_count,yytext);
		}

"{"		{
			fprintf(tokenout,"<LCURL,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <LCURL> Lexeme %s found\n",line_count,yytext);
		}

"}"	 	{
			fprintf(tokenout,"<RCURL,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <RCURL> Lexeme %s found\n",line_count,yytext);
		}
"[" 		{
			fprintf(tokenout,"<LTHIRD,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <LTHIRD> Lexeme %s found\n",line_count,yytext);
		}
"]" 		{
			fprintf(tokenout,"<RTHIRD,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <RTHIRD> Lexeme %s found\n",line_count,yytext);
		}
"," 		{
			fprintf(tokenout,"<COMMA,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <COMMA> Lexeme %s found\n",line_count,yytext);
		}
";"		{
			fprintf(tokenout,"<SEMICOLON,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <SEMICOLON> Lexeme %s found\n",line_count,yytext);
		}






{ERROR_IDENTIFIER}   {
			fprintf (logout,"Error at line %d: Invalid prefix on ID or invalid suffix on Number %s\n",line_count,yytext);
			error_count++;

		}
		

			

			
{WHITESPACE} 	{}	

			


%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	logout= fopen("log.txt","w");
	tokenout= fopen("token.txt","w");

	yyin= fin;
	yylex();
	st.print();
	fclose(yyin);
	fclose(tokenout);
	fclose(logout);
	return 0;
}
