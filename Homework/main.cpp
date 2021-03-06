#include <iostream>

#include "cnn.h"
#include "config.h"

#include "./data/weights_conv1.h"
#include "./data/weights_conv2.h"
#include "./data/weights_ip1.h"
#include "./data/weights_ip2.h"
#include "./data/bias_conv1.h"
#include "./data/bias_conv2.h"
#include "./data/bias_ip1.h"
#include "./data/bias_ip2.h"
#include "./data/test_set.h"
#include "./data/label.h"

using namespace std;

int main() {

	for (uint32_t iter = 0; iter < 1000; ++iter){
			for (uint32_t i =0 ; i < 784; ++i){
					test_image[iter][i] = ts[784 * iter + i];
			}

			conv(test_image[iter], make_pair(28, 28), 1,
							_weights_conv1,
							_bias_conv1, 20,
							feature_map1,
							make_pair(5, 5), 0, 1);

			max_pool(feature_map1, make_pair(24, 24), 20,
							make_pair(2, 2), 2, max_pool1);

			conv(max_pool1, make_pair(12, 12), 20,
							_weights_conv2,
							_bias_conv2, 50,
							feature_map2,
							make_pair(5, 5), 0, 1);

			max_pool(feature_map2, make_pair(8, 8), 50,
							make_pair(2, 2), 2, max_pool2);

			ip(max_pool2,
							make_pair(4, 4), 50,
							_weights_ip1,
							_bias_ip1,
							500, ip1);

			ReLu(ip1,	make_pair(1, 1), 500, tanh1);

			ip(tanh1,
							make_pair(1, 1), 500,
							_weights_ip2,
							_bias_ip2,
							10, ip2);

			accuracy(iter, ls, ip2);
	}

	return 0;
}
