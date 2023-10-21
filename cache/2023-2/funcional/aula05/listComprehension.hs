listaInt :: [Int]
listaInt = [1..5]

times2 :: Int -> Int
times2 n = 2 * n

sum1 :: Int -> Int
sum1 n = n + 1

-- list Comprehension --
--times2 :: [Int] -> [Int]
--times2 lista = [2*x | x <- lista]

--times2, times3 :: Int -> Int
--times2 n = 2*n
--times3 n = 3*n

-- Qual é o tipo de mapInt ? --
--mapInt :: (Int->Int) -> [Int] -> [Int] -- funciona só com inteiros
--mapInt f [] = []
--mapInt f (x:xs) = (f x) : mapInt f xs

--mapInt :: (t->t) -> [t] -> [t] -- funciona com qualquer tipo! (Permite generalização) [reusabilidade de código]
--mapInt f [] = []
--mapInt f (x:xs) = (f x) : mapInt f xs

--mapInt :: [Int] -> [Int]
--mapInt [] = []
--mapInt (x:xs) = (sum1 x) : mapInt xs

--mapInt f lista = (f cadaElemento) : mapInt f cadaElemento
--mapInt f (x:xs) = (f x) : mapInt f xs

--mapInt f lista = [ (f x) | x <- lista]