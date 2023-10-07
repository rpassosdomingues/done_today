isHigh :: Int -> Int -> Int
isHigh a b
   | a > b = a
   | otherwise = b

bigger :: [Int] -> Int
bigger [x] = x
bigger (x:xs) = isHigh x (bigger xs)