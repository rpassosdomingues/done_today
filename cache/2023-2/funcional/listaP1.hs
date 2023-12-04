{-
===============================
Author: Rafael Passos Domingues
    RA: 2023.1.08.036
  Data: Nov 9 Thu [08h18]
===============================
-}

-- =============================================================================================
-- Questão 1 --
-- =============================================================================================
ehPrimo :: Int -> Bool
ehPrimo z
    | (z /= 2) && (ehPar z) = False
    | otherwise = (ehDivisivel z z)

ehPar :: Int -> Bool
ehPar y = (mod y 2) == 0

ehDivisivel :: Int -> Int -> Bool
ehDivisivel _ 0 = False
ehDivisivel a b = (mod a b) == 0

-- =============================================================================================
-- Questão 2 --
-- =============================================================================================
ordenaEmTupla :: Int -> Int -> Int -> Int -> (Int, Int, Int, Int)
ordenaEmTupla a b c d = (menor4, menor3, menor2, maior4)
    where
        menor4 = minimo a (minimo b (minimo c d))
        menor3 = minimo a (minimo b c)
        menor2 = minimo a b
        maior4 = maximo a (maximo b (maximo c d))

minimo :: Int -> Int -> Int
minimo a b
    | a < b     = a
    | otherwise = b

maximo :: Int -> Int -> Int
maximo a b
    | a > b     = a
    | otherwise = b

-- =============================================================================================
-- Questão 3 --
-- =============================================================================================
quantosDiasAno :: Int -> Int
quantosDiasAno ano
    | ehBissexto ano = 366
    | otherwise = 365

ehBissexto :: Int -> Bool
ehBissexto ano = mod ano 4 == 0

-- =============================================================================================
-- Questão 4 --
-- =============================================================================================
quantosDiasMes :: Int -> Int -> Int
quantosDiasMes ano mes
    | mes == 2 && ehBissexto ano                    = 29
    | mes == 2                                      = 28
    | mes == 4 || mes == 6 || mes == 9 || mes == 11 = 30
    | otherwise = 31

-- =============================================================================================
-- Questão 5 --
-- =============================================================================================
dia :: Int -> Int -> Int -> Int
dia ano mes dia
    | not (ehDataValida ano mes dia) = -1
    | otherwise = diasPassados ano mes dia

diasPassados :: Int -> Int -> Int -> Int
diasPassados ano mes dia = somaDias [quantosDiasMes ano m | m <- [1..mes-1]] + dia

somaDias :: [Int] -> Int
somaDias [] = 0
somaDias (x:xs) = x + somaDias xs

ehDataValida :: Int -> Int -> Int -> Bool
ehDataValida ano mes dia = mesValido && diaValido
    where
        mesValido = mes >= 1 && mes <= 12
        diaValido = dia >= 1 && dia <= quantosDiasMes ano mes

-- =============================================================================================
-- Questão 6 --
-- =============================================================================================
encontraMaiorMenor :: [Int] -> (Int, Int)
encontraMaiorMenor [] = ((-1), (-1))
encontraMaiorMenor [x] = (x, x)
encontraMaiorMenor (x:xs) = recipiente x x xs

recipiente :: Int -> Int -> [Int] -> (Int, Int)
recipiente maior menor [] = (menor, maior)
recipiente maior menor (x:xs)
    | ehMenor x menor = recipiente maior x xs
    | ehMaior x maior = recipiente x menor xs
    | otherwise = recipiente maior menor xs

ehMaior :: Int -> Int -> Bool
ehMaior a b = a > b

ehMenor :: Int -> Int -> Bool
ehMenor a b = a < b

-- =============================================================================================
-- Questão 7 --
-- =============================================================================================
quickSort :: [Int] -> [Int]
quickSort [] = []
quickSort (x:xs) = quickSort [y | y <- xs, y <= x] ++ [x] ++ quickSort [y | y <- xs, y > x]

-- =============================================================================================
-- Questão 8 --
-- =============================================================================================
replicante :: [Int] -> [Int]
replicante [] = []
replicante (x:xs) = espelho x x ++ replicante xs

espelho :: Int -> Int -> [Int]
espelho 0 _ = []
espelho n x = x : espelho (n-1) x

-- =============================================================================================
-- Questão 9 -- [Realizada com ajuda do BING AI]
-- =============================================================================================
serie :: Int -> Int -> Int
serie _ 0 = 0
serie x n = somaTermos x n 1 0 True

somaTermos :: Int -> Int -> Int -> Int -> Bool -> Int
somaTermos _ 0 _ soma _ = soma
somaTermos x n i soma inverteDivisao = somaTermos x (n - 1) (i + 2) (acumulador x i soma inverteDivisao) (not inverteDivisao)

acumulador :: Int -> Int -> Int -> Bool -> Int
acumulador x i acumula inverteDivisao = acumula + termo x i inverteDivisao

termo :: Int -> Int -> Bool -> Int
termo x i inverteDivisao
    | inverteDivisao = divisaoInteira x i
    | otherwise = divisaoInteira i x

divisaoInteira :: Int -> Int -> Int
divisaoInteira a b = a `div` b
