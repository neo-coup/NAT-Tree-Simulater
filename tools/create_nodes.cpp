#include <stdio.h>
#include <random>

const double TYPE_0 = 12.5;   // Open Internet
const double TYPE_1 = 12.5;   // Full cone NAT
const double TYPE_2 = 5.0;    // Restricted cone NAT
const double TYPE_3 = 40.0;   // Port Restricted cone NAT
const double TYPE_4 = 16.0;   // Symmetric NAT
const double TYPE_5 = 14.0;   // UDP Blocked

int selectConnectionType();
int isMobile(double, int);

int main(int argc, char** argv) {
    double mobile_ratio = atoi(argv[1]);

    for(int i=0; i<10000; i++) {
        int type = selectConnectionType();
        int mobile = isMobile(mobile_ratio, type);
        printf("%d,%d,%d\n", i, type, mobile);
    }
}

int selectConnectionType() {

    std::random_device rnd;
    // 小数点第一位まで残し、パーセント単位計算
    double n = (rnd() % 1000) / 10;

    if(n < TYPE_0) return  0;
    n -= TYPE_0;
    if(n < TYPE_1) return  1;
    n -= TYPE_1;
    if(n < TYPE_2) return  2;
    n -= TYPE_2;
    if(n < TYPE_3) return  3;
    n -= TYPE_3;
    if(n < TYPE_4) return  4;
    n -= TYPE_4;
    if(n < TYPE_5) return  5;
    // n -= TYPE_5;
    return 0;
};

int isMobile(double n, int type) {
    bool ret = false;

    std::random_device rnd;
    ret = (rnd() % 100) < n;


    return (int)ret;
}
