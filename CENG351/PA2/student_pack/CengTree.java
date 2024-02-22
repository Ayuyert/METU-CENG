import java.util.ArrayList;

public class CengTree
{
    public CengTreeNode root;
    // Any extra attributes...

    public CengTree(Integer order)
    {
        CengTreeNode.order = order;
        // TODO: Initialize the class
        this.root = new CengTreeNodeLeaf(null);

    }

    public void addBook(CengBook book)
    {
        // TODO: Insert Book to Tree
        this.root.addBookHelper(book, this);
    }

    public ArrayList<CengTreeNode> searchBook(Integer bookID)
    {

            if(root.type == CengNodeType.Leaf){
                ((CengTreeNodeLeaf)root).LeafSearch(bookID,true);
            }
            else{
                if(root != null) ((CengTreeNodeInternal) root).InterSearch(bookID);
            }


        return null;
    }

    public void printTree()
    {
        int tab =0;
        if(root == null) return;

        this.root.PrintHelper2( tab, 0);
    }

    // Any extra functions...
}
