Código feito em C++ visando resolver o seguinte problema:

1. Acesse o site https://dados.gov.br/dataset/preco-de-medicamentos-no-brasil-consumidor e baixe o arquivo 
2. Leia o arquivo baixado, considerando que é um arquivo csv delimitado por ‘;’ (ponto e vírgula), e que a primeira linha é o ‘header’ (lista dos campos).
 
Nota: No nome dos arquivos que você irá ver, PF significa Preço de Fábrica, e PMC significa Preço Máximo ao Consumidor
 
3. Dê output no console o seguinte:
	a. O nome dos campos do arquivo	
	b. O produto com o maior preço de fábrica sem impostos (todos se tiver mais que um com o maior preço)
	c. Quais os possíveis tipos de produtos
	d. O produto e preço do genérico mais barato
4. Salve todos os registros com o preço final sem impostos superior a ‘100’, com comercialização 2018 marcada como ‘Sim’ e que sejam Tarja Vermelha em um arquivo chamado “output.csv”
5. Leia o arquivo que você criou no item anterior e ordene o conteúdo por ordem alfabética do campo produto (sobrescreva o arquivo com os registros ordenados).
6. Com o conteúdo deste segundo arquivo, responda:
	a. Qual o valor total (soma) dos preços finais sem imposto?
	b. Quantos tipos diferentes de produtos estão presentes?
	c. Existe algum produto que possua a mesma “substância” de um outro produto do arquivo original com preço final sem impostos inferior a ‘100’?
 
Este código possui a solução apenas até o indíce número 4, para executar basta rodar o arquivo .exe.