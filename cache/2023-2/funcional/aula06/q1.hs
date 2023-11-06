ehPrimo :: Int -> Bool
ehPrimo n 
   | n == 1 = False
   | otherwise = (n == 2) || (mod n 1 == 0) || (mod n n == 0)