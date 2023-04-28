# antlr4-perfopt-test

The detail see PR#4237 https://github.com/antlr/antlr4/pull/4237 

## build antlr4 & generate C++ parser && build Cpp-runtime
```
bash build_all_deps.sh
```

## run coucurrent_perf_test (default lexer & parser)
```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j8

# test with 1 thread before optimization
./output/concurrent_perf_test 1
# test with 4 threads before optimization
./output/concurrent_perf_test 4
# test with 16 threads before optimization
./output/concurrent_perf_test 16
```

## run concurrent_perf_test (optimized lexer & parser)
```
mkdir build.opt && cd build.opt
cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_PR4237_OPT=1
make -j8

# test with 1 thread after optimization
./output/concurrent_perf_test 1
# test with 4 threads after optimization
./output/concurrent_perf_test 4
# test with 16 threads after optimization
./output/concurrent_perf_test 16
```

