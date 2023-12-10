merge :: [Int] -> [Char] -> [(Int, Char)]
merge [] [] = []
merge (a:b) (c:d) = (a,c) : merge b d