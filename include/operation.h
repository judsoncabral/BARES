#ifndef OPERATION_H
#define OPERATION_H

#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <iterator>
#include <cassert>
#include <stack>
#include <stdexcept>

using namespace std;

using symbol = char;
using value_type = long int;

class Operation{
	private:
		//Variável onde vai guarda a operação original
		string original;
		//Vetor onde vai guardar os token
		vector <string> token;
		//Vetor onde vai guarda o posfix
		vector <string> posfix;
		//Variável onde vai guardar onde está o erro
		int col;
		//Variável onde vai guardar o resultado
		int result;
		//Variável onde vai guardar qual erro foi achado
		string erro;

		/*
			Função para verificar se é operador
		 */
		bool is_operator(symbol s);
		/*
			Função para verificar se é operando
		 */
		bool is_operand(symbol s);
		/*
			Função para verificar se é abertura de parênteses
		 */
		bool is_opening_scope(symbol s);
		/*
			Função para verificar se é fechamento de parênteses
		 */
		bool is_closing_scope(symbol s);
		/*
			Função para retorna a procedência do operador
		 */
		short get_precedence(symbol s);
		/*
			Função para ver se op1 tem procedência maior ou igual a do op2
		 */
		bool has_higher_or_eq_precedence( string op1 , string op2 );

		//regras
		
		/*
			Função que verifica se tem algum operando fora da faixa
		 */
		bool fora_da_faixa();
		/*
			Função que verifica se tem algum termo faltando no token
		 */
		bool faltando_termo();
		/*
			Função verifica se o token começa com algum termo errado(operador ou fechamento de parênteses)
		 */
		bool comeco_invalido();
		/*
			Função para verificar se ta faltando fechamento de parênteses no token
		 */
		bool missing_closing_scope();
		/*
			Função verifica se não tem o que ser feito(token vazio prenchido com espaços ou sem números)
		 */
		bool vazio();
		/*
			Função verifica se tem algum termo invalido
		 */
		bool termo_invalido();

		
		/*
			Função para retornar a operaão (op) entre v1 e v2 e retornar o valor
			Caso ocorra algum erro
		 */
		int execute_operator( int v1, int v2, char op );
		/*
			Função para fazer o calculo de todo o posfix
		 */
		void evaluate_postfix();
		/*
			Função para criar o posfix
		 */
		void pos_fix();

	public:
		Operation();
		~Operation();
		/*
			Função para retornar a mensagem de erro
		 */
		string mensagem_de_erro();
		/*
			Função para pegar o posfix
		 */
		string pegando_posfix();
		/*
			Função para pegar o resultado
		 */
		int resultado();

		int coluna();
		/*
			Função que cria o token e realiza a chamda da criação do posfix
			e do resultado.
		 */
		void make_token(std::string x); 
		/*
			Verifica se teve algum erro e caso tenha ele retorna falso
		 */
		bool regra();
		/*
			Limpa todas as informações
		 */
		void clear();
		
};
#endif