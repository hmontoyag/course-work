import java.io.*;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.sql.*;
import java.util.Scanner;

public class Project3 {

    static final String DB_URL = "jdbc:oracle:thin:@claros.cs.purdue.edu:1524:strep";
    static final String USER = "hmontoya";
    static final String PASS = "a0axT5SE";
    boolean status;
    String user;
    int globalUserId;
    boolean admin;

    public Project3() {
        this.status = false;
        this.user = null;
        this.admin = false;
    }

    public static String encrypt(String plainText, String key){
        HashMap<Character, Integer> alphaMap = new HashMap<>();
        Integer i = 0;
        //make hash and list for easy retrieval
        for (char letter='a'; letter<='z'; letter++){
            alphaMap.put(Character.valueOf(letter),i);
            i++;
        }
        ArrayList<Character> record = new ArrayList<>();
        for(char letter='a'; letter<='z' ;letter++){
            record.add(Character.valueOf(letter));
        }
        //keep track of casing
        int[] cases = new int[plainText.length()];
        for(int j = 0; j<=plainText.length()-1;j++){
            if(Character.isUpperCase(plainText.charAt(j))){
                cases[j] = 1;
            } else {
                cases[j]=0;
            }
        }
        key = key.toLowerCase();
        plainText = plainText.toLowerCase();
        String combo = key + plainText;
        combo = combo.replaceAll("[^a-zA-Z]", "");
        combo = combo.trim();
        int kc = 0;
        int[] encryption = new int[plainText.length()];
        for(int j=0; j<=plainText.length()-1;j++){
            int ptnum;
            int cnum;
            int totnum;
            if(Character.valueOf(plainText.charAt(j)) >= 'a' && Character.valueOf(plainText.charAt(j)) <= 'z') {
                    ptnum = alphaMap.get(Character.valueOf(plainText.charAt(j)));
                    cnum = alphaMap.get(Character.valueOf(combo.charAt(kc)));
                    totnum = (ptnum + cnum) % 26;
                    encryption[j] = totnum;
                    kc++;
            } else {
                encryption[j] = -1;
            }
        }
        String result = "";
        for(int j=0; j!=encryption.length;j++){
            if (encryption[j] >=0) {
                char c = record.get(encryption[j]);
                if(cases[j]==1){
                    c = Character.toUpperCase(c);
                }
                result = result + c;
            } else {
                result = result + plainText.charAt(j);
            }
        }
        return result;
    }

    public static String decrypt(String plainText, String key) {
        HashMap<Character, Integer> alphaMap = new HashMap<>();
        Integer i = 0;
        //make hash and list for easy retrieval
        for (char letter = 'a'; letter <= 'z'; letter++) {
            alphaMap.put(Character.valueOf(letter), i);
            i++;
        }
        ArrayList<Character> record = new ArrayList<>();
        for (char letter = 'a'; letter <= 'z'; letter++) {
            record.add(Character.valueOf(letter));
        }
        //keep track of casing
        int[] cases = new int[plainText.length()];
        for (int j = 0; j <= plainText.length() - 1; j++) {
            if(Character.isAlphabetic(plainText.charAt(j))) {
                if (Character.isUpperCase(plainText.charAt(j))) {
                    cases[j] = 1;
                } else {
                    cases[j] = 0;
                }
            } else {
                cases[j]=-1;
            }
        }

        key = key.toLowerCase();
        plainText = plainText.toLowerCase();
        String clean = plainText.replaceAll("[^a-zA-Z]", "");
        clean = clean.trim();
        int e=0;
        int k = 0;
        //System.out.println(clean);

        int[] encryption = new int[clean.length()];
        for (k = 0; k<key.length(); k++){
            int num = (((alphaMap.get(clean.charAt(k))-alphaMap.get(key.charAt(k)))%26)+26)%26;
            encryption[e++] = num;
        }
        int t=0;
        for(k=k;k!=clean.length();k++){
            int num = (((alphaMap.get(clean.charAt(k))-encryption[t])%26)+26)%26;
            encryption[e++] = num;
            t++;
        }
        /*for(int j = 0; j!=encryption.length;j++){
            System.out.println(encryption[j]);
        }*/






    int kc =0;
        String result = "";
        for (int j = 0; j != plainText.length(); j++) {
            if (cases[j] >= 0) {
                char c = record.get(encryption[kc]);
                if (cases[j] == 1) {
                    c = Character.toUpperCase(c);
                }
                result = result + c;
                kc++;
            } else {
                result = result + plainText.charAt(j);
            }
        }
        return result;
    }






    public static void main(String[] args){
        Project3 pr = new Project3();
        /*String r = encrypt("'category 1'", "cK");
        System.out.println(r);
        System.out.println(decrypt(r,"cK"));*/


        Connection conn = null;
        Statement stmt = null;
        int cmdNumber = 1;
        String command ="";
        String fname = args[0];
        String outname = args[1];


            //SQL BLOCK*************************************************************************************************
            try {
                Class.forName("oracle.jdbc.OracleDriver");
                conn = DriverManager.getConnection(DB_URL, USER, PASS);

                stmt = conn.createStatement();
                //SCANNER Block*****************************************************************************************
                try {
                    Scanner scanner = new Scanner(new File(fname));
                    Writer writer = new BufferedWriter(new FileWriter(outname));
                    //COMMANDS read*************************************************************************************
                    while (scanner.hasNext()){
                        command = scanner.next();
                        //LOGIN
                        if(command.equals("LOGIN")){
                            String usr = scanner.next();
                            String pass = scanner.next();
                            writer.append(cmdNumber + ": " +command + " " + usr + " " + pass+"\n");
                            cmdNumber++;

                            String query ="SELECT * FROM users WHERE username = '" + usr + "'";
                            ResultSet rs = stmt.executeQuery(query);
                            String dbpass = null;
                            String dbusr = null;
                            int usrid = 0;
                            while(rs.next()) {
                                usrid = rs.getInt("UserId");
                                dbpass = rs.getString("Password");
                                dbusr = rs.getString("Username");
                            }
                            if (dbpass.equals(pass)||(dbusr.equals(usr) && pr.status == true)){
                                pr.status = true;
                                pr.user = usr;
                                pr.globalUserId=usrid;
                                writer.append("Login successful"+"\n");
                                if(usrid == 1){  // the handout states a user (userid:1, username: admin) with roleid:1, role:ADMIN, will always exist
                                    //therefore is usrid = 1, the user is an admin.  And it also states we will have only
                                    // one admin. So that is the only case where a user is admin.
                                    pr.admin = true;
                                } else {
                                    pr.admin = false;
                                }

                            } else {
                                    writer.append("Invalid login"+"\n");
                            }







                        //CREATE....
                        } else if(command.equals("CREATE")){
                            String crtWhat = scanner.next();
                            //CREATE ROLE
                            if(crtWhat.equals("ROLE")) {
                                String roleName = scanner.next();
                                String encKey = scanner.next();
                                writer.append(cmdNumber + ": " + command + " " + crtWhat + " " + roleName + " " + encKey + "\n");
                                cmdNumber++;

                                if (pr.admin == true && pr.status == true) {
                                    String query = "SELECT count(*) as count FROM roles";
                                    ResultSet rs = stmt.executeQuery(query);
                                    int toBeId = -1;
                                    while (rs.next()) {
                                        toBeId = rs.getInt("count") + 1;
                                    }

                                    query = "INSERT INTO Roles " +
                                            "VALUES (" + toBeId + ", '" + roleName + "', '" + encKey + "')";
                                    stmt.executeUpdate(query);
                                    writer.append("Role created successfully\n");

                                } else {
                                    writer.append("Authorization failure\n");
                                }



                            //CREATE USER
                            } else if(crtWhat.equals("USER")){
                                String usr = scanner.next();
                                String pass = scanner.next();
                                writer.append(cmdNumber + ": " +command + " " + crtWhat + " " + usr + " " + pass+"\n");
                                cmdNumber++;

                                if(pr.admin==true && pr.status== true){
                                    String query ="SELECT count(*) as count FROM users";
                                    ResultSet rs = stmt.executeQuery(query);
                                    int toBeId=-1;
                                    while(rs.next()) {
                                        toBeId = rs.getInt("count")+1;
                                    }

                                    query = "INSERT INTO users " +
                                            "VALUES ("+toBeId+", '"+usr+"', '"+pass+"')";
                                    stmt.executeUpdate(query);
                                    writer.append("User created successfully\n");

                                } else {
                                    writer.append("Authorization failure\n");
                                }

                            }
                        //GRANT....
                        }else if(command.equals("GRANT")) {
                            String grntWhat = scanner.next();
                            //GRANT ROLE
                            if (grntWhat.equals("ROLE")) {
                                String usr = scanner.next();
                                String roleName = scanner.next();
                                writer.append(cmdNumber + ": " +command + " " + grntWhat + " " + usr + " " + roleName+"\n");
                                cmdNumber++;
                                if(pr.admin==true && pr.status== true){
                                    String query = "SELECT userid FROM users WHERE username ='" + usr + "'";
                                    ResultSet rs = stmt.executeQuery(query);
                                    int usrid = -1;
                                    while (rs.next()) {
                                        usrid = rs.getInt("userid");
                                    }
                                    query = "SELECT roleid FROM roles WHERE rolename ='" + roleName + "'";
                                    rs = stmt.executeQuery(query);
                                    int roleid = -1;
                                    while (rs.next()) {
                                        roleid = rs.getInt("roleid");
                                    }
                                    //System.out.println(usrid + roleid);
                                    query = "INSERT INTO usersroles " +
                                            "VALUES ("+usrid+", "+roleid+")";
                                    stmt.executeUpdate(query);
                                    writer.append("Role assigned successfully\n");
                                } else {
                                    writer.append("Authorization failure\n");
                                }




                                //GRANT PRIVILEGE
                            } else if (grntWhat.equals("PRIVILEGE")) {
                                String privName = scanner.next();
                                scanner.next();
                                String roleName = scanner.next();
                                scanner.next();
                                String tableName = scanner.next();
                                writer.append(cmdNumber + ": " +command + " " + grntWhat + " " + privName + " TO " + roleName + " ON " + tableName+"\n");
                                cmdNumber++;

                                if(pr.admin==true && pr.status== true){
                                    String query = "SELECT privid FROM privileges WHERE privname ='" + privName + "'";
                                    ResultSet rs = stmt.executeQuery(query);
                                    int privid = -1;
                                    while (rs.next()) {
                                        privid = rs.getInt("privid");
                                    }
                                    //System.out.println(privid);
                                    query = "SELECT roleid FROM roles WHERE rolename ='" + roleName + "'";
                                    rs = stmt.executeQuery(query);
                                    int roleid = -1;
                                    while (rs.next()) {
                                        roleid = rs.getInt("roleid");
                                    }
                                    //System.out.println(usrid + roleid);
                                    query = "INSERT INTO rolesprivileges " +
                                            "VALUES ("+roleid+", "+privid+",'"+tableName+"')";
                                    stmt.executeUpdate(query);
                                    writer.append("Privilege granted successfully\n");
                                } else {
                                    writer.append("Authorization failure\n");
                                }

                            }
                        //REVOKE PRIVILEGE
                        }else if (command.equals("REVOKE")){
                                scanner.next();
                                String privName = scanner.next();
                                scanner.next();
                                String roleName = scanner.next();
                                scanner.next();
                                String tableName = scanner.next();
                            writer.append(cmdNumber + ": " +command + " PRIVILEGE "  + privName + " FROM " + roleName + " ON " + tableName+"\n");
                                cmdNumber++;

                            if(pr.admin==true && pr.status== true){
                                String query = "SELECT privid FROM privileges WHERE privname ='" + privName + "'";
                                ResultSet rs = stmt.executeQuery(query);
                                int privid = -1;
                                while (rs.next()) {
                                    privid = rs.getInt("privid");
                                }
                                //System.out.println(privid);
                                query = "SELECT roleid FROM roles WHERE rolename ='" + roleName + "'";
                                rs = stmt.executeQuery(query);
                                int roleid = -1;
                                while (rs.next()) {
                                    roleid = rs.getInt("roleid");
                                }
                                //System.out.println(usrid + roleid);
                                query = "DELETE FROM rolesprivileges WHERE roleid =" + roleid +" and privid= " + privid + " and tablename='" + tableName +"'";
                                stmt.executeUpdate(query);
                                writer.append("Privilege revoked successfully\n");
                            } else {
                                writer.append("Authorization failure\n");
                            }


                            //INSERT
                        }else if (command.equals("INSERT")){
                            scanner.next();
                            String tableName = scanner.next();
                            scanner.next();
                            String values = scanner.nextLine();

                            writer.append(cmdNumber + ": " +command + " INTO "  + tableName + " VALUES" +values+"\n");
                            cmdNumber++;
                            String[] tokens = values.split("\\)");
                            //values = values.trim();
                            String[] params = tokens[1].split(" ");
                            String columnNo = params[2];
                            String ownerRole = params[3];
                            //writer.append("|" + tokens[0] + "|\n");
                           // writer.append("|" + columnNo + "|\n");
                           // writer.append("|" + ownerRole + "|\n");
                            String query = "SELECT roleid FROM roles WHERE rolename = '" + ownerRole + "'" ;
                            int roleid = -1;
                            ResultSet rs = stmt.executeQuery(query);
                            while (rs.next()) {
                                roleid = rs.getInt("roleid");
                            }
                            values = tokens[0].trim();
                            values = values + ", " + columnNo + ", " + roleid +")";
                            values = values.trim();
                            //System.out.println(">" +values+"<");
                            query = "SELECT roleid FROM usersroles WHERE userid =" + pr.globalUserId ;
                            rs = stmt.executeQuery(query);
                            ArrayList<Integer> roles = new ArrayList<Integer>();
                            int pick;
                            boolean hasPermit = false;
                            while (rs.next()) {
                                pick = rs.getInt(1);
                                roles.add(pick);
                            }
                            for(int i=0;i!=roles.size();i++){
                               query = "SELECT count(*) as count from rolesprivileges WHERE privid = 1 and roleid = " + roles.get(i) + " and tablename = '" + tableName + "'";
                                rs = stmt.executeQuery(query);
                                int cc = -1;
                                while (rs.next()) {
                                    cc = rs.getInt("count");
                                    if(cc > 0){
                                        hasPermit = true;
                                    }
                                }
                            }
                            if(hasPermit){
                                String[] parameters = values.split(",");
                                parameters[0] = parameters[0].substring(1);
                                parameters[parameters.length-1] = parameters[parameters.length-1].substring(0,parameters[parameters.length-1].length()-1);
                                for(int i=0;i!=parameters.length;i++){
                                    parameters[i]=parameters[i].trim();
                                }
                                if(Integer.parseInt(columnNo) > 0 ){
                                    query = "SELECT encryptionkey from roles WHERE rolename = '" + ownerRole +"'";
                                    rs = stmt.executeQuery(query);
                                    String key = "";
                                    while (rs.next()) {
                                        key = rs.getString("encryptionkey");
                                    }
                                    parameters[Integer.parseInt(columnNo)-1] = pr.encrypt(parameters[Integer.parseInt(columnNo)-1],key);
                                }
                                String toInsert = "( " + parameters[0];
                                for(int i=1;i!=parameters.length;i++){
                                    toInsert = toInsert+", " +parameters[i];
                                }
                                toInsert = toInsert + ")";
                                //System.out.println(toInsert);
                                query = "INSERT INTO " + tableName+
                                        " VALUES " + toInsert;
                               //System.out.println(query);
                                stmt.executeUpdate(query);
                                writer.append("Row inserted successfully\n");

                            } else {
                                writer.append("Authorization failure\n");
                            }





                        //SELECT
                        }else if (command.equals("SELECT")){
                            scanner.next();
                            scanner.next();
                            String tableName = scanner.next();
                            writer.append(cmdNumber + ": " +command + " * FROM "  + tableName+"\n");
                            cmdNumber++;

                            String query = "SELECT roleid FROM usersroles WHERE userid =" + pr.globalUserId ;
                            ResultSet rs = stmt.executeQuery(query);
                            ArrayList<Integer> roles = new ArrayList<Integer>();
                            int pick;
                            boolean hasPermit = false;
                            while (rs.next()) {
                                pick = rs.getInt(1);
                                roles.add(pick);
                            }
                            for(int i=0;i!=roles.size();i++) {
                                query = "SELECT count(*) as count from rolesprivileges WHERE privid = 2 and roleid = " + roles.get(i) + " and tablename = '" + tableName + "'";
                                rs = stmt.executeQuery(query);
                                int cc = -1;
                                while (rs.next()) {
                                    cc = rs.getInt("count");
                                    if (cc > 0) {
                                        hasPermit = true;
                                    }
                                }
                            }

                            if(hasPermit){
                                query = "SELECT * FROM " + tableName;
                                rs = stmt.executeQuery(query);
                                ResultSetMetaData rsmd = rs.getMetaData();
                                int columnCount = rsmd.getColumnCount();
                                if (columnCount >=1){
                                    writer.append(rsmd.getColumnName(1));
                                }
                                if(columnCount > 1){
                                    for(int i = 2; i<=columnCount-2; i++){
                                        writer.append(", " + rsmd.getColumnName(i));
                                    }
                                }
                                writer.append("\n");
// ALL COLUMN NAMES PRINTED
                                HashMap<Integer,String> roleKeys = new HashMap<Integer, String>();
//all good on the north of here *************************************************************************************************************************

                                query = "SELECT roles.roleid, encryptionkey FROM roles JOIN usersroles ON roles.roleid = usersroles.roleid WHERE usersroles.userid = " + pr.globalUserId;
                                rs = stmt.executeQuery(query);

                                while(rs.next()) {
                                    String key = rs.getString("encryptionkey");
                                    int id = rs.getInt("roleid");
                                    roleKeys.put(id,key);
                                    //System.out.println(key + " : " + id);

                                }

                                query = "SELECT * FROM " + tableName;
                                rs = stmt.executeQuery(query);

                                while(rs.next()){
                                    if (columnCount >=1){
                                        writer.append(rs.getString(1));
                                    }
                                    if(columnCount > 1){
                                        for(int i = 2; i<=columnCount-2; i++){
                                            if(i == rs.getInt("EncryptedColumn")){
                                                    if(roleKeys.containsKey(rs.getInt("OwnerRole"))){
                                                        writer.append(", " + pr.decrypt(rs.getString(i),roleKeys.get(rs.getInt("OwnerRole"))));
                                                    } else {
                                                        writer.append(", " + rs.getString(i));
                                                    }
                                            } else {
                                                writer.append(", " + rs.getString(i));

                                            }

                                        }
                                    }
                                }
/*


                                    String key ="";
                                    while(setForKey.next()) {
                                         key = setForKey.getString("EncryptionKey");
                                    }
                                    System.out.println("checkpoint 0");
                                    if (columnCount >=1){
                                        System.out.println("checkpoint 1");

                                        writer.append(cname);
                                        System.out.println("checkpoint 2");

                                    }
                                    System.out.println("checkpoint 3");
                                    if(columnCount > 1){
                                        System.out.println("checkpoint 4");
                                       for(int i = 2; i<=columnCount-2; i++){

                                            if(i==rs.getInt("encryptedColumn") && authToDecrypt==true){
                                                writer.append(", " + pr.decrypt(rs.getString(rsmd.getColumnName(i)),key));
                                            }
                                            writer.append(", " + rs.getObject(rsmd.getColumnName(i)).toString());
                                        }

                                    }
                                }*/
                                writer.write("\n");



                            } else {
                                writer.append("Authorization failure\n");
                            }

                        //QUIT
                        }else if (command.equals("QUIT")) {
                            writer.write(cmdNumber + ": QUIT");
                            cmdNumber++;

                        }

                        writer.write("\n");

                    }
                    writer.close();


                }catch(Exception e){
                    System.out.println("Error."  + cmdNumber+" "+ command);
                }



            } catch (SQLException e) {
                e.printStackTrace();

            } catch (Exception e) {
                //Handle errors for Class.forName
                e.printStackTrace();
            } finally {
                //finally block used to close resources
                try {
                    if (stmt != null)
                        stmt.close();
                } catch (SQLException se2) {
                }// nothing we can do
                try {
                    if (conn != null)
                        conn.close();
                } catch (SQLException se) {
                    se.printStackTrace();
                }//end finally try
            }



    }

}
