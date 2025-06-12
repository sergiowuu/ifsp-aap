# 🍷 Vinheria - Monitoramento Inteligente de Ambiente com Arduino

![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow)
![License](https://img.shields.io/badge/license-MIT-blue)
![Arduino](https://img.shields.io/badge/plataforma-Arduino%20UNO-green)

---

## 📑 Índice

- [📖 Descrição do Projeto](#descrição-do-projeto)
- [🚧 Status do Projeto](#status-do-projeto)
- [✨ Funcionalidades e Demonstração da Aplicação](#funcionalidades-e-demonstração-da-aplicação)
- [📂 Acesso ao Projeto](#acesso-ao-projeto)
- [🛠️ Tecnologias Utilizadas](#tecnologias-utilizadas)
- [🤝 Pessoas Contribuidoras](#pessoas-contribuidoras)
- [👨‍💻 Pessoas Desenvolvedoras do Projeto](#pessoas-desenvolvedoras-do-projeto)
- [📄 Licença](#licença)

---

## 📖 Descrição do Projeto

Este projeto foi desenvolvido para uma vinheria tradicional que está iniciando sua transformação digital. O objetivo é criar um sistema embarcado com Arduino UNO que monitora em tempo real os principais fatores que influenciam a qualidade do vinho armazenado: **luminosidade**, **temperatura** e **umidade**.

A aplicação simula sensores via Tinkercad, fornecendo alertas visuais e sonoros com base em faixas ideais, além de exibir valores em um display LCD. O sistema proporciona ao proprietário um nível de controle semelhante ao atendimento presencial, mesmo à distância.

---

## 🚧 Status do Projeto

🟨 **Em desenvolvimento**  
O sistema está operando em ambiente de simulação com funcionalidades essenciais implementadas, mas pode ser expandido com suporte à comunicação com sistemas web no futuro.

---

## ✨ Funcionalidades e Demonstração da Aplicação

- 📟 **Exibição sequencial de dados no LCD 16x2**
  - Temperatura com status (Baixa / OK / Alta)
  - Umidade com status (Baixa / OK / Alta)
  - Luminosidade (Escuro / Meia luz / Claro)

- 🔴 🟡 🟢 **LEDs indicativos**
  - Verde: ambiente ideal (escuro)
  - Amarelo: meia luz ou temperatura fora do ideal
  - Vermelho: muita luz ou umidade fora do ideal

- 🔊 **Buzzer de alarme**
  - Ativado em qualquer situação crítica

- 📊 **Medições com média de 5 leituras**
  - Evita variações bruscas e melhora a precisão

---

## 📂 Acesso ao Projeto

Você pode acessar a simulação do circuito diretamente no Tinkercad clicando no link abaixo:

🔗 [Acessar o projeto no Tinkercad](https://www.tinkercad.com/things/i9cVRcC92tC-desafio-vinheria?sharecode=_ZiN8jLkU_dcmi5OsLV_2vzHSaEKzdJBJCLwXj9m2P4)

> 💡 É necessário ter uma conta gratuita no Tinkercad para visualizar e editar a simulação.

---

## 🛠️ Tecnologias Utilizadas

- Arduino UNO (Tinkercad)
- Sensor de temperatura TMP36
- Potenciômetro (simula sensor de umidade)
- Sensor de luminosidade (LDR + resistor)
- LCD 16x2 (com interface de 6 fios)
- LEDs (vermelho, amarelo e verde)
- Buzzer ativo
- Linguagem C/C++ para Arduino

---

## 🤝 Pessoas Contribuidoras

Se você deseja contribuir com sugestões ou melhorias, entre em contato ou abra uma issue no repositório.

---

## 👨‍💻 Pessoas Desenvolvedoras do Projeto

- **Giovanne Brandão de Aquino**
- **Leonardo de Lima Pedroso**
- **Ricardo Queiroz Oliani**
- **Sérgio de Chong Wu**

---

## 📄 Licença

Este projeto está sob a licença **MIT**.  
Você pode usá-lo, modificar e distribuir, desde que mantenha os devidos créditos ao autor original.

---
