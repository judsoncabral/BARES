#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <iterator>
#include <cassert>
#include <stack>
#include <stdexcept>
#include "../include/operation.h"

using namespace std;


using symbol = char;
using value_type = long int;

Operation::Operation(){
	col = 0;
	result = 0;
	erro = "0";

}
 Operation::~Operation(){
 	col = 0;
	posfix.clear();
	result = 0;
	erro.clear();
	original.clear();
	token.clear();
 }
bool Operation::is_operator(symbol s){ 
	if(string("^*%/+-").find(s) != string::npos){
		return true;
	}
	else{
		return false;
	}
}
bool Operation::is_operand(symbol s){ 
	if(string("0123456789").find(s) != string::npos){
		return true;
	}
	else{
		return false;
	}
}

bool Operation::is_opening_scope( symbol s ){ 
	if(s == '('){
		return true;
	}
	else{
		return false;
	}
}
bool Operation::is_closing_scope(symbol s){
	if(s == ')'){
		return true;
	} 
	else{
		return false;
	}
}

short Operation::get_precedence( symbol op ){
    switch( op )
    {
        case '^': return 3;

        case '*':
        case '/':
        case '%': return 2;

        case '+':
        case '-': return 1;

        case '(': return 0;

        default: assert(false);
    }
    return -1;
}
bool Operation::has_higher_or_eq_precedence( string op1 , string op2 ){
	char aux1 = op1[0];
	char aux2 = op2[0];
    if ( get_precedence(aux1) >= get_precedence(aux2) )
    {
        return  true ;
    }
    return false;
    
}

bool Operation::fora_da_faixa(){
	int i;
	string aux;
	for(i = 0 ; i < distance(token.begin(),token.end()) ; i++){
		aux = token[i];
		if(is_operand(aux[0]) == true){
			long operando = stol(aux);
			if(operando >32767){
				col = i;
				erro = "Integer constant out of range beginning at column("+to_string(col)+")!";
				
				return true;
			}
			
		}
	}

	if(result > 32767 || result < -32767){
		erro = "Numeric overflow error!";
	}
	return false;
}
bool Operation::faltando_termo(){
	string aux;
	int dist = distance(token.begin(),token.end());
	int i = 1;
	aux = token[dist-1];
	while(aux[0] == ' '){
		aux = token[dist-1-i];
		i++;
	}
		
	if(is_operator(aux[0]) == true || is_opening_scope(aux[0]) == true){
		
		col = distance(token.begin(),token.end())-i+1;
		erro = "Missing <term> at column("+to_string(col)+")!";
		
		return true;
	}
	return false;
}
bool Operation::comeco_invalido(){
	string aux;
	//int dist = distance(seq.begin(),seq.end());
	int i = 1;
	aux = token[0];
	while(aux[0] == ' '){
		aux = token[i];
		i++;
	}
	
	if(is_operator(aux[0]) == true || is_closing_scope(aux[0]) == true){
		col = i-1;
		erro = "Ill formed integer at column("+to_string(col)+")!";
		
		return true;
	}
	return false;
}
bool Operation::missing_closing_scope(){
	string aux;
	int closing = 0;
	int opening = 0;
	for(auto i(0) ; i < distance( token.begin(),token.end() ) ; i++ ){
		aux = token[i];	
		if( is_opening_scope(aux[0]) == true ){
			opening++;
		}
		else if( is_closing_scope(aux[0]) == true ){
			closing++;
			if(closing > opening){
				col = i;
				erro = "Extraneous symbol after valid expression found at column("+to_string(col)+")!";
				return true;
			}
		}
	}
	if(closing != opening){
		col = distance( token.begin(),token.end() );
		erro = "Missing closing ')' at column("+to_string(col)+")!";
		return true;
	}
	return false;
}
bool Operation::termo_invalido(){
	int i;
	string aux;
	string aux1;
	string aux2;
	//verifico se tem um termo diferente
	for(i = 0 ; i < distance(token.begin(),token.end()) ; i++){
		aux = token[i];
		if(is_operand(aux[0]) == true){
		}
		else if(is_operator(aux[0]) == true){
		}
		else if(is_closing_scope(aux[0]) == true){
		}
		else if(is_opening_scope(aux[0]) == true){
		}
		else if(aux[0] == ' '){
		}
		else{
			col = i;
			erro = "Extraneous symbol after valid expression found at column("+to_string(col)+")!";
			//cout << erro << endl;
			return true;
		}
	}
	//verifico se tem duas operações coladas
	for(i = 1 ; i < distance(token.begin(),token.end() )-1 ; i++){
		aux = token[i];
		aux1 = token[i+1];
		
		if(is_operator(aux[0]) == true && is_operator(aux1[0]) == true ){
			col = i;
			erro = "Extraneous symbol after valid expression found at column("+to_string(col)+")!";
			//cout << erro << endl;
			return true;
		}else if( is_closing_scope(aux[0]) == true && is_opening_scope(aux1[0]) ){
			col = i;
			erro = "Extraneous symbol after valid expression found at column("+to_string(col)+")!";
			//cout << erro << endl;
			return true;
		}
	}

	//verifico se tem duas operações coladas (distanciadas por espaços)
	//ou se tem dois numeros separados por espaços
	//ou se não tem operações entre scopes
	int j = 1;
	int w = 1;
	for(i = 1 ; i < distance(token.begin(),token.end())-1 ; i++){
		aux = token[i];
		if(aux[0] == ' '){
			aux1 = token[i-j];
			aux2 = token[i+w];
			while(aux1[0] == ' ' && i-j > 0){
				j++;
				aux1 = token[i-j];
			}
			while( aux2[0] == ' ' && i+w < distance( token.begin(),token.end() ) ){
				w++;
				aux2 = token[i+w];
			}
			if( is_operand(aux1[0]) == true && is_operand(aux2[0]) == true ){
				col = i;
				erro = "Extraneous symbol after valid expression found at column("+to_string(col)+")!";
				//cout << erro << endl;
				return true;
			}else if( is_operator(aux1[0]) == true && is_operator(aux2[0]) == true ){
				col = i;
				erro = "Extraneous symbol after valid expression found at column("+to_string(col)+")!";
				//cout << erro << endl;
			}else if( is_closing_scope(aux1[0]) == true && is_opening_scope(aux2[0]) == true ){
				col = i;
				erro = "Extraneous symbol after valid expression found at column("+to_string(col)+")!";
				//cout << erro << endl;
			}
		}
	}
	return false;

}
bool Operation::vazio(){
	int operandos = 0;
	string aux;
	for(auto i(0) ; i < distance(token.begin(),token.end() ) ; i++){
		aux = token[i];
		if(is_operand(aux[0]) == true){
			operandos++;
		}	
	}
	if(operandos == 0){
		col = distance( token.begin(),token.end() );
		erro = "Unexpected end of expression at column("+to_string(col)+")!";
		return true;
	}
	return false;
}

int Operation::execute_operator( int v1, int v2, char op )
{
    switch( op )
    {
        case '^':
            return pow( v1, v2 );
        case '*':
            return v1 * v2;
        case '/':
            if ( v2 == 0 ) {
            	erro = "Division by zero";
            	//throw std::runtime_error("Division by zero");
            	return 0;
            }
            return v1/v2;
        case '%':
            if ( v2 == 0 ){
             erro = "Division by zero";
             //throw std::runtime_error("Division by zero");
             return 0;
            }
            return v1%v2;
        case '+':
            return v1+v2;
        case '-':
            return v1-v2;
        //default:
    }
    throw std::runtime_error("Invalid operator!");
}
void Operation::evaluate_postfix()
{
    std::stack< int > s;
    string aux;
    // For each operator/operando in the input posfix expression do this...
    for( auto i(0) ; i < distance( posfix.begin(),posfix.end() ) ; i++ )
    {
    	aux = posfix[i];
        if ( is_operand( aux [0]) == true )
            s.push( stoi (aux) ); // Do not forget to convert it into integer.
        else if ( is_operator( aux[0] ) == true )
        {
            // IMPORTANT: Pop out operandos in reverse order!
            auto op2 = s.top(); 
            s.pop();
            auto op1 = s.top(); 
            s.pop();
            // The result of the operation is pushed back into the stack.
            s.push( execute_operator( op1, op2, aux[0] /* any of ^ * / % + - */ ) );
        }
        else assert( false ); // unexpected symbol...
    }
    // cout << "Resultado: " << s.top() << endl;
    result = s.top();
}
void Operation::pos_fix(){
	std::stack<string> s; // auxiliary data structure.
    string aux;
    string top;

    // Process each incoming symbol
    for( auto i(0) ; i < distance( token.begin(),token.end() ) ; i++ )
    {	aux = token[i];
        if ( is_operand( aux[0] ) == true )
            posfix.push_back(aux); // send it straight to the output symbol queue.
        else if ( is_opening_scope( aux[0] ) == true )
            s.push( aux ); // always goes into the "waiting room"
        else if ( is_closing_scope( aux[0]) == true )
        {
            // Pop out all pending operations.
            top = s.top();
            while( not is_opening_scope( top[0] 	) )
            {
            	//coloca = s.top();
                // remove operator and send it to the posfix expression.
                posfix.push_back(s.top());
                s.pop();
                top = s.top();
            }
            // Don't forget to get rid of the opening scope.
            s.pop();
        }
        else if ( is_operator( aux[0] ) == true )
        {
            // Send out the "waiting" operator with higher or equal precedence...
            // unless they have equal precedence AND are right associated.
            while ( not s.empty() and has_higher_or_eq_precedence( s.top(), aux ) )
            {
                posfix.push_back(s.top()); // send it to the output
                s.pop(); // get rid of the operator.
            }
            // The incoming symbol always goes into the "waiting room".
            s.push( aux ) ;
        }
        else // white space or whatever
        {
            // Do nothing. Just ignore this...
        }
    }

    // Clear out any pending operators stored in the stack.
    while ( not s.empty() )
    {
        posfix.push_back( s.top() );
        s.pop();
    }

 
    // for(auto c(0) ; c < distance(posfix.begin(), posfix.end() ) ; c++){
    // 	cout << posfix[c];
    // }
    // cout<<endl;

    
    //return posfix;
}
bool Operation::regra(){

	if(fora_da_faixa() == true){
		return false;
	}else if(faltando_termo() == true){
		return false;
	}else if(comeco_invalido() == true){
		return false;
	}else if(missing_closing_scope() == true){
		return false;
	}else if(vazio() == true){
		return false;
	}else if(termo_invalido() == true){
		return false;
	}else if(erro != "0"){
		return false;
	}else{
		return true;
	}

}
void Operation::make_token(std::string x){

	original = x;
	
	int i;
	string coloca;
	string colocaNUM;

	for(i = 0 ; i < distance(x.begin(),x.end()) ; i++){
		if(is_closing_scope(x[i]) == true){
			if(colocaNUM.empty() == false){
				token.push_back(colocaNUM);
				colocaNUM.clear();
			}
			coloca.push_back(x[i]);
			token.push_back(coloca);
			coloca.clear();
		}
		else if(is_opening_scope(x[i]) == true){
			if(colocaNUM.empty() == false){
				token.push_back(colocaNUM);
				colocaNUM.clear();
			}
			coloca.push_back(x[i]);
			token.push_back(coloca);
			coloca.clear();
		}

		else if(is_operator(x[i]) == true){
			if(colocaNUM.empty() == false){
				token.push_back(colocaNUM);
				colocaNUM.clear();
			}
			coloca.push_back(x[i]);
			token.push_back(coloca);
			coloca.clear();
	
		}
		else if(is_operand(x[i]) == true){

			colocaNUM.push_back(x[i]);
			
		}

		else{
			if(colocaNUM.empty() == false){
				token.push_back(colocaNUM);
				colocaNUM.clear();
			}
			coloca.push_back(x[i]);
			token.push_back(coloca);
			coloca.clear();
		}
	}
	if(colocaNUM.empty() == false){
		token.push_back(colocaNUM);
		colocaNUM.clear();
	}

	// for(auto w(0) ; w < distance(token.begin(),token.end()) ; w++){
	// 	cout << "Coluna" << w << " " << token[w] << endl;
	// }
	
	if(regra() == true){
		pos_fix();
		evaluate_postfix();

	}
	
}
string Operation::mensagem_de_erro(){
	return erro;
}
string Operation::pegando_posfix(){
	string aux;
	string posfixReturn;
	for(auto c(0) ; c < distance( posfix.begin(),posfix.end() ) ; c++ ){
		aux = posfix[c];
		for(auto j(0); j < distance(aux.begin() , aux.end() ) ; j++){
			posfixReturn.push_back(aux[j]);
		}
	}
	//cout << posfixReturn << endl;
	return posfixReturn;
}
int Operation::resultado(){
	if(regra() == true){
		return result;
	}else{
		return 0;
	}
}
int Operation::coluna(){
	return col;
}
void Operation::clear(){
	col = 0;
	posfix.clear();
	result = 0;
	erro.clear();
	original.clear();
	token.clear();
}