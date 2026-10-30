# Detector de Chuva com Servo Motor (Arduino)

Projeto simples em Arduino que usa um **sensor de chuva** para detectar água e acionar um **servo motor**. Quando começa a chover, o servo vai para uma posição; quando a chuva para, ele volta para a outra. Pode ser usado como base para uma janela automática, uma cobertura retrátil, um varal inteligente, etc.

## Demonstração

**Veja o projeto funcionando:** https://www.instagram.com/reel/DexVmK6MUz9/?cplk=MXJmaDhqc2lmNjRjNA==



## Materiais

|Qtde|Componente|
|-|-|
|1|Arduino Uno (ou compatível)|
|1|Módulo sensor de chuva (placa de trilhas + módulo comparador, ex.: YL-83 / FC-37)|
|1|Servo motor (ex.: SG90 ou MG90S)|
|1|Protoboard|
|\~8|Jumpers macho-macho e macho-fêmea|
|1|Cabo USB para o Arduino|
|(opcional)|Fonte externa de 5 V para o servo|

\---

## Montagem na protoboard

### Ligações

**Sensor de chuva** (usar a saída analógica **AO**, não a digital **DO**):

|Pino do módulo|Liga em|
|-|-|
|VCC|5V do Arduino|
|GND|GND do Arduino|
|AO|**A0** do Arduino|
|DO|*não utilizado*|

> A placa de trilhas (a parte que fica exposta à água) se conecta ao módulo comparador por dois fios. Confirme que ela está ligada ao módulo antes de testar.

**Servo motor:**

|Fio do servo|Cor comum|Liga em|
|-|-|-|
|Alimentação|Vermelho|5V|
|Terra|Marrom ou preto|GND|
|Sinal|Laranja ou amarelo|**Pino digital 9**|

### Passo a passo

1. **Desligue o Arduino** (sem cabo USB) antes de montar.
2. Use jumpers para levar o **5V** do Arduino à **linha vermelha (+)** da protoboard e o **GND** à **linha azul (−)**.
3. Ligue o **VCC** do módulo do sensor na linha **+** e o **GND** na linha **−**.
4. Ligue o pino **AO** do módulo ao pino **A0** do Arduino.
5. Ligue o fio **vermelho** do servo na linha **+**, o fio **marrom/preto** na linha **−** e o fio de **sinal** ao **pino 9** do Arduino.
6. Confira tudo duas vezes e só então conecte o cabo USB.

### Atenção com a alimentação do servo

Servos puxam bastante corrente ao se mover. Se notar que o servo **treme**, que o **Arduino reinicia** ou que as leituras ficam instáveis, alimente o servo com uma **fonte externa de 5 V** e **una o GND da fonte ao GND do Arduino** (o GND precisa ser comum). Nunca ligue o positivo da fonte externa no 5V do Arduino.

\---

## Como usar

1. Instale a [Arduino IDE](https://www.arduino.cc/en/software).
2. Clone ou baixe este repositório:

```bash
   git clone https://github.com/SEU\_USUARIO/NOME\_DO\_REPOSITORIO.git
   ```

3. Abra o arquivo `.ino` do projeto na Arduino IDE.
4. Selecione a placa (**Ferramentas → Placa**) e a porta (**Ferramentas → Porta**).
5. Clique em **Carregar** (upload).
6. Abra o **Monitor Serial** em **9600 baud** para acompanhar as leituras.

A biblioteca `Servo` já vem instalada com a IDE, não é preciso instalar nada extra.

\---

## Como funciona

O sensor de chuva entrega um valor analógico entre 0 e 1023. **Quanto mais molhada a placa, menor o valor.** O código lê esse valor a cada 500 ms e usa um **acumulador** para evitar que uma gota isolada ou uma oscilação do sensor acione o servo por engano:

* Leitura **abaixo de 510** (molhado): o acumulador sobe **+1**, até o máximo de 50.
* Leitura **a partir de 510** (seco): o acumulador desce **−5**, até o mínimo de 0.
* Acumulador **≥ 10**: considera que **está chovendo** e move o servo para `POS\_ABERTO` (0°).
* Acumulador **= 0**: considera que **parou de chover** e move o servo para `POS\_FECHADO` (90°).
* Entre 1 e 9 o estado anterior é mantido (histerese), o que evita que o servo fique abrindo e fechando em garoa fraca.

### Tempos aproximados

|Evento|Tempo|
|-|-|
|Detectar chuva (a partir do seco)|\~5 s de placa molhada|
|Detectar que secou (a partir do máximo)|até \~5 s de placa seca|

\---

## Ajustes e calibração

|O que ajustar|Onde|Efeito|
|-|-|-|
|Sensibilidade|`510` no `if (ValorAnalog < 510)`|Aumente para detectar com menos água; diminua para exigir mais água|
|Rapidez para detectar chuva|`acumulador >= 10`|Valor menor responde mais rápido|
|Tempo para considerar que secou|`ACUMULADOR\_MAX` e o `5` do `acumulador -= 5`|Máximo maior ou passo menor deixa o retorno mais lento|
|Posições do servo|`POS\_ABERTO` e `POS\_FECHADO`|Troque os valores se o movimento estiver invertido para a sua estrutura|

**Dica de calibração:** abra o **Monitor Serial** (9600 baud) e observe os valores com a placa seca e depois com algumas gotas. Use esses números para escolher o limiar no lugar do 510.

\---



## Autor

**José Luiz Soares e Silva**

