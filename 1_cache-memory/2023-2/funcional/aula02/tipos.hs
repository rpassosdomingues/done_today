--ehMaior :: Int -> Int -> Bool
--ehMaior m n = m > n

--logaritmo :: Float -> Float 		   (?)
--logaritmo operado = logBase base operado (?)

--fibonacci :: Int -> Int
--fibonacci 1 = 0
--fibonacci 2 = 1
--fibonacci n = fibonacci (n-1) + fibonacci (n-2)

fatorial :: Integer -> Integer
fatorial 0 = 1			-- base
fatorial n = n * fatorial (n-1) -- chamada recursiva passando o valor de n
