bitcoin-cli loadwallet test01 > /dev/null
VAR1=`bitcoin-cli getnewaddress`
bitcoin-cli generatetoaddress 102 $VAR1 > /dev/null
echo `bitcoin-cli getbalance`
echo $VAR1
export $VAR1