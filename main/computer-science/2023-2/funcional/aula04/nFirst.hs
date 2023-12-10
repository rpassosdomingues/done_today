nFirst :: [Int] -> Int -> [Int]
nFirst [] _ = []
nFirst _ 0 = []
nFirst (x:xs) n = x : nFirst xs (n-1)