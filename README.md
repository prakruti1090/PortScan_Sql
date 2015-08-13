# PortScan_Sql
This application detects scanner IP addresses over a network. The application uses encrypted network flow data to perform port scan detection.
Four portscan detection algorithms namely classic, time invariant ,TRW(Threshold Random Walk) and BLR(Bayesian Logistic Regression) are implemented on encrypted data. 
CryptDB is used for data encryption. 
The application interacts with the encrypted databases through CryptDB's proxy server.


Installations:
First CryptDB has to be installed on the system.

After installing CryptDB, build the following tables.
scan_sip
ipset

mysql create table queries:
# create the following tables using cryptDB and connect to the encrypted database using the code below for connection
create table scan_sip(s_id integer auto_increment primary key,sip varchar(25),dip varchar(25),flags varchar(10),packets integer,hit integer,misses integer);

create table ipset(ip varchar(25))

Connecting to CryptDB
# C code to connect to CryptDB's Proxy Server
const char *server = "127.0.0.1"; 
const char *user = "root";
const char *password = "letmein"; 
unsigned int port=3307;
const char *database = "Db_Name";
conn = mysql_init(NULL);
/* Connect to database */
if (!mysql_real_connect(conn, server,user, password, database, port, NULL, CLIENT_MULTI_STATEMENTS))
 {
 fprintf(stderr, "%s\n", mysql_error(conn));
 }

