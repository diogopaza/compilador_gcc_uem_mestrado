<h1>Trabalho disciplina Linguagens de Programação - UEM</h1>
<p><strong>gcc --version  ==  esse comando retornará a versão do compilador 
do sistema operacional.</strong></p>
<h2>Perfil de um programa</h2>

<p>perf list sw == exibi lista de eventos pré-definidos</p>

<p>perf stat dd if=/dev/zero of=test.iso bs=10M count=1
 == executa um comando e coleta estatísticas de desempenho do Linux durante 
a execução do comando.</p>
![img/dd-command.png]
<img src="img/dd-command.png">
<p>perf record ./programa == gera perfil do programa</p>
<p>perf report == le os dados do perfil do programa</p>

