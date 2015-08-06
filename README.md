# PortScan_Sql
This application detects scanner IP addresses over a network. The application uses encrypted network flow data to perform port scan detection.
Four portscan detection algorithms namely classic, time invariant ,TRW(Threshold Random Walk) and BLR(Bayesian Logistic Regression) are
implemented on encrypted data. 
CryptDB is used for data encryption. 

Installations:
First CryptDB has to be installed on the system.

After installing CryptDB, build the following tables.
scan_sip
ipset
