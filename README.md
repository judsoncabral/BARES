# BARES

  BARES é uma aplicação de uma calculadora.
  
## Author

Judson Cabral de Melo

## Como funciona?

  O programa vai pegar uma string onde teria o calculo(através de um arquivo ou cin no terminal),tokenizar a string pega e caso não tenha nenhum erro ela ira criar um posfix e apos a criação do posfix, ira fazer um calculo para saber a resposta e para acessar a resposta a pessoa tem que chamar uma função.

## Compilação:

  Para compilar, abra o terminal na pasta BARES e escreva o seguinte comando no terminal:

g++ -Wall -std=c++17 -pedantic src/operation.cpp src/bares.cpp -o bares

## Execução:

  Para compilar, abra o terminal na pasta BARES e escreva o seguinte comando no terminal:

./bares teste.txt

ou 

./bares
  
  Onde teste.txt seria um exemplo de arquivo de entrada(com os calculos que deseja fazer),no caso ira ler linha por linha e ira calcular e depois criar um arquivo na pasta /result/result.txt onde ira ter as respostas ou então o erro de cada expressão.

onde você iria simplesmente escrever a expressão que deseja calcular via terminal.

## Durante a execução:

  Caso tenha fornecido o arquivo ele ira indicar o caminho da pasta com as respostas. 
E caso não tenha fornecido ele ira pedir uma expressão.

## O que eu não fiz?

  Não fiz o programa entender números negativos.

## Observações:

  Coluna começa a contagem com 0 e não 1.
