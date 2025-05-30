﻿# Mottu Control - Documentação do Projeto

## 📍 Problema

As filiais da empresa Mottu enfrentam desafios significativos na gestão e monitoramento das motos estacionadas em seus pátios. A ausência de um sistema automatizado resulta em problemas como:

- Dificuldades em localizar motos específicas rapidamente.
- Ineficiência na gestão de disponibilidade e manutenção das motos.
- Alto índice de erros decorrentes do registro manual.
- Atrasos operacionais e aumento de custos.

Esses desafios impactam diretamente a eficiência operacional e a satisfação do cliente, destacando a necessidade de uma solução tecnológica efetiva.

## 📶 Justificativa para uso de IoT

A escolha pela tecnologia de IoT (Internet das Coisas) justifica-se pela capacidade de coletar, transmitir e gerenciar informações em tempo real. O uso de dispositivos IoT permite:

- Monitoramento remoto e contínuo das motos.
- Atualização imediata do status das motos e suas localizações.
- Automação de tarefas manuais que hoje geram ineficiência.
- Redução significativa de erros e retrabalho operacional.

A implementação de IoT proporcionará maior eficiência operacional, economia de recursos e uma gestão estratégica aprimorada.

## 🛠️ Tecnologias utilizadas

O projeto utilizará as seguintes tecnologias principais:

- **ESP32 WiFi LoRa:**  
  Microcontrolador robusto, capaz de conectar-se a redes Wi-Fi e LoRa, possibilitando comunicação estável e eficiente entre dispositivos.

- **Módulo A9G:**  
  Dispositivo GSM/GPRS + GPS que será responsável por:

  - Coletar e fornecer informações precisas sobre localização das motos.
  - Comunicar-se via rede celular para envio das coordenadas GPS para servidores remotos.

- **React Native e Expo:**  
  Para o desenvolvimento de um aplicativo mobile com interface amigável, permitindo aos usuários visualizar e gerenciar as motos em tempo real.

- **AsyncStorage:**  
  Armazenamento local no aplicativo mobile para dados como cadastro de motos, clientes e históricos.

- **Ionicons e LinearGradient:**  
  Componentes gráficos para uma interface visual agradável, intuitiva e padronizada com a identidade visual da Mottu.

## ✅ Resultados Parciais

Até o momento, o projeto obteve avanços expressivos:

- Comunicação eficaz entre o módulo A9G e ESP32, garantindo captura precisa dos dados de GPS.
- Envio contínuo e estável das coordenadas GPS via GSM/GPRS utilizando requisições HTTP.
- Protótipo funcional do aplicativo mobile, com telas intuitivas para gerenciamento e visualização das motos cadastradas.
- Armazenamento local confiável utilizando AsyncStorage.
- Fluxo robusto de navegação no aplicativo implementado com React Navigation, facilitando a usabilidade.

Esses resultados validam a viabilidade técnica da solução e abrem caminho para as próximas etapas do desenvolvimento.

## Integrantes 
- Gabriel Teodoro RM555962
- Luka Shibuya RM558123
- Eduardo Giovannini RM555030

