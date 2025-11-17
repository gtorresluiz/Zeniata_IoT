# 📘 Projeto Zeniata – Sistema Inteligente de Monitoramento de Permanência na Cadeira

## 👥 Integrantes

- **Eduardo Fedeli Souza** — RM550132  
- **Gabriel Torres Luiz** — RM98600  
- **Otávio Vitoriano Da Silva** — RM552012  

## 🧠 Visão Geral

O **Zeniata** é um sistema IoT desenvolvido para monitorar quanto tempo uma pessoa permanece sentada e enviar alertas automáticos quando o limite saudável é ultrapassado.
Ele combina **sensor de pressão, microcontrolador, MQTT e Node-RED** para gerar alertas por e-mail ou outras plataformas.

O objetivo é promover bem-estar, reduzir sedentarismo e incentivar pausas regulares, alinhado ao contexto do **futuro do trabalho**.

## 🪑 O Problema

No ambiente corporativo moderno, pessoas passam horas sentadas sem perceber.
Esse comportamento pode gerar:

- **Dores lombares e desconforto**  
- **Fadiga física e mental**  
- **Redução de produtividade**  
- **Riscos de lesões por esforço repetitivo**
- **Sedentarismo prolongado**

O desafio é monitorar o tempo sentado de forma não invasiva, baixa complexidade e alertar quando necessário.

## ⚙️ A Solução – Projeto Zeniata

O Zeniata utiliza um sensor de pressão instalado na cadeira para detectar quando a pessoa está sentada.
Esses dados são enviados para um microcontrolador (ESP32/ESP8266/Arduino + Wi-Fi), que transmite as leituras via MQTT para o Node-RED.

No Node-RED:

- O valor da pressão é recebido;
- É analisado se o usuário permanece sentado por muito tempo;
- Um controle evita múltiplos alertas (mínimo 1 minuto entre e-mails);
- Um e-mail é enviado automaticamente em caso de risco.

Diferenciais da solução

- Simples, de baixo custo e fácil instalação.
- Comunicação IoT 100% funcional via MQTT.
- Fluxo escalável para dashboards, SMS, WhatsApp, Teams etc.
- Automatização inteligente com Node-RED.

## 🔌 Arquitetura do Sistema

###[SENSOR DE PRESSÃO] 
        ↓
###[ESP32 / ESP8266]
        ↓ MQTT
###[BROKER MQTT]
        ↓
###[NODE-RED] 
  
→ Processamento
→ Lógica de tempo
→ Envio de e-mail

## 🧩 Tecnologias

### Hardware

- Sensor de pressão (FSR / sensor resistivo)
- ESP32 ou ESP8266
- Jumpers
- Protoboard
- Fonte USB

### Software

- Arduino IDE
- Biblioteca PubSubClient (MQTT)
- Node-RED
- Node de E-mail (nodemailer ou node padrão)
- Broker MQTT (public ou local: Mosquitto, HiveMQ, EMQX)

## 📈 Resultados Esperados

- Prevenção de desconfortos físicos
- Incentivo a pausas saudáveis
- Melhoria de ergonomia e bem-estar
- Aumento de produtividade
- Sistema escalável e aplicável em empresas reais

## 📄 Licença

### Projeto acadêmico — uso livre para estudo e melhorias.
