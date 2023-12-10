{-
===============================
Author: Rafael Passos Domingues
    RA: 2023.1.08.036
  Data: Oct 21 Sat [19h00]
===============================
-}

import Data.Char

listaInt :: [Int]
listaInt = [1..5]

listaChar :: [Char]
listaChar = ['a'..'e']

-- tupla 1
pessoaFilmes :: (Int, String, String, Bool, Int)
pessoaFilmes = (27, "Rafael", "Ficção Científica", True, 150)

-- tupla 2
filmeRecomendado :: (String, Int, [String])
filmeRecomendado = ("Interestelar", 169, ["Matthew McConaughey", "Anne Hathaway"])

-- (1) Desenvolva uma função polimórfica que retorne o reverso de uma lista.

inverteLista :: [t] -> [t]
inverteLista [] = []
inverteLista (x:xs) = inverteLista xs ++ [x]

-- (2) Desenvolva uma função polimórfica que retorne duplas de elementos de duas tuplas que são passadas como parâmetro

match :: (Int, String, String, Bool, Int) -> (String, Int, [String]) -> [(String, String)]
match (idade, nome, _, _, _) (_, _, atores) = [(nome, ator) | ator <- atores]

netflix :: [(String, String)]
netflix = match pessoaFilmes filmeRecomendado

-- (3) Aplicar a função pré-definida isDigit a partir do import Data.Char
-- Função que filtra os dígitos de uma string

aniversario = "14 Julho 1996"

digits :: String -> String
digits cenoura = filter isDigit cenoura