# <h1>Manual de Configuração para ESP8266</h1>

<h3>Circuito eletrônico</h3>

Para montagem do circuito você vai precisar de:
<ul>
<li>1 resistor 2200 ohms;</li>
<li>1 sensor de temperatura e umidade DHT11;</li>
<li>1 módulo WIFI ESP8266;</li>
<li>1 fonte de alimentação 4,5V;</li>
<li>1 módulo FTD232;</li>
<li>1 protoboard;</li>
<li>15 Jumpers.</li>
</ul>
Monte o circuito conforme esquema abaixo:
<p align="center">
  <img src="/images/1.png" width="600"/
 </p>
 

<h3>Criar planta Weather no portal WEG IoT e seus sensores</h3>
Entre com o seu login e senha no portal WEG IoT (https://iot.weg.net/#/) e acesse a área de criação de plantas.
No menu esquerdo selecione a opção Smart Cities e então adicione uma planta do tipo Clima.
 <p align="center">
  <img src="/images/2.png" width="600"/
 </p>

Preencha as informações de endereço solicitadas e clique em Avançar.
 <p align="center">
  <img src="/images/3.png" width="400"/
 </p>

Na próxima tela adicione os sensores que serão utilizados, clicando em adicionar. A seguinte tela irá abrir:
  <p align="center">
  <img src="/images/4.png" width="400"/
 </p>
<ul>
<li>Número de série: Nome ou código do sensor.</li>
<li>Modelo: Selecione a opção WTH001.</li>
</ul>

Repita o processo acima caso tenha mais de um sensor para cadastrar na mesma planta.

<h3>Configurar a IDE de desenvolvimento Arduino</h3>

Baixe a IDE de desenvolvimento Arduino do site oficial, no endereço:
> https://www.arduino.cc/en/Main/Software

Efetue a instalação da IDE do Arduino seguindo os passos do instalador.

Faça o download desse repositório, e extraia o conteúdo em um diretório de sua preferência.

Localize o arquivo `libraries.ZIP`, ele contém todas as bibliotecas necessárias. Extraia as pastas com as bibliotecas para o diretório: 
> C:\Users\SEU_USUARIO\Documents\Arduino\libraries

Caso a pasta libraries não exista no diretório acima, você pode criá-la manualmente.

Abra o arquivo `ESP-DHT_comMD5.ino` com a IDE do arduino e acesse o menu Arquivo -> Preferências. Neste menu adicione o link abaixo à opção “ URLs adicionais para Gerenciadores de Placas”
> http://arduino.esp8266.com/stable/package_esp8266com_index.json

 <p align="center">
  <img src="/images/5.png" width="600"/
 </p>

Feito isso, abra o menu Ferramentas, clique em Placas e selecione a opção Gerenciador de placas. Na página que abrir você pode filtrar por _“ESP8266”_ ou procure na listagem por _“esp8266 by ESP8266 Community”_ e instale o pacote.
 
 <p align="center">
  <img src="/images/6.png" width="600"/
 </p>

Quando terminar a instalação abra o mesmo menu (Ferramentas -> Placa) e selecione a opção _“Generic ESP8266 Module”_.
Configure o módulo com os seguintes parâmetros:
 
 <p align="center">
  <img src="/images/7.png" width="300"/
 </p>

<h3>Fazer upload para o ESP8266</h3>

No arquivo `ESP-DHT_comMD5.ino` altere as seguintes variáveis:
 
 <p align="center">
  <img src="/images/8.png" width="600"/
 </p>

Feitas as modificações, verifique se o código possui alguma pendência, e então conecte o FTD232 ao seu computador, selecione no menu Ferramentas a porta em que ele está conectado e faça o upload para o ESP8266.
 
 <p align="center">
  <img src="/images/9.png" width="300"/
 </p>

Caso ocorra algum problema no deploy, pegue o fio branco do esquema apresentado anteriormente (reset), conecte-o com o vcc, clique para fazer o deploy e em seguida retorne o fio branco à posição original. Isso fara com que o ESP8266 se reinicie, e entre em modo de programação.

Com o ESP ainda conectado ao PC pelo módulo FTD232, abra o monitor da porta serial com o atalho CTRL + SHIFT + M e verifique se o módulo ESP8266 conectou-se a sua rede. Certifique-se de que o campo de velocidade do monitor seja o mesmo configurado no código (115200). 

Agora o DHT11 enviará os dados de temperatura e umidade direto para o ESP, que, conectado ao portal IoT WEG, armazena as informações nos bancos de dados, e esses dados aparecem na sua planta cadastrada!
