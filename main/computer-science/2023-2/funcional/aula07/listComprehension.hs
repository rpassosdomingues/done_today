isEven :: Int -> Bool
isEven x = mod x 2 == 0

buildList = [x*x | x <- [9..39], isEven x]
otherBuildList = [y*y | y <- [9..39], isEven y, y > 11, y < 19]

aList = [v | v <- [9..90], v < 100]
bList = ['a'..'g']

zipar :: [Int] -> [Bool] -> [(Int,Bool)]
zipar [] [] = []
zipar (x:xs) (y:ys) = (x,y) : zipar xs ys

inverteLista :: [a] -> [a]
inverteLista [] = []
inverteLista (x:xs) = inverteLista xs ++ [x]