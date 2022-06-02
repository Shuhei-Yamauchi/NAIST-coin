




# if($#==1){
#     bitcoin-cli createwallet test01
#     VAR1=`bitcoin-cli getnewaddress`
#     bitcoin-cli generatetoaddress 102 $VAR1 > /dev/null
#     echo `bitcoin-cli getbalance`
#     echo $VAR1
# }

bitcoin-cli loadwallet test01
bitcoin-cli generatetoaddress 108 bcrt1qas25rkeau3qc0evmp92x270axngw3w6mj0py79  > /dev/null
bitcoin-cli asendtoaddress bcrt1qas25rkeau3qc0evmp92x270axngw3w6mj0py79 0.1
