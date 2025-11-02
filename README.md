# Projeto IoT - Sistemas Embarcados (Unidade 3)

[cite_start]Este projeto é um trabalho individual para a disciplina DCA3706 - Sistemas Embarcados [cite: 4][cite_start], da Universidade Federal do Rio Grande do Norte (UFRN) [cite: 2][cite_start], ministrada pelo Prof. Micael Balza[cite: 5].

## 1. Objetivo do Projeto

[cite_start]O objetivo deste trabalho é projetar e simular um sistema embarcado completo conectado à internet[cite: 9]. [cite_start]O sistema deve ser capaz de coletar dados de um sensor [cite: 10][cite_start], exibi-los em um display local [cite: 11][cite_start], sincronizar seu relógio com um servidor NTP [cite: 12] [cite_start]e publicar os dados coletados em um broker MQTT remoto[cite: 14].

[cite_start]Uma restrição fundamental do projeto é o uso da **linguagem C pura**, sem a utilização das funções e bibliotecas do framework Arduino[cite: 35].

## 2. Problematização: Monitoramento de Estufa Inteligente

[cite_start]Como problematização[cite: 19], este projeto simula um dispositivo de monitoramento para uma estufa inteligente. O sistema coletará dados vitais (temperatura e umidade) do ambiente. O monitoramento dessas variáveis é crucial para garantir as condições ideais para o crescimento de plantas, permitindo o acompanhamento remoto e a futura automação de sistemas de ventilação ou irrigação.

## 3. Stack de Hardware e Software

Este projeto é desenvolvido na plataforma de simulação Wokwi utilizando a seguinte stack:

* **Microcontrolador:** Atmega328P (simulado na placa Arduino Uno).
* **Linguagem:** C (AVR-GCC), com manipulação direta de registradores.
* **Sensor:** DHT22 (para medição de temperatura e umidade).
* **Display:** OLED SSD1306 (comunicação via I2C).
* **Interface de Rede:** Módulo Ethernet W5500 (comunicação via SPI).

## 4. Requisitos Funcionais

* [cite_start][ ] Coletar dados do sensor DHT22[cite: 10].
* [cite_start][ ] Exibir a última leitura no display OLED[cite: 11].
* [cite_start][ ] Conectar à rede via módulo Ethernet (W5500)[cite: 29].
* [cite_start][ ] Sincronizar o relógio interno via NTP[cite: 12].
* [cite_start][ ] Armazenar 10 amostras em uma fila (com leituras a cada 1 segundo)[cite: 13, 32].
* [cite_start][ ] Publicar o grupo de 10 amostras em um broker MQTT[cite: 14, 33].
