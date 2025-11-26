# Tetris – Projeto Acadêmico em C com Raylib

## 🎮 Sobre o Projeto

Este projeto consiste no desenvolvimento de uma versão do clássico **Tetris**, programado em **C** e utilizando a biblioteca gráfica **raylib**. O jogo foi desenvolvido como parte da disciplina **Programação Imperativa e Funcional**, explorando conceitos fundamentais de lógica, modularização, estruturas de dados e fluxo de execução.

Nosso foco foi criar um **casual game funcional, organizado e de fácil manutenção**, além de proporcionar uma experiência sólida de desenvolvimento em equipe.

---

## 🚧 Estrutura do Projeto

O projeto está organizado de forma modular, separando cada responsabilidade em diretórios próprios para maior clareza e escalabilidade.

```
📂 Tetris
 ┣ 📂 src
 │  ┣ 📂 blocks        # Representação e manipulação dos blocos
 │  ┣ 📂 colors        # Definição das cores do jogo
 │  ┣ 📂 grid          # Lógica da grade e colisões
 │  ┣ 📂 Game          # Loop principal do jogo
 │  ┣ 📂 menu          # Tela e lógica do menu inicial
 │  ┗ main.c           # Arquivo principal
 ┣ 📂 raylib           # Biblioteca raylib (include + lib)
 ┗ README.md
```

---

## ▶️ Como Executar

Certifique‑se de ter a biblioteca **raylib** configurada corretamente no projeto.

A compilação deve ser feita a partir da pasta `src` usando o comando:

```bash
cd src
gcc main.c blocks/blocks.c colors/colors.c grid/grid.c Game/game.c menu/menu.c -o Tetris.exe \
   -I./raylib/include -I./blocks -I./colors -I./grid -I./Game -I./Menu \
   -L./raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
```

Após isso, basta executar o arquivo gerado:

```
./Tetris.exe
```

---

## 🕹️ Funcionalidades

* Movimentação lateral e rotação das peças
* Detecção de colisão e encaixe
* Sistema de limpeza de linhas
* Controle de níveis (3 dificuldades)
* Menu inicial funcional
* Grid responsivo
* Paleta de cores personalizada

---

## 👥 Contribuidores

* Arthur D'ávila
* Maria Eduarda Pernambuco
* Nathália Carvalho

---

## 📌 Possíveis Melhorias Futuras
* Tela de Game Over estilizada
* Implementar efeitos sonoros
* Adicionar animações na limpeza de linhas
