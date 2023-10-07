listaChar :: [Char]
listaChar = ['H','a','s','k','e','l','l']

listaInt :: [Int]
--listaInt = [1,2,3,4,5]
listaInt = [1..100]
listaPar = [0,2..30]
listaImpar = [1,3..30]
construtorLista = 1 : [2,3,4,5]
concatenaListas = [1,2] ++ [3,4]

{-
cabecaCauda :: [Int] -> Int
--cabecaCauda (h:t) = x -- head=cabeça, tail=cauda
cabecaCauda (x:xs) = x
-}