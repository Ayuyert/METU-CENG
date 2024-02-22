import java.util.ArrayList;

public class CengTreeNodeLeaf extends CengTreeNode
{
    private ArrayList<CengBook> books;
    // TODO: Any extra attributes

    public CengTreeNodeLeaf(CengTreeNode parent)
    {
        super(parent);

        // TODO: Extra initializations

        this.type = CengNodeType.Leaf;
        this.books = new ArrayList<>();
    }

    // GUI Methods - Do not modify
    public int bookCount()
    {
        return books.size();
    }
    public Integer bookKeyAtIndex(Integer index)
    {
        if(index >= this.bookCount()) {
            return -1;
        } else {
            CengBook book = this.books.get(index);

            return book.getBookID();
        }
    }


    @Override
    public void addBookHelper(CengBook kitap, CengTree tree) {


        int yer=0;
        if(books.size() == 0) books.add(kitap);
        else if (kitap.getBookID() > books.get(books.size()-1).getBookID()) this.books.add(kitap);
        else {while (yer < this.books.size() && this.books.get(yer).getBookID() < kitap.getBookID()) yer++;
        this.books.add(yer, kitap);}


        if(books.size()> this.order<<1)
        {
            CengTreeNodeInternal parent = (CengTreeNodeInternal) this.getParent();
            CengTreeNodeLeaf newNodeToAdd= new CengTreeNodeLeaf(getParent());
            int merkez = books.size()>>1;
            CengBook ortaK = books.get(merkez);
            for(int i=merkez; i<books.size(); i++){
                newNodeToAdd.books.add(this.books.get(i));
            }
            this.books.subList(merkez,books.size()).clear();


            //ESKİSİ KÜÇÜK YENİSİ BÜYÜK


            if(parent!=null)
            {
                parent.CreateInternal(newNodeToAdd, ortaK.getBookID(),true, tree);

            }
            else
            {
                CengTreeNodeInternal newRoot= new CengTreeNodeInternal(null);

                newRoot.CreateInternal(this,ortaK.getBookID(), true, tree);
                newRoot.CreateInternal(newNodeToAdd, ortaK.getBookID(), false, tree);
                tree.root=newRoot;
                this.setParent(newRoot);
                newNodeToAdd.setParent(newRoot);

            }
        }
    }
    public int Maxbul(){
        return this.books.get(this.books.size()-1).getBookID();
    }

    public void PrintHelper(int  tab, int max) {
        String tabs = "";
        for(int u=0; u<tab; u++) tabs += "\t";
        System.out.print(tabs);
        System.out.println("<data>");
        for(int p=0; p< this.books.size();p++){
            System.out.print(tabs);
            System.out.println("<record>" + books.get(p).getBookID() +"|"+ books.get(p).getBookTitle() + "|" +
                    books.get(p).getAuthor() + "|" + books.get(p).getGenre()+"</record>"
            );

        }

        System.out.print(tabs);
        if(this.books.get(this.books.size()-1).getBookID() == max) System.out.print("</data>");
        else System.out.println("</data>");
        

    }
    @Override
    public void PrintHelper2(int k, int a){
    	if(this.books.size()==0) return;
    	int p=0;
	for(; p< this.books.size()-1;p++){
            
            System.out.println("<record>" + books.get(p).getBookID() +"|"+ books.get(p).getBookTitle() + "|" +
                    books.get(p).getAuthor() + "|" + books.get(p).getGenre()+"</record>");
    	}
    	
    	System.out.print("<record>" + books.get(p).getBookID() +"|"+ books.get(p).getBookTitle() + "|" +
                    books.get(p).getAuthor() + "|" + books.get(p).getGenre()+"</record>"
            );
    }

    @Override
    public void SearchHelper(int t){

    }

    public CengBook LeafSearch(int BookNum, boolean yaz) {
        int p=0;
        while(p<books.size()){

            if(BookNum == books.get(p).getBookID()) {
                if(yaz)System.out.print("<record>" + books.get(p).getBookID() +"|"+ books.get(p).getBookTitle() + "|" +
                        books.get(p).getAuthor() + "|" + books.get(p).getGenre()+"</record>"
                );
                return books.get(p);
            }
            p++;
        }
        System.out.println("Could not find " + BookNum +".");
        return null;
    }
    // Extra Functions
}
