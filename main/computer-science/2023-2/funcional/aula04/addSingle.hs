contains :: [Int] -> Int -> Bool
contains [] _ = False
contains (x:xs) n
    | x == n = True
    | otherwise = contains xs n

addSingle :: [Int] -> Int -> [Int]
addSingle xs n
    | contains xs n = xs
    | otherwise = xs ++ [n]