#include <cstring>
#include <vector>
#include <sqlite3.h> 
#include <iostream>

using namespace std;

string response;
string old_readers;
sqlite3 *db;
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    char* columnName;
    char* columnValueString;
    short int columnValueShortInt = 0;
    int columnValueInt = 0;

    //  cout << "begin of callback function\n";

    for(i=0; i<argc; i++)
    {
        columnName = azColName[i];
        if (strcmp(columnName, "MESSAGE")==0)
        {
            if (argv[i] != NULL)
                response = argv[i];
            else response="FALSE";
        }
        if (strcmp(columnName, "READERS")==0)
        {
            if (argv[i] != NULL)
                old_readers = argv[i];
            else response="FALSE";
        }

    }
    //  cout << "end of call back function \n";
    return 0;
}

int chat_insert(string chat_hash, vector<string> emails)
{
    char *zErrMsg = 0;
    int  rc;
    //   char *sql;
    string database_name="recent.db";
    /* Open database */
    rc = sqlite3_open(database_name.data(), &db);
    if( rc ){
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 0;
    }else{
        cout << "Opened database successfully\n";
    }

    /* Create SQL statement */

    string  create = "CREATE TABLE IF NOT EXISTS CHATS("  \
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                      "HASH        TEXT    NOT NULL),"  \
                      "RECIPIENTS        TEXT    NOT NULL);";

    char *c_sql = new char[create.length() + 1];
    strcpy(c_sql, create.c_str());
    rc = sqlite3_exec(db, c_sql, callback, 0, &zErrMsg);

    string recips="";
    for (int x = 0; x < emails.size(); x++){
        recips+=emails[x];
    }

    /* Execute SQL statement */
    string ssql = "INSERT INTO CHATS (HASH, RECIPIENTS) "  \
                   "VALUES ('"+chat_hash+"', '"+recips+"'); " ;

    char *i_sql = new char[ssql.length() + 1];
    strcpy(i_sql, ssql.c_str());
    rc = sqlite3_exec(db, i_sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        cout << "SQL error: " << zErrMsg;
        sqlite3_free(zErrMsg);
    }else{
        cout << "Table created successfully\n";
    }
    sqlite3_close(db);
    return 0;
}

int database_insert(string message)
{
    char *zErrMsg = 0;
    int  rc;
    //   char *sql;
    string database_name="recent.db";
    /* Open database */
    rc = sqlite3_open(database_name.data(), &db);
    if( rc ){
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 0;
    }else{
        cout << "Opened database successfully\n";
    }

    /* Create SQL statement */

    string  create = "CREATE TABLE IF NOT EXISTS MESSAGES("  \
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                      "MESSAGE        TEXT    NOT NULL);";

    char *c_sql = new char[create.length() + 1];
    strcpy(c_sql, create.c_str());
    rc = sqlite3_exec(db, c_sql, callback, 0, &zErrMsg);

    /* Execute SQL statement */
    string ssql = "INSERT INTO MESSAGES (MESSAGE) "  \
                   "VALUES ('"+message+"'); " ;

    char *i_sql = new char[ssql.length() + 1];
    strcpy(i_sql, ssql.c_str());
    rc = sqlite3_exec(db, i_sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        cout << "SQL error: " << zErrMsg;
        sqlite3_free(zErrMsg);
    }else{
        cout << "Table created successfully\n";
    }
    sqlite3_close(db);
    return 0;
}

string chats_retrieve(string database_id, string idhash, string readers)
{
    response="";

    string new_readers;
    char *zErrMsg = 0;
    int  rc;

    rc = sqlite3_open(database_id.data(), &db);
    if( rc ){
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 0;
    }else{
        cout << "Opened database successfully\n";
    }

    string  read = "select MESSAGE,READERS from messages where IDHASH='"+idhash+"';";
    rc = sqlite3_exec(db, read.data(), callback, 0, &zErrMsg);

    if ( response.empty() ) return "FALSE";

    std::string delimiter = ",";

    size_t pos = 0;
    std::string token;
    while ((pos = old_readers.find(delimiter)) != std::string::npos) {
        token = old_readers.substr(0, pos);
        old_readers.erase(0, pos + delimiter.length());
        if (new_readers.empty() && token != readers ) new_readers+=token;
        else if (token != readers) new_readers+=","+token;
    }
    if (old_readers != readers ) new_readers+= old_readers;
    string  remove_readers = "update  messages set READERS='"+new_readers+"'where IDHASH='"+idhash+"';";
    rc = sqlite3_exec(db, remove_readers.data(), callback, 0, &zErrMsg);


    if ( new_readers.empty() ) {
        string  deleterow = "delete from messages where IDHASH='"+idhash+"';";
        rc = sqlite3_exec(db, deleterow.data(), callback, 0, &zErrMsg);
        cout << "Row deleted" << endl;
    }

    if( rc != SQLITE_OK ){
        cout << "SQL error: " << zErrMsg;
        sqlite3_free(zErrMsg);
    }else{
        cout << "Table created successfully\n";
    }
    sqlite3_close(db);
    return response;
}

string database_retrieve(string database_id, string idhash, string readers)
{
    response="";

    string new_readers;
    char *zErrMsg = 0;
    int  rc;

    rc = sqlite3_open(database_id.data(), &db);
    if( rc ){
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 0;
    }else{
        cout << "Opened database successfully\n";
    }

    string  read = "select MESSAGE,READERS from messages where IDHASH='"+idhash+"';";
    rc = sqlite3_exec(db, read.data(), callback, 0, &zErrMsg);

    if ( response.empty() ) return "FALSE";

    std::string delimiter = ",";

    size_t pos = 0;
    std::string token;
    while ((pos = old_readers.find(delimiter)) != std::string::npos) {
        token = old_readers.substr(0, pos);
        old_readers.erase(0, pos + delimiter.length());
        if (new_readers.empty() && token != readers ) new_readers+=token;
        else if (token != readers) new_readers+=","+token;
    }
    if (old_readers != readers ) new_readers+= old_readers;
    string  remove_readers = "update  messages set READERS='"+new_readers+"'where IDHASH='"+idhash+"';";
    rc = sqlite3_exec(db, remove_readers.data(), callback, 0, &zErrMsg);


    if ( new_readers.empty() ) {
        string  deleterow = "delete from messages where IDHASH='"+idhash+"';";
        rc = sqlite3_exec(db, deleterow.data(), callback, 0, &zErrMsg);
        cout << "Row deleted" << endl;
    }

    if( rc != SQLITE_OK ){
        cout << "SQL error: " << zErrMsg;
        sqlite3_free(zErrMsg);
    }else{
        cout << "Table created successfully\n";
    }
    sqlite3_close(db);
    return response;
}
