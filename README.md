# Projeto IoT - Sistemas Embarcados - Engenharia de Computação - UFRN 

Trabalho referente a disciplina DCA3706 - Sistemas Embarcados, Universidade Federal do Rio Grande do Norte (UFRN).

## 1. Objetivo do Projeto

O objetivo deste trabalho é projetar e simular um sistema embarcado completo conectado à internet. O sistema deve ser capaz de coletar dados de um sensor, exibi-los em um display local, sincronizar seu relógio com um servidor NTP e publicar os dados coletados em um broker MQTT remoto.

Uma restrição fundamental do projeto é o uso da **linguagem C pura**, sem a utilização das funções e bibliotecas do framework Arduino.

## 2. Problematização: Monitoramento de Estufa Inteligente

Como problematização, este projeto simula um dispositivo de monitoramento para uma estufa inteligente. O sistema coletará dados vitais (temperatura e umidade) do ambiente. O monitoramento dessas variáveis é crucial para garantir as condições ideais para o crescimento de plantas, permitindo o acompanhamento remoto e a futura automação de sistemas de ventilação ou irrigação.

## 3. Stack de Hardware e Software

Este projeto é desenvolvido na plataforma de simulação Wokwi utilizando a seguinte stack:

* **Microcontrolador:** Atmega328P (simulado na placa Arduino Uno).
* **Linguagem:** C (AVR-GCC), com manipulação direta de registradores.
* **Sensor:** DHT22 (para medição de temperatura e umidade).
* **Display:** OLED SSD1306 (comunicação via I2C).
* **Interface de Rede:** Módulo Ethernet W5500 (comunicação via SPI).

## 4. Requisitos Funcionais

* [ ] Coletar dados do sensor DHT22.
* [ ] Exibir a última leitura no display OLED.
* [ ] Conectar à rede via módulo Ethernet (W5500).
* [ ] Sincronizar o relógio interno via NTP.
* [ ] Armazenar 10 amostras em uma fila (com leituras a cada 1 segundo).
* [ ] Publicar o grupo de 10 amostras em um broker MQTT.
