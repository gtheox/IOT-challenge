# 🛰️ Mottu IOT - Rastreador GPS/GPRS

Projeto de Internet das Coisas (IoT) para a matéria de Arquiteturas Disruptivas, focado na criação de um dispositivo de rastreamento em tempo real para a frota de motocicletas da empresa Mottu.

---

## 📚 Sumário

- [Integrantes](#-integrantes)
- [📍 Problema](#-problema)
- [📶 Justificativa para Uso de IoT](#-justificativa-para-uso-de-iot)
- [🏛️ Arquitetura da Solução Completa](#️-arquitetura-da-solução-completa)
- [🛠️ Tecnologias Utilizadas](#️-tecnologias-utilizadas)
- [🔌 Circuito e Montagem](#-circuito-e-montagem)
- [📊 Fluxograma de Funcionamento](#-fluxograma-de-funcionamento)
- [🚀 Como Configurar e Usar](#-como-configurar-e-usar)
- [✅ Resultados](#-resultados)
- [📹 Vídeo de Apresentação](#-vídeo-de-apresentação)

---

## 👨‍💻 Integrantes

| Nome                           | RM     | GitHub                                          |
| ------------------------------ | ------ | ----------------------------------------------- |
| Gabriel Teodoro Gonçalves Rosa | 555962 | [gtheox](https://github.com/gtheox)             |
| Luka Shibuya                   | 558123 | [lukashibuya](https://github.com/lukashibuya)   |
| Eduardo Giovannini             | 555030 | [DuGiovannini](https://github.com/DuGiovannini) |

---

## 📍 Problema

A empresa Mottu enfrenta desafios na gestão eficiente de suas motos, que são distribuídas por diversos pátios. O controle manual resulta em imprecisão, perdas, atrasos operacionais e dificuldade em monitorar a localização e o status exato de cada veículo, impactando a eficiência e aumentando custos.

## 📶 Justificativa para Uso de IoT

A tecnologia de Internet das Coisas (IoT) é a solução ideal para automatizar e otimizar este monitoramento. Através de sensores e comunicação em tempo real, o IoT permite a captura de dados precisos e constantes sobre a localização das motos, tornando o processo mais rápido, confiável e menos suscetível a erros humanos.

---

## 🏛️ Arquitetura da Solução Completa

A solução foi projetada como um ecossistema integrado, conectando três projetos:

1.  **Dispositivo IoT (Este Projeto):** Um protótipo baseado em ESP32 com um módulo A9G (GPS/GPRS) é instalado na moto. Ele captura as coordenadas de GPS e as envia periodicamente via rede celular (HTTP POST).
2.  **Backend (API .NET):** Uma API RESTful recebe os dados de localização do dispositivo IoT e os persiste em um banco de dados Oracle, atualizando o registro da moto correspondente.
3.  **Frontend (App Mobile):** Um aplicativo em React Native consome a API .NET para exibir os dados. A tela de "Detalhes da Moto" funciona como um **dashboard de telemetria**, exibindo a última localização recebida em um mapa.

---

## 🛠️ Tecnologias Utilizadas

- **Hardware:**
  - `ESP32 WiFi LoRa`: Microcontrolador principal com display OLED integrado.
  - `Módulo A9G`: Responsável pela captura de coordenadas GPS e comunicação via rede celular GPRS.
  - `Push Button`: Para interações de configuração no dispositivo.
- **Software Embarcado:**
  - `Arduino Framework (C++)`: Linguagem de programação para o ESP32.
  - `TinyGPS++`: Biblioteca para decodificação de dados de GPS.
- **Backend & Persistência:**
  - `API em ASP.NET Core`: Para receber e processar os dados de telemetria.
  - `Banco de Dados Oracle`: Para o registro persistente do histórico de dados.
- **Frontend & Dashboard:**
  - `React Native com Expo`: Para a interface gráfica (dashboard) que exibe a localização em tempo real.

---

## 🔌 Circuito e Montagem

_Insira aqui a imagem da idealização do seu circuito. Você pode fazer o upload da imagem para o seu repositório GitHub e referenciá-la aqui._
`![Diagrama do Circuito](caminho/para/sua/imagem_do_circuito.png)`

---

## 📊 Fluxograma de Funcionamento

_Insira aqui a imagem do seu fluxograma._
`![Fluxograma](caminho/para/sua/imagem_do_fluxograma.png)`

---

## 🚀 Como Configurar e Usar

**1. Backend (API .NET)**

- Garanta que a API .NET esteja em execução e acessível na rede local.

**2. Hardware (Dispositivo IoT)**

1.  Abra o arquivo `Rastreador.ino` na Arduino IDE.
2.  Atualize as variáveis `SERVER_IP` com o IP da máquina onde a API está rodando, `SERVER_PORT` com a porta correta (ex: 5012) e `APN` com a da sua operadora de celular.
3.  Carregue (upload) o código para a placa ESP32.
4.  Ligue o dispositivo. Ele tentará se conectar à rede GPRS e obter um sinal de GPS.

**3. Frontend (App Mobile)**

1.  Execute o aplicativo mobile em um emulador ou dispositivo físico.
2.  Navegue até a lista de motos e clique em uma para ver a tela de detalhes. O mapa exibirá a última localização enviada pelo dispositivo IoT.

---

## ✅ Resultados

O projeto resultou em um protótipo de ponta a ponta totalmente funcional:

- O dispositivo IoT captura com sucesso as coordenadas de GPS.
- A comunicação via GPRS (HTTP) envia os dados de forma confiável para a API .NET.
- A API persiste os dados de localização no banco de dados Oracle.
- O aplicativo mobile funciona como um dashboard, exibindo a telemetria em um mapa, cumprindo todos os requisitos principais do desafio.

---

## 📹 Vídeo de Apresentação

https://youtu.be/owKnEOmz8ac

