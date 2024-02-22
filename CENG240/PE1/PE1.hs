module PE1 where

import Text.Printf

-- PE1: Recipe Calculator
-- The premise of this homework if to write a recipe calculator that
-- calculates: how much a recipe costs to make, what can be made with the
-- ingredients already available, and how much extra ingredients need to
-- be bought in order to make a recipe.

-- Recipe = Recipe Name [(Ingredient, Quantity)]
data Recipe = Recipe String [(String, Double)] deriving Show

-- Price = Price Ingredient Quantity Price
data Price = Price String Double Double deriving Show

-- You can use this as-is
getRounded :: Double -> Double 
getRounded x = read s :: Double
               where s = printf "%.2f" x

--contra ::(String,Double) -> [(String,Double)]-> Bool
getdiff :: String->Double->[(String,Double)]->Double
makerecipe :: String->[(String,Double)]->Recipe
getprice :: Price->Double
finder :: String->[(String, Double)]->Double
bulucu :: (String, Double) -> [(String, Double)] -> [(String, Double)]
--missingust :: [(String,Double)]->[Recipe]-> [[(String,Double)]]
--flatreciplist ::[Recipe] -> [(String,Double)]
getprice  (Price a b c) =c/b
getmalzemekg(_,kg)=kg
getstr (str, _)=str
getstr3 (Price atr _ _)= atr
getreciliste (Recipe a b) = b
getstrecipe (Recipe a _) = a
makerecipe a b = (Recipe a b)


finder key (x:xs) = 
    if key == getstr x
        then getmalzemekg x
        else 
            if xs== []
                then 0
                else finder key xs
       
finder _ _ = 0


getdiff _ sayi [] = -sayi
getdiff key sayi recipelist =
    if key == getstr (head recipelist)
        then (getmalzemekg (head recipelist)) - sayi
        else getdiff key sayi (tail recipelist)
    

fazla [] _ = []
fazla liste reci = 
    let recilist = getreciliste reci
        recipekey = getstr (head recilist)
        kafa= head liste
        elde= finder (getstr kafa) liste
        gereksiz = (getdiff (getstr kafa) elde recilist)
            in if (gereksiz < 0)
            then [(getstr kafa,-gereksiz)] ++ fazla (tail liste) reci
            else  fazla (tail liste) reci
            
            
flatreciplist [] = []        
flatreciplist reciplist =
    getreciliste (head reciplist) ++ flatreciplist (tail reciplist) 
   
combiner [] = []
combiner liste =
    let kafa = head liste
        kuyruk = tail liste
    in if varmi (getstr kafa) (tail liste) 
            then let yeniliste = bulucu kafa (tail liste)
                     in combiner yeniliste
            else [(head liste)] ++ combiner (tail liste)
        
        
varmi _ [] = False     
varmi kafastr liste= 
    if kafastr == getstr(head liste)
        then True
        else varmi kafastr (tail liste)
        
bulucu _ [] = []
bulucu hed liste =
    if (getstr hed) == getstr (head liste)
        then [((getstr hed), (getmalzemekg (head liste))+ getmalzemekg (hed))] ++ tail liste
        else [(head liste)] ++ bulucu hed (tail liste)
    

makedata _ [] = []
makedata [] _ = []
makedata eksiklist fiyatlist = 
    let fiyat = (getIngredientCost (head eksiklist) fiyatlist)
    in [(getstr (head eksiklist), getmalzemekg (head eksiklist), fiyat)] ++ makedata (tail eksiklist) fiyatlist
             
    



-- Calculate how much the given amount of the given ingredient costs
getIngredientCost :: (String, Double) -> [Price] -> Double
getIngredientCost malzeme liste  = 
    let kafa = head liste
        kuyruk = tail liste
    in if getstr3(kafa) == getstr(malzeme)
        then getRounded $(getprice kafa)*getmalzemekg malzeme
        else getIngredientCost malzeme kuyruk
    
    

-- Calculate how much it costs to buy all the ingredients of a recipe
recipeCost :: Recipe -> [Price] -> Double
recipeCost reci prays = 
    let liste = getreciliste reci
        kafa = head liste
        kuyruk = tail liste
        stro= getstrecipe reci
        laste= makerecipe stro kuyruk
    in if  kuyruk == []
        then getIngredientCost kafa prays
        else (getIngredientCost kafa prays) + recipeCost laste prays

-- Given a list of how much you already have of each ingredient,
-- calculate how much of which ingredients are missing for a recipe
missingIngredients :: Recipe -> [(String, Double)] -> [(String, Double)]
missingIngredients _ [] = []
missingIngredients (Recipe _ []) _ = []
missingIngredients reci liste =  
    let recilist = getreciliste reci
        recipekey = getstr (head recilist)
        elde= finder recipekey liste
        gerekli = (getdiff recipekey elde recilist)
        recipekuy = tail (getreciliste reci)
        recipe2 = makerecipe (getstrecipe reci) recipekuy
    in if (gerekli > 0)
        then [(recipekey,gerekli)] ++ missingIngredients recipe2 liste
        else  missingIngredients recipe2 liste
        


-- Given a list of ingredients in your kitchen, calculate what you would
-- have left after making the given recipe. If there isn't enough of an
-- ingredient, the recipe cannot be made! You shouldn't change the amount
-- of ingredient in that case.
makeRecipe :: [(String, Double)] -> Recipe -> [(String, Double)]
makeRecipe [] _ = []
makeRecipe _ (Recipe _ [])= []
makeRecipe liste reci =  
    if missingIngredients reci liste /= []
        then liste
        else fazla liste reci
        



-- Given a list of ingredients you already have, and a list of recipes,
-- make a shopping list showing how much of each ingredient you need
-- to buy, and its cost. Each ingredient mush appear in the shopping list
-- at most once (no duplicates!).
makeShoppingList :: [(String, Double)] -> [Recipe] -> [Price] -> [(String, Double, Double)]
makeShoppingList eldekiler tariflist fiyatlist = 
    let nihairecipelist = (flatreciplist tariflist)
        combined = combiner nihairecipelist 
        eksiklist = missingIngredients (makerecipe "Furkan" combined) eldekiler
        final = makedata eksiklist fiyatlist
    in final
    




--makeShoppingList _ _ _ = []
