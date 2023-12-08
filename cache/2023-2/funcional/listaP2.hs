{-
===============================
Author: Rafael Passos Domingues
    RA: 2023.1.08.036
  Data: Dec 8 Fri [16h00]
===============================
-}

listaIntA :: [Int]
listaIntA = [1..10]

listaIntB :: [Int]
listaIntB = [100..90]

-- =============================================================================================
-- Questão 1 --
-- =============================================================================================

ehPerfeito :: Int -> Bool
ehPerfeito n = (somaDivisores n) == n

somaDivisores :: Int -> Int
somaDivisores m = acumulador [divisor | divisor <- [1..m-1], (ehDivisivel m divisor)]

acumulador :: [Int] -> Int
acumulador [] = 0
acumulador (x:xs) = foldr (+) x xs -- x + acumulador xs

ehDivisivel :: Int -> Int -> Bool
ehDivisivel _ 0 = False
ehDivisivel a b = (mod a b) == 0

-- =============================================================================================
-- Questão 2 --
-- =============================================================================================

contaString :: [Char] -> [(Char, Int)]
contaString xs = contaStringAux xs xs

contaStringAux :: [Char] -> [Char] -> [(Char, Int)]
contaStringAux _ [] = []
contaStringAux original (x:xs) =
  (x, contaChar x original) : contaStringAux original xs

contaChar :: Char -> [Char] -> Int
contaChar l xs = foldr (somaSeIgual l) 0 xs

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
simulaCartesiano (x:xs) listaB = combinaElementos x listaB ++ simulaCartesiano xs listaB

combinaElementos :: Int -> [Int] -> [(Int, Int)]
combinaElementos _ [] = []
combinaElementos x (y:ys) = (x, y) : combinaElementos x ys

-- =============================================================================================
-- Questão 6 --
-- =============================================================================================

filtraPositivos :: [Int] -> [Int]
filtraPositivos xs = filter ehPositivo xs

ehPositivo :: Int -> Bool
ehPositivo n = n >= 0

-- =============================================================================================
-- Questão 7 --
-- =============================================================================================

somaLista :: [Int] -> Int
somaLista [] = 0
somaLista [x] = dobro x
somaLista (x:xs) = foldr (+) (dobro x) (somaDobro xs)

somaDobro :: [Int] -> [Int]
somaDobro lista = map dobro lista

dobro :: Int -> Int
dobro n = 2 * n

-- =============================================================================================
-- Questão 8 --
-- =============================================================================================

juntaSilabas :: [[Char]] -> [Char]
juntaSilabas = foldr (++) []
--juntaSilabas [] = []
--juntaSilabas (x:xs) = x ++ juntaSilabas xs