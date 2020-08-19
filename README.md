# QAP\_landscape
This repo contains the source code that extracts the Fitness Landscape measures used for characterizing QAP instances in the paper ["On the use of fitness landscape features in meta-learning based algorithm selection for the quadratic assignment problem"](https://www.sciencedirect.com/science/article/pii/S0304397519306693).

The sampling is performed by the [Metropolis-Hasting algorithm](https://link.springer.com/chapter/10.1007/978-3-540-24855-2_76), followed by a best improvement local search on each solution with the swap operator.

# Usage
Running `make` will generate two binary files:
* bin/mh
* bin/ft

First you need to execute the sampling method:

`$ ./bin/mh -f <path to instance file> -s <sample size> -o <sample file>`

This will save the sample in the binary `<sample file>` and print the CPU execution time. Then, you run the feature extractor on the generated sample:

`$ ./bin/ft -f <sample file> [-c <cropped sample size>]`

Which will print the values of the extracted features in the following order:
* Optima Fitness Coefficient
* Average Descent
* Fitness Distance Correlation
* Average Distance to Optima
* Accumulated Escape Probability
* Dispersion Metric (base sample)
* Dispersion Metric (local optima sample)

If you pass the optional argument `-c <cropped sample size>`, the features will be computed considering a cropped subsample.
