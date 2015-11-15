# PVC
Funcionamento do programa:

Deve-se alterar as variáveis das linhas 13 e 14 para imagem utilizada:
imgname: Qual imagem está sendo utilizada.
outputtxt: Nome do arquivo onde os pontos e desvios padrões serão salvos.

Sugestão para padronizar os arquivos:

imgname: "frontalface/7.jpg"
outputtxt: "Points07.txt"

Usuário deve clicar nos 31 pontos de interesse (exatamente na ordem do arquivo de orientação disponibilizado pelo professor).
Quando não for possível localizar esse ponto, o usuário deve clicar com o botão direito do mouse, fazendo com que as coordenadas -1,-1 sejam salvas no arquivo de saída.

Ordem de execução:

a.Primeira definição dos 31 pontos.
b.Segunda definição dos 31 pontos.
c.Terceira definição dos 31 pontos. (todos os 93 pontos são salvo no arquivo buffer.txt).
d.Os cálculos das médias e desvios padrões são feitos: Por exemplo, os3 valores do ponto 1 estão localizadas nas linhas 1, 32 e 63 do arquivo buffer.txt.
e.Os valores calculados são armazenados no arquivo de saída (definido na linha 14 do main.cpp).

Os pontos serão marcados graficamente na mesma imagem de entrada.

Arquivo TXT de saída:

No arquivo de saída a primeira coluna corresponde à média da coordenada x, a segunda coluna à média da coordenada y, a terceira coluna ao desvio padrão da coordenada x e a quarta coluna ao desvio padrão da coordenada y.

Ainda precisa ser definido (Problemas):

a. Qual o valor máximo aceitável para o desvio padrão de cada imagem? Essa etapa pode ser feita manualmente: analisa-se os dois desvios padrões (x e y) do arquivo de saída, caso esteja dentro da faixa aceitável finaliza-se o processo para aquela imagem, caso não esteja, repete-se o procedimento.
b. Algumas imagens são grandes e não podem ser visualizadas por completo para marcar os pontos: pode ser necessário redimensionar a mesma ou alterar a visualização (linha 161 da main.cpp cria a janela e linha 167 mostra a imagem).


