<h1>Trabalho disciplina Linguagens de Programação - UEM</h1>
<p><strong>gcc --version  ==  esse comando retornará a versão do compilador 
do sistema operacional.</strong></p>
<h2>Perfil de um programa</h2>

<p>perf list sw == exibi lista de eventos pré-definidos</p>
<p><img src="img/sw-command.png">
</p>
<p>perf stat == Este comando fornece estatísticas globais para eventos
 de desempenho comuns, incluindo instruções executadas e
 ciclos de relógios consumidos. Você pode
 usar a opção de sinalizadores para reunir estatísticas de eventos além de
eventos de medição padrão.
 A partir do Red Hat Enterprise Linux 6.4 é possível usar perf status para filtrar monitoramento baseado em um ou mais grupos de controle especificados (cgroups). 

 </p>
<p>perf stat dd if=/dev/zero of=test.iso bs=10M count=1
 == executa um comando e coleta estatísticas de desempenho do Linux durante 
a execução do comando.</p>

<img src="img/dd-command.png">




<p>perf record ./programa == gera perfil do programa</p>
<p>perf report == le os dados do perfil do programa</p>

