{-
-- Fatorial sem uso da multiplicação --
! limitado a fatorial de 8 !
===============================
Autor: Rafael Passos Domingues
   RA: 2023.1.08.036
 Data: Sep 24 Sun [22h30]
===============================
-}

--Usando Multiplicação
--fatorial :: Integer -> Integer
--fatorial 0 = 1			            --base
--fatorial n = n * fatorial (n-1) --chamada recursiva passando o valor de n

soma :: Int -> Int -> Int
soma x y
  | x == 0    = y
  | y == 0    = x
  | otherwise = soma (x - 1) (y + 1)

multiplica :: Int -> Int -> Int
multiplica a b
  | a == 0    = 0
  | b == 0    = 0
  | otherwise = soma a (multiplica a (b - 1))

--Sem usar multiplicação
fatorial :: Int -> Int
fatorial 0 = 1                                --base
fatorial n = multiplica n (fatorial (n - 1))  --chamada recursiva fazendo reuso da função de soma