



#echo donaldo888 | sudo -S make install
bitcoin-cli loadwallet test01
bitcoin-cli generatetoaddress 108 bcrt1qjc97wxz4kmam9c7xtjtce9euhzakemudrcvm6a
ADDRESS=`bitcoin-cli asendtoaddress bcrt1qjc97wxz4kmam9c7xtjtce9euhzakemudrcvm6a 0.1`
bitcoin-cli getrawtransaction $ADDRESS -1