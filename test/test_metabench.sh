#!/bin/bash

# Use the results from meta-optimization to benchmark
../build/bin/cisat --bench --input output_meta.txt --output output_metabench.txt --verbose

