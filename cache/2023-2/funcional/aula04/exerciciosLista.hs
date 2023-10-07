{-
===============================
Author: Rafael Passos Domingues
    RA: 2023.1.08.036
  Data: Oct 6 Fri [19h30]
===============================
-}

listInt :: [Int]
listInt = [1..7]

listChar :: [Char]
listChar = ['H','a','s','k','e','l','l']

nFirst :: [Int] -> Int -> [Int]
nFirst [] _ = []
nFirst _ 0 = []
nFirst (x:xs) n = x : nFirst xs (n-1)

reverseList :: [Int] -> [Int]
reverseList [] = []
reverseList (x:xs) = reverseList xs ++ [x]

merge :: [Int] -> [Char] -> [(Int, Char)]
merge [] [] = []
merge (a:b) (c:d) = (a,c) : merge b d

contains :: [Int] -> Int -> Bool
contains [] _ = False
contains (x:xs) n
    | x == n = True
    | otherwise = contains xs n

addSingle :: [Int] -> Int -> [Int]
addSingle xs n
    | contains xs n = xs
    | otherwise = xs ++ [n]

isHigh :: Int -> Int -> Int
isHigh a b
   | a > b = a
   | otherwise = b

bigger :: [Int] -> Int
bigger [x] = x
bigger (x:xs) = isHigh x (bigger xs)