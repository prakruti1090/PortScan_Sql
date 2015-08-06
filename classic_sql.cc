#include "mysql.h"
#include <cstdio>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
int main() {
MYSQL *conn;
MYSQL_RES *res,*res_tot_flows,*res_sip,*res_ddip,*res_flags,*res_packets,*res_d,*res_scanner;
MYSQL_RES *res_hit1,*res_hit2,*mysqlResult,*res_miss,*res_ch1,*res_ch2,*res_sip2,*res_ht1,*res_ht2,*res_ht22,*re
s_ht3,*res_ht33;
MYSQL_ROW row,mysqlRow,row_tot_flows,row_sip,row_ddip,row_flags,row_packets,row_d,row_scanner;
MYSQL_ROW row_hit1,row_hit2,row_miss,row_ch1,row_ch2,row_sip2,row_ht1,row_ht2,row_ht22,row_ht3,row_ht33;
unsigned int num_fields;
MYSQL_RES *res_syn,*res_f,*res_nom,*res_noh;
MYSQL_ROW row_syn,row_f,row_nom,row_noh;
int curr_id=1;
 float hit_likelihood,miss_likelihood,likelihood;
int noh,nom,miss;
std::string sip,hit,misses,flags,packets,dip,sip1,dip1,mq0;
int tot_flows,ch1,ch2;
const char *server = "localhost";
  const char *user = "root";
   const char *password = "letmein"; /* set me first */
   //unsigned int port=3307;
   const char *database = "TRW_PLAIN";
   conn = mysql_init(NULL);
   /* Connect to database */

 if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0))
 {
     fprintf(stderr, "%s\n", mysql_error(conn));
 }

/*if (mysql_query(conn, "select count(*) from scan;"))
 {
    fprintf(stderr, "%s\n", mysql_error(conn));
}
res_tot_flows=mysql_store_result(conn);
row_tot_flows = mysql_fetch_row(res_tot_flows);
istringstream tot_flows_buff(row_tot_flows[0]);
tot_flows_buff >> tot_flows; 
cout<<tot_flows<<endl;
*/
mysql_query(conn,"drop table if exists scan_sip;");
//std::string status="NULL";
if(mysql_query(conn, "create table scan_sip(s_id integer auto_increment primary key,sip varchar(25),dip varchar(
25),flags varchar(10),packets integer,hit integer,misses integer);"))
{
fprintf(stderr, "%s\n", mysql_error(conn));
}
                              
std::string new_conn="insert into scan_sip(sip,dip,flags,packets) select sip,dip,flags,packets from scan group b
y sip,dip;";
//cout<<new_conn<<endl;
mysql_query(conn,new_conn.c_str());
mysqlResult = mysql_store_result(conn); // Get the Result Set

mysql_query(conn,"select distinct sip from scan_sip;");
res_d=mysql_store_result(conn);
string d;

//cout<<"distinct sips:"<<endl;
while ((row_d = mysql_fetch_row(res_d))!=NULL)
{
d=string(row_d[0]);
cout<<d<<endl;

string bro_query="select count(distinct dip) from scan_sip where sip=" + "'" +d +"';";

if (mysql_query(conn, bro_query.c_str)
 {
    fprintf(stderr, "%s\n", mysql_error(conn));
}
res_ddip=mysql_store_result(conn);
row_ddip = mysql_fetch_row(res_ddip);
istringstream ddip_buff(row_ddip[0]);
ddip_buff >> ddip;
cout<<ddip<<endl;

mysql_query(conn,"drop table if exists sc;");
mysql_query(conn,"create table sc(source_ip varchar(25),status varchar(10));");

if(ddip>100)
{
string sc_iq="insert into sc values(";
string sc_q=sc_iq + "'" +d + "'" + "," + "'scanner');";
mysql_query(conn,sc_q.c_str());
}
mysql_query(conn,"select source_ip from sc;");
res_scanner=mysql_store_result(conn);
string scanner;

cout<<"LIST OF SCANNER IP's:"<<endl;
while ((row_scanner = mysql_fetch_row(res_scanner))!=NULL)
{
 scanner=string(row_scanner[0]);
 cout<<scanner<<endl;
}
mysql_close(conn);
return 0;
}

