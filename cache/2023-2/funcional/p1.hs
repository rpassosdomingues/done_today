{-
===============================
Author: Rafael Passos Domingues
    RA: 2023.1.08.036
  Data: Nov 10 Fri [12h00]
===============================
-}

-- =============================================================================================
-- Questão 1 --
-- =============================================================================================
ehPar :: Int -> Bool
ehPar numero = mod numero 2 == 0

ehDivisivel :: Int -> Int -> Bool
ehDivisivel numerador denominador = mod numerador denominador == 0

temDivisorImpar :: Int -> Int -> Bool
temDivisorImpar num divisor
    | divisor * divisor > num = True
    | ehDivisivel num divisor = False
    | otherwise               = temDivisorImpar num (divisor + 2)

ehPrimo :: Int -> Bool
ehPrimo n
    | n <= 1    = False
    | n == 2    = True
    | ehPar n   = False
    | otherwise = not (temDivisorImpar n 3)

-- =============================================================================================
-- Questão 2 --
-- =============================================================================================
minimo :: Int -> Int -> Int
minimo a b
    | a < b     = a
    | otherwise = b

maximo :: Int -> Int -> Int
maximo a b
    | a > b     = a
    | otherwise = b

ordenaEmTupla :: Int -> Int -> Int -> Int -> (Int, Int, Int, Int)
ordenaEmTupla a b c d = (menor4, menor3, menor2, maior4)
    where
        menor4 = minimo a (minimo b (minimo c d))
        menor3 = minimo a (minimo b c)
        menor2 = minimo a b
        maior4 = maximo a (maximo b (maximo c d))

-- =============================================================================================
-- Questão 3 --
-- =============================================================================================
ehBissexto :: Int -> Bool
ehBissexto ano = mod ano 4 == 0

quantosDias :: Int -> Int
quantosDias ano
    | ehBissexto ano = 366
    | otherwise = 365

-- =============================================================================================
-- Questão 4 --
-- =============================================================================================
diasMes :: Int -> Int -> Int
diasMes ano mes
    | mes == 2 && ehBissexto ano                    = 29
    | mes == 2                                      = 28
    | mes == 4 || mes == 6 || mes == 9 || mes == 11 = 30
    | otherwise = 31

-- =============================================================================================
-- Questão 5 --
-- =============================================================================================
dataValida :: Int -> Int -> Int -> Bool
dataValida ano mes dia = mesValido && diaValido
    where
        mesValido = mes >= 1 && mes <= 12
        diaValido = dia >= 1 && dia <= diasMes ano mes

diasPassados :: Int -> Int -> Int -> Int
diasPassados ano mes dia = sum [diasMes ano m | m <- [1..mes-1]] + dia

dia :: Int -> Int -> Int -> Int
dia ano mes dia
    | not (dataValida ano mes dia) = -1
    | otherwise = diasPassados ano mes dia

-- =============================================================================================
-- Questão 6 --
-- =============================================================================================
ehMaior :: Int -> Int -> Bool
ehMaior a b = a > b

ehMenor :: Int -> Int -> Bool
ehMenor a b = a < b

encontraMaiorEMenor :: [Int] -> (Int, Int)
encontraMaiorEMenor [] = ((-1),(-1))
encontraMaiorEMenor [x] = (x, x)
encontraMaiorEMenor (x:xs) = recMaiorMenor x x xs
    where
        recMaiorMenor maior menor [] = (menor, maior)
        recMaiorMenor maior menor (x:xs)
            | ehMenor x menor = recMaiorMenor maior x xs
            | ehMaior x maior = recMaiorMenor x menor xs
            | otherwise = recMaiorMenor maior menor xs

-- =============================================================================================
-- Questão 7 --
-- =============================================================================================
quicksort :: (Ord a) => [a] -> [a]
quicksort [] = []
quicksort (x:xs) = quicksort [y | y <- xs, y <= x] ++ [x] ++ quicksort [y | y <- xs, y > x]

ordena :: (Ord a) => [a] -> [a]
ordena = quicksort

-- =============================================================================================
-- Questão 8 --
-- =============================================================================================
repeteElemento :: [Int] -> [Int]
repeteElemento [] = []
repeteElemento (x:xs) = replicate x x ++ repeteElemento xs

-- =============================================================================================
-- Questão 9 --
-- =============================================================================================
serie :: Int -> Int -> Int
serie _ 0 = 0
serie x n = somaSerie x n 1 0 True

somaSerie :: Int -> Int -> Int -> Int -> Bool -> Int
somaSerie _ 0 _ soma _ = soma
somaSerie x n i soma divisao = somaSerie x (n - 1) (i + 2) (somaTermo x i soma divisao) (not divisao)

somaTermo :: Int -> Int -> Int -> Bool -> Int
somaTermo x i acumulador divisao
    | divisao = acumulador + (x `div` i)
    | otherwise = acumulador + (i `div` x)

