import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class CengTreeParser
{
    public static ArrayList<CengBook> parseBooksFromFile(String filename)
    {
        ArrayList<CengBook> bookList = new ArrayList<CengBook>();

        // You need to parse the input file in order to use GUI tables.
        // TODO: Parse the input file, and convert them into CengBooks

        try {
            File text = new File(filename);
            Scanner scan = new Scanner(text);

            while(scan.hasNextLine()){
                String line = scan.nextLine();
                String[] params = line.split("\\|");

                bookList.add(new CengBook(
                        Integer.parseInt(params[0]),
                        params[1],
                        params[2],
                        params[3]
                ));
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }



        return bookList;
    }

    public static void startParsingCommandLine() throws IOException
    {
        // TODO: Start listening and parsing command line -System.in-.
        // There are 4 commands:
        // 1) quit : End the app, gracefully. Print nothing, call nothing, just break off your command line loop.
        // 2) add : Parse and create the book, and call CengBookRunner.addBook(newlyCreatedBook).
        // 3) search : Parse the bookID, and call CengBookRunner.searchBook(bookID).
        // 4) print : Print the whole tree, call CengBookRunner.printTree().

        // Commands (quit, add, search, print) are case-insensitive.


        Scanner scan = new Scanner(System.in);

        while (scan.hasNextLine()) {
            String line = scan.nextLine();

            String[] eklenen = line.split("\\|");

            String yapılacak = eklenen[0];

            if (yapılacak.equals("quit")) {
                break;
            } else if (yapılacak.equals("add")) {
                CengBook cengVideo = new CengBook(
                        Integer.parseInt(eklenen[1]), eklenen[2], eklenen[3], eklenen[4]
                );

                CengBookRunner.addBook(cengVideo);
            } else if (yapılacak.equals("search")) {
                CengBookRunner.searchBook(Integer.parseInt(eklenen[1]));
            } else if (yapılacak.equals("print")) {
                
                CengBookRunner.printTree();
            }
        }




    }
}
