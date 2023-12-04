{-
===============================
Author: Rafael Passos Domingues
    RA: 2023.1.08.036
  Data: Dec 8 Fri [17h00]
===============================
-}

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
acumulador (x:xs) = foldr (+) x xs

-- Função auxiliar para verificar se um número é divisível por outro, evitando divisão por zero.
ehDivisivel :: Int -> Int -> Bool
ehDivisivel _ 0 = False
ehDivisivel a b = (mod a b) == 0