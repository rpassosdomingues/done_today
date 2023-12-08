{-
===============================
Author: Rafael Passos Domingues
    RA: 2023.1.08.036
  Data: Dec 8 Fri [17h00]
===============================
-}

listaIntA :: [Int]
listaIntA = [1..10]

listaIntB :: [Int]
listaIntB = [100..90]

-- =============================================================================================
-- Questão 1 --
-- =============================================================================================

-- Função principal
ehPerfeito :: Int -> Bool
ehPerfeito n = (somaDivisores n) == n

-- Função auxiliar para obter a soma dos divisores de um número
somaDivisores :: Int -> Int
somaDivisores m = acumulador [divisor | divisor <- [1..m-1], (ehDivisivel m divisor)]

-- Função auxiliar para acumular a soma dos divisores
acumulador :: [Int] -> Int
acumulador [] = 0
acumulador (x:xs) = foldr (+) x xs -- x + acumulador xs

-- Função auxiliar para verificar se um número é divisível por outro, evitando divisão por zero.
ehDivisivel :: Int -> Int -> Bool
ehDivisivel _ 0 = False
ehDivisivel a b = (mod a b) == 0

-- =============================================================================================
-- Questão 2 --
-- =============================================================================================

-- Função principal
contaString :: [Char] -> [(Char, Int)]
contaString xs = contaStringAux xs xs

-- Função auxiliar recursiva
contaStringAux :: [Char] -> [Char] -> [(Char, Int)]
contaStringAux _ [] = []
contaStringAux original (x:xs) =
  (x, contaChar x original) : contaStringAux original xs

-- Função auxiliar para somar as letras
contaChar :: Char -> [Char] -> Int
contaChar l xs = foldr (somaSeIgual l) 0 xs

-- Função auxiliar para somar se o caractere for igual
somaSeIgual :: Char -> Char -> Int -> Int
somaSeIgual l x acc
  | x == l = acc + 1
  | otherwise = acc

-- =============================================================================================
-- Questão 3 --
-- =============================================================================================

inverteString :: [Char] -> [Char]
inverteString [] = []
inverteString (x:xs) = inverteString xs ++ [x]

-- =============================================================================================
-- Questão 4 --
-- =============================================================================================

listaQuadrados :: [Int] -> [Int]
listaQuadrados (x:xs) = map quadrado (x:xs)

quadrado :: Int -> Int
quadrado q = q * q

-- =============================================================================================
-- Questão 5 --
-- =============================================================================================

simulaCartesiano :: [Int] -> [Int] -> [(Int, Int)]
simulaCartesiano [] _ = []
simulaCartesiano _ [] = []
simulaCartesiano (x:xs) (y:ys) = [(x, y) | y <- ys] ++ simulaCartesiano xs ys

-- =============================================================================================
-- Questão 6 --
-- =============================================================================================

filtraPositivos :: [Int] -> [Int]
filtraPositivos xs = filter ehPositivo xs

ehPositivo :: Int -> Bool
ehPositivo n = n >= 0