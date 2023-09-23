#!/bin/bash

# Informações do repositório
REPO_NAME="novo_repositorio"
GITHUB_USER="rpassosdomingues"
FILE_NAME="README.md"
COMMIT_MESSAGE="first commit"

# Crie um novo diretório
mkdir $REPO_NAME
cd $REPO_NAME

# Inicialize o repositório Git
git init

# Crie um arquivo README.md com algum conteúdo
echo "# Meu Novo Repositório" >> $FILE_NAME

# Adicione o arquivo README.md ao repositório
git add $FILE_NAME

# Faça o primeiro commit
git commit -m "$COMMIT_MESSAGE"

# Associe o repositório local ao repositório remoto no GitHub
git remote add origin https://github.com/$GITHUB_USER/$REPO_NAME.git

# Faça o push do código para o GitHub
git push -u origin main
