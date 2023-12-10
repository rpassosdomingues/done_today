{-
===============================
Author: Rafael Passos Domingues
    RA: 2023.1.08.036
  Data: Nov 18 Sat [17h48]
===============================
-}

listInt :: [Int]
listInt = [1..10]

-- ====================================================================
-- Practicing 1
-- ====================================================================

nFirst :: [Int] -> Int -> [Int]
nFirst [] _     = []
nFirst _ 0      = []
nFirst (x:xs) n = x : nFirst xs (n-1)


-- ====================================================================
-- Practicing 2
-- ====================================================================

exist :: [Int] -> Int -> Bool
exist [] _ = False
exist (x:xs) n
    | (n == x)  = True
    | otherwise = exist xs n

-- ====================================================================
-- Practicing 3
-- ====================================================================

bigger :: Int -> Int -> Int
bigger a b
    | (a > b)   = a
    | otherwise = b

big :: [Int] -> Int
big []     = error "Empty List!"
big (x:xs) = bigger x (big xs)

-- ====================================================================
-- Practicing 4
-- ====================================================================

mirror :: [Int] -> [Int]
mirror []     = []
mirror (x:xs) = mirror xs ++ [x]

-- ====================================================================
-- Practicing 5
-- ====================================================================

lastElement :: [Int] -> Int
lastElement []     = error "Empty List!"
lastElement [x]    = x
lastElement (x:xs) = last xs

-- ====================================================================
-- Practicing 6
-- ====================================================================

kthElement :: [Int] -> Int -> Int
kthElement [] _     = error "The list is over!"
kthElement (x:_) 0  = x
kthElement (_:xs) k = kthElement xs (k - 1)