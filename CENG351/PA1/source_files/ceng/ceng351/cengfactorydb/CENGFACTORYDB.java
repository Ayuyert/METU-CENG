package ceng.ceng351.cengfactorydb;

public class CENGFACTORYDB implements ICENGFACTORYDB{
    /**
     * Place your initialization code inside if required.
     *
     * <p>
     * This function will be called before all other operations. If your implementation
     * need initialization , necessary operations should be done inside this function. For
     * example, you can set your connection to the database server inside this function.
     */
    public void initialize() {

    }

    /**
     * Should create the necessary tables when called.
     *package ceng.ceng351.cengfactorydb;
import java.sql.*;
import java.util.ArrayList;
public class CENGFACTORYDB implements ICENGFACTORYDB{
    /**
     * Place your initialization code inside if required.
     *
     * <p>
     * This function will be called before all other operations. If your implementation
     * need initialization , necessary operations should be done inside this function. For
     * example, you can set your connection to the database server inside this function.
     */
    private static String user = "e2521698"; // TODO: Your userName
    private static String password = "I+dwsziJm#0S"; //  TODO: Your password
    private static String host = "144.122.71.128"; // host name
    private static String database = "db2521698"; // TODO: Your database name
    private static int port = 8080; // port
    Connection connection =  null;
    public void initialize() {

        String url = "jdbc:mysql://" + host + ":" + port + "/" + database;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection =  DriverManager.getConnection(url, user, password);
        }

        catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }


    /**
     * Should create the necessary tables when called.
     *
     * @return the number of tables that are created successfully.
     */
    public int createTables(){
        int numberofTablesInserted = 0;
        /**
         * Should drop the tables if exists when called.
         *
         * @return the number of tables are dropped successfully.
         */

        String queryCreateFactoryTable = "create table if not exists Factory(" +
                "factoryId int ," +
                "factoryName Text ," +
                "factoryType Text ," +
                "country Text ," +
                "primary key (factoryId))";

        String queryCreateEmployeeTable = "create table if not exists Employee(" +
                "employeeId int ," +
                "employeeName Text ," +
                "department Text ," +
                "salary int ," +
                "primary key (employeeId))";

        String queryCreateWorks_InTable = "CREATE TABLE IF NOT EXISTS Works_In(" +
                "factoryId INT ," +
                "employeeId INT ," +
                "startDate TEXT ," +
                "PRIMARY KEY (factoryId, employeeId)," +
                "FOREIGN KEY (factoryId) REFERENCES Factory(factoryId) ," +
                "FOREIGN KEY (employeeId) REFERENCES Employee(employeeId) ON DELETE CASCADE )";


        String queryCreateProductTable = "create table if not exists Product(" +
                "productId int ," +
                "productName Text ," +
                "productType Text ," +
                "primary key (productId))";

        String queryCreateProduceTable = "CREATE TABLE IF NOT EXISTS Produce(" +
                "factoryId INT ," +
                "productId INT ," +
                "amount INT ," +
                "productionCost INT ," +
                "PRIMARY KEY (factoryId, productId)," +
                "FOREIGN KEY (factoryId) REFERENCES Factory(factoryId)  ," +
                "FOREIGN KEY (productId) REFERENCES Product(productId)  )";


        String queryCreateShipmentTable = "CREATE TABLE IF NOT EXISTS Shipment(" +
                "factoryId INT ," +
                "productId INT ," +
                "amount INT ," +
                "pricePerUnit INT ," +
                "PRIMARY KEY (factoryId, productId)," +
                "FOREIGN KEY (factoryId) REFERENCES Factory(factoryId) ," +
                "FOREIGN KEY (productId) REFERENCES Product(productId) )";


        try {
            Statement statement = this.connection.createStatement();

            statement.executeUpdate(queryCreateFactoryTable);
            numberofTablesInserted++;


            statement.executeUpdate(queryCreateEmployeeTable);
            numberofTablesInserted++;


            statement.executeUpdate(queryCreateWorks_InTable);
            numberofTablesInserted++;


            statement.executeUpdate(queryCreateProductTable);
            numberofTablesInserted++;


            statement.executeUpdate(queryCreateProduceTable);
            numberofTablesInserted++;

            statement.executeUpdate(queryCreateShipmentTable);
            numberofTablesInserted++;


            statement.close();
        }

        catch (SQLException e) {
            e.printStackTrace();
        }

        return numberofTablesInserted;
    }


    /**
     * Should drop the tables if exists when called.
     *
     * @return the number of tables are dropped successfully.
     */
    public int dropTables(){

        int numberofTablesDropped = 0;

        String queryDropFactoryTable = "drop table if exists Factory";

        String queryDropEmployeeTable = "drop table if exists Employee";

        String queryDropWorks_InTable = "drop table if exists Works_In";

        String queryDropProductTable = "drop table if exists Product";

        String queryDropProduceTable = "drop table if exists Produce";

        String queryDropShipmentTable = "drop table if exists Shipment";


        try {
            Statement statement = this.connection.createStatement();



            statement.executeUpdate(queryDropProduceTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropWorks_InTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropShipmentTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropFactoryTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropEmployeeTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropProductTable);
            numberofTablesDropped++;





            //close
            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return numberofTablesDropped;


    }


    /**
     * Should insert an array of Factory into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertFactory(Factory[] factories){

        int numberOfInserts=0;
        for(int i=0; i<factories.length;i++){
            try{
                Factory fact = factories[i];

                PreparedStatement stmt=this.connection.prepareStatement("insert into Factory values(?,?,?,?)");
                stmt.setInt(1,fact.getFactoryId());
                stmt.setString(2,fact.getFactoryName());
                stmt.setString(3,fact.getFactoryType());
                stmt.setString(4,fact.getCountry());

                stmt.executeUpdate();

                //Close
                stmt.close();
                numberOfInserts++;


            }
            catch (SQLException e) {
                e.printStackTrace();
            }

        }
        return numberOfInserts;

    }

    /**
     * Should insert an array of Employee into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertEmployee(Employee[] employees){

        int numberofRowsInserted=0;
        for(int i=0; i<employees.length;i++){
            try{
                Employee fact = employees[i];

                PreparedStatement stmt=this.connection.prepareStatement("insert into Employee values(?,?,?,?)");
                stmt.setInt(1,fact.getEmployeeId());
                stmt.setString(2,fact.getEmployeeName());
                stmt.setString(3,fact.getDepartment());
                stmt.setInt(4,fact.getSalary());

                stmt.executeUpdate();

                //Close
                stmt.close();
                numberofRowsInserted++;


            }
            catch (SQLException e) {
                e.printStackTrace();
            }

        }
        return numberofRowsInserted;

    }

    /**
     * Should insert an array of WorksIn into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertWorksIn(WorksIn[] worksIns){

        int numberofRowsInserted=0;
        for(int i=0; i<worksIns.length;i++){
            try{
                WorksIn fact = worksIns[i];

                PreparedStatement stmt=this.connection.prepareStatement("insert into Works_In values(?,?,?)");
                stmt.setInt(1,fact.getFactoryId());
                stmt.setInt(2,fact.getEmployeeId());
                stmt.setString(3,fact.getStartDate());

                stmt.executeUpdate();

                //Close
                stmt.close();
                numberofRowsInserted++;


            }
            catch (SQLException e) {
                e.printStackTrace();
            }

        }
        return numberofRowsInserted;

    }

    /**
     * Should insert an array of Product into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertProduct(Product[] products){

        int numberofRowsInserted=0;
        for(int i=0; i<products.length;i++){
            try{
                Product fact = products[i];

                PreparedStatement stmt=this.connection.prepareStatement("insert into Product values(?,?,?)");
                stmt.setInt(1,fact.getProductId());
                stmt.setString(2,fact.getProductName());
                stmt.setString(3,fact.getProductType());

                stmt.executeUpdate();

                //Close
                stmt.close();
                numberofRowsInserted++;


            }
            catch (SQLException e) {
                e.printStackTrace();
            }

        }
        return numberofRowsInserted;

    }



    /**
     * Should insert an array of Produce into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertProduce(Produce[] produces){

        int numberofRowsInserted=0;
        for(int i=0; i<produces.length;i++){
            try{
                Produce fact = produces[i];

                PreparedStatement stmt=this.connection.prepareStatement("insert into Produce values(?,?,?,?)");
                stmt.setInt(1,fact.getFactoryId());
                stmt.setInt(2,fact.getProductId());
                stmt.setInt(3,fact.getAmount());
                stmt.setInt(4,fact.getProductionCost());

                stmt.executeUpdate();

                //Close
                stmt.close();
                numberofRowsInserted++;


            }
            catch (SQLException e) {
                e.printStackTrace();
            }

        }
        return numberofRowsInserted;

    }


    /**
     * Should insert an array of Shipment into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertShipment(Shipment[] shipments){

        int numberofRowsInserted=0;
        for(int i=0; i<shipments.length;i++){
            try{
                Shipment fact = shipments[i];

                PreparedStatement stmt=this.connection.prepareStatement("insert into Shipment values(?,?,?,?)");
                stmt.setInt(1,fact.getFactoryId());
                stmt.setInt(2,fact.getProductId());
                stmt.setInt(3,fact.getAmount());
                stmt.setInt(4,fact.getPricePerUnit());

                stmt.executeUpdate();

                //Close
                stmt.close();
                numberofRowsInserted++;


            }
            catch (SQLException e) {
                e.printStackTrace();
            }

        }
        return numberofRowsInserted;

    }

    /**
     * Should return all factories that are located in a particular country.
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesForGivenCountry(String country) {

        ArrayList<Factory> factos = new ArrayList<>();

        try {
            String query = "Select distinct * " +
                    "From Factory F " +
                    "Where F.country = '" + country +
                    "' Order By F.factoryId ASC ;";
            PreparedStatement pstmt = this.connection.prepareStatement(query);
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                int factoryId = rs.getInt("factoryId");
                String factoryName = rs.getString("factoryName");
                String factoryType = rs.getString("factoryType");
                String factoryCountry = rs.getString("country");

                Factory factory = new Factory(factoryId, factoryName, factoryType, factoryCountry);
                factos.add(factory);
            }
        }



        catch (SQLException e)
        {
            e.printStackTrace();
        }
        Factory[] factoryArray = new Factory[factos.size()];
        factoryArray = factos.toArray(factoryArray);
        return factoryArray;
    }



    /**
     * Should return all factories without any working employees.
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesWithoutAnyEmployee() {

        ArrayList<Factory> factos = new ArrayList<>();

        try {
            String query = "Select distinct * " +
                    "From Factory F " +
                    "Where F.factoryId NOT IN ( " +
                    "Select W.factoryId " +
                    "From Works_In W )" +
                    "Order By F.factoryId ASC ;";
            PreparedStatement pstmt = this.connection.prepareStatement(query);
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                int factoryId = rs.getInt("factoryId");
                String factoryName = rs.getString("factoryName");
                String factoryType = rs.getString("factoryType");
                String factoryCountry = rs.getString("country");

                Factory factory = new Factory(factoryId, factoryName, factoryType, factoryCountry);
                factos.add(factory);
            }
        }

        catch (SQLException e)
        {
            e.printStackTrace();
        }
        Factory[] factoryArray = new Factory[factos.size()];
        factoryArray = factos.toArray(factoryArray);
        return factoryArray;
    }

    /**
     * Should return all factories that produce all products for a particular productType
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesProducingAllForGivenType(String productType) {

        ArrayList<Factory> factos = new ArrayList<>();

        try {
            String query = "SELECT F.factoryId, F.factoryName, F.factoryType, F.country " +
                    "FROM Factory F " +
                    "WHERE NOT EXISTS ( " +
                    "    SELECT P.productId " +
                    "    FROM Product P " +
                    "    WHERE P.productType = '" +productType +
                    "'    AND NOT EXISTS ( " +
                    "        SELECT Pr.factoryId " +
                    "        FROM Produce Pr " +
                    "        WHERE Pr.factoryId = F.factoryId " +
                    "        AND Pr.productId = P.productId " +
                    "    ) " +
                    ")  " +
                    " Order By F.factoryId ASC ;";




            PreparedStatement pstmt = this.connection.prepareStatement(query);
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                int factoryId = rs.getInt("factoryId");
                String factoryName = rs.getString("factoryName");
                String factoryType = rs.getString("factoryType");
                String factoryCountry = rs.getString("country");

                Factory factory = new Factory(factoryId, factoryName, factoryType, factoryCountry);
                factos.add(factory);
            }
        }

        catch (SQLException e)
        {
            e.printStackTrace();
        }
        Factory[] factoryArray = new Factory[factos.size()];
        factoryArray = factos.toArray(factoryArray);
        return factoryArray;


    }


    /**
     * Should return the products that are produced in a particular factory but
     * don’t have any shipment from that factory.
     *
     * @return Product[]
     */
    public Product[] getProductsProducedNotShipped() {
        ArrayList<Product> factos = new ArrayList<>();

        try {
            String query = "SELECT distinct P.productId, P.productName, P.productType\n" +
                    "FROM Product P\n" +
                    "INNER JOIN Produce Pr ON P.productId = Pr.productId\n" +
                    "LEFT JOIN Shipment S ON Pr.factoryId = S.factoryId AND Pr.productId = S.productId\n" +
                    "AND S.factoryId IS NULL\n" +
                    " Order By S.productId ASC ;";




            PreparedStatement pstmt = this.connection.prepareStatement(query);
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                int productId = rs.getInt("productId");
                String productName = rs.getString("productName");
                String productType = rs.getString("productType");


                Product factory = new Product(productId, productName, productType);
                factos.add(factory);
            }
        }

        catch (SQLException e)
        {
            e.printStackTrace();
        }
        Product[] factoryArray = new Product[factos.size()];
        factoryArray = factos.toArray(factoryArray);
        return factoryArray;
    }


    /**
     * For a given factoryId and department, should return the average salary of
     *     the employees working in that factory and that specific department.
     *
     * @return double
     */
    public double getAverageSalaryForFactoryDepartment(int factoryId, String department) {
        String query = "SELECT AVG(E.salary) AS averageSalary " +
                "FROM Employee E " +
                "JOIN Works_In W ON E.employeeId = W.employeeId " +
                "WHERE W.factoryId = ? " +
                "AND E.department = ?";

        double averageSalary = 0;

        try (PreparedStatement pstmt = connection.prepareStatement(query)) {
            pstmt.setInt(1, factoryId);
            pstmt.setString(2, department);

            ResultSet rs = pstmt.executeQuery();

            if (rs.next()) {
                averageSalary = rs.getDouble("averageSalary");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return averageSalary;
    }



    /**
     * Should return the most profitable products for each factory
     *
     * @return QueryResult.MostValueableProduct[]
     */
    public QueryResult.MostValueableProduct[] getMostValueableProducts() {
        ArrayList<QueryResult.MostValueableProduct> mostValuableProducts = new ArrayList<>();
        String query = "SELECT factoryId, productId, productName, productType, profit " +
                "FROM ( " +
                "    SELECT PR.factoryId, PR.productId, P.productName, P.productType, " +
                "    (-1 * PR.amount * PR.productionCost) + " +
                "    (CASE WHEN S.amount IS NOT NULL THEN S.amount * S.pricePerUnit ELSE 0 END) AS profit, " +
                "    ROW_NUMBER() OVER (PARTITION BY PR.factoryId ORDER BY " +
                "    (-1 * PR.amount * PR.productionCost) + " +
                "    (CASE WHEN S.amount IS NOT NULL THEN S.amount * S.pricePerUnit ELSE 0 END) DESC) AS rn " +
                "    FROM Produce PR " +
                "    INNER JOIN Product P ON PR.productId = P.productId " +
                "    LEFT JOIN Shipment S ON PR.factoryId = S.factoryId AND PR.productId = S.productId " +
                ") AS ranked " +
                "WHERE rn = 1 " +
                "ORDER BY profit DESC";



        /*"SELECT factoryId, productId, productName, productType, profit " +
                "FROM ( " +
                "    SELECT S.factoryId, P.productId, P.productName, P.productType, " +
                "        (S.amount * S.pricePerUnit) - (Pr.amount * Pr.productionCost) AS profit, " +
                "        ROW_NUMBER() OVER(PARTITION BY S.factoryId ORDER BY (S.amount * S.pricePerUnit) - (Pr.amount * Pr.productionCost) DESC) AS rn " +
                "    FROM Shipment S " +
                "    JOIN Produce Pr ON S.factoryId = Pr.factoryId AND S.productId = Pr.productId " +
                "    JOIN Product P ON P.productId = S.productId " +
                "    GROUP BY S.factoryId, P.productId " +
                "    HAVING profit > 0 " +
                ") ranked " +
                "WHERE rn = 1 " +
                "ORDER BY factoryId ASC";*/

        try (Statement stmt = connection.createStatement()) {
            ResultSet rs = stmt.executeQuery(query);

            while (rs.next()) {
                int factoryId = rs.getInt("factoryId");
                int productId = rs.getInt("productId");
                String productName = rs.getString("productName");
                String productType = rs.getString("productType");
                double profit = rs.getDouble("profit");

                QueryResult.MostValueableProduct product = new QueryResult.MostValueableProduct(factoryId, productId, productName, productType, profit);
                mostValuableProducts.add(product);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return mostValuableProducts.toArray(new QueryResult.MostValueableProduct[0]);
    }


    /**
     * For each product, return the factories that gather the highest profit
     * for that product
     *
     * @return QueryResult.MostValueableProduct[]
     */
    public QueryResult.MostValueableProduct[] getMostValueableProductsOnFactory() {
        ArrayList<QueryResult.MostValueableProduct> mostValuableProducts = new ArrayList<>();
        String query = "SELECT factoryId, productId, productName, productType, profit " +
                "FROM (SELECT PR.factoryId, PR.productId, P.productName, P.productType, " +
                "MAX((-1 * PR.amount * PR.productionCost) + " +
                "CASE WHEN S.amount IS NOT NULL THEN S.amount * S.pricePerUnit ELSE 0 END) AS profit, " +
                "ROW_NUMBER() OVER(PARTITION BY PR.productId " +
                "ORDER BY MAX((-1 * PR.amount * PR.productionCost) + " +
                "CASE WHEN S.amount IS NOT NULL THEN S.amount * S.pricePerUnit ELSE 0 END) DESC) AS rn " +
                "FROM Produce PR " +
                "INNER JOIN Product P ON PR.productId = P.productId " +
                "LEFT JOIN Shipment S ON PR.factoryId = S.factoryId AND PR.productId = S.productId " +
                "GROUP BY PR.factoryId, PR.productId, P.productName, P.productType) AS sub " +
                "WHERE rn = 1 " +
                "ORDER BY profit DESC, productId ASC";



        try (Statement stmt = connection.createStatement()) {
            ResultSet rs = stmt.executeQuery(query);

            while (rs.next()) {
                int factoryId = rs.getInt("factoryId");
                int productId = rs.getInt("productId");
                String productName = rs.getString("productName");
                String productType = rs.getString("productType");
                int profit = rs.getInt("profit");

                QueryResult.MostValueableProduct mostValueableProduct = new QueryResult.MostValueableProduct(factoryId, productId, productName, productType, profit);
                mostValuableProducts.add(mostValueableProduct);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return mostValuableProducts.toArray(new QueryResult.MostValueableProduct[0]);
    }



    /**
     * For each department, should return all employees that are paid under the
     *     average salary for that department. You consider the employees
     *     that do not work earning ”0”.
     *
     * @return QueryResult.LowSalaryEmployees[]
     */
    public QueryResult.LowSalaryEmployees[] getLowSalaryEmployeesForDepartments() {
        ArrayList<QueryResult.LowSalaryEmployees> lowSalaryEmployeesList = new ArrayList<>();
        String query = "SELECT distinct E.employeeId, E.employeeName, E.department, " +
                "CASE WHEN W.employeeId IS NULL THEN 0 ELSE E.salary END AS salary " +
                "FROM Employee E " +
                "LEFT JOIN Works_In W ON E.employeeId = W.employeeId " +
                "WHERE E.salary < IFNULL((SELECT AVG(E2.salary) " +
                "                         FROM Employee E2 " +
                "                         WHERE E2.department = E.department), 0) " +
                "OR E.employeeId NOT IN (SELECT employeeId FROM Works_In) " +
                "ORDER BY E.employeeId ASC";

        try (Statement stmt = connection.createStatement()) {
            ResultSet rs = stmt.executeQuery(query);

            while (rs.next()) {
                int employeeId = rs.getInt("employeeId");
                String employeeName = rs.getString("employeeName");
                String department = rs.getString("department");
                int salary = rs.getInt("salary");

                QueryResult.LowSalaryEmployees lowSalaryEmployee = new QueryResult.LowSalaryEmployees(employeeId, employeeName, department, salary);
                lowSalaryEmployeesList.add(lowSalaryEmployee);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return lowSalaryEmployeesList.toArray(new QueryResult.LowSalaryEmployees[0]);
    }




    /**
     * For the products of given productType, increase the productionCost of every unit by a given percentage.
     *
     * @return number of rows affected
     */
    public int increaseCost(String productType, double percentage) {
        int rowsAffected = 0;
        try {
            String sql = "UPDATE Produce pr " +
                    "JOIN Product p ON pr.productId = p.productId " +
                    "SET pr.productionCost = pr.productionCost * (1 + ?) " +
                    "WHERE p.productType = ?";
            PreparedStatement pstmt = connection.prepareStatement(sql);
            pstmt.setDouble(1, percentage / 100.0);
            pstmt.setString(2, productType);
            rowsAffected = pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return rowsAffected;
    }



    /**
     * Deleting all employees that have not worked since the given date.
     *
     * @return number of rows affected
     */
    public int deleteNotWorkingEmployees(String givenDate) {
        int rowsAffected = 0;

        try {
            String deleteQuery = "DELETE FROM Employee WHERE employeeId NOT IN " +
                    "(SELECT employeeId FROM Works_In WHERE STR_TO_DATE(startDate, '%Y-%m-%d') > ?)";

            PreparedStatement pstmt = connection.prepareStatement(deleteQuery);
            pstmt.setString(1, givenDate);

            rowsAffected = pstmt.executeUpdate();

            pstmt.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return rowsAffected;
    }






    /**
     * *****************************************************
     * *****************************************************
     * *****************************************************
     * *****************************************************
     *  THE METHODS AFTER THIS LINE WILL NOT BE GRADED.
     *  YOU DON'T HAVE TO SOLVE THEM, LEAVE THEM AS IS IF YOU WANT.
     *  IF YOU HAVE ANY QUESTIONS, REACH ME VIA EMAIL.
     * *****************************************************
     * *****************************************************
     * *****************************************************
     * *****************************************************
     */

    /**
     * For each department, find the rank of the employees in terms of
     * salary. Peers are considered tied and receive the same rank. After
     * that, there should be a gap.
     *
     * @return QueryResult.EmployeeRank[]
     */
    public QueryResult.EmployeeRank[] calculateRank() {
        return new QueryResult.EmployeeRank[0];
    }

    /**
     * For each department, find the rank of the employees in terms of
     * salary. Everything is the same but after ties, there should be no
     * gap.
     *
     * @return QueryResult.EmployeeRank[]
     */
    public QueryResult.EmployeeRank[] calculateRank2() {
        return new QueryResult.EmployeeRank[0];
    }

    /**
     * For each factory, calculate the most profitable 4th product.
     *
     * @return QueryResult.FactoryProfit
     */
    public QueryResult.FactoryProfit calculateFourth() {
        return new QueryResult.FactoryProfit(0,0,0);
    }

    /**
     * Determine the salary variance between an employee and another
     * one who began working immediately after the first employee (by
     * startDate), for all employees.
     *
     * @return QueryResult.SalaryVariant[]
     */
    public QueryResult.SalaryVariant[] calculateVariance() {
        return new QueryResult.SalaryVariant[0];
    }

    /**
     * Create a method that is called once and whenever a Product starts
     * losing money, deletes it from Produce table
     *
     * @return void
     */
    public void deleteLosing() {

    }
}
     * @return the number of tables that are created successfully.
     */
    public int createTables() {
        return 0;
    }

    /**
     * Should drop the tables if exists when called.
     *
     * @return the number of tables are dropped successfully.
     */
    public int dropTables() {
        return 0;
    }

    /**
     * Should insert an array of Factory into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertFactory(Factory[] factories) {
        return 0;
    }

    /**
     * Should insert an array of Employee into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertEmployee(Employee[] employees) {
        return 0;
    }

    /**
     * Should insert an array of WorksIn into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertWorksIn(WorksIn[] worksIns) {
        return 0;
    }

    /**
     * Should insert an array of Product into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertProduct(Product[] products) {
        return 0;
    }


    /**
     * Should insert an array of Produce into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertProduce(Produce[] produces) {
        return 0;
    }


    /**
     * Should insert an array of Shipment into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertShipment(Shipment[] shipments) {
        return 0;
    }

    /**
     * Should return all factories that are located in a particular country.
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesForGivenCountry(String country) {
        return new Factory[0];
    }



    /**
     * Should return all factories without any working employees.
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesWithoutAnyEmployee() {
        return new Factory[0];
    }

    /**
     * Should return all factories that produce all products for a particular productType
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesProducingAllForGivenType(String productType) {
        return new Factory[0];
    }


    /**
     * Should return the products that are produced in a particular factory but
     * don’t have any shipment from that factory.
     *
     * @return Product[]
     */
    public Product[] getProductsProducedNotShipped() {
        return new Product[0];
    }


    /**
     * For a given factoryId and department, should return the average salary of
     *     the employees working in that factory and that specific department.
     *
     * @return double
     */
    public double getAverageSalaryForFactoryDepartment(int factoryId, String department) {
        return 0.0;
    }


    /**
     * Should return the most profitable products for each factory
     *
     * @return QueryResult.MostValueableProduct[]
     */
    public QueryResult.MostValueableProduct[] getMostValueableProducts() {
        return new QueryResult.MostValueableProduct[0];
    }

    /**
     * For each product, return the factories that gather the highest profit
     * for that product
     *
     * @return QueryResult.MostValueableProduct[]
     */
    public QueryResult.MostValueableProduct[] getMostValueableProductsOnFactory() {
        return new QueryResult.MostValueableProduct[0];
    }


    /**
     * For each department, should return all employees that are paid under the
     *     average salary for that department. You consider the employees
     *     that do not work earning ”0”.
     *
     * @return QueryResult.LowSalaryEmployees[]
     */
    public QueryResult.LowSalaryEmployees[] getLowSalaryEmployeesForDepartments() {
        return new QueryResult.LowSalaryEmployees[0];
    }


    /**
     * For the products of given productType, increase the productionCost of every unit by a given percentage.
     *
     * @return number of rows affected
     */
    public int increaseCost(String productType, double percentage) {
        return 0;
    }


    /**
     * Deleting all employees that have not worked since the given date.
     *
     * @return number of rows affected
     */
    public int deleteNotWorkingEmployees(String givenDate) {
        return 0;
    }


    /**
     * *****************************************************
     * *****************************************************
     * *****************************************************
     * *****************************************************
     *  THE METHODS AFTER THIS LINE WILL NOT BE GRADED.
     *  YOU DON'T HAVE TO SOLVE THEM, LEAVE THEM AS IS IF YOU WANT.
     *  IF YOU HAVE ANY QUESTIONS, REACH ME VIA EMAIL.
     * *****************************************************
     * *****************************************************
     * *****************************************************
     * *****************************************************
     */

    /**
     * For each department, find the rank of the employees in terms of
     * salary. Peers are considered tied and receive the same rank. After
     * that, there should be a gap.
     *
     * @return QueryResult.EmployeeRank[]
     */
    public QueryResult.EmployeeRank[] calculateRank() {
        return new QueryResult.EmployeeRank[0];
    }

    /**
     * For each department, find the rank of the employees in terms of
     * salary. Everything is the same but after ties, there should be no
     * gap.
     *
     * @return QueryResult.EmployeeRank[]
     */
    public QueryResult.EmployeeRank[] calculateRank2() {
        return new QueryResult.EmployeeRank[0];
    }

    /**
     * For each factory, calculate the most profitable 4th product.
     *
     * @return QueryResult.FactoryProfit
     */
    public QueryResult.FactoryProfit calculateFourth() {
        return new QueryResult.FactoryProfit(0,0,0);
    }

    /**
     * Determine the salary variance between an employee and another
     * one who began working immediately after the first employee (by
     * startDate), for all employees.
     *
     * @return QueryResult.SalaryVariant[]
     */
    public QueryResult.SalaryVariant[] calculateVariance() {
        return new QueryResult.SalaryVariant[0];
    }

    /**
     * Create a method that is called once and whenever a Product starts
     * losing money, deletes it from Produce table
     *
     * @return void
     */
    public void deleteLosing() {

    }
}
