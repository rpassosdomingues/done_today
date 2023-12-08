{-
==============================
    Recuperação P1
==============================    
Aluno: Rafael Passos Domingues
   RA: 2023.1.08.036
------------------------------
-}

-- Lista aleatória a ser passada como parâmetro para testes
lista :: [Int]
lista = [2,8,4,1,7,5,3,6,9]

-- Função principal
decrescente :: [Int] -> [Int]
decrescente [] = []
decrescente (x:xs) = inverte (ordena (x:xs))

-- Usando List Comprehension com a intenção de buscar entendimento de como não usar
quickSort :: [Int] -> [Int]
quickSort [] = []
quickSort (x:xs) = quickSort [y | y <- xs, y <= x] ++ [x] ++ quickSort [y | y <- xs, y > x]

-- Tentantiva de Função de ordenação implementando quickSort sem usar o construtor de listas
ordena :: [Int] -> [Int]
ordena [] = []
ordena (x:xs) = ordena (menores xs) ++ [x] ++ ordena (maiores xs)
--ordena (x:xs) = ordena (filter (<) x) ++ [x] ++ ordena (filter (>) x)

menores :: [Int] -> [Int]
menores [] = []
menores (x:xs)
    | [x] <= (menores xs) = (x:xs)
    | otherwise = menores xs

maiores :: [Int] -> [Int]
maiores [] = []
maiores (x:xs)
    | [x] > (maiores xs) = (x:xs)
    | otherwise = maiores xs

inverte :: [Int] -> [Int]
inverte [] = []
inverte (x:xs) = inverte xs ++ [x]