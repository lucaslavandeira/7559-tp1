//
// Created by lucas on 9/6/19.
//

#ifndef TP1_DISTRIBUTIONCHAIN_H
#define TP1_DISTRIBUTIONCHAIN_H

class DistributionChain {
    int chain_id;
public:
    explicit DistributionChain(int chain_id);
    // Returns the PID of the process
    int start();
};


#endif //TP1_DISTRIBUTIONCHAIN_H
