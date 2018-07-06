#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include "../include/operation.h"

int main(int argc,char *argv[]){

	string arq;
    string expressao;
	//se não for passado nenhum argumento ele fecha;
	if (argc == 1){
        cout <<"Digite a expressão que deseja calcular:"<< endl;
        cin >> expressao;
        Operation P;
        P.make_token(expressao);
            if(P.regra() == true){
                cout << expressao << "     " << P.resultado() << endl;
            }else{
                cout << expressao << "     " << P.mensagem_de_erro() << endl;
            }   
            P.clear();

            expressao.clear();

    }
    else{
    	arq = argv[1];

        ifstream txtFile;
        txtFile.open(arq);

        if(!txtFile){
            cout << "Arquivo não pode ser lido"<< endl;
        }
        //operãção
        string op;


        std::ofstream result;
        result.open("result/result.txt");

        while(!txtFile.eof()){
            getline(txtFile,op);
            if(op.empty() != true){
                Operation P;
                P.make_token(op);
                if(P.regra() == true){
                    // result << "Expressão:" << op <<"Posfix:" << P.pegando_posfix() << "Resultado: "<<P.resultado() << endl;
                    //cout << setfill(' ');
                    result << std::left << "Expressão: " << setw(23) << op << setw(12) << "Resultado:" << setw(12) << P.resultado() << endl;
                }else{
                    result << "Expressão: " << setw(22) << op  << setw(8)<<" Erro:" << P.mensagem_de_erro() << endl;
                }   
                P.clear();
            }
        }
        arq.clear();
        op.clear();

        result.close();
        txtFile.close();

        cout << "Arquivo criado(result.txt) com respostas na pasta /result/result.txt" << endl;
    }


    
    return EXIT_SUCCESS;



}