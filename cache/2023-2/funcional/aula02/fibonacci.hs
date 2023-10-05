fibonacci :: Int -> Int
fibonacci 1 = 0
fibonacci 2 = 1
fibonacci n = fibonacci (n-1) + fibonacci (n-2)
   --|Caso base 1
   --|Caso base 2
   --|otherwise = Caso Geral