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
MYSQL_RES *res,*res_tot_flows,*res_sip,*res_dip,*res_flags,*res_packets,*res_d,*res_scanner;
MYSQL_RES *res_hit1,*res_hit2,*mysqlResult,*res_miss,*res_ch1,*res_ch2,*res_sip2,*res_ht1,*res_ht2,*res_ht22,*re
s_ht3,*res_ht33;
MYSQL_ROW row,mysqlRow,row_tot_flows,row_sip,row_dip,row_flags,row_packets,row_d,row_scanner;
MYSQL_ROW row_hit1,row_hit2,row_miss,row_ch1,row_ch2,row_sip2,row_ht1,row_ht2,row_ht22,row_ht3,row_ht33;
unsigned int num_fields;
MYSQL_RES *res_syn,*res_f,*res_nom,*res_noh;
MYSQL_ROW row_syn,row_f,row_nom,row_noh;
int curr_id=1;
 float hit_likelihood,miss_likelihood,likelihood;
int noh,nom,miss;
std::string sip,hit,misses,flags,packets,dip,sip1,dip1,mq0;
int tot_flows,ch1,ch2;
//code for connecting to local mysql database
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
 // code for connecting to cryptDB's server and encrypted database
 const char *server = "127.0.0.1"; 
const char *user = "root";
const char *password = "letmein"; 
unsigned int port=3307;
//change the database name
const char *database = "TRW_crypt";
conn = mysql_init(NULL);
/* Connect to database */
if (!mysql_real_connect(conn, server,user, password, database, port, NULL, CLIENT_MULTI_STATEMENTS))
 {
 fprintf(stderr, "%s\n", mysql_error(conn));
 }
mysql_query(conn,"drop table if exists ipset;");
mysql_query(conn,"create table ipset(ip varchar(25));");
mysql_query(conn,"insert into ipset values('131.243.18.66');");
mysql_query(conn,"insert into ipset values('131.243.68.51');");
mysql_query(conn,"insert into ipset values('128.3.99.47');");
mysql_query(conn,"insert into ipset values('128.3.96.153');");
mysql_query(conn,"insert into ipset values('128.3.209.164');");
mysql_query(conn,"insert into ipset values('213.147.167.100');");
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
//mysql_query(conn, "alter table scan_sip add(hit integer);");
//mysql_query(conn, "alter table scan_sip add(misses integer);");
//mysql_query(conn, "alter table scan_sip add(status varchar(10));");
//mysql_query(conn, "insert into scan_sip(hit,misses) values(0,0);");
//mysql_query(conn, "insert into scan_sip(status) values('u|');");
//mysql_query(conn, "update scan_sip set hit=0;");
//mysql_query(conn, "update scan_sip set misses=0;");
//mysql_query(conn, "update scan_sip set status='NULL';");
/*if(mysql_query(conn, "select * from scan_sip into outfile '/tmp/sb1.txt' FIELDS TERMINATED BY '|' LINES TERMIN
ATED BY '\n'")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }*/
if (mysql_query(conn, "select count(*) from scan_sip;"))
 {
    fprintf(stderr, "%s\n", mysql_error(conn));
}
res_tot_flows=mysql_store_result(conn);
row_tot_flows = mysql_fetch_row(res_tot_flows);
istringstream tot_flows_buff(row_tot_flows[0]);
tot_flows_buff >> tot_flows;
cout<<tot_flows<<endl;

while(curr_id<tot_flows)
{
stringstream ss;
ss << curr_id;
string id_query = ss.str();
cout<<ss.str()<<endl;
/*std::string h1="select count(*) from scan_sip where s_id=ss.str()";
//std::string h2="and flags='s' + " ";
std::string hit1_query= h1 + " " + "and dip in('131.243.18.66','131.243.68.51','128.3.99.47','128.3.96.153',
'128.3.209.164','213.147.167.100');";
*/
/*std::string ht_query="select count(*) from scan_sip s1 inner join ipset i1 where s1.s_id=" +ss.str();
std::string hit1_query=ht_query + " " + "and s1.flags='S' and s1.dip=i1.ip;";
//cout<<hit1_query<<endl;
*/
//std::string h1="select count(*) from scan_sip where s_id=" + ss.str();
std::string h1="select count(*) from scan_sip s1 inner join ipset i1 where s1.s_id=" +ss.str();
std::string hit1_query= h1 + " " + "and s1.flags='S' and s1.dip=i1.ip;";
cout<<hit1_query<<endl;
mysql_query(conn, hit1_query.c_str());
mysql_query(conn, hit1_query.c_str());
res_hit1=mysql_store_result(conn);
row_hit1=mysql_fetch_row(res_hit1);
istringstream buffer1(row_hit1[0]);
int hit1;
buffer1 >> hit1;
cout<<"hit1:"<<hit1<<endl;

std::string hit2_query=h1 + " " + "and s1.flags!='S' and s1.dip!=i1.ip;";
mysql_query(conn, hit2_query.c_str());
//mysql_query(conn, hit1_query.c_str());
cout<<hit2_query<<endl;
res_hit2=mysql_store_result(conn);
row_hit2=mysql_fetch_row(res_hit2);
istringstream buffer2(row_hit2[0]);
int hit2;
buffer2 >> hit2;
std::cout<<"hit2:"<<hit2<<std::endl;
int h = hit1 + hit2;
stringstream hh;
hh << h;
hit = hh.str();
if(h>0)
{
string uph = "update scan_sip set hit=1;";
mysql_query(conn,uph.c_str());
cout<<uph<<endl;
}
if(h==0)
{
string miss_query= h1 + " " + "and s1.flags='S' and s1.dip!=i1.ip;";
cout<<miss_query<<endl;
mysql_query(conn, miss_query.c_str());
res_miss=mysql_store_result(conn);
cout<<miss_query<<endl;
row_miss=mysql_fetch_row(res_miss);
istringstream miss_buff(row_miss[0]);
miss_buff >> miss;
cout<<"miss:"<<miss<<endl;
stringstream ms;
ms << miss;
misses = ms.str();
string up2;
up2="update scan_sip set misses=1;";
cout<<up2<<endl;
mysql_query(conn,up2.c_str());
}
curr_id = curr_id+1;
}
mysql_query(conn,"drop table if exists sc;");
mysql_query(conn,"create table sc(source_ip varchar(25),status varchar(10));");
mysql_query(conn,"select distinct sip from scan_sip where hit>0 or misses>0;");
res_d=mysql_store_result(conn);
string d;
string synq="select count(*) from scan_sip where sip=";
cout<<"distinct sips:"<<endl;
while ((row_d = mysql_fetch_row(res_d))!=NULL)
{
 d=string(row_d[0]);
cout<<d<<endl;
string sq=synq + "'" +d + "'" + " " + "and flags='S';";
mysql_query(conn,sq.c_str());
res_syn=mysql_store_result(conn);
row_syn = mysql_fetch_row(res_syn);
istringstream syn_buff(row_syn[0]);
int syns;
syn_buff >> syns;
cout<<"syns:"<<syns<<endl;
string s_dq="'" +d + "'" + ";";
string sp_fq="select count(*) from scan_sip where sip=" + s_dq;
mysql_query(conn,sp_fq.c_str());
res_f=mysql_store_result(conn);
row_f=mysql_fetch_row(res_f);
istringstream f_buff(row_syn[0]);
int f;
f_buff >> f;
cout<<"sip_flows:"<<f<<endl;
string no_hits="select sum(hit) from scan_sip where sip=" + s_dq;
mysql_query(conn,no_hits.c_str());
res_noh=mysql_store_result(conn);
row_noh=mysql_fetch_row(res_noh);
istringstream h_buff(row_noh[0]);
noh;
h_buff >> noh;
cout<<"noh:"<<noh<<endl;
string no_misses="select sum(misses) from scan_sip where sip=" + s_dq;
mysql_query(conn,no_misses.c_str());
res_nom=mysql_store_result(conn);
row_nom=mysql_fetch_row(res_nom);
istringstream m_buff(row_nom[0]);
nom;
m_buff >> nom;
cout<<"nom:"<<nom<<endl;
int k=0;
if(noh > 0)
{
hit_likelihood=1;
while(k < noh)
{
hit_likelihood = hit_likelihood  *  0.25;
k++;
}
}
cout<<"hit_likelihood:"<<hit_likelihood<<endl;
 int j=0;
if(nom > 0)
{
miss_likelihood=1;
while(j < nom)
{
miss_likelihood = miss_likelihood  *  4;
j++;
}
}
cout<<"miss_likelihood:"<<miss_likelihood<<endl;
if(noh == 0)
{
likelihood =  miss_likelihood;
}
if(nom == 0)
{
likelihood = hit_likelihood;
}

if(noh > 0 && nom > 0)
{
likelihood = hit_likelihood * miss_likelihood;
}
cout<<"likelihood:"<<likelihood<<endl;
if(likelihood > 99 && syns==f)
{
string sc_iq="insert into sc values(";
string sc_q=sc_iq + "'" +d + "'" + "," + "'scanner');";
mysql_query(conn,sc_q.c_str());
}
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
