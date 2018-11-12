main :: IO ()
main = putStrLn (greet "World")

greeting = "Howdy"
greet who = greeting ++ ", " ++ who


add :: Int -> Int -> Int
add = (+)

data Compass = North | East | West | South
  deriving (Eq, Ord, Enum, Show)

data Expression = Number Int
                | Add Expression Expression
                | Subtract Expression Expression
                deriving (Eq, Ord, Show)

calculate :: Expression -> Int
calculate (Number x) = x
calculate (Add x y) = (calculate x) + (calculate y)
calculate (Subtract x y) = (calculate x) - (calculate y)

newHead :: [a] -> a
newHead [] = error "Empty list"
newHead (x:xs) = x

newTail [] = error "Empty list"
newTail (x:xs) = xs
