import java.util.ArrayList;

public class CengTreeNodeInternal extends CengTreeNode
{
    private ArrayList<Integer> keys;
    private ArrayList<CengTreeNode> children;

    public CengTreeNodeInternal(CengTreeNode parent)
    {
        super(parent);

        this.type = CengNodeType.Internal;
        this.keys = new ArrayList<>();
        this.children = new ArrayList<>();
    }

    // GUI Methods - Do not modify
    public ArrayList<CengTreeNode> getAllChildren()
    {
        return this.children;
    }
    public Integer keyCount()
    {
        return this.keys.size();
    }
    public Integer keyAtIndex(Integer index)
    {
        if(index >= this.keyCount() || index < 0)
        {
            return -1;
        }
        else
        {
            return this.keys.get(index);
        }
    }



    public void CreateInternal(CengTreeNode newNode, int ortaK, boolean check,  CengTree tree){
        if(this.children.size() == 0) {
            //this.keys.add(ortaK);
            this.children.add(newNode);
        }
        else {
            int i = 0;
            while (i < this.keys.size() && this.keys.get(i) < ortaK) i++;
            this.keys.add(i,ortaK);
            this.children.add(i+1,newNode);
        }

        int size = this.keys.size();
        if(size> CengTreeNode.order*2){
            CengTreeNodeInternal parent = (CengTreeNodeInternal) this.getParent();
            CengTreeNodeInternal newNodeToAdd= new CengTreeNodeInternal(parent);
            int midIn = size >> 1;
            int ortaKey = this.keys.get(midIn);

            for(int k = midIn+1; k<size; k++){
                newNodeToAdd.keys.add(this.keys.get(k));
            }

            this.keys.subList(midIn, size).clear();

            for(int i = midIn+1; i<this.children.size(); i++){
                this.children.get(i).setParent(newNodeToAdd);
                newNodeToAdd.children.add(this.children.get(i));
            }

            this.children.subList(midIn + 1, this.children.size()).clear();

            if(parent != null){
                parent.CreateInternal(newNodeToAdd, ortaKey, true, tree);
            }

            else{

                CengTreeNodeInternal rootNew = new CengTreeNodeInternal(null);

                tree.root = rootNew;

                rootNew.CreateInternal(this, ortaKey, true, tree);
                rootNew.CreateInternal(newNodeToAdd, ortaKey, false, tree);
                newNodeToAdd.setParent(rootNew);
                this.setParent(rootNew);
            }

        }

    }



    @Override

    public void addBookHelper(CengBook kitap, CengTree tree)
    {
        int s=0;
        while (s < this.keys.size() && this.keys.get(s) <= kitap.getBookID()) s++;
        this.children.get(s).addBookHelper(kitap, tree);
    }
    private int Sacmalik(CengTreeNode buyuk){
        if(buyuk.type == CengNodeType.Leaf) return ((CengTreeNodeLeaf)buyuk).Maxbul();
        else return Sacmalik(((CengTreeNodeInternal)buyuk).children.get(((CengTreeNodeInternal)buyuk).children.size()-1));
    }
    @Override
    public void PrintHelper2(int tab ,int maxa){
    	if(this == null) return;
        int max = Sacmalik(this);
        PrintHelper(0, max);
    }

    public void PrintHelper(int tab,int max) {

        String tabs = "";
        for(int u=0; u<tab; u++) tabs += "\t";
        System.out.print(tabs);
        System.out.println("<index>");
        for(int i=0; i<this.keys.size();i++){
            System.out.print(tabs);
            System.out.println(keys.get(i));
        }
        System.out.print(tabs);
       System.out.println("</index>");
        

        for(int k=0; k<this.children.size(); k++){
            if(this.children.get(0).type == CengNodeType.Internal)
                ((CengTreeNodeInternal)this.children.get(k) ).PrintHelper(tab+1,max);
            else ((CengTreeNodeLeaf)this.children.get(k) ).PrintHelper(tab+1,max);

        }
    }

    @Override
    public void SearchHelper(int BookNum) {

    }

public ArrayList<CengTreeNode> InterSearch(int bookNum){
        CengBook rete = null;
        CengTreeNode current = null;
        ArrayList<CengTreeNode> ret = new ArrayList<>();
        ArrayList<ArrayList<Integer>> ret2 = new ArrayList<>();
        ret.add(this);
        ArrayList<Integer> t2 = new ArrayList<>();
       // for(int yeter =0; yeter<this.keys.size(); yeter++) t2.add(this.keys.get(yeter));


        int t=0;
        while(true){

            ArrayList <Integer> temp = new ArrayList<>();
            t++;
            current = ret.get(ret.size()-1);
            if(current.type == CengNodeType.Internal) {
                ret2.add(((CengTreeNodeInternal)current).keys);
                int i = 0;
                while (i < ((CengTreeNodeInternal)current).keys.size() && bookNum >= ((CengTreeNodeInternal)current).keys.get(i)) {
                    temp.add(((CengTreeNodeInternal)current).keys.get(i));
                    i++;
                }
                //ret2.add(temp);
                if (bookNum > ((CengTreeNodeInternal)current).keys.get(((CengTreeNodeInternal)current).keys.size() - 1)) i =
                        ((CengTreeNodeInternal)current).children.size()-1;
                ret.add(((CengTreeNodeInternal)current).children.get(i));

            }

            else if(current.type == CengNodeType.Leaf){
                rete = ((CengTreeNodeLeaf) current).LeafSearch(bookNum, false);
                break;
            }

            temp.clear();
        }

        if(rete != null){

            for(int i=0; i<ret2.size()+1; i++){

                if(i== ret2.size()){
                    for(int k=0; k<i; k++) System.out.print("\t");
                    ((CengTreeNodeLeaf) current).LeafSearch(bookNum, true);
                    break;
                }

                for(int k=0; k<i; k++) System.out.print("\t");
                System.out.println("<index>");
                for (int j=0; j< ret2.get(i).size(); j++){
                    for(int k=0; k<i; k++) System.out.print("\t");
                    System.out.println(ret2.get(i).get(j));
                }
                for(int k=0; k<i; k++) System.out.print("\t");
               System.out.println("</index>");
            }
        }

        return ret;
    }

    // Extra Functions
}

