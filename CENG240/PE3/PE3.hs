{-# LANGUAGE FlexibleInstances #-}

module PE3 where

import Data.List (sort, sortBy)
import Text.Printf (printf)

data Term = Const Integer | Pw Integer Power | Trig Integer Power Trigonometric | Exp Integer Power Exponential

data Power = Power Integer
data Polynomial = Polynomial [(Integer, Power)]
data Exponential = Exponential Polynomial
data Trigonometric = Sin Polynomial | Cos Polynomial

class Evaluable a where
    function :: a -> (Integer -> Double)

class Differentiable a where
    derivative :: a -> [Term]

-- You can use this as is
getRounded :: Double -> Double 
getRounded x = read s :: Double
               where s = printf "%.2f" x

-- You don't have to follow the order the functions appear in the file
-- For example, you could first define all Show instances, then all Eq instances etc.
-- if that implementation order is more convenient for you.



-- INSTANCES FOR POWER
powerci _ 0 = 1
powerci x n =
    x*powerci x (n-1)
    
makederip (Polynomial []) = []
makederip (Polynomial ((int, (Power pow)):xs)) =
    if ((int /= 0) && (pow /=0))
            then if pow /=1
                    then [Pw  (pow*int) (Power (pow-1))] ++ makederip (Polynomial xs)
                    else [(Const (pow*int))] ++ makederip (Polynomial xs)
            else makederip (Polynomial xs)
    
instance Show Power where
    show (Power a) = 
        if a == 0
            then "1"
        else if a == 1
            then "x"
        else 
            "x^"++ show a

instance Eq Power where
    (Power k) == (Power n) = k==n
    

instance Ord Power where
   (Power k) <= (Power n) =    k <=  n
   (Power k) >= (Power n) =   k >= n
   (Power k) < (Power n) =   k <  n
   (Power k) > (Power n) =   k >  n

instance Evaluable Power where
    function (Power n) = \x -> 
       if n == 0 then 1
            else fromIntegral $ powerci x n
   

instance Differentiable Power where
    derivative (Power pow) = 
        if pow /= 1
            then
                 [Pw pow (Power (pow-1))]
            else [Const pow]


sakat [] = ""
sakat [(inta, (Power  k)):xs] = 
    if  k /= 0 
        then if length xs /= 0 
                then if (inta >1)
                        then show inta ++ show (Power  k) ++ " + " ++ sakat [xs]
                        else if inta == 1
                                then  show (Power  k) ++ " + " ++ sakat [xs]
                                else "0" ++ sakat [xs]
                else if (inta >1)
                        then show inta ++ show (Power  k)
                        else if inta == 1
                                then  show (Power  k)
                                else "0"
                    
                    
        else
            show inta 
            
polyhelper [] _ = 0         
polyhelper ((inta, (Power  k)):xs) ex =
    inta * (powerci ex k) + polyhelper xs ex
    
-- INSTANCES FOR POLYNOMIAL

instance Show Polynomial where
    show (Polynomial u) = sakat [u]

instance Evaluable Polynomial where
    function (Polynomial u) = \x ->
        fromInteger $ polyhelper u x
        

instance Differentiable Polynomial where
    derivative a = 
        makederip a

sinderiv (Polynomial []) = []
sinderiv (Polynomial ((int, (Power pow)):xs)) = 
    if int == 0
        then [] ++ sinderiv (Polynomial xs)
        else if pow == 0
                then [] ++ sinderiv (Polynomial xs)
                else [Trig (int*pow) (Power (pow-1)) ( Cos (Polynomial ((int, (Power pow)):xs)))] ++ sinderiv (Polynomial xs)
                
cosderiv (Polynomial []) = []
cosderiv (Polynomial ((int, (Power pow)):xs)) = 
    if int == 0
        then [] ++ cosderiv (Polynomial xs)
        else if pow == 0
                then [] ++ cosderiv (Polynomial xs)
                else [Trig (-1*int*pow) (Power (pow-1)) ( Sin (Polynomial ((int, (Power pow)):xs)))] ++ cosderiv (Polynomial xs)
                
                




-- INSTANCES FOR TRIGONOMETRIC

instance Show Trigonometric where
    show (Sin (Polynomial ((int, (Power pow)):xs))) = 
        if (length xs == 0 && pow == 1)
            then 
                if int /= 0
                    then "sin" ++ show (Polynomial ((int, (Power pow)):xs))
                    else "0"
            else "sin(" ++ show (Polynomial ((int, (Power pow)):xs)) ++ ")"
            
        
    show (Cos (Polynomial ((int, (Power pow)):xs))) = 
        if (length xs == 0 && pow == 1)
            then 
                if int /= 0
                    then "cos" ++ show (Polynomial ((int, (Power pow)):xs))
                    else "0"
            else "cos(" ++ show (Polynomial ((int, (Power pow)):xs)) ++ ")"
        

instance Evaluable Trigonometric where
    function (Sin (Polynomial u)) = \x -> 
        getRounded $ sin( fromIntegral ( polyhelper u x))
        
    function (Cos (Polynomial u)) = \x -> 
        getRounded $ cos(fromIntegral  (polyhelper u x))

instance Differentiable Trigonometric where
    derivative (Sin u) = 
        sinderiv u
    derivative (Cos u) = 
        cosderiv u

expderiv (Polynomial []) = []
expderiv (Polynomial ((int, (Power pow)):xs)) = 
    if int == 0
        then [] ++ expderiv (Polynomial xs)
        else if pow == 0
                then [] ++ expderiv (Polynomial xs)
                else [Exp (int*pow) (Power (pow-1)) (Exponential (Polynomial ((int, (Power pow)):xs)) )] ++ expderiv (Polynomial xs)

-- INSTANCES FOR EXPONENTIAL

instance Show Exponential where
    show (Exponential poly) = "e^(" ++ show poly ++")"

instance Evaluable Exponential where
    function (Exponential (Polynomial u)) = \x -> 
        getRounded $ exp (fromIntegral (polyhelper u x))

instance Differentiable Exponential where
    derivative (Exponential u) = 
        expderiv u



-- INSTANCES FOR TERM

instance Show Term where
    show (Trig int pow poli) = 
        show int ++ show pow ++ show poli
        
    show (Const a) = show a
    show (Pw a b) = show a ++ show b
    show (Exp a b c) = show a ++ show b ++ show c

instance Evaluable Term where
    function (Const a) = \x -> fromIntegral a
    function (Pw a (Power m)) = \x -> fromIntegral $ a*(powerci x m)
    function (Exp a (Power m) (Exponential (Polynomial u))) = \x -> 
        let ilk = fromIntegral $ a*(powerci x m)
            iki = exp (fromIntegral (polyhelper u x))
            in getRounded $ fromIntegral ilk*iki
            
    function (Trig int (Power pow) (Sin (Polynomial u))) = \x -> 
        let ilk = fromIntegral $ int*(powerci x pow)
            iki = sin (fromIntegral (polyhelper u x))
            in getRounded $ fromIntegral ilk*iki
    
    function (Trig int (Power pow) (Cos (Polynomial u))) = \x -> 
        let ilk = fromIntegral $ int*(powerci x pow)
            iki = cos (fromIntegral (polyhelper u x))
            in getRounded $ fromIntegral ilk*iki
    
    
instance Differentiable Term where
    derivative (Const a) = []
    derivative (Pw a (Power pow)) =
        if (pow /= 1 && pow /=0) 
            then
                 [Pw (pow*a) (Power (pow-1))]
            else if pow == 1
                then[Const (pow*a)]
                else [Const 0]
    derivative _ = []
        





-- INSTANCES FOR [TERM]

instance Evaluable [Term] where
   function []= \x -> 0.0
   function (ex:xs)= \x -> getRounded $(function ex x)+(function xs x)

instance Differentiable [Term] where
    
    derivative (x:xs) = (derivative x) ++ (derivative xs)
    derivative _ = []
