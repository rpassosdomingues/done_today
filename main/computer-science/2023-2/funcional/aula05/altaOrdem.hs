{-
-- Folding
folding :: [Int] -> Int

-- Filtering
filter :: [Int] ->[Int]

-- Mapping
mapping :: [Int] -> [Int]

-- funções pre-definidas do hugs: foldrl, map, filter

--polimorfismo: função que aceita qualquer tipo de argumento
-}

listaInt :: [Int]
listaInt = [1..5]

times2 :: [Int] -> [Int]
times2 [] = []
times2 (x:xs) = (2*x) : times2 xs

times3 :: [Int] -> [Int]
times3 [] = []
times3 (x:xs) = (3*x) : times3 xs