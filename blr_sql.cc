#include "mysql.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cmath>
#define TCP_BETA0    -2.83835
#define TCP_BETA2    3.30902
#define TCP_BETA4    -0.15705
#define TCP_BETA13   -0.00232
#define TCP_BETA15   -1.04741
#define TCP_BETA19   3.16302
#define TCP_BETA21   -3.26027
using namespace std;
main() {
   MYSQL *conn;
   MYSQL_RES *res,*res_ddip,*res_dipc,*res_tflows,*res_flags,*res_sip1,*res_sport,*res_packets;
   MYSQL_RES *res_sip,*res_tot_flows ,*res_dip,*res_avg_ack,*res_pck,*res_avg_sport,*res_nbytes,*res_udip,*res_b
s;
   MYSQL_ROW row,row_ddip,row_dipc,row_tot_flows,row_tflows,row_dip,row_sip,row_avg_ack,row_pck,row_avg_sport,ro
w_packets,row_sport,row_flags,row_sip1,row_nbytes,row_udip,row_bs;
   int curr_id,tot_flows,ch1,ch2;
int tprev=0;
int t_sport;
double x2,x4,x13,x13_1,x15,x19,x21;
const char *server = "localhost";
const char *user = "root";
const char *password = "letmein"; /* set me first */
   const char *database = "TRW_plain";
   conn = mysql_init(NULL);
   /* Connect to database */

if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
   }
   /* send SQL query */
string dip;
  if (mysql_query(conn, "select count(*) from scan_sip;" )) {
      fprintf(stderr, "%s\n", mysql_error(conn));
   }
res=mysql_store_result(conn);
row=mysql_fetch_row(res);
istringstream buffer(row[0]);
buffer >>tot_flows;
printf("total records:%d",tot_flows);
mysql_query(conn,"drop table if exists sc_blr;");
//mysql_query(conn,"create table sc_blr(src varchar(25));");
if (mysql_query(conn, "create table sc_blr(src varchar(25));")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
   }
mysql_query(conn,"drop table if exists temp;");
if (mysql_query(conn, "create table temp(src varchar(25),dip varchar(25),cnt integer);")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
   }
mysql_query(conn,"select distinct sip from scan_sip;");
res_sip1=mysql_store_result(conn);
string s;
while ((row_sip1 = mysql_fetch_row(res_sip1))!=NULL)
{
s=string(row_sip1[0]);
cout<<s<<endl;
int length = s.length();
for (int i = 0; i < length; i++)
 {
  if(s[i] == '\n')
  s.erase(i, 1);
 }
std::string t_flows_query="select count(*) from scan_sip where sip='" +s + "'" + ";";
mysql_query(conn,t_flows_query.c_str());
res_tflows=mysql_store_result(conn);
row_tflows=mysql_fetch_row(res_tflows);
istringstream buffer3(row_tflows[0]);
int t_flows;
buffer3 >>t_flows;
printf("total flows:%d",t_flows);
std::string x2_query="select count(*) from scan_sip where sip='" +s + "'" + " " + "and flags not like '%A';";
mysql_query(conn,x2_query.c_str());
res_avg_ack=mysql_store_result(conn);
row_avg_ack=mysql_fetch_row(res_avg_ack);
istringstream buffer4(row_avg_ack[0]);
int avg_ack;
buffer4>>avg_ack;
//printf("avg_ack:%d",avg_ack);
std::string x4_query="select count(*) from scan_sip where sip='" +s + "'" + " " + "and packets<3;";
//cout<<x4_query<<endl;
mysql_query(conn,x4_query.c_str());
res_pck=mysql_store_result(conn);
row_pck=mysql_fetch_row(res_pck);
istringstream buffer5(row_pck[0]);
int pck;
buffer5>>pck;
//cout<<"pck:"<<pck<<endl;
std::string x15_query="select count(*) from scan_sip where sip='" +s + "'" +  " " + "and payload=1;";
//cout<<x15_query<<endl;
mysql_query(conn, x15_query.c_str());
res_nbytes=mysql_store_result(conn);
row_nbytes=mysql_fetch_row(res_nbytes);
istringstream buffer6(row_nbytes[0]);
int nbytes;
buffer6>>nbytes;
//cout<<"nbytes:"<<nbytes<<endl;
std::string d_dip="select distinct dip from scan_sip where sip='" +s + "'" + ";";
mysql_query(conn,d_dip.c_str());
res_ddip=mysql_store_result(conn);
string d;
//cout<<"distinct sips:"<<endl;
while ((row_ddip = mysql_fetch_row(res_ddip))!=NULL)
{
d=string(row_ddip[0]);
//cout<<d<<endl;
std::string x13_query="select count(distinct sport) from scan_sip where dip='" +d + "'" + " " + "and sip='" +s +
 "'" + ";";
//cout<<x13_query<<endl;
mysql_query(conn,x13_query.c_str());
res_sport=mysql_store_result(conn);
row_sport=mysql_fetch_row(res_sport);
string d_sport=(row_sport[0]);
                                                        
std::string temp_q="insert into temp values('" +s + "'" + ",'" +d + "'" + "," +d_sport + ");";
//cout<<temp_q<<endl;
mysql_query(conn,temp_q.c_str());
}
std::string x13_query2="select avg(cnt) from temp where src='" +s + "';";
//cout<<x13_query2<<endl;
mysql_query(conn,x13_query2.c_str());
res_avg_sport=mysql_store_result(conn);
row_avg_sport=mysql_fetch_row(res_avg_sport);
istringstream sp_buff(row_avg_sport[0]);
int sumport;
sp_buff >> sumport;
//cout<<"sport:"<<sumport<<endl;
std::string x_query="select count(distinct dip) from temp where src='" +s + "';";
//cout<<x_query<<endl;
mysql_query(conn,x_query.c_str());
res_dipc=mysql_store_result(conn);
row_dipc=mysql_fetch_row(res_dipc);
istringstream dipc_buff(row_dipc[0]);
int uudip;
dipc_buff>>uudip;
std::string x19_query="select count(distinct dip) from scan_sip where sip='" +s + "'" + ";";
//cout<<x19_query<<endl;
mysql_query(conn,x19_query.c_str());
res_udip=mysql_store_result(conn);
row_udip=mysql_fetch_row(res_udip);
istringstream udip_buff(row_udip[0]);
int udip;
udip_buff >> udip;
std::string x21_query="select count(*) from scan_sip where sip='" +s + "'" + " " + "and flags in('SA','RA','R');
";
//cout<<x21_query<<endl;
mysql_query(conn,x21_query.c_str());
res_bs=mysql_store_result(conn);
row_bs=mysql_fetch_row(res_bs);
istringstream bs_buff(row_bs[0]);
int bs;
bs_buff >> bs;
x2=((double)avg_ack/(double)t_flows);
//cout<<"x2:"<<x2<<endl;
x4=((double)pck/(double)t_flows);
//cout<<x4<<endl;
x13=((double)sumport);
//cout<<"x13:"<<x13<<endl;
x15=((double)nbytes/(double)t_flows);
//cout<<x15<<endl;
x19=((double)udip/(double)t_flows);
//cout<<x19<<endl;
x21=((double)bs/(double)t_flows);
//cout<<x19<<endl;
double y;
y=TCP_BETA0 + (TCP_BETA2*x2)-(TCP_BETA4*x4)-(TCP_BETA13*x13)-(TCP_BETA15*x15)+(TCP_BETA19*x19)-(TCP_BETA21*x21);
cout<<"prob y:"<<y<<endl;
double p,q;
p=exp(y);
//cout<<"p"<<p;
q=1.0+q;
//cout<<"q"<<q;
double scan_prob;
scan_prob=p/q;
cout<<"scan_prob:"<<scan_prob<<endl;
if(scan_prob >0.5)
{
cout<<"IFFFFFFF:"<<endl;
string sc="insert into sc_blr values('" + s + "'" +");";
mysql_query(conn,sc.c_str());
}
}
mysql_close(conn);
return 0;
}

