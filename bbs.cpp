#include <fstream>

#include "account.hpp"


using namespace std;


int post ( int post_id=-1, string postBody ) {

    if( post_id == -1 ){
        string queryStr = "INSERT INTO posts (post_string) VALUES ('" + postBody + "');";

        if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
            cout<<"failed to post: [ "<<postBody<<" ]"<<endl;
            return -1;
        } else {
            cout<<"new post: [ "<<postBody<<" ]"<<endl;
            return 1;
        }
    } else {
        string queryStr = "UPDATE posts SET post_string='" + string + "' WHERE post_id=" + to_string( post_id ) + ";";

        if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
            cout<<"failed to reply: [ "<<postBody<<" ]"<<endl;
            return -1;
        } else {
            cout<<"new post: [ "<<postBody<<" ]"<<endl;
            return 1;
        }
    }

}


string checkPostFromID( int post_id ){

    string queryStr = "SELECT post_string FROM posts WHERE post_id=" + to_string( post_id ) + ";";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<"check post failed!"<<endl;
        return "chekc post failed!";
    } else {
        MYSQL_RES* result = mysql_store_result( &ciyacaSQL );
        MYSQL_ROW row = mysql_fetch_row( result );
        string post_string = row[0];
        mysql_free_result( result );
        cout<<"check post : "<<post_string<<endl;
        return post_string;
    }

}


string checkPosts( int quality ){

    string queryStr = "SELECT * FROM posts ORDER BY post_id DESC 0," + to_string( quality ) + ";";

    if( mysql_query( &ciyacaSQL, queryStr.c_str() ) ){
        cout<<"check posts failed!"<<endl;
        return "check posts failed!";
    } else {
        MYSQL_RES* result = mysql_store_result( &ciyacaSQL );

        string sumPostsString = "<lis>";
        for ( int i = 0; i<mysql_num_rows( result ); i++ ) {
            MYSQL_ROW row = mysql_fetch_row( result );
            sumPostsString += "<li>\n<div>";
            sumPostsString += row[0];   // post_id
            sumPostsString += "</div>\n";
            sumPostsString += row[1]+4;   // post_string
        }
        sumPostsString += "</lis>";

        mysql_free_result( result );
        return sumPostsString;
    }

}


int uploadFile( string fileName, vector<char> fileData ){

    string path = "../net_disk/" + fileName;
    ofstream outputFile( path, ios::binary );

    outputFile.write( &fileData[0], fileData.size() );
    outputFile.close();

    return 0;
}


vector<char> downloadFile( string fileName ){

    vector<char> fileData;
    string path = "../net_disk/" + fileName;
    ifstream inputFile( path, ios::binary );

    inputFile.read()
    long fileSize = inputFile.tellg();
    fileData.resize( fileSize );
    inputFile.read( fileData.data(), fileData.size() );
    inputFile.close()

    return fileData;

}