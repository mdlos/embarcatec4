<img width=100% src="https://capsule-render.vercel.app/api?type=waving&color=02A6F4&height=120&section=header"/>
<h1 align="center">Embarcatec | Atividade de Interrupções</h1>

<div align="center">  
  <img width=40% src="http://img.shields.io/static/v1?label=STATUS&message=DESENVOLVIDO&color=02A6F4&style=for-the-badge"/>
</div>

## 🗒️ Objetivo do Projeto

Funcionalidades

1. O LED vermelho do LED RGB deve piscar continuamente 5 vezes por segundo.
2. O botão A deve incrementar o número exibido na matriz de LEDs cada vez que for pressionado.
3. O botão B deve decrementar o número exibido na matriz de LEDs cada vez que for pressionado.
4. Os LEDs WS2812 devem ser usados para criar efeitos visuais representando números de 0 a 9.
   • Formatação fixa: Cada número deve ser exibido na matriz em um formato fixo, como
   caracteres em estilo digital (ex.: segmentos iluminados que formem o número).
   • Alternativamente, é permitido utilizar um estilo criativo, desde que o número seja claramente
   identificável.

🗒️ Lista de requisitos

Neste projeto, você deverá utilizar os seguintes componentes conectados à placa BitDogLab:
• Matriz 5x5 de LEDs (endereçáveis) WS2812, conectada à GPIO 7.
• LED RGB, com os pinos conectados às GPIOs (11, 12 e 13).
• Botão A conectado à GPIO 5.
• Botão B conectado à GPIO 6.

## 🛠 Tecnologias

1. **Git e Github**;
2. **VScode**;
3. **Linguagem C**;
4. **Extensões no VScode do Raspberry Pi Pico Project e CMake**

## 💻 Instruções para Importar, Compilar e Rodar o Código Localmente

Siga os passos abaixo para clonar o repositório, importar no VS Code usando a extensão do **Raspberry Pi Pico Project**, compilar e executar o código.

1. **Clone o repositório para sua máquina local**Abra o terminal e execute os comandos abaixo:
   ```bash
   git clone https://github.com/usuario/projeto.git
   cd projeto

   ```
2. **Abra o VS Code e instale a extensão "Raspberry Pi Pico Project" (caso não já a tenha instalada)**

- No VS Code, vá até "Extensões" (Ctrl+Shift+X)
- Pesquise por "Raspberry Pi Pico Project"
- Instale a extensão oficial

4. **Compile o projeto**
5. **Rode o código no Raspberry Pi Pico**

- Conecte o Raspberry Pi Pico ao PC segurando o botão "BOOTSEL".
- Arraste e solte o arquivo `.uf2`, localizado dentro da pasta "build" do seu projeto, gerado na unidade USB montada.
- O código será carregado automaticamente e o Pico será reiniciado.

## 💻 Desenvolvedor

<table>
  <tr>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/72825281?v=4" width="100px;" alt=""/><br /><sub><b> Marcio Fonseca </b></sub></a><br />👨‍💻</a></td>
  </tr>
</table>

## 🎥 Demonstração:

- Para ver o funcionamento do projeto, acesse o vídeo:
clique na imagem para ver o vídeo de funcionamento no Linux:
[![Demostração](https://github.com/mdlos/embarcatec4/blob/main/imagens/2025-01-31.png?raw=true)](https://youtu.be/OZlVZHFHEOo)

</div>
