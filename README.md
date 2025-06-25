# SenseClima – Estação Ambiental MQTT

## 🎯 Objetivo

Desenvolver um dispositivo embarcado capaz de realizar leituras periódicas de temperatura e umidade do ambiente, utilizando o sensor DHT22, e enviar essas informações via MQTT para um broker remoto. O projeto utiliza o microcontrolador iMCP HTNB32L e é alimentado por bateria, adotando práticas de economia de energia para prolongar sua autonomia.

## 🧰 Componentes Utilizados

- **Microcontrolador:** iMCP HTNB32L  
- **Sensor de temperatura e umidade:** DHT22 (GPIO)  
- **Conectividade:** NB-IoT (modem interno)  
- **Alimentação:** Bateria recarregável (ex: Li-Ion 3.7 V)  
- **Broker MQTT:**  
  - IP: `131.255.82.115`  
  - Porta: `1883`  
- **PCB personalizada:** obrigatória para montagem do dispositivo final

## ⚙️ Requisitos Funcionais

### Leitura do sensor DHT22

- Capturar valores de temperatura e umidade relativa.
- Validar os dados lidos; caso inválidos, publicar `"NaN"`.

### Envio via MQTT

- Publicar os dados periodicamente nos tópicos padronizados.
- Os intervalos de envio devem ser definidos pelos próprios desenvolvedores.

### Recebimento via MQTT

- Escutar comandos para ajuste do intervalo de envio de dados.

### Economia de Energia

- Utilizar modo low power entre leituras e transmissões.
- Determinar os melhores valores de intervalo para equilibrar desempenho e autonomia.

## 🛰️ Tópicos MQTT Padronizados

> **IMPORTANTE**: Substitua `<ambiente>` pelo nome do local e `<board>` por um identificador único do dispositivo (ex: `lab1`, `node1`). Ambos devem ser em letras minúsculas e sem espaços.

| Finalidade   | Tópico MQTT                                         | Direção   | Tipo de dado |
|--------------|------------------------------------------------------|-----------|---------------|
| Temperatura  | `hana/<ambiente>/senseclima/<board>/temperature`    | Publicação | `"27.8"`     |
| Umidade      | `hana/<ambiente>/senseclima/<board>/humidity`       | Publicação | `"64.2"`     |
| Intervalo    | `hana/<ambiente>/senseclima/<board>/interval`       | Assinatura | `"30"`       |

## 🖨️ Desenvolvimento da PCB

- A placa deve integrar o HTNB32L e o sensor DHT22.
- Deve conter conector de bateria e, se possível, circuito de recarga.
- Marcação serigrafada clara dos pinos e sinais.
- Projeto realizado em EasyEDA, KiCad ou similar.
- Entregas: `.pdf` e `.gerber` do layout, `.pdf` do esquemático.

## 🔍 Observações Técnicas

- O DHT22 requer tempo de estabilização ao ligar.
- Leituras muito frequentes reduzem a vida útil da bateria.
- Reconectar automaticamente ao broker MQTT em caso de falha.
- Testar diferentes intervalos para melhor desempenho energético.

## 📋 Critérios de Avaliação

- Funcionamento do envio dos dados via MQTT.
- Controle remoto do intervalo de leitura.
- Uso correto dos tópicos MQTT.
- Documentação completa na Wiki do GitHub com progresso e dificuldades.
- Projeto de PCB funcional e documentado.
- Implementação de baixo consumo de energia.
- Apresentação funcional do projeto.
- *(Opcional)* Registro pessoal com aprendizados adquiridos.

---

> Projeto desenvolvido no Módulo 4 do Curso de Capacitação em Sistemas Embarcados com o iMCP HTNB32L – Hana Embedded.
