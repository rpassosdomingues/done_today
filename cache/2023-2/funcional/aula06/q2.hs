menor2 :: Int -> Int -> Int
menor2 x y
    | x < y = x
    | otherwise = y

menor :: Int -> Int -> Int
menor (menor2 a b) (menor2 c d)
    | (menor2 a b) < (menor2 c d) = menor2 a b
    | otherwise = menor2 c d

ordenaEmTupla :: Int -> Int -> Int -> Int -> [Int]
ordenaEmTupla a b c d
    | otherwise = insereOrd x (insere xs)

insereOrd ::(Ord a) => a -> [a] -> [a]
insereOrd x [] = [x]
insereOrd x (y:ys)
| x <= y = (x:y:ys)
| otherwise = y: (insereOrd x ys)

--ordenaEmTupla :: Int -> Int -> Int -> Int -> [Int]
--ordenaEmTupla a b c d = a:b:c:d:[] 