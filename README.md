NAIST Bitcoin Core integration/staging tree
=====================================
Account model implementation (2022/06/02)

It implements its own commands "asendtoaddress and "agetbalance" are implemented.

Help for using each is described below.

(1) asendtoaddress command.
    Description: bitcoin-cli asendtoaddress [from btc address] [to btc address] amount
    return: transaction hash.
    ex: bitcoin-cli asendtoaddress bcrt1q0hqq9yh3j768yw38zd7lslp24m98ze930hwqrc bcrt1qsd03af0afrmtqge39c3csrfxuha65vw88r8mnw 1

(2)agetbalance command.
    Description: bitcoin-cli agetbalance
    return: amount
    ex: bitcoin-cli agetbalance
    5049.0000000000

(3) Test scenario
    Confirm the operation of the above command in regression test mode.
        1. bitcoind -regtest
        2. bitcoin-cli createwallet test01
        3. bitcoin-cli getnewaddress
        (get new btc address )
        4. bitcoin-cli agetbalance (confirm it is 0.)
        5.bitcoin-cli generatetoaddress 101 > /dev/null
        6.bitcoin-cli agetbalance (onfirm it is 5050.0000000000)
        7. bitcoin-cli asendtoaddress [new btc address] [dummy btc address(ex:bcrt1q0hqq9yh3j768yw38zd7lslp24m98ze930hwqrc)] 1
        8. bitcoin-cli agetbalance (confirm it is 5049.0000000000)
        9. bitcoin-cli asendtoaddress [dummy btc address(ex:bcrt1q0hqq9yh3j768yw38zd7lslp24m98ze930hwqrc)] [new btc address] 1
        (Confirm it is ERROR.)