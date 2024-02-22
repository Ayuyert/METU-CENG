module PE2 where

-- PE2: Dungeon Crawler
-- Dungeon map is :: Tree Chamber [Encounter]
-- Each encounter is either a fight or a treasure
-- Fights deal you damage (reduce HP) but enemies drop some gold (add
-- gold)
-- Tresures just give gold, or potions (which give hp)
-- Nodes hold encounters, when you visit a node you go through all of them in order
-- You start with a certain amount of HP and 0 gold.
-- You lose HP and accumulate gold as you descend the tree and go through encounters

-- Polymorphic tree structure
data Tree a b = EmptyTree | Leaf a b | Node a b [Tree a b] deriving (Show, Eq)

-- Every location in the tree is of some Chamber type.
data Chamber = Cavern |
               NarrowPassage |
               UndergroundRiver |
               SlipperyRocks deriving (Show, Eq)

-- An enemy has a name, an amount of damage that it deals
-- and an amount of gold that it drops (in that order).
data Enemy = Enemy String Integer Integer deriving (Show, Eq)

-- Gold n gives n amount of gold
-- Potion n heals n hp
data Loot = Gold Integer | Potion Integer deriving (Show, Eq)

-- An encounter is either a Fight with an Enemy, or a treasure where
-- you find Loot
data Encounter = Fight Enemy | Treasure Loot deriving (Show, Eq)

-- This is a type synonym for how we will represents our dungeons
type Dungeon = Tree Chamber [Encounter]

-- First argument is starting HP
-- Second argument is the dungeon map
-- Third argument is the path (each integer in the list shows what child
-- you descend into)
-- Calculate how much HP you have left and how much gold you've
-- accumulated after traversing the given path
getnodeliste (Node a b c) = c
traverseg (hp,gold) (Leaf a []) yollist =  (hp,gold)
traverseg (hp,gold) (Leaf a (Fight (Enemy isim hasar altin):xs)) yollist  = traverseg (hp-hasar,gold+altin) (Leaf a xs) []
traverseg (hp,gold) (Leaf a (Treasure (Potion heal):xs)) yollist = traverseg (hp+heal,gold) (Leaf a xs) []
traverseg (hp,gold) (Leaf a (Treasure (Gold altin):xs)) yollist  = traverseg (hp,gold+altin) (Leaf a xs) []
traverseg (hp,gold) (Node _ [] _) [] = (hp,gold) 
traverseg (hp,gold) (Node _ [] liste) yollist =  traverseg (hp,gold) (liste !! (head yollist)) (tail yollist)
traverseg (hp,gold) (Node a (Fight (Enemy isim hasar altin):xs) c) yollist = traverseg (hp-hasar,gold+altin) (Node a  xs c) yollist
traverseg (hp,gold) (Node a (Treasure (Potion heal):xs) c) yollist = traverseg (hp+heal,gold) (Node a xs c) yollist
traverseg (hp,gold) (Node a (Treasure (Gold altin):xs) c) yollist = traverseg (hp,gold+altin) (Node a xs c) yollist
    
 
getface  b c = c









traversePath :: Integer -> Dungeon -> [Int] -> (Integer, Integer)
traversePath hp harita yollist = 
    traverseg (hp, 0) harita yollist
    


traversePath _ _ _ = (0, 0)

-- First argument is starting HP
-- Second argument is dungeon map
-- Find which path down the tree yields the most gold for you
-- You cannot turn back, i.e. you'll find a non-branching path
-- You do not need to reach the bottom of the tree
-- Return how much gold you've accumulated

getpara [] para = para
getpara (x:xs) para =
    case x of
        Treasure (Gold altin) -> getpara xs (para+altin)
        Treasure _ -> getpara xs para
        Fight (Enemy _ _ loot) -> getpara xs (para+loot)
    
    


gainer :: Integer->[Integer]->Dungeon->[Integer]
gainer coin liste agac =
    case agac of
       EmptyTree -> liste ++ []
       Leaf oda a -> liste ++ [getpara a coin]
       Node oda a childs -> 
        let
            coina = getpara a coin
            aaa = foldr (++) [] (map (gainer coina liste) childs)
        in 
            aaa

getmax :: [Integer] -> Integer -> Integer
getmax [] sayi = sayi
getmax (x:xs) sayi =
    if (sayi<x)
        then 
            let ucak=x
                in getmax xs ucak
        else getmax xs sayi

findMaximumGain :: Integer -> Dungeon -> Integer
findMaximumGain hp agac = 
    let 
        para = 0
        hasagac = (findViablePaths hp agac)
        hasliste = []
        gains = (gainer para hasliste  hasagac)
    in getmax gains 0
    
    
--findMaximumGain _ _ = 0

-- First argument is starting HP
-- Second argument is the dungeon map
-- Remove paths that you cannot go thorugh with your starting HP. (By
-- removing nodes from tree).
-- Some internal nodes may become leafs during this process, make the
-- necessary changes in such a case.


verified :: Integer -> [Encounter] -> Integer
verified hp [] = hp
verified hp (x:xs) =
    if hp<= 0
        then hp
        else
            case x of
                Fight (Enemy _ hasar _) -> verified (hp-hasar) xs
                Treasure (Potion heal) -> verified (hp+heal) xs
                Treasure _ -> verified hp xs
    



findViablePaths :: Integer -> Dungeon -> Dungeon

findViablePaths hp zindan =
  case zindan of
    EmptyTree -> EmptyTree
    Leaf oda a ->
      if (verified hp a) > 0
        then Leaf oda a
        else EmptyTree
    Node oda a liste ->
     if verified hp a > 0 
      then let 
                hpa = verified hp a
                verifiedcocuk = filter (/= EmptyTree) $ map (findViablePaths hpa ) liste
                
           in if [] == verifiedcocuk
                then Leaf oda a
                else Node oda a verifiedcocuk
      else EmptyTree



     


-- First argument is starting HP
-- Second Argument is dungeon map
-- Find, among the viable paths in the tree (so the nodes you cannot
-- visit is already removed) the two most distant nodes, i.e. the two
-- nodes that are furthest awat from each other.
mostDistantPair :: Integer -> Dungeon -> (Integer, Dungeon)
mostDistantPair hp zindan= 
    let
        kral = findViablePaths hp zindan
    in 
        case kral of 
            Leaf a b -> (0,Leaf a b)
            EmptyTree -> (0,EmptyTree)
            Node a b c -> (0,EmptyTree)


mostDistantPair _ _ = (0, EmptyTree)


ratio :: [Encounter]->Integer->Integer->(Integer,Integer)
ratio [] para damage = 
    if damage <=0
        then (5,0)
        else (para,damage)
            
ratio (x:xs) damage para =
    case x of
        Fight (Enemy _ hasar loot) -> ratio xs (para+loot)  (damage+hasar) 
        Treasure (Gold altin) -> ratio xs (para+altin) damage 
        Treasure (Potion hp) -> ratio xs para (damage-hp) 


sumList [] (c,d) = (c,d)
sumList ((zindan,(x,y)):xs) (c,d) =  
    case zindan of
        Leaf a b -> sumList xs (c+x,d+y)
        Node oda liste cocuk->
            sumList xs (c+x,d+y)
        
        


--maxfind::[(Dungeon,(Integer,Integer))]->(Integer,Integer)->Dungeon->[(Dungeon,(Integer,Integer))]
maxfind zindan  = 
    case zindan of 
        Leaf a b -> [(Leaf a b, ratio b 0 0)]
        Node oda list cocuk ->
            let 
                u = [(Node oda list cocuk, ratio list 0 0)] ++foldr (++) [] ( map (maxfind)  cocuk)
            in 
                u
                
generalmax zindan = 
    case zindan of
        Leaf a b-> [(sumList (maxfind (Leaf a b) ) (0,0),Leaf a b)]
        Node oda a b -> [(sumList (maxfind (Node oda a b) ) (0,0),Node oda a b)] ++ foldr (++) [] (map (generalmax) b)
            

getmax2 [] _ _ zindan = zindan
getmax2 (((x,y),zindan):xs) maxx maxy maxzindan = 
    if x <=0 
        then zindan
        else if x*maxy>y*maxx
             then getmax2 xs x y zindan
             else getmax2 xs maxx maxy maxzindan

-- Find the subtree that has the highest total gold/damage ratio
-- Simply divide the total gold in the subtree by the total damage
-- in the subtree. You only take whole subtrees (i.e you can take a new
-- node as the root of your subtree, but you cannot remove nodes
-- below it). Note that the answer may be the whole tree.
mostEfficientSubtree :: Dungeon -> Dungeon
mostEfficientSubtree zindan = 
    case zindan of
        EmptyTree->EmptyTree
        Leaf a b -> Leaf a b
        Node a b c -> 
            let
                a= generalmax zindan
            in 
                getmax2 a 0 1 zindan



--mostEfficientSubtree _ = EmptyTree

